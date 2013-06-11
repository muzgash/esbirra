#include <Control.hpp>

#include <signal.h>
#include <wiringPi.h>
#include <softPwm.h>

#include <bcm2835.h>

#include <cstdlib>
#include <fstream>
#include <time.h>

Control::Control() {
    this->_signature = "b:si";
	this->_help = "This method controls the measure and the brightness while\
	               keeping track of the data gathered and the history of the lightning";
	_viBrightness.push_back(0);
	_viBiomass.push_back(0);
}

void Control::execute(xmlrpc_c::paramList const& paramList,
		         xmlrpc_c::value* const pReturn) {
    
	try{
		string const sAction(paramList.getString(0));

		paramList.verifyEnd(2);

		if ( sAction == "status-brightness" ) {
		     cout<<"Asking brightness status\n";
		     *pReturn = xmlrpc_c::value_int(_viBrightness.back());
		}
		else if ( sAction == "status-biomass" ) {
		     cout<<"Asking biomass status\n";
		    *pReturn = xmlrpc_c::value_int(_viBiomass.back());
		}

		//MEASURE SECTION
		else if ( sAction == "measure" ) {
			cout<<"Measuring...\n";

			if ( _bMeasuring == true ) {
				*pReturn = xmlrpc_c::value_int(1);
				cout<<"Measuring is in progress, don't be so hasty\n";
				return;
			}

            _bMeasuring = true;
			bool const io(paramList.getInt(1));

            try {
				if (!bcm2835_init()) *pReturn = xmlrpc_c::value_int(0);
				bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);

				bcm2835_gpio_write(RPI_GPIO_P1_11,HIGH);
				cout<<"System state: "<<io<<endl;
				wiringPiSetupGpio();
				softPwmCreate(11,0,255);
				softPwmWrite(11,0);

				ifstream serialUSB;
				serialUSB.open("/dev/ttyUSB0");
				string str;

				time_t time_i;
				time(&time_i);
				time_t time_f;

				int i=0;
				int data=0;
				do {
				getline(serialUSB,str);
				cout<<str<<endl;
				i++;
				if (i>5) data+=atoi(str.c_str());
				} while(i<30); //30 second
				time(&time_f);
				cout<<"Data was read in "<<difftime(time_f,time_i)<<" seconds\n";

				bcm2835_gpio_write(RPI_GPIO_P1_11,LOW);
				softPwmWrite(11,_viBrightness.back());

                _viBiomass.push_back(int(data/25));
				*pReturn = xmlrpc_c::value_int(int(data/25));
				_bMeasuring = false;
			} catch ( exception const& e ) {
			    cerr<<"Something went horribly wrong during measure transaction: "
				    <<e.what()<<endl;
				*pReturn = xmlrpc_c::value_int(0);
				_bMeasuring=false;
			}
		}

		//BRIGHTNESS SECTION
		else if ( sAction == "brightness" ) {
			cout<<"Changing brightness\n";

			int const value(paramList.getInt(1));
            
			try {
				wiringPiSetupGpio();
				softPwmCreate(11,0,255);
				softPwmWrite(11,value);

                _viBrightness.push_back(value);

				*pReturn = xmlrpc_c::value_int(1);
			} catch ( exception const& e ) {
			    cerr<<"Something went horribly wrong during brightness transaction: "
				    <<e.what()<<endl;
				*pReturn = xmlrpc_c::value_int(0);
			}
		}


	} catch ( exception const& e ) {
			cerr<<"Something went horribly wrong: "<<e.what()<<endl;
			*pReturn = xmlrpc_c::value_int(0);;
	}
}


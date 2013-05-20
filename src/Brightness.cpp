#include <signal.h>
#include <wiringPi.h>
#include <softPwm.h>


#include<Brightness.hpp>

using namespace std;

Brightness::Brightness() {
	this->_signature = "b:i";
	this->_help = "This method sets the brightness of the leds";
}

void Brightness::execute(xmlrpc_c::paramList const& paramList,
                         xmlrpc_c::value *   const  pReturn) {
	cout<<"Entered brightness method\n";

	try{

		int const value(paramList.getInt(0));

		paramList.verifyEnd(1);

		cout<<"Brightness value: "<<value<<endl;

		wiringPiSetupGpio();
		softPwmCreate(11,0,255);
		softPwmWrite(11,value);

		*pReturn = xmlrpc_c::value_boolean(true);

	} catch ( exception const& e ) {
		cerr<<"Something went horribly wrong during brightness transaction "<<e.what()<<endl;
		*pReturn = xmlrpc_c::value_boolean(false);;
	}
	

}

#include<IOMeasure.hpp>
#include<bcm2835.h>

IOMeasure::IOMeasure() {
	this->_signature = "b:i";
	this->_help = "This method turns on the laser and photodiode while switching off"
				  "the ilumination and oxygenation";
}

void IOMeasure::execute(xmlrpc_c::paramList const& paramList,
                           xmlrpc_c::value * const returnVal) {
	cout<<"Entered io.measure method\n";

	try{
		bool const io( paramList.getInt(0));
		paramList.verifyEnd(1);

       	if (!bcm2835_init()) *returnVal = xmlrpc_c::value_boolean(false);

		bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);

        if( io == 0 ) bcm2835_gpio_write(RPI_GPIO_P1_11,HIGH);
		else  bcm2835_gpio_write(RPI_GPIO_P1_11,LOW);

		cout<<"System state: "<<io<<endl;

		*returnVal = xmlrpc_c::value_boolean(true);

	} catch ( exception const& e ) {
		cerr<<"Something went horribly wrong during IOMeasure transaction "<<e.what()<<endl;
	}
}

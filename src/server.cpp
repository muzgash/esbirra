#include<IOMeasure.hpp>
#include<Brightness.hpp>

using namespace std;


int main(int argc,char** argv) {
    try {
        xmlrpc_c::registry registry;

        xmlrpc_c::methodPtr const pBrightness(new Brightness);
        xmlrpc_c::methodPtr const pIOMeasure(new IOMeasure);

        registry.addMethod("brightness", pBrightness);
        registry.addMethod("io.measure", pIOMeasure);
        
		cout<<"xmlrpc_c server running on port pi"<<endl;
        xmlrpc_c::serverAbyss server(
            xmlrpc_c::serverAbyss::constrOpt()
			.allowOrigin("http://localhost")
            .registryP(&registry)
            .portNumber(31416)
			.serverOwnsSignals(false)
			.expectSigchld(true)
			.uriPath("/esbirra"));

        while(1){server.runOnce();}
        assert(false);
    } catch (exception const& e) {
        cerr << "Something went horribly wrong  " << e.what() << endl;
    }
    return 0;
}

#ifndef __IOMEASURE_HPP__
#define __IOMEASURE_HPP__

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */
#include <cassert>
#include <stdexcept>
#include <iostream>
#ifdef _WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

using namespace std;




class IOMeasure : public xmlrpc_c::method {
public:
    IOMeasure();
	void execute(xmlrpc_c::paramList const& paramList,
	             xmlrpc_c::value * const returnVal); 
};


#endif

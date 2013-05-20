CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

INCLUDE_DIRECTORIES( include )

ADD_DEFINITIONS( -std=c++0x )

ADD_LIBRARY( brightness
include/Brightness.hpp
src/Brightness.cpp
)

ADD_LIBRARY( iomeasure
include/IOMeasure.hpp
src/IOMeasure.cpp
)

ADD_EXECUTABLE( server src/server.cpp )

LINK_DIRECTORIES( /usr/lib/x86_64-linux-gnu )

TARGET_LINK_LIBRARIES( server wiringPi /home/pi/marbles/lib/bcm2835.o rt brightness iomeasure xmlrpc  xmlrpc++  xmlrpc_abyss  xmlrpc_client  xmlrpc_client++  xmlrpc_cpp  xmlrpc_packetsocket  xmlrpc_server  xmlrpc_server++  xmlrpc_server_abyss  xmlrpc_server_abyss++  xmlrpc_server_cgi  xmlrpc_server_cgi++  xmlrpc_server_pstream++  xmlrpc_util  xmlrpc_xmlparse  xmlrpc_xmltok pthread )

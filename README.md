esbirra
=======

**M**arvellous **A**rduino and **R**aspberryPi **B**ioreactor **L**ight **E**lectronic **S**ystem

Note about configuration on server side:
Must enable proxy_http module on apache
#a2enmod proxy_http
and add the following lines to /etc/apache2/mods-enabled/proxy.conf

ProxyRequests On
ProxyVia On
ProxyPass /esbirra-server http://localhost:31416/esbirra
ProxyPassMatch /esbirra-server http://localhost:31416/esbirra
ProxyPassReverse /esbirra-server http://localhost:31416/esbirra

Restart apache
#service apache2 restart

This is for your JavaScript code to see the route to the server including the port
Client must point to the server route, in this case, http://localhost/esbirra-server
and server must point to the client direction, i.e. uriPath(/esbirra)



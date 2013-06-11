
var brightness_value=0;
var brightness_mem=0;
var io=1;

//COMMUNICATION WITH XMLRPC_C++-SERVER
function addParam(dom,type,data) {
    var param_tag = dom.createElement("param");
	var value_tag = dom.createElement("value");
	var type_tag = dom.createElement(type);
	var data = dom.createTextNode(data);

	type_tag.appendChild(data);
	value_tag.appendChild(type_tag);
	param_tag.appendChild(value_tag);

	return param_tag;
}

function request(method) {

	if( window.XMLHttpRequest ) xmlhttp = new XMLHttpRequest();
	else xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");

	var dom = document.implementation.createDocument(null,"methodCall",null);
	var method_tag = dom.getElementsByTagName("methodCall")[0];
	var method_name_tag = dom.createElement("methodName");

	//XML is created to be like this:
	//<methodCall>
	//  <methodName>method</methodName>
	//  <params>
	//      <param>
	//      	<value><TYPE>THIS IS A TEST</TYPE></value>
	//  	</param>
	//	</params>
	//</methodCall>
	method_name_tag.appendChild(dom.createTextNode("control"));
	method_tag.appendChild(method_name_tag);
	params_tag = dom.createElement("params");
	params_tag.appendChild(addParam(dom,"string",method))
	if( method == "brightness" ) params_tag.appendChild(addParam(dom,"int",brightness_value));
	else if( method == "measure" ) params_tag.appendChild(addParam(dom,"int",io));
	else if( method == "status-brightness" ) params_tag.appendChild(addParam(dom,"int",0));
	else if( method == "status-biomass" ) params_tag.appendChild(addParam(dom,"int",0));
	method_tag.appendChild(params_tag);

	var serial_dom = new XMLSerializer().serializeToString(dom);
	//console.log(serial_dom);
	xmlhttp.open("POST","http://192.168.0.17/marbles-server",false);
	xmlhttp.setRequestHeader("Content-Type","text/xml");
	xmlhttp.upload.addEventListener("error",function(){alert("something went wrong uploading the request");},false);
	xmlhttp.send(serial_dom);

	if( xmlhttp.readyState == 4 && xmlhttp.status == 200 ) {
		var response = xmlhttp.responseXML;
		//console.log(response);

		//DO SOMETHING WITH THE INFORMATION
		return response;
	}
	else if( xmlhttp.status == 503 ) alert("Couldn't connect to server");
	else console.log("Ready State = "+xmlhttp.readyState+" and status = "+xmlhttp.status);
    if( xmlhttp.readyState == 3 ) console.log("statusText: " + xmlhttp.statusText + "\nHTTP status code: " + xmlhttp.status);
}

function init() {
    response = request("status-brightness");
	brightness_tag_val = response.getElementsByTagName("value")[0].childNodes[0].textContent;
	document.getElementById("slider-0").value = brightness_tag_val;
	document.getElementById("leds-slider").value = brightness_tag_val;

	response = request("status-biomass");
	biomass_tab_val = response.getElementsByTagName("value")[0].childNodes[0].textContent;
	document.getElementById("biomass").innerHTML=biomass_tab_val;
}

//GLOBAL
function brightness(element) {
    /*if( element == 'slider' ) {
		value = parseInt(document.getElementById("leds-slider").value);
		slider_number = document.getElementById("slider-number");
		slider_number.innerHTML = value;
		color= Math.abs(value-255);
		slider_number.style.color = "rgb("+color+","+color+","+color+")";
	}*/
	if( element == 'slider' ) {
	    value = parseInt(document.getElementById("slider-0").value);
	    value = parseInt(document.getElementById("leds-slider").value);
	}
	//circle = document.getElementById("circle");
	//size=value/15+20;
	//circle.style.width = size+"px";
	//circle.style.height = size+"px";
	//circle.style.background = "rgb(0,0,"+value+")";
	brightness_value = value;
	request('brightness');
	//console.log(brightness_value);
	
}



function IO() {
    image = document.getElementById("on-off");
    io=0;
	response=request('measure');
	biomass_tab_val = response.getElementsByTagName("value")[0].childNodes[0].textContent;
	document.getElementById("biomass").innerHTML=biomass_tab_val;
}

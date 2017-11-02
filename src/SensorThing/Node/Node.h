#ifndef NODE_H
#define NODE_H

#include <ESP8266WiFi.h>
#include <user_interface.h>
#include <IPAddress.h>

class Node
{
public:
	Node();
	bool Post(IPAddress ip, ushort port);
	
	void AddDataPoint(const char* name, float value);

private:
	WiFiClient	connection;
	String		postData;
};

#endif
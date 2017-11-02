#include "Node.h"
#include "..\Trace\Log.h"
#include <stdlib.h>
#include <user_interface.h>

Node::Node()
{
	this->postData = "";
}

void Node::AddDataPoint(const char* name, float value)
{
	char buffer[20];
	dtostrf(value, 0, 2, buffer);
	if (this->postData.length() > 0)
		this->postData += "&";
	this->postData += String(name) + "=" + buffer;
}

bool Node::Post(IPAddress ip, ushort port)
{
	if (!this->connection.connect(ip, port))
		return false;

	if (!this->connection.connected())
		return false;

	this->connection.print(F("POST /api/datapoints?"));
	this->connection.print(this->postData);
	this->connection.print(F(" HTTP/1.1\r\n"));
	this->connection.print(F("Host: "));
	this->connection.print(ip);
	this->connection.print(F("\r\n"));
	this->connection.print(F("Content-Type: application/json\r\n"));
	this->connection.print(F("Content-Length: 0\r\n"));
	this->connection.print(F("\r\n"));
	this->connection.flush();
	this->connection.stop();
	yield();

	return true;
}

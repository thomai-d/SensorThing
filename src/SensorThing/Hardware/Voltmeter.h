#ifndef VOLTMETER_H
#define VOLTMETER_H

#include <inttypes.h>

class VoltmeterClass
{
public:

	/// precision:	AD-converter's precision in bits (ESP8266: 10bits)
	/// r1:			Resistor 1's value in kOhm
	/// r2:			Resistor 2's value in kOhm (this voltage drop is measured)
	/// vRef:		AD-converter's reference voltage (ESP8266: 1V)
	VoltmeterClass(uint8_t precision, float r1, float r2, float vRef);

	float Read();

private:
	uint8_t precision;
	float r1;
	float r2;
	float vRef;
};

extern VoltmeterClass Voltmeter;

#endif
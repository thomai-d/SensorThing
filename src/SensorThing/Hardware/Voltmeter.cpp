#include "Voltmeter.h"

#include "../Configuration.h"
#include <Arduino.h>

VoltmeterClass::VoltmeterClass(uint8_t precision, float r1, float r2, float vRef)
{
	this->precision = precision;
	this->r1 = r1;
	this->r2 = r2;
	this->vRef = vRef;
}

float VoltmeterClass::Read()
{
	return (((float)analogRead(A0) / ((uint16_t)1 << this->precision)) * (this->r1 + this->r2) / this->r2) + VOLTMETER_OFFSET;
}

VoltmeterClass Voltmeter(ADC_PRECISION, VOLTMETER_R1, VOLTMETER_R2, ADC_REF);

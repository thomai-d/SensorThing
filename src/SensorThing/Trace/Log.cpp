#include "Log.h"

#include <Arduino.h>
#include "..\Configuration.h"

void LogClass::Initialize()
{
#ifdef DEBUG
	Serial.begin(SERIAL_BAUD);
	Serial.println();
#endif
}

void LogClass::printfloat(const __FlashStringHelper * text, float value)
{
#ifdef DEBUG
	Serial.print(text);
	Serial.println(value, 2);
#endif
}

size_t LogClass::write(uint8_t c)
{
#ifdef DEBUG
	return Serial.write(c);
#endif
}

LogClass Log;




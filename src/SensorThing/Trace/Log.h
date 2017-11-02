#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include "..\Configuration.h"

class LogClass : public Print
{
public:

	void Initialize();

	void printfloat(const __FlashStringHelper* text, float value);

	virtual size_t write(uint8_t) override;
};

extern LogClass Log;

#endif
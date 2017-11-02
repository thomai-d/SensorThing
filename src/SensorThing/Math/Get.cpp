#include "Get.h"
#include <math.h>

float GetClass::AbsoluteHumidity(float temp, float relHumid)
{
	float a = temp >= 0 ? 7.5 : 7.6;
	float b = temp >= 0 ? 237.3 : 240.7;
	float sdd = 6.1078 * powf(10, (a * temp) / (b + temp));
	float dd = relHumid / 100 * sdd;
	
	const float mw = 18.016;
	const float r = 8314.3;
	float tempK = 273.15 + temp;
	float absoluteHumidity = 100000 * mw / r * dd / tempK;

	return absoluteHumidity;
}

float GetClass::DewPoint(float temp, float relHumid)
{
	float a = temp >= 0 ? 7.5 : 7.6;
	float b = temp >= 0 ? 237.3 : 240.7;
	float sdd = 6.1078 * powf(10, (a * temp) / (b + temp));
	float dd = relHumid / 100 * sdd;

	float v = log10f(dd / 6.1078);
	float dewPoint = b * v / (a - v);


	return dewPoint;
}

GetClass Get;
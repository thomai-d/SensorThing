#ifndef GET_H
#define GET_H

#define TIME_DELTA_MS(x, y) (x > y ? (uint32_t)x - (uint32_t)y : (uint32_t)y - (uint32_t)x)

class GetClass
{
public:
	float AbsoluteHumidity(float temp, float relHumid);
	float DewPoint(float temp, float relHumid);
};

extern GetClass Get;

#endif
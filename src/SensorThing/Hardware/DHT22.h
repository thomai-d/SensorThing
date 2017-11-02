#ifndef dht_h
#define dht_h

#include <Arduino.h>

#define DHTLIB_OK                0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
#define DHTLIB_INVALID_VALUE    -999

#define DHTLIB_DHT11_WAKEUP     18
#define DHTLIB_DHT_WAKEUP       1

// max timeout is 100 usec.
// For a 16 Mhz proc 100 usec is 1600 clock cycles
// loops using DHTLIB_TIMEOUT use at least 4 clock cycli
// so 100 us takes max 400 loops
// so by dividing F_CPU by 40000 we "fail" as fast as possible
#define DHTLIB_TIMEOUT (F_CPU/40000)

class DHT22Class
{
public:
	DHT22Class(uint8_t pin) { this->pin = pin; }

	bool Update();

	void Enable();
	void Disable();

    float humidity;
    float temperature;
	float absHumidity;
	float dewPoint;

private:
	uint8_t pin;
    uint8_t bits[5];
    int _readSensor(uint8_t wakeupDelay);
};

extern DHT22Class DHT22;

#endif

#include "DHT22.h"

#include "..\Configuration.h"
#include "..\Math\Get.h"

bool DHT22Class::Update()
{
    int rv = _readSensor(DHTLIB_DHT_WAKEUP);
    if (rv != DHTLIB_OK)
    {
        humidity    = DHTLIB_INVALID_VALUE;
        temperature = DHTLIB_INVALID_VALUE;
        dewPoint    = DHTLIB_INVALID_VALUE;
        absHumidity = DHTLIB_INVALID_VALUE;
		return false;
    }

    // CONVERT AND STORE
    humidity = word(bits[0], bits[1]) * 0.1;
    temperature = word(bits[2] & 0x7F, bits[3]) * 0.1;
    if (bits[2] & 0x80)  // negative temperature
    {
        temperature = -temperature;
    }

	dewPoint	= Get.DewPoint(temperature, humidity);
	absHumidity	= Get.AbsoluteHumidity(temperature, humidity);

    // TEST CHECKSUM
    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (bits[4] != sum)
    {
		return false;
    }

	return true;
}

void DHT22Class::Enable()
{
	pinMode(DHT22_ENABLE_PIN, OUTPUT);
	digitalWrite(DHT22_ENABLE_PIN, HIGH);
}

void DHT22Class::Disable()
{
	digitalWrite(DHT22_ENABLE_PIN, LOW);
	pinMode(DHT22_ENABLE_PIN, INPUT);
}

// return values:
// DHTLIB_OK
// DHTLIB_ERROR_TIMEOUT
int DHT22Class::_readSensor(uint8_t wakeupDelay)
{
    // INIT BUFFERVAR TO RECEIVE DATA
    uint8_t mask = 128;
    uint8_t idx = 0;

    // replace digitalRead() with Direct Port Reads.
    // reduces footprint ~100 bytes => portability issue?
    // direct port read is about 3x faster

    // EMPTY BUFFER
    for (uint8_t i = 0; i < 5; i++) bits[i] = 0;

    // REQUEST SAMPLE
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // T-be 
    delay(wakeupDelay);
    digitalWrite(pin, HIGH);   // T-go
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // GET ACKNOWLEDGE or TIMEOUT
    uint16_t loopCntLOW = DHTLIB_TIMEOUT;
    while (digitalRead(pin) == LOW )  // T-rel
    {
        if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    uint16_t loopCntHIGH = DHTLIB_TIMEOUT;
    while (digitalRead(pin) != LOW )  // T-reh
    {
        if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    // READ THE OUTPUT - 40 BITS => 5 BYTES
    for (uint8_t i = 40; i != 0; i--)
    {
        loopCntLOW = DHTLIB_TIMEOUT;
        while (digitalRead(pin) == LOW )
        {
            if (--loopCntLOW == 0) return DHTLIB_ERROR_TIMEOUT;
        }

        uint32_t t = micros();

        loopCntHIGH = DHTLIB_TIMEOUT;
        while (digitalRead(pin) != LOW )
        {
            if (--loopCntHIGH == 0) return DHTLIB_ERROR_TIMEOUT;
        }

        if ((micros() - t) > 40)
        { 
            bits[idx] |= mask;
        }
        mask >>= 1;
        if (mask == 0)   // next byte?
        {
            mask = 128;
            idx++;
        }
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);

    return DHTLIB_OK;
}

DHT22Class DHT22(DHT22_PIN);
//#define DEBUG

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>

#define SERIAL_BAUD		74880

#ifdef DEBUG
#define SLEEPTIME_US	10 * 1000 * 1000
#else
#define SLEEPTIME_US	30 * 60 * 1000 * 1000
#endif

#define DHT22_PIN				4
#define DHT22_ENABLE_PIN		15			// HIGH = on, HIGH_IMP = off
#define VBATT_ENABLE_PIN		12			// HIGH = on, HIGH_IMP = off
#define SUCCESS_LED_PIN			14			// LOW = on, HIGH_IMP = off

#define DHT22_RETRY_COUNT		5
#define DHT22_RETRY_DELAY_MS	300

#define ADC_REF			1.0			// ADC reference voltage
#define ADC_PRECISION	10			// ADC precision bits
#define VOLTMETER_R1		6700.0
#define VOLTMETER_R2		999.0
#define VOLTMETER_OFFSET	0.028

extern const char*		WifiSSID;
extern const char*		WifiPass;

// HOME
#define WIFI_GATEWAY	IPAddress(192, 168, 0, 1)
#define WIFI_SUBNET		IPAddress(255, 255, 255, 0)
#define WIFI_DNS		IPAddress(192, 168, 0, 1)
#define WIFI_IP			IPAddress(192, 168, 0, 54)

#define NODE_SERVER		IPAddress(192, 168, 0, 10)
#define NODE_DEBUG_HOST	IPAddress(192, 168, 0, 20)
#define NODE_PORT		3007

// ERROR Codes

enum Error
{
	Ok = 0,
	DHTReadFailed = 1,
	WirelessConnectFailed = 2,
	PostToNodeFailed = 3,
};

#endif

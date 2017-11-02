// Dependencies
#include <ESP8266WiFi.h>
#include <user_interface.h>
#include "Math\Get.h"

// Abstractions
#include "Trace\Log.h"
#include "Configuration.h"
#include "Hardware\DHT22.h"
#include "Hardware\Wireless.h"
#include "Hardware\Voltmeter.h"
#include "Node\Node.h"

void GoDeepSleep(Error error)
{
	if (error > 0)
	{
		Serial.print("Error: ");
		Serial.println(error);
		
		blinkLed(error, 200);
	}
	else
	{
#ifdef DEBUG
		blinkLed(1, 500);
#endif
	}

	ESP.deepSleep(SLEEPTIME_US);
}

void blinkLed(int times, int duration)
{
	pinMode(2, OUTPUT);
	for (int n = 0; n < times; n++)
	{
		delay(duration);
		digitalWrite(2, LOW);
		delay(duration);
		digitalWrite(2, HIGH);
	}
	pinMode(2, INPUT);
}

void VBattEnable(bool enable)
{
	if (enable)
	{
		pinMode(VBATT_ENABLE_PIN, OUTPUT);
		digitalWrite(VBATT_ENABLE_PIN, HIGH);
	}
	else
	{
		digitalWrite(VBATT_ENABLE_PIN, LOW);
		pinMode(VBATT_ENABLE_PIN, INPUT);
	}
}

uint32_t start_millis;

void setup() {

	start_millis = millis();

	Log.Initialize();
	Log.println(F("Raumsensor V1"));

	DHT22.Enable();

	if (!Wireless.Connect())
	{
		DHT22.Disable();
		GoDeepSleep(Error::WirelessConnectFailed);
	}

	Log.println(F("Connecting to DHT22 ..."));
	uint8_t dhtReadFails = 0;
	while (!DHT22.Update())
	{
		Log.println(F("... retry"));
		dhtReadFails++;
		if (dhtReadFails == DHT22_RETRY_COUNT)
		{
			Log.println(F("ERROR: Communication with DHT22 failed!"));
			GoDeepSleep(Error::DHTReadFailed);
		}

		delay(DHT22_RETRY_DELAY_MS);
	}

	DHT22.Disable();

	float dewPoint		= DHT22.dewPoint;
	float humidity		= DHT22.humidity;
	float roomTemp		= DHT22.temperature;
	float absHumidity	= DHT22.absHumidity;
	VBattEnable(true);
	float voltage		= Voltmeter.Read();
	VBattEnable(false);

	Log.printfloat(F("Room-Temp:   "), roomTemp);
	Log.printfloat(F("Rel. Humid:  "), humidity);
	Log.printfloat(F("Abs. Humid:  "), absHumidity);
	Log.printfloat(F("DewPoint:    "), dewPoint);
	Log.printfloat(F("Voltage:     "), voltage);

	uint32_t now = millis();
	Node node;
	node.AddDataPoint("volt", voltage);
	node.AddDataPoint("temp", roomTemp);
	node.AddDataPoint("dewpoint", dewPoint);
	node.AddDataPoint("relhumid", humidity);
	node.AddDataPoint("abshumid", absHumidity);
	node.AddDataPoint("runtime", TIME_DELTA_MS(start_millis, now));

#ifdef DEBUG
	node.Post(NODE_DEBUG_HOST, NODE_PORT);
#else
	if (!node.Post(NODE_SERVER, NODE_PORT))
	{
		Log.print("Posting to ");
		Log.print(NODE_SERVER);
		Log.println(" failed.");
		GoDeepSleep(Error::PostToNodeFailed);
	}
#endif

	Log.print("Successfully posted to ");
	Log.println(NODE_SERVER);

	now = millis();
	Log.print("Total runtime: ");
	Log.println(TIME_DELTA_MS(start_millis, now));

	GoDeepSleep(Error::Ok);
}

void loop()
{
}

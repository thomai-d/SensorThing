#include "Wireless.h"

#include <Arduino.h>
#include <ESP8266WIFI.h>
#include "..\Trace\Log.h"
#include "..\Configuration.h"

bool WirelessClass::Connect()
{
	wl_status_t status = WiFi.status();

	Log.printf("Connecting to %s ...", WifiSSID);
	WiFi.mode(WiFiMode::WIFI_STA);
	WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET, WIFI_DNS);

#ifdef WIFI_CHANNEL
	WiFi.begin(WifiSSID, WifiPass, WIFI_CHANNEL);
#else
	WiFi.begin(WifiSSID, WifiPass);
#endif
	WiFi.waitForConnectResult();

	status = WiFi.status();
	if (status == WL_CONNECTED)
	{
		Log.println("ok");

		Log.print("Local IP: ");
		Log.println(WiFi.localIP());

		return true;
	}

	Log.printf("failed, status: %d\n", status);
	return false;
}

WirelessClass Wireless;

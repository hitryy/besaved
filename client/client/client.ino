#include "Manager.h"
#include "Params.h"

Manager manager(GPS_RX, GPS_TX, BTN_PIN, GPS_CYCLES_LEFT_BOUND);

void setup() {
	Serial.begin(9600);
	manager.init();

	while (!Serial);

	if (!manager.init()) {
		Serial.println("Init failed");

		return;
	}

	Serial.println("besaved v. 0.0 | Client side started. Monitoring GPS data started...");
}

void loop() {
	String gpsDataCoordAgeSpeedRow = manager.startGetDataAndSend();

	if (gpsDataCoordAgeSpeedRow != GpsProvider::NONE_DATA) {
		Serial.println(gpsDataCoordAgeSpeedRow);
	}	
}
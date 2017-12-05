#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <RadioHead-master\RH_RF95.h>
#include <GpsProvider.h>

GpsProvider gpsProvider(0, 1);
RH_RF95 rf95;

void setup() {
	Serial.begin(9600);
	gpsProvider.beginSerial();

	while (!Serial);

	if (!rf95.init()) {
		Serial.println("RF95 init failed. Please, check the shield");
	}

	Serial.println("besaved v. 0.0. Client side started. Minitoring GPS coords");
}

void loop() {
	unsigned long loopStarted = millis();

	gpsProvider.initLoopStarted(loopStarted);

	gpsProvider.tryGetNewData();
}
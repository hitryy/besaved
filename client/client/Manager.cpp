#include "Manager.h"

String Manager::startGetDataAndSend() {
	int btnStatus = digitalRead(_btnPin);

	unsigned long loopStarted = millis();

	_gpsProvider.initLoopStarted(loopStarted);

	String gpsDataCoordAgeSpeedRow = _gpsProvider.tryGetNewData();
	
	JsonObject& data = getPacketData();
	sendDataByLoRaAndWait(data);

	return gpsDataCoordAgeSpeedRow;
}

bool Manager::initLoRa() {
	return _loRaProvider.init();
}

bool Manager::init() {
	pinMode(_btnPin, OUTPUT);

	_gpsProvider.beginSerial();
	bool initResult = initLoRa();

	return initResult;
}

JsonObject& Manager::getPacketData() {	
	float fLatitude = _gpsProvider.getFLatitude();
	float fLongitude = _gpsProvider.getFLongitude();
	unsigned long age = _gpsProvider.getFixAge();
	float speedKmph = _gpsProvider.getSpeedKmph();

	JsonObject& data = _jsonBuffer.createObject();

	data["lat"] = fLatitude;
	data["long"] = fLongitude;
	data["age"] = age;
	data["speed"] = speedKmph;

	return data;
}

void Manager::sendDataByLoRaAndWait(JsonObject& data) {
	_jsonBuffer.clear();
}

#pragma once

#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include "GpsProvider.h"
#include "LoRaProvider.h"

class Manager {
public:
	Manager(uint8_t GpsRx, uint8_t GpsTx, uint8_t btnPin) : _gpsProvider(GpsRx, GpsTx), _btnPin(btnPin) {}
	~Manager() {}
	
	bool init();
	String startGetDataAndSend();
	JsonObject& getPacketData();

	void sendDataByLoRaAndWait(JsonObject& data);
private:
	uint8_t _btnPin;
	GpsProvider _gpsProvider;
	LoRaProvider _loRaProvider;
	StaticJsonBuffer<289> _jsonBuffer;

	bool initLoRa();
};

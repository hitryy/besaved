#include "Manager.h"

using namespace std;

String Manager::startGetDataAndSend() {
	_btnStatus = digitalRead(_btnPin);

	unsigned long loopStarted = millis();

	_gpsProvider.initLoopStarted(loopStarted);

	String gpsDataCoordAgeSpeedRow = _gpsProvider.tryGetNewData();
	
	if (gpsDataCoordAgeSpeedRow != GpsProvider::NONE_DATA) {
		String packet = getPacketData();

		byte packetBuff[52];
		uint8_t size = sizeof(packetBuff);

		_stringToByteArray(packet, packetBuff, size);

		sendDataByLoRa(packetBuff, size);

		Serial.print("Try to send: ");
		Serial.println(packet);
	}

	return gpsDataCoordAgeSpeedRow;
}

bool Manager::_initLoRa() {
	return _loRaProvider.init();
}

void Manager::_stringToByteArray(String str, byte arr[], int size)
{
	for (int i = 0; i < size; i++) {
		arr[i] = str[i];
	}
}

bool Manager::init() {
	pinMode(_btnPin, OUTPUT);

	_gpsProvider.beginSerial();
	bool initResult = _initLoRa();

	return initResult;
}

String Manager::getPacketData() {
	float fLatitude = _gpsProvider.getFLatitude();
	float fLongitude = _gpsProvider.getFLongitude();
	float speedKmph = _gpsProvider.getSpeedKmph();

	char fLatChar[16] = { '\0' }, fLonChar[16] = { '\0' }, speedKmphChar[16] = { '\0' };

	dtostrf(fLatitude, 2, 6, fLatChar);
	dtostrf(fLongitude, 2, 6, fLonChar);
	dtostrf(speedKmph, 2, 6, speedKmphChar);

	String completePacket = String(fLatChar) + ';' + 
							String(fLonChar) + ';' + 
							String(speedKmphChar) + ';' + 
							_btnStatus;

	return completePacket;
}

void Manager::sendDataByLoRa(byte* data, uint8_t size) {
	_loRaProvider.sendData(data, size);
}

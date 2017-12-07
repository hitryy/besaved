#include "LoRaProvider.h"

bool LoRaProvider::init() {
	return _rf95.init();
}

void LoRaProvider::sendData(byte* data, int size) {
	_rf95.send(data, size);

	bool checkSending = _rf95.waitPacketSent();
	
	if (checkSending) {
		Serial.print("Packet sent by LoRa | ");
		Serial.print("size: ");
		Serial.println(size);
	}
}

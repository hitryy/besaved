#include "LoRaProvider.h"

bool LoRaProvider::init() {
	return _rf95.init();
}

void LoRaProvider::sendDataAndWait(uint8_t data[]) const {
}

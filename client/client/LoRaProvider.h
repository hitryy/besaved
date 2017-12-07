#pragma once

#include <RH_RF95.h>

class LoRaProvider {
public:
	LoRaProvider() {}
	~LoRaProvider() {}

	bool init();

	void sendData(byte* data, int size);
private:
	RH_RF95 _rf95;
};

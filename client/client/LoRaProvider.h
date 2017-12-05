#pragma once

#include <RH_RF95.h>

class LoRaProvider {
public:
	LoRaProvider() {}
	~LoRaProvider() {}

	bool init();

	void sendDataAndWait(uint8_t data[]) const;
private:
	RH_RF95 _rf95;
};

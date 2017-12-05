#include "GpsProvider.h"

void GpsProvider::beginSerial() {
	if (!_isSerialBegan) {
		_gpsSerial.begin(9600);
	}
}

void GpsProvider::initLoopStarted(long loopStarted) {
	_loopStarted = loopStarted;
}

void GpsProvider::tryGetNewData() {
	while (millis() - _loopStarted < 1000) {
		if (_tryReadGps()) {
			_newDataCame = true;
		}
	}

	if (_newDataCame) {
		_getGpsData();
		_printGpsData();
	}
}

bool GpsProvider::getNewDataCame() const {
	return _newDataCame;
}

long GpsProvider::getLatitude() const {
	return _latitude;
}

long GpsProvider::getLongitude() const {
	return _longitude;
}

unsigned long GpsProvider::getFixAge() const {
	return _fix_age;
}

bool GpsProvider::_tryReadGps() {
	while (_gpsSerial.available()) {
		int ch = _gpsSerial.read();

		if (_gps.encode(ch)) {
			return true;
		}
	}

	return false;
}

void GpsProvider::_getGpsData() {
	_gps.get_position(&_latitude, &_longitude, &_fix_age);
}

void GpsProvider::_printGpsData() {
	String gpsCompleteData = GPS_DATA + LATITUDE_INFO;
	gpsCompleteData += _latitude;
	gpsCompleteData += LONGITUDE_INFO;
	gpsCompleteData += _longitude;
	gpsCompleteData += AGE;
	gpsCompleteData += _fix_age;

	Serial.println(gpsCompleteData);
}
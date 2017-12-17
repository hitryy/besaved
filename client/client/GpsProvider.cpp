#include "GpsProvider.h"

const String GpsProvider::NONE_DATA = "none";

void GpsProvider::beginSerial() {
	if (!_isSerialBegan) {
		_gpsSerial.begin(9600);
	}
}

void GpsProvider::initLoopStarted(long loopStarted) {
	_loopStarted = loopStarted;
}

String GpsProvider::tryGetNewData() {
	if (_gpsCyclesLeftBound != 0) {
		_gpsCyclesLeft++;
	}

	while (millis() - _loopStarted < 500) {
		if (_tryReadGps()) {
			_newDataCame = true;
		}
	}

	if (_gpsCyclesLeft == _gpsCyclesLeftBound) {
		_gpsCyclesLeft = 0;
	}

	if (_newDataCame) {
		_assignGpsData();
		String gpsDataCoordAgeSpeedRow = getGpsDataCoordAgeSpeedRow();

		return gpsDataCoordAgeSpeedRow;
	}

	return NONE_DATA;
}

String GpsProvider::getGpsDataCoordAgeSpeedRow() const {
	String gpsDataCoordAgeSpeed = GPS_DATA + LATITUDE_INFO;
	gpsDataCoordAgeSpeed += String(getFLatitude(), 8);
	gpsDataCoordAgeSpeed += LONGITUDE_INFO;
	gpsDataCoordAgeSpeed += String(getFLongitude(), 8);
	gpsDataCoordAgeSpeed += AGE;
	gpsDataCoordAgeSpeed += getFixAge();

	return gpsDataCoordAgeSpeed;
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

float GpsProvider::getFLatitude() const {
	return _fLatitude;
}

float GpsProvider::getFLongitude() const {
	return _fLongitude;
}

unsigned long GpsProvider::getFixAge() const {
	return _fixAge;
}

float GpsProvider::getSpeedKmph() const {
	return _speedKmph;
}

bool GpsProvider::_tryReadGps() {
	if (_gpsCyclesLeft != _gpsCyclesLeftBound) {
		return false;
	}

	while (_gpsSerial.available()) {
		int ch = _gpsSerial.read();

		if (_gps.encode(ch)) {
			return true;
		}
	}

	return false;
}

void GpsProvider::_assignGpsData() {
	_gps.get_position(&_latitude, &_longitude, &_fixAge);
	_gps.f_get_position(&_fLatitude, &_fLongitude, &_fixAge);
	_speedKmph = _gps.f_speed_kmph();
}
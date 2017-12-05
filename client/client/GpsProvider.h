#pragma once

#include "Arduino.h"
#include <TinyGPS.h>
#include "SoftwareSerial.h"

class GpsProvider
{
public:
	const String GPS_DATA = "GPS Data |";
	const String LATITUDE_INFO = " LAT:";
	const String LONGITUDE_INFO = " LONG:";
	const String AGE = " FIX_AGE:";
	const String SPEED = " SPEED:";
	const String DATE = " DATE";

	GpsProvider(uint8_t GpsRx, uint8_t GpsTx) : _gpsSerial(GpsRx, GpsTx) {}
	~GpsProvider() {};

	void beginSerial();
	void initLoopStarted(long loopStarted);

	void tryGetNewData();

	bool getNewDataCame() const;
	long getLatitude() const;
	long getLongitude() const;
	unsigned long getFixAge() const;

private:
	bool _isSerialBegan;

	TinyGPS _gps;
	SoftwareSerial _gpsSerial;
	bool _newDataCame;
	long _loopStarted;

	long _latitude;
	long _longitude;
	unsigned long _fix_age;

	bool _tryReadGps();
	void _getGpsData();
	void _printGpsData();
};


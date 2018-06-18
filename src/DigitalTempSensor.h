#ifndef DIGITALTEMPSENSOR_H_
#define DIGITALTEMPSENSOR_H_

#include "application.h"
#include "OneWire.h"
#include "spark-dallas-temperature.h"
#include <math.h>

class DigitalTempSensor {

	public:
		DigitalTempSensor(byte pin, unsigned long tempPollMs);

    void process(unsigned long currentTs);
		float getLastTempC();
		float getLastTempF();
		bool hasTemp();
		unsigned long getLastTempTs();

		float toF(float tempC);

	private:
		const unsigned int DS_DELAY = 900;         // Reading the temperature from the DS18x20 can take up to 750ms

		byte pin;

		OneWire* oneWire;
    DallasTemperature* sensor;
		DeviceAddress sensorAddress;

    bool tmpRequested = false;
		float lastTempC = -999;
		unsigned long lastTempReqestedTs = 0;
		unsigned long lastTempTs = 0;

		unsigned long tempPollMs = 15000;

		void requestTemp(unsigned long currentTs);
		void updateTemp(unsigned long currentTs);

		float readTempC();
};

#endif

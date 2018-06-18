#include "Particle.h"
#include "DigitalTempSensor.h"
#include "PietteTech_DHT.h"

#define DIGITAL_TEMP_PIN D0
#define PRESSURE_PIN A0
#define DHT_PIN D2
#define DHT_TYPE DHT22

DigitalTempSensor *tempSensor;
PietteTech_DHT *dht;

double poolTempF = 0;
double filterPsi = 0;
double airTempF = 0;
double humidity = 0;
double heatIndex = 0;
String json;

unsigned long TEMP_DELAY = 15000;

unsigned long lastPressureTs = 0;
unsigned long PRESSURE_DELAY = 15000;

unsigned long lastDHTTs = 0;
unsigned long DHT_DELAY = 15000;

double MIN_PRESSURE_ADC = 409.5;
double MAX_PRESSURE_ADC = 3685.5;
double MAX_PRESSURE_MPA = 1.2;
double PSI_MPA = 145.038;

unsigned long lastJsonTs = 0;
unsigned long JSON_DELAY = 25000;

STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

void setup() {
  Serial.begin(9600);

  pinMode(PRESSURE_PIN, INPUT);
  tempSensor = new DigitalTempSensor(DIGITAL_TEMP_PIN, TEMP_DELAY);

  dht = new PietteTech_DHT(DHT_PIN, DHT_TYPE);
  //dht->begin();

  Particle.variable("poolTempF", poolTempF);
  Particle.variable("filterPsi", filterPsi);
  Particle.variable("airTempF", airTempF);
  Particle.variable("humidity", humidity);
  Particle.variable("heatIndex", heatIndex);
  Particle.variable("json", json);
}

void loop() {
  unsigned long currentTs = millis();
  checkProbeTemp(currentTs);
  checkPressure(currentTs);
  checkDHT(currentTs);
  updateJson(currentTs);
}

void updateJson(unsigned long currentTs) {
  if (currentTs - lastJsonTs > JSON_DELAY) {
    lastJsonTs = currentTs;
    char buffer[2000];
    sprintf(buffer, "{\"poolTempF\": %1.2f, \"filterPsi\": %1.2f, \"airTempF\": %1.2f, \"humidity\": %1.2f, \"heatIndex\": %1.2f}", poolTempF, filterPsi, airTempF, humidity, heatIndex);
    json = String(buffer);
  }
}

void checkProbeTemp(unsigned long currentTs) {
  tempSensor->process(currentTs);
  if (!tempSensor->hasTemp())
    return;
  poolTempF = tempSensor->getLastTempF();
}

void checkPressure(unsigned long currentTs) {
  if (currentTs - lastPressureTs > PRESSURE_DELAY) {
    lastPressureTs = currentTs;

    double rawADC = analogRead(PRESSURE_PIN);
    float newPressurePsi = (rawADC - MIN_PRESSURE_ADC) * MAX_PRESSURE_MPA / (MAX_PRESSURE_ADC - MIN_PRESSURE_ADC) * PSI_MPA;
    if (newPressurePsi < 0 || newPressurePsi > 100) {
      Serial.println("Failed to read from pressure sensor!");
  		return;
  	}
    filterPsi = newPressurePsi;
  }
}

void checkDHT(unsigned long currentTs) {
  if (currentTs - lastDHTTs > DHT_DELAY) {
    lastDHTTs = currentTs;

    int result = dht->acquireAndWait(1000); // wait up to 1 sec (default indefinitely)
    switch (result) {
      case DHTLIB_OK:
        break;
      case DHTLIB_ERROR_CHECKSUM:
        Serial.println("Failed to read from DHT sensor: Checksum error");
        return;
      case DHTLIB_ERROR_ISR_TIMEOUT:
        Serial.println("Failed to read from DHT sensor: ISR time out error");
        return;
      case DHTLIB_ERROR_RESPONSE_TIMEOUT:
        Serial.println("Failed to read from DHT sensor: Response time out error");
        return;
      case DHTLIB_ERROR_DATA_TIMEOUT:
        Serial.println("Failed to read from DHT sensor: Data time out error");
        return;
      case DHTLIB_ERROR_ACQUIRING:
        Serial.println("Failed to read from DHT sensor: Acquiring");
        return;
      case DHTLIB_ERROR_DELTA:
        Serial.println("Failed to read from DHT sensor: Delta time to small");
        return;
      case DHTLIB_ERROR_NOTSTARTED:
        Serial.println("Failed to read from DHT sensor: Not started");
        return;
      default:
        Serial.println("Failed to read from DHT sensor: Unknown error");
        return;
    }

    humidity = dht->getHumidity();
    airTempF = dht->getFahrenheit();
    heatIndex = computeHeatIndex(airTempF, humidity);
  }
}

float computeHeatIndex(float tempFahrenheit, float percentHumidity) {
// Adapted from equation at: https://github.com/adafruit/DHT-sensor-library/issues/9 and
// Wikipedia: http://en.wikipedia.org/wiki/Heat_index
	return -42.379 +
		 2.04901523 * tempFahrenheit +
		10.14333127 * percentHumidity +
		-0.22475541 * tempFahrenheit * percentHumidity +
		-0.00683783 * pow(tempFahrenheit, 2) +
		-0.05481717 * pow(percentHumidity, 2) +
		 0.00122874 * pow(tempFahrenheit, 2) * percentHumidity +
		 0.00085282 * tempFahrenheit * pow(percentHumidity, 2) +
		-0.00000199 * pow(tempFahrenheit, 2) * pow(percentHumidity, 2);
}

float computeDewPoint(float tempCelcius, float percentHumidity) {
	double a = 17.271;
	double b = 237.7;
	double tC = (a * (float) tempCelcius) / (b + (float) tempCelcius) + log( (float) percentHumidity / 100);
	double Td = (b * tC) / (a - tC);
	return Td;
}

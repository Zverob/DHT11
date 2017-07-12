#include <DHT11.h>

void DHT11::init(uint8_t data) {
	dataPin = data;
}

uint8_t DHT11::lastIntRHdata() {
	return intRHdata;
}

uint8_t DHT11::lastDecRHdata() {
	return decRHdata;
}

uint8_t DHT11::lastIntTdata() {
	return intTdata;
}

uint8_t DHT11::lastDecTdata() {
	return decTdata;
}

uint8_t DHT11::update() {
	unsigned long previousMillis = 0;
	intRHdata = 0;
	decRHdata = 0;
	intTdata = 0;
	decTdata = 0;
	crc = 0;
	pinMode(dataPin, OUTPUT);
	digitalWrite(dataPin, HIGH);
	waitMilliseconds(18);
	digitalWrite(dataPin, LOW);
	waitMilliseconds(18);
	pinMode(dataPin, INPUT);
	previousMillis = millis();
	while(digitalRead(dataPin)) {
		if(millis()-previousMillis>100) return 1;
	}
	previousMillis = millis();
	while(!digitalRead(dataPin)) {
		if(millis()-previousMillis>100) return 1;
	}
	previousMillis = millis();
	while(digitalRead(dataPin)) {
		if(millis()-previousMillis>100) return 1;
	}
	intRHdata = read8bit();
	decRHdata = read8bit();
	intTdata = read8bit();
	decTdata = read8bit();
	crc = read8bit();
	if(intRHdata + decRHdata + intTdata + decTdata == crc) return 0;
	else return 1;
}

uint8_t DHT11::read8bit() {
	uint8_t tmp = 0;
	uint8_t count = 0;
	unsigned long previousMillis = 0;
	unsigned long previousMicros = 0;
	while(count!=8) {
		if(digitalRead(dataPin)) {
			previousMicros = micros();
			previousMillis = millis();
			while(digitalRead(dataPin)) {
				if(millis()-previousMillis>100) return 1;
			}
			if(micros()-previousMicros<40) {
				tmp<<=1;
			}
			else {
				tmp<<=1;
				tmp|=0x01;
			}
			count++;
		}
	}
	return tmp;
}

void DHT11::waitMilliseconds(unsigned long data) {
	unsigned long previousMillis = 0;
	previousMillis = millis();
	while(millis()-previousMillis<data);
}

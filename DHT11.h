#ifndef DHT11_h
#define DHT11_h

#include <inttypes.h>
#include <Arduino.h>

class DHT11 {
	public:
		void init(uint8_t data);
		uint8_t lastIntRHdata();
		uint8_t lastDecRHdata();
		uint8_t lastIntTdata();
		uint8_t lastDecTdata();
		uint8_t update();
	private:
		uint8_t dataPin;
		uint8_t intRHdata;
		uint8_t decRHdata;
		uint8_t intTdata;
		uint8_t decTdata;
		uint8_t crc;
		uint8_t read8bit();
};

#endif

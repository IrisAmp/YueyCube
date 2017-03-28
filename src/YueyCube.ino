#include <neopixel.h>

#include "Interface.h"
#include "Program.h"

#define WIFI_BUTTON D3

#define LED_PIN D0
#define LED_COUNT 512
#define PIXEL_TYPE WS2812B

SYSTEM_MODE(SEMI_AUTOMATIC);

class Cube : public ICube
{
public:
	Cube(Adafruit_NeoPixel _strip)
		: strip(_strip)
	{ }

	void setup()
	{
		this->strip.begin();
		this->strip.clear();
		this->strip.setBrightness(255);
		this->strip.show();
	}

	void clear()
	{
		this->strip.clear();
	}

	void setPixel(uint16_t x, uint16_t y, uint16_t z, uint32_t color)
  {
		uint16_t index = this->xyzToIndex(x, y, z);
		this->strip.setPixelColor(index, color);
	}

	void setPixelIndex(uint16_t i, uint32_t color)
	{
		this->strip.setPixelColor(i, color);
	}

	uint32_t getPixel(uint16_t x, uint16_t y, uint16_t z)
	{
		uint16_t index = this->xyzToIndex(x, y, z);
		return this->strip.getPixelColor(index);
	}

	uint32_t getPixelIndex(uint16_t i)
	{
		return this->strip.getPixelColor(i);
	}

	void setCorners(uint32_t color)
	{
		this->setPixelIndex(0, color);
		this->setPixelIndex(7, color);
		this->setPixelIndex(56, color);
		this->setPixelIndex(63, color);
		this->setPixelIndex(448, color);
		this->setPixelIndex(455, color);
		this->setPixelIndex(504, color);
		this->setPixelIndex(511, color);
	}

	void setBrightness(uint16_t brightness)
	{
		this->strip.setBrightness(255);
	}

	void show()
	{
		this->strip.show();
	}

protected:
	Adafruit_NeoPixel strip;

	uint16_t xyzToIndex(uint16_t x, uint16_t y, uint16_t z)
	{
		return (8 * x) + y + (8 * 8 * z);
	}
};

Cube cube(Adafruit_NeoPixel(LED_COUNT, LED_PIN, PIXEL_TYPE));
Program program(&cube);

bool connect = false;

void wifiButton()
{
	detachInterrupt(WIFI_BUTTON);
	cube.clear();
	cube.setCorners(0x320000);
	cube.show();
	delay(1000);
	connect = true;
}

void setup()
{
	attachInterrupt(WIFI_BUTTON, wifiButton, FALLING);
	cube.setup();
	program.setup();
}

void loop()
{
	if (connect) {
		if (!Particle.connected()) {
			cube.clear();
			cube.setCorners(0x321600);
			cube.show();
      Particle.connect();
      waitUntil(Particle.connected);
			cube.clear();
			cube.setCorners(0x00FF00);
			cube.show();
      delay(500);
		} else {
			cube.clear();

      unsigned long t = millis();
			if (t % 500 > 490) {
				cube.setCorners(0x646464);
			} else {
				cube.setCorners(0x000808);
			}

      unsigned long spinnerT = t % 40;
      if (spinnerT < 10) {
				cube.setPixel(3, 4, 7, 0xFFFFFF);
      } else if (spinnerT < 20) {
				cube.setPixel(4, 4, 7, 0xFFFFFF);
      } else if (spinnerT < 30) {
				cube.setPixel(4, 3, 7, 0xFFFFFF);
      } else {
				cube.setPixel(3, 3, 7, 0xFFFFFF);
      }

			cube.show();
		}
	} else {
		program.loop();
	}
}

#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Adafruit_NeoPixel.h>
#include <SPI.h>
class LedControl {
public:
    LedControl(uint16_t numPixels, uint16_t pin);
    void setup();
    void setPixelColor(uint16_t n, uint32_t color);
    void show();
    void setTemperatureColor(float temperature);
    void setStatusColor(bool sensorStatus);

private:
    Adafruit_NeoPixel strip;
};

#endif

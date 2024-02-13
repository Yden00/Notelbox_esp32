#include "LedControl.h"
#include <SPI.h>
LedControl::LedControl(uint16_t numPixels, uint16_t pin) : strip(numPixels, pin, NEO_GRBW + NEO_KHZ800) {}

void LedControl::setup()
{
    strip.begin();
    show();
}

void LedControl::setPixelColor(uint16_t n, uint32_t color)
{
    strip.setPixelColor(n, color);
}
void LedControl::setStatusColor(bool sensorStatus)
{
    if (sensorStatus)
    {
        setPixelColor(0, strip.Color(0, 255, 0));
    }
    else
    {
        setPixelColor(0, strip.Color(255, 0, 0));
    }
    show();
}

void LedControl::show()
{
    strip.show();
}

void LedControl::setTemperatureColor(float temperature)
{
    
    uint32_t color;
    if (temperature < 0)
    {
        color = strip.Color(255, 0, 120);
    }
    else if (temperature < 10)
    {
        color = strip.Color(0, 0, 255);
    }
    else if (temperature < 20)
    {
        color = strip.Color(0, 100, 255);
    }
    else if (temperature < 35)
    {
        color = strip.Color(0, 255, 0);
    }
    else if (temperature < 40)
    {
        color = strip.Color(255, 165, 0);
    }
    else
    {
        color = strip.Color(255, 0, 0);
    }
    setPixelColor(1, color);
    show();
}

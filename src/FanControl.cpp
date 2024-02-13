#include "FanControl.h"
#include <SPI.h>
FanControl::FanControl(uint8_t channel, uint32_t frequency, uint8_t pin, uint8_t resolution) : channel(channel)
{
    ledcSetup(channel, frequency, resolution);
    ledcAttachPin(pin, channel);
}

void FanControl::setup()
{
}
void FanControl::charging_control(float temperature) {
    if (temperature > 25) {
        digitalWrite(25, HIGH); 
        Serial.println("Relay Status: HIGH");
    } else {
        digitalWrite(25, LOW);
        Serial.println("Relay Status: LOW"); 
    }
}
void FanControl::setFanSpeed(float temperature)
{
    int speed;
    if (temperature < 0)
    {
        speed = 0;
    }
    else if (temperature < 10)
    {
        speed = 25;
    }
    else if (temperature < 20)
    {
        speed = 76;
    }
    else if (temperature < 35)
    {
        charging_control(temperature);
        speed = 128;
    }
    else if (temperature < 40)
    {
        charging_control(temperature);
        speed = 178;
    }
    else
    {
        speed = 255;
    }
    currentSpeed = speed;
}

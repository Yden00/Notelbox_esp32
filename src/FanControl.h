#ifndef FANCONTROL_H
#define FANCONTROL_H

#include <Arduino.h>
#include <SPI.h>
class FanControl {
public:
    FanControl(uint8_t channel, uint32_t frequency, uint8_t pin, uint8_t resolution);
    void setup();
    void charging_control(float temperature);
    void setFanSpeed(float temperature);
    int getFanSpeed() const { return currentSpeed; }
private:
    uint8_t CONTROL_PIN = 25;
    uint8_t channel;
    int currentSpeed;
};

#endif

#pragma once

#include "wled.h"

//This is an empty v2 usermod template. Please see the file usermod_v2_example.h in the EXAMPLE_v2 usermod folder for documentation on the functions you can use!


class UsermodHCSR501 : public Usermod {
  private:
    int pinStateCurrent   = LOW;  // current state of pin
    int pinStatePrevious  = LOW;  // previous state of pin
    const int PIN_TO_SENSOR = 4; // GIOP19 pin connected to OUTPUT pin of sensor

  public:
    /*
     * setup() is called once at boot. WiFi is not yet connected at this point.
     * You can use it to initialize variables, sensors or similar.
     */
    void setup() {
      pinMode(PIN_TO_SENSOR, INPUT); // set ESP32 pin to input mode to read value from OUTPUT pin of sensor
    }

    void loop() {
      pinStatePrevious = pinStateCurrent; // store old state
      pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state
      
      if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
        Serial.println("Motion detected!");
        // TODO: turn on alarm, light or activate a device ... here
      }
      else
      if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
        Serial.println("Motion stopped!");
        // TODO: turn off alarm, light or deactivate a device ... here
      }
    }

    /*
     * getId() allows you to optionally give your V2 usermod an unique ID (please define it in const.h!).
     * This could be used in the future for the system to determine whether your usermod is installed.
     */
    uint16_t getId()
    {
      return USERMOD_ID_HCSR501;
    }
};
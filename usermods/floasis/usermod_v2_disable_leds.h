#pragma once

#include "wled.h"

//This is an empty v2 usermod template. Please see the file usermod_v2_example.h in the EXAMPLE_v2 usermod folder for documentation on the functions you can use!

class UsermodDisableLeds : public Usermod {
private:

public:
    /*
    * handleOverlayDraw() is called just before every show() (LED strip update frame) after effects have set the colors.
    * Use this to blank out some LEDs or set them to a different color regardless of the set effect mode.
    * Commonly used for custom clocks (Cronixie, 7 segment)
    */
    void handleOverlayDraw()
    {
        strip.setPixelColor(33, RGBW32(0,0,0,0));
        strip.setPixelColor(130, RGBW32(0,0,0,0));
        strip.setPixelColor(147, RGBW32(0,0,0,0));
        strip.setPixelColor(175, RGBW32(0,0,0,0));
        strip.setPixelColor(192, RGBW32(0,0,0,0));
        strip.setPixelColor(214, RGBW32(0,0,0,0));
        strip.setPixelColor(227, RGBW32(0,0,0,0));
        strip.setPixelColor(236, RGBW32(0,0,0,0));
        strip.setPixelColor(231, RGBW32(0,0,0,0));
        strip.setPixelColor(264, RGBW32(0,0,0,0));
        strip.setPixelColor(259, RGBW32(0,0,0,0));
        strip.setPixelColor(259, RGBW32(0,0,0,0));
        strip.setPixelColor(259, RGBW32(0,0,0,0));
        strip.setPixelColor(259, RGBW32(0,0,0,0));
    }
};
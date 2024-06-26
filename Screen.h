#ifndef SCREEN_H
#define SCREEN_H

#include <XPT2046_Touchscreen.h>
#include <Arduino_GFX_Library.h>
#include "SDCard.h" // Include the SDCard class

class Screen {
public:
    Screen(uint8_t touchCsPin, uint8_t touchIrqPin, SDCard *sdCard, Arduino_ESP32RGBPanel *bus);
    bool begin();
    void drawTouchPoint();
    void setRotation(uint8_t rotation);

    // Make gfx public for accessibility
    Arduino_RPi_DPI_RGBPanel *gfx;

private:
    XPT2046_Touchscreen ts;
    SDCard *sdCard; // Pointer to SDCard class
    uint8_t touchCsPin;
    uint8_t touchIrqPin;
};

#endif // SCREEN_H

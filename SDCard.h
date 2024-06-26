#ifndef SDCARD_H
#define SDCARD_H

#include <SD.h>
#include <Arduino_GFX_Library.h>

class SDCard {
public:
    SDCard(uint8_t csPin);
    bool begin();
    void listFiles(const char *dirname, Arduino_RPi_DPI_RGBPanel *gfx);

private:
    uint8_t csPin;
};

#endif // SDCARD_H

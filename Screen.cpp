#include "Screen.h"

Screen::Screen(uint8_t touchCsPin, uint8_t touchIrqPin, SDCard *sdCard, Arduino_ESP32RGBPanel *bus)
    : ts(touchCsPin, touchIrqPin), sdCard(sdCard), touchCsPin(touchCsPin), touchIrqPin(touchIrqPin) {
    gfx = new Arduino_RPi_DPI_RGBPanel(
        bus,
        480 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
        272 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
        1 /* pclk_active_neg */, 9000000 /* prefer_speed */, true /* auto_flush */
    );
}

bool Screen::begin() {
    gfx->begin();
    gfx->fillScreen(BLUE);

    if (!ts.begin()) {
        return false;
    }

    ts.setRotation(0);

    if (!sdCard->begin()) {
        return false;
    }

    return true;
}

void Screen::setRotation(uint8_t rotation) {
    ts.setRotation(rotation);
}

void Screen::drawTouchPoint() {
    if (ts.touched()) {
        TS_Point p = ts.getPoint();
        
        // Adjust touch coordinates to screen coordinates
        int16_t x = map(p.x, 200, 3800, gfx->width(), 0);  // Adjust these values if needed
        int16_t y = map(p.y, 200, 3800, 0, gfx->height()); // Adjust these values if needed
        
        // Ensure coordinates stay within bounds
        x = constrain(x, 0, gfx->width());
        y = constrain(y, 0, gfx->height());

        // Draw a circle at the touch point
        gfx->fillCircle(x, y, 10, WHITE);
    }
}

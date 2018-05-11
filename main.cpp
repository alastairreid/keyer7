////////////////////////////////////////////////////////////////
// Minimalist test program
////////////////////////////////////////////////////////////////

#include <bluefruit.h>

void setup() {
}

const static int MaxBrightness = 20;
static int velocity = 1;
static int brightness = 0;
static int phase = 0;

void loop() {
    digitalWrite(LED_CONN, phase < brightness ? HIGH : LOW);
    phase++;
    if (phase >= MaxBrightness) {
        phase = 0;
        brightness += velocity;
        if (brightness == MaxBrightness) {
            velocity = -1;
        } else if (brightness == 0) {
            velocity = 1;
        }
    }
    delay(1);
}

////////////////////////////////////////////////////////////////
// End
////////////////////////////////////////////////////////////////

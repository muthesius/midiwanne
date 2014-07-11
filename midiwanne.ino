#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define DELAY 500

void setup() {
    MIDI.begin();
}

void loop() {
    if (true) { // TODO check real switch
        MIDI.sendNoteOn(42, 127, 1);
        delay(DELAY);
        MIDI.sendNoteOff(42, 0, 1);
    }
}

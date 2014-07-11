#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
    MIDI.begin();
}

void loop() {
    // TODO Go through all input pin groups

    // TODO Identify (physically) topmost closed circuit (if any)

    // TODO Send a MIDI note of the corresponding pitch/velocity for as long as it is closed

    // DEBUG Send a note to check MIDI output
    if (true) { // TODO check real switch
        MIDI.sendNoteOn(42, 127, 1);
        delay(500);
        MIDI.sendNoteOff(42, 0, 1);
        delay(1000);
    }
}

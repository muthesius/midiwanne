#include <MIDI.h>

// This is only needed for MIDI Library v >= 4.2
//MIDI_CREATE_DEFAULT_INSTANCE();

// Pin numbers for sensor steps, grouped per sensor
int inputPins[][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

void setup() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Declare sensor steps as input
            pinMode(inputPins[i][j], INPUT);
            // Enable pull-up resistors
            digitalWrite(inputPins[i][j], HIGH);
        }
    }

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

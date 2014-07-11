#include <MIDI.h>

// This is only needed for MIDI Library v >= 4.2
//MIDI_CREATE_DEFAULT_INSTANCE();

// Pin numbers for sensor steps, grouped per sensor
int inputPins[][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
// MIDI pitches per sensor
int pitches[] = {42, 54, 62};
// MIDI velocities per sensor step
int velocities[] = {31, 63, 127};

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
    // Go through all input pin groups
    for (int i = 0; i < 3; i++) {
        int velocity = 0;
        // Identify (physically) topmost closed circuit (if any)
        for (int j = 0; j < 3; j++) {
            int val = digitalRead(inputPins[i][j]);
            if (val == HIGH) {
                velocity = velocities[j];
            }
        }
        /* Send a MIDI note of the corresponding pitch/velocity for as long
           as it is closed.

           Hint: sendNoteOn with velocity = 0 is like sendNoteOff */
        MIDI.sendNoteOn(pitches[i], velocity, 1);
    }
}

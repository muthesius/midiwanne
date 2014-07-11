#include <MIDI.h>

// This is only needed for MIDI Library v >= 4.2
//MIDI_CREATE_DEFAULT_INSTANCE();

byte const sensorCount = 3;
byte const sensorStepCount = 3;
// Pin numbers for sensor steps, grouped per sensor
byte const inputPins[sensorCount][sensorStepCount] = {
    {2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
// MIDI pitches per sensor
byte const pitches[sensorCount] = {42, 54, 62};
// MIDI velocities per sensor step
byte const velocities[sensorStepCount] = {31, 63, 127};
byte const midiChannelOut = 1;

void setup() {
    for (byte i = 0; i < sensorCount; i++) {
        for (byte j = 0; j < sensorStepCount; j++) {
            // Declare sensor steps as input
            pinMode(inputPins[i][j], INPUT_PULLUP);
        }
    }

    MIDI.begin();
}

void loop() {
    // Go through all input pin groups
    for (byte i = 0; i < sensorCount; i++) {
        byte velocity = 0;
        // Identify (physically) topmost closed circuit (if any)
        for (byte j = 0; j < sensorStepCount; j++) {
            if (LOW == digitalRead(inputPins[i][j])) {
                // Circuit is closed (inverted logic b/c pullup)
                velocity = velocities[j];
            }
        }
        /* Send a MIDI note of the corresponding pitch/velocity for as long
           as it is closed.

           Hint: sendNoteOn with velocity = 0 is like sendNoteOff */
        MIDI.sendNoteOn(pitches[i], velocity, midiChannelOut);
    }
}

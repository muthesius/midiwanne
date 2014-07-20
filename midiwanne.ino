#include <MIDI.h>

// This is only needed for MIDI Library v >= 4.2
//MIDI_CREATE_DEFAULT_INSTANCE();

byte const sensorCount = 3;
byte const sensorStepCount = 3;
// Pin numbers for sensor steps, grouped per sensor
byte const inputPins[sensorCount][sensorStepCount] = {
    {2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
// MIDI pitches per sensor
byte const pitches[sensorCount] = {69, 72, 76}; // A4, C5, E5
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
    // This is only needed when debugging, e.g. with Hairless MIDI
    Serial.begin(115200);
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

           Hint: sendNoteOn with velocity = 0 is like sendNoteOff
           *but* depending on the output they may still be considered
           different messages */
        if (velocity > 0) {
            // The sendNoteOff is needed for (downward) changes in velocity
            // Again: This is pretty dependent on the output
            MIDI.sendNoteOff(pitches[i], 64, midiChannelOut);
            MIDI.sendNoteOn(pitches[i], velocity, midiChannelOut);
        } else {
            MIDI.sendNoteOff(pitches[i], 64, midiChannelOut);
        }
    }
    // Depending on the output there should be a longer/shorter delay
    // between notes - think keypress on pianos vs. organs
    //delay(200);
}

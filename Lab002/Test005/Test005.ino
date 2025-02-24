#include <Arduino.h>

struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
};

Button button = {34, 0, false};

void ARDUINO_ISR_ATTR isr() {
    button.numberKeyPresses += 1;
    button.pressed = true;
}
void setup() {
    Serial.begin(115200);
    pinMode(button.PIN, INPUT_PULLUP);
    attachInterrupt(button.PIN, isr, FALLING);
}
void loop() {
    if (button.pressed) {
        Serial.printf("Button  has been pressed %u times\n", button.numberKeyPresses);
        button.pressed = false;
    }  
}
#include "wiring_shift_mod.h"
#include "driver/rtc_io.h"

#define CLOCK_TYPE CLOCK_INVERT
#define CLOCK_DELAY_US 1
#define WAKEUP_GPIO GPIO_NUM_34

const int strobe_pin = 17;
const int clock_pin = 16;
const int data_pin = 4;

// Variables for state tracking
bool isRunning = false;
unsigned long counter = 0;
RTC_DATA_ATTR int bootCount = 0;

// Function to convert BCD to 7-segment display format
char BCD_TO_7SEGMENT(uint8_t A) {
    static char LOOKUPTB[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
    };
    return LOOKUPTB[A];
}

// Send command to TM1638
void sendCommand(uint8_t value) {
    digitalWrite(strobe_pin, LOW);
    shiftOutMod(data_pin, clock_pin, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, value);
    digitalWrite(strobe_pin, HIGH);
}

// Reset display
void reset() {
    sendCommand(0x40);
    digitalWrite(strobe_pin, LOW);
    shiftOutMod(data_pin, clock_pin, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, 0xc0);
    for(uint8_t i = 0; i < 16; i++) {
        shiftOutMod(data_pin, clock_pin, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, 0x00);
    }
    digitalWrite(strobe_pin, HIGH);
}

// Display single digit
void displayDigit(char position, uint8_t digit) {
    char data = BCD_TO_7SEGMENT(digit);
    char address = 0xc0 | (position << 1);
    
    digitalWrite(strobe_pin, LOW);
    shiftOutMod(data_pin, clock_pin, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, address);
    shiftOutMod(data_pin, clock_pin, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, data);
    digitalWrite(strobe_pin, HIGH);
}

// Display full number
void displayNumber(unsigned long number) {
    for(int i = 0; i < 8; i++) {
        displayDigit(7 - i, number % 10);
        number /= 10;
    }
}

// Read button states
uint8_t readButtons() {
    uint8_t buttons = 0;
    digitalWrite(strobe_pin, LOW);
    shiftOutMod(data_pin, clock_pin, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US, 0x42);
    
    pinMode(data_pin, INPUT);
    for(uint8_t i = 0; i < 4; i++) {
        uint8_t v = shiftInMod(data_pin, clock_pin, LSBFIRST, CLOCK_TYPE, CLOCK_DELAY_US) << i;
        buttons |= v;
    }
    
    pinMode(data_pin, OUTPUT);
    digitalWrite(strobe_pin, HIGH);
    return buttons;
}

void setup() {
    // Initialize pins
    pinMode(strobe_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);
    pinMode(data_pin, OUTPUT);
    pinMode(WAKEUP_GPIO, INPUT);
    
    Serial.begin(115200);
    
    // Configure sleep wakeup
    esp_sleep_enable_ext0_wakeup(WAKEUP_GPIO, 1);
    
    // Initialize display
    sendCommand(0x8f);  // Set maximum brightness
    reset();
    displayNumber(0);   // Show initial 00000000
    
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
}

void loop() {
    // Check SW3-1 state
    int switchState = digitalRead(WAKEUP_GPIO);
    
    if (switchState == LOW) {
        // Turn off display and enter sleep mode
        reset();
        Serial.println("Entering sleep mode");
        delay(100);
        esp_deep_sleep_start();
    } else {
        // Normal operation mode
        uint8_t buttons = readButtons();
        
        // Check S8 (Start/Stop)
        if (buttons & 0x80) {
            isRunning = !isRunning;
            delay(200); // Debounce
        }
        
        // Check S1 (Reset)
        if (buttons & 0x01) {
            counter = 0;
            isRunning = false;
            displayNumber(counter);
            delay(200); // Debounce
        }
        
        // Update counter if running
        if (isRunning) {
            counter++;
            if (counter > 99999999) {
                counter = 0;
            }
            displayNumber(counter);
            delay(1); // 1ms delay for counting speed
        }
    }
}

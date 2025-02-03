//#include <tone.h>
#include <Tone32.h>
#define BUZZER_PIN 12
#define BUZZER_CHANNEL 0
#define silence 500

int note = {
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_G4,
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_C4,

  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_G4,
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_C4
  };

int noteDurations[] = {
  500, 500, 500, 500,
  500, 500, 500, 500,
  500, 500, 500, 500,
  1000, 1000,

  500, 500, 500, 500,
  500, 500, 500, 500,
  500, 500, 500, 500,
  1000, 1000
};

void setup()
{
 for(int i = 0;i < 10;i++)
 {
 tone(BUZZER_PIN, NOTE_C4, 500, BUZZER_CHANNEL);
 tone(BUZZER_PIN, NOTE_F5, 500, BUZZER_CHANNEL);
 }
 delay(5000);
}
void loop()
{
 tone(BUZZER_PIN, NOTE_C4, 500, BUZZER_CHANNEL);
 delay(silence);
}

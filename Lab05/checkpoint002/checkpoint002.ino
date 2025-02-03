//#include <tone.h>
#include <Tone32.h>
#define BUZZER_PIN 12
#define BUZZER_CHANNEL 0
#define silence 500

int note[] = {
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

int count;
int num;

void setup()
{
 num = sizeof(note)/sizeof(note[1]);
 count = 0;
}
void loop()
{
 tone(BUZZER_PIN, note[count], noteDuration[count]*1.3, BUZZER_CHANNEL);
 count++;
 count = count % num;
}

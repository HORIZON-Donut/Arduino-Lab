//#include <tone.h>
#include <Tone32.h>
#define BUZZER_PIN 12
#define BUZZER_CHANNEL 0
#define silence 500
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
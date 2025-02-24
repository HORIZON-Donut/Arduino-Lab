const int DG[2] = {27, 14};
const int segMentPin[7] = {4, 0, 17, 16, 23, 19, 18};
const int dot = 20;

int i;
bool segMent[7];

void setup()
{
  for(i = 0; i < 2; i++)
  {
    pinMode(DG[i], OUTPUT);
    digitalWrite(DG[i], HIGH);
  }

  for(i = 0; i < 7; i++)
  {
    pinMode(segMentPin[i], OUTPUT);
    digitalWrite(segMentPin[i], HIGH);
  }
}

void loop(){}
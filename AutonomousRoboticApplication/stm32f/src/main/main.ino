#include <Wire.h>

void setup()
{
  Wire.begin(2);
  Wire.onRequest(requestEvent);
  pinMode(PC13, OUTPUT);
}

void loop()
{
}

void requestEvent()
{
  Wire.write("HI FROM STM");
  digitalWrite(PC13, !digitalRead(PC13));
}


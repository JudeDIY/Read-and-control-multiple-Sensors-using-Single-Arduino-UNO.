#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int PulseWire = A1;

const int relay = 13;
const int led = 11;
const int buzzer = 10;
const int ldrPin = A0;

const int soilpin = A2;
const int led1 = 9;

int Sensor = 400;
int Threshold = 550;
int soilthres = 500;

PulseSensorPlayground pulseSensor;

void setup() 
{
Serial.begin(9600);
pinMode(relay, OUTPUT);
pinMode(led, OUTPUT);
pinMode(buzzer, OUTPUT);
pinMode(ldrPin, INPUT);

pinMode(soilpin, INPUT);
pinMode(led1, OUTPUT);

pulseSensor.analogInput(PulseWire);
pulseSensor.setThreshold(Threshold);
delay(100);
}

void ldr()
{
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus < Sensor) 
  {
  digitalWrite(relay, HIGH);
  digitalWrite(led, HIGH);
  digitalWrite(buzzer, HIGH);
  tone(buzzer, 1000, 200);
  } 
  else 
  {
  digitalWrite(relay, LOW);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  noTone(buzzer);
  }
}

void heart() 
{
pulseSensor.begin();
int myBPM = pulseSensor.getBeatsPerMinute();
if (pulseSensor.sawStartOfBeat())
{
  Serial.print("BPM: ");
  Serial.println(myBPM);
}
  delay(10);
}

void soil()
{
  int soilStatus = analogRead(soilpin);
  if (soilStatus > soilthres) 
  {
  digitalWrite(led1, HIGH);
  } 
  else 
  {
  digitalWrite(led1, LOW);
}
}

void loop()
{
  ldr();
  heart();
  soil();
}


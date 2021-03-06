#include <FastLED.h>
#define Wit    12
#define Rood    9
#define Groen   11
#define LED_PINB    A4
#define LED_PINF    6
#define NUM_LEDSR    7
#define NUM_LEDSF   28
CRGB ledsf[NUM_LEDSF];
CRGB ledsr[NUM_LEDSR];

int ledrange=7;
int lengfront = 22;
int lengfrontt=28;
int lengback = 6;
int signaldelay=200;
int leddelay=25;
int leddelayL=20;
int switchPinG = 3;
int switchPinRed = 5;
int switchPinL = 2; 
int switchPinR = 4;               
int ledPin = LED_BUILTIN;               // ingebouwde LED pin
int switchStateG = LOW;                  // waarde van de drukknop
int switchStateRed = LOW;

int switchStateL = LOW;
int switchStateR = LOW;

// Voer uit bij de start van programma
void setup() {
    Serial.begin(9600);                 // stel de seriële monitor in
    Serial.println("Start");
    FastLED.addLeds<WS2812, LED_PINB, GRB>(ledsr, NUM_LEDSR);
    FastLED.addLeds<WS2812, LED_PINF, GRB>(ledsf, NUM_LEDSF);

    pinMode(switchPinG, INPUT);          // stel de switch pin in als invoer
    pinMode(switchPinR, INPUT);
    pinMode(Wit,OUTPUT);
    pinMode(Groen,OUTPUT);
    pinMode(Rood,OUTPUT);
    
    
}

void loop() {
  digitalWrite(Rood, HIGH);
  switchStateG = digitalRead(switchPinG);    // Lees de digitale waarde van de schakelaar (LOW/HIGH)
  switchStateRed = digitalRead(switchPinRed);
  switchStateL = digitalRead(switchPinL);
  switchStateR = digitalRead(switchPinR);                              //leest status van alle knoppen
  Serial.print("G:  ");
  Serial.println(switchStateG);
  Serial.print("Red:  ");
  Serial.println(switchStateRed);
  Serial.print("L:  ");
  Serial.println(switchStateL);
  Serial.print("R:  ");
  Serial.println(switchStateR);
    
   
   if (switchStateR == HIGH) {               // Rechts
      rechts();
    } 


  if (switchStateL == HIGH) {               // Links
      links();
    }
    
  if (switchStateG == HIGH) {               // Flasher
    flash();
    }

  if (switchStateRed == HIGH) {             // Deliveroo flow
       deliveroo();
    }     
    
  if (switchStateG == LOW && switchStateRed == LOW){    // uit
        uit();
  }
  
}

void rechts(){
  Serial.println("Rechts");
  digitalWrite(Wit, HIGH);
          for (int i=0; i<=lengfront; i++){
            Serial.println(i);
            ledsf[i] = CRGB(255, 106, 0);
            ledsr[i] = CRGB(255, 106, 0);
            if(i>=ledrange){
              ledsf[i-ledrange] = CRGB(0, 0, 0);
              ledsr[i-ledrange] = CRGB(0, 0, 0);
            }
            FastLED.show();
            delay(leddelay); 
            digitalWrite(Wit, LOW);
            }
}

void links(){
  Serial.println("Links");
  digitalWrite(Groen, HIGH);
    for (int i=28; i>=-6; i--){
            Serial.println(i);
            if (i>=0){
            
              ledsf[i] = CRGB(255, 106, 0);
              ledsr[i] = CRGB(255, 106, 0);
            }
            
            if(i<=21){
              ledsf[i+ledrange] = CRGB(0, 0, 0);
              ledsr[i+ledrange] = CRGB(0, 0, 0);
            }
            FastLED.show();
            delay(leddelayL); 
            digitalWrite(Groen, LOW);
            }
}

void flash(){
  Serial.println("Flasher");
  digitalWrite(Groen, HIGH);
    for (int i=0; i<=lengfront; i++){
            ledsf[i] = CRGB(255, 255, 255);
            FastLED.show();                   // maakt alles wit
            digitalWrite(Groen, LOW);
              }
}

void deliveroo(){
  digitalWrite(Rood, LOW);
  int delayy=20;
  Serial.println("Deliveroo flow");
    for(int j=0;j<=6;j++){
      ledsr[j]=CRGB(0,255,106);
      FastLED.show();
    }
       for (int i=0; i<lengfront; i++){
        ledsf[i] = CRGB(0, 255, 106);
        FastLED.show();
        delay(50);
        digitalWrite(Rood, HIGH);     
      }
}

void uit(){
   for (int i=0; i<=lengfront; i++){
            ledsf[i] = CRGB(0,0,0);
            ledsr[i] = CRGB(0,0,0);
            FastLED.show();  
  }
}

void readstatus(){
    switchStateG = digitalRead(switchPinG);    // Lees de digitale waarde van de schakelaar (LOW/HIGH)
    switchStateRed = digitalRead(switchPinRed);
    switchStateL = digitalRead(switchPinL);
    switchStateR = digitalRead(switchPinR);
}

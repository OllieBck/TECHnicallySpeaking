#include <IRremote.h>

IRsend irsend;

int pulse_khz = 38;

unsigned int samPwr[] = {4500, 4350, 600, 1600, 600, 1600, 600, 1600, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 1600, 550, 1650, 550, 550, 550, 550, 550, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 550, 1650, 550};
//unsigned int epson[] = {8800, 4400, 650, 1550, 650, 1550, 650, 500, 600, 500, 600, 500, 650, 500, 600, 500, 600, 1600, 600, 1600, 650, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 650, 1550, 650, 500, 600, 500, 600, 500, 650, 500, 600, 500, 600, 1600, 600, 500, 650, 500, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 500, 650, 1550, 600, 1650, 550, 550, 600};

//channel up
unsigned int chanUp[] = {4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};

// channel down
unsigned int chanDown[] = {4650,4300,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,1550,700,400,700,450,650,400,700,1550,700,1500,700,1550,700,1500,700,400,700,1550,650,1550,700,1500,700};

// volume up
unsigned int volUp[] = {4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,1500,700,1550,650};

// volume down
unsigned int volDown[] = {4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,400,700,400,700,450,700,400,700,400,700,400,700,1550,700,400,700,1500,700,1500,700,1550,700,1500,700};

unsigned int volDown_length = sizeof(volDown) / sizeof(volDown[0]);
unsigned int volUp_length = sizeof(volUp) / sizeof(volUp[0]);
unsigned int samPwr_length = sizeof(samPwr)/ sizeof(samPwr[0]);
unsigned int chanUp_length = sizeof(chanUp)/ sizeof(chanUp[0]);
unsigned int chanDown_length = sizeof(chanDown)/ sizeof(chanDown[0]);

//unsigned int epson_bit_length = sizeof(epson) / sizeof(epson[0]);

const int ledPin = 13;
int incomingByte;

void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  // the projectors
  //irsend.sendRaw(epson, epson_bit_length, pulse_khz);
  
  //delay(20);

  //irsend.sendRaw(samsung, samsung2_bit_length, pulse_khz);
  // the TV's
  /*
  irsend.sendRaw(volDown, volDown_length, pulse_khz);
  irsend.sendRaw(volUp, volUp_length, pulse_khz);
  irsend.sendRaw(chanUp, chanUp_length, pulse_khz);
  irsend.sendRaw(chanDown, chanDown_length, pulse_khz);
  irsend.sendRaw(samPwr, samPwr_length, pulse_khz);
  */

  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'O') {
      digitalWrite(ledPin, HIGH);
      irsend.sendRaw(samPwr, samPwr_length, pulse_khz);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'D') {
      irsend.sendRaw(volDown, volDown_length, pulse_khz);
    }
    if (incomingByte == 'U') {
      irsend.sendRaw(volUp, volUp_length, pulse_khz);
    }
    if (incomingByte == 'F') {
      irsend.sendRaw(chanUp, chanUp_length, pulse_khz);
    }
    if (incomingByte == 'B') {
      irsend.sendRaw(chanDown, chanDown_length, pulse_khz);
    } 
  }
}

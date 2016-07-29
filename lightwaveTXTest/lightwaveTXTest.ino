

#include <LwTx.h>

/*
   command : parameter
   -------------------
         0 : 0    = off
         1 : 0    = on
         1 : 160  = increase
         0 : 160  = decrease
         1 : 64   = min brightness
         1 : 95   = max brightness
*/

int count, pulses, A_SIG=0, B_SIG=1;


byte addr[] = {5, 9, 3, 0, 1};

const int sw0Pin = 7;
//const int sw1Pin = 3;
//const int sw2Pin = 12;
//const int potPin = A5;

boolean sw0;
//boolean sw1;
//boolean sw2;
//int pot;
//int dim;
//int oldDim;

void setup() {
  attachInterrupt(0, A_RISE, RISING);
  attachInterrupt(1, B_RISE, RISING);  
  

  pinMode(sw0Pin, INPUT_PULLUP);
//  pinMode(sw1Pin, INPUT_PULLUP);
  //  pinMode(sw2Pin, INPUT_PULLUP);
//  pinMode(potPin, INPUT);

  Serial.begin(9600);

  //Transmit on pin 12, 6 repeats, no invert, 140uSec tick)
  lwtx_setup(12, 6, 0, 140);
  //Set address
  lwtx_setaddr(addr);

  //initialise dimmer
//  pot = analogRead(potPin);
//  oldDim = map(pot, 0, 1023, 0, 31);
}

void loop() {
  sw0 = digitalRead(sw0Pin);
//  sw1 = digitalRead(sw1Pin);
//  //  sw2 = digitalRead(sw2Pin);
//  pot = analogRead(potPin);
//  dim = map(pot, 0, 1023, -1, 31);

//  if (lwtx_free()) {
//    if (dim != oldDim) {
//      if (dim == -1) {
//        lwtx_cmd(0, 0, 2, 3); //turn off
//        //Serial.println("OFF");
//      } else {
//        lwtx_cmd(1, 64 + dim, 2, 3); //set to dim level
//        //Serial.print("DIM: ");
//        //Serial.println(dim);
//      }
//      oldDim = dim;
//    }
//
    if (sw0 == LOW) {
      lwtx_cmd(1, 160, 2, 3); //brightness up
      //Serial.println("UP");
    }
//    if (sw0 == LOW) {
//      lwtx_cmd(0, 160, 2, 3); //brightness down
//      //Serial.println("DOWN");
//    }
//  }

//  if (pulses / 4 > count) {    
//      count = pulses / 4;
//      up();
//      Serial.println(count);
//  }
//
//  
//  if (pulses / 4 < count) {    
//      count = pulses / 4;
//      down();
//      Serial.println(count);
//  }


}


void A_RISE(){
 detachInterrupt(0);
 A_SIG=1;
 
 if(B_SIG==0)
// pulses++;//moving forward
  up();
 if(B_SIG==1)
// pulses--;//moving reverse
  down();
// Serial.println(pulses/4);
 attachInterrupt(0, A_FALL, FALLING);
}

void A_FALL(){
  detachInterrupt(0);
 A_SIG=0;
 
 if(B_SIG==1)
// pulses++;//moving forward
  up();
 if(B_SIG==0)
// pulses--;//moving reverse
  down();
// Serial.println(pulses/4);
 attachInterrupt(0, A_RISE, RISING);  
}

void B_RISE(){
 detachInterrupt(1);
 B_SIG=1;
 
 if(A_SIG==1)
// pulses++;//moving forward
  up();
 if(A_SIG==0)
// pulses--;//moving reverse
  down();
// Serial.println(pulses/4);
 attachInterrupt(1, B_FALL, FALLING);
}

void B_FALL(){
 detachInterrupt(1);
 B_SIG=0;
 
 if(A_SIG==0)
// pulses++;//moving forward
  up();
 if(A_SIG==1)
// pulses--;//moving reverse
  down();
// Serial.println(pulses/4);
 attachInterrupt(1, B_RISE, RISING);
}

void up () {
  if (lwtx_free()) {
    lwtx_cmd(1, 160, 2, 3); //brightness up
    Serial.println("UP");
  }
}

void down () {
  if (lwtx_free()) {
    lwtx_cmd(0, 160, 2, 3); //brightness down
    Serial.println("DOWN");
  }
}


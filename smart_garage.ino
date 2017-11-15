/*
 * ===================================================================
 * 
 * Seconda consegna di Sistemi Embedded e Internet of things
 * Savini Gianni 731806
 * 
 * ===================================================================
 */
#include "config.h"
#include "ButtonImpl.h"
#include "LedExt.h"
#include "Led.h"
#include "LedExt.h"
#include "Sonar.h"
#include "Pir.h"

//Led* ledr;
//LedExt* led1, led2;
//ProximitySensor* prox;
Pir* pir;
//Button* touch, closing
bool state = false;

void setup() {
  Serial.begin(9600);
  LedExt* led1 = new LedExt(LDIST1);
  LedExt* led2 = new LedExt(LDIST2);
  Led* ledr = new Led(LR);
  Sonar* prox = new Sonar(PROXECHO, PROXTRIG);
  pir = new Pir(PIR);
  Button* touch = new ButtonImpl(TOUCH);
  Button* closing = new ButtonImpl(CLOSE);
  
}

void loop() {
  if(state) {
    delay(4000);
    state = false;
  }
  
  Serial.println(pir->isDetected());
}

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

#include "Scheduler.h"

volatile State state;

//Led* ledr;
//LedExt* led1, led2;
//ProximitySensor* prox;
Pir* pir;
//Button* touch, closing
bool state = false;
Scheduler sched;

void setup() {

  Task* t0 = new Init();
  t0->init(50);
  sched.addTask(t0);

  Task* t1 = new OpenGarage();
  t1->init(10);
  sched.addTask(t1);

  Task* t2 = new Parking();
  t2->init(10);
  sched.addTask(t2);

  Task* t3= new Stop();
  t3->init(10);
  sched.addTask(t3);

  Task* t4 = new CloseGarage();
  t4->init(10);
  sched.addTask(t4);

  state = INI;
  
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

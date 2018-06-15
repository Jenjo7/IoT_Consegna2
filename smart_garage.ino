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
#include "Init.h"
#include "OpenGarage.h"
#include "Parking.h"
#include "Stop.h"
#include "CloseGarage.h"

#include "Scheduler.h"

volatile State state;

//Led* ledr;
//LedExt* led1, led2;
//ProximitySensor* prox;
Pir* pir;
//Button* touch, closing
bool st = false;
Scheduler sched;

void setup() {

  sched.init(100);

  Task* t0 = new Init();
  t0->init(200);
  sched.addTask(t0);

  Task* t1 = new OpenGarage(LR, PIR);
  t1->init(100);
  sched.addTask(t1);

  Task* t2 = new Parking( LDIST1,  LDIST2,  LR,  CLOSE,  TOUCH, PROXECHO,  PROXTRIG);
  t2->init(100);
  sched.addTask(t2);

  Task* t3= new Stop(LR, PROXECHO,  PROXTRIG);
  t3->init(100);
  sched.addTask(t3);

  Task* t4 = new CloseGarage(LR);
  t4->init(100);
  sched.addTask(t4);

  state = INI;
  
  Serial.begin(9600);
  LedExt* led1 = new LedExt(LDIST1);
  LedExt* led2 = new LedExt(LDIST2);
  LedExt* ledr = new LedExt(LR);
  Sonar* prox = new Sonar(PROXECHO, PROXTRIG);
  pir = new Pir(PIR);
  Button* touch = new ButtonImpl(TOUCH);
  Button* closing = new ButtonImpl(CLOSE);
  
}

void loop() {
  sched.schedule();
}

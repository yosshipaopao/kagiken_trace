#include <Arduino.h>
#include "motor.h"
#define rep(i,n) for(int i = 0; i < n; i++)
const int M1_L = 5, M1_R = 6, M2_L = 10, M2_R = 9;
const int SW_1 = 20, SW_2 = 21;
Motor m1(M1_L, M1_R);
Motor m2(M2_L, M2_R);
int m_pow = 255;
int sp[4] = {14, 15, 16, 17};
void setup() {
  pinMode(SW_1,INPUT);
  pinMode(SW_2,INPUT);
  m1.setup();
  m2.setup();
  rep(i, 4) pinMode(sp[i], INPUT);

  while (digitalRead(SW_1)) delay(10);
}
bool e = false;

void loop() {
  bool a,b,c,d;
  a=digitalRead(sp[0]);
  b=digitalRead(sp[1]);
  c=digitalRead(sp[2]);
  d=digitalRead(sp[3]);
  const bool nta = !a&!b&!c&!d;
  const bool ml0 = (!nta&((!a&c)|d))|(nta&!e);
  const bool ml1 = (!nta&(!a|c))|(nta&!e);
  const bool mr0 = (!nta&((b&!d)|a))|(nta&e);
  const bool mr1 = (!nta&(!d|b))|(nta&e);
  const bool ef = d|a;
  const bool ev = !d|a;
  e = (ef&ev)|(!ef&e);
  m1.forward(((int)ml0*2 + (int)ml1*5 - 2) * m_pow / 5);
  m2.forward(((int)mr0*2 + (int)mr1*5 - 2) * m_pow / 5);
  digitalWrite(2,e);
  digitalWrite(4,!e);
}

#include <Arduino.h>
#include "motor.h"
#include "sensor.h"

#define rep(i,n) for(int i = 0; i < n; i++)

const int M1_L = 5, M1_R = 6, M2_L = 10, M2_R = 9;
Motor m2(M1_L, M1_R);
Motor m1(M2_L, M2_R);
int s_thr = 500;
int sp[4] = {14, 15, 16, 17};
bool s[4];

void setup() {
  m1.setup();
  m2.setup();
  rep(i, 4) pinMode(sp[i], INPUT);
}

bool q0 = false, q1 = false;
void loop() {
  bool a,b,c,d,e,f;
  rep(i, 4) s[i] = analogRead(sp[i]) > s_thr;
  a=s[0];
  b=s[1];
  c=s[2];
  d=s[3];
  e=q0;
  f=q1;
  //const bool sb = !s[0] & !s[1] & !s[2] & !s[3];
  //const bool ml0 = s[3] | (!s[0] & s[1]) | ((sb & q0) | (!q0 & !q1)); // (!a&b)|((sb&e)|(!e&!f))|d;
  const bool ml0 = (!a&!c&e)|(!e&!f)|(!a&b)|d;  
  const bool ml1 = ml0|(!a&c);


  //const bool mr0 = s[0] | (!s[3] & s[2]) | ((sb & q1) | (!q0 & !q1));
  //const bool mr0 = a|(!d&c)|((sb&f)|(!e&!f));
  const bool mr0 = (!b&!d&f)|(!e&!f)|(c&!d)|a;
  const bool mr1 = mr0|(b&!d);  

  //q0 = (!s[0] & s[3]) | (sb & q0);
  q0 = (!a&!b&!c&e)|(!a&d);
  //q1 = (!s[3] & s[0]) | (sb & q1);
  q1 = (!b&!c&!d&f)|(!d&a);
  
  m2.forward(((int)ml0 + (int)ml1) * 75);
  m1.forward(((int)mr0 + (int)mr1) * 75);
}

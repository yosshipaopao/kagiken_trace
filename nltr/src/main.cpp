#include <Arduino.h>
#include "sensor.h"
#include "motor.h"
#define rep(i,n) for(int i = 0; i < n; i++)


const int M1_L = 5, M1_R = 6, M2_L = 10, M2_R = 9;
const int SW_1 = 20, SW_2 = 21;
Motor m2(M1_L, M1_R);
Motor m1(M2_L, M2_R);
int sp[4] = {14, 15, 16, 17};
Sensor s(sp, 4, 500);

void setup() {
  Serial.begin(9600);
  m1.setup();
  m2.setup();
  s.setup();  
  while (digitalRead(SW_1)) delay(10);  
}

const int pow_l = 255 ,pow_m = 255, pow_s = 175;

int pre_dir = 0;
void loop() {
  switch (s.state())
  {
  case 0b0000:
    switch (pre_dir)
    {
    case -1:
      m1.forward(pow_s);
      m2.forward(pow_l);
      break;
    case 0:
      m1.forward(pow_m);
      m2.forward(pow_m);
      break;
    case 1:
      m1.forward(pow_l);
      m2.forward(pow_s);
      break;
    }
    break;
  case 0b0110:
    m1.forward(pow_l);
    m2.forward(pow_l);
    break;
  case 0b0010:
    m1.forward(pow_l);
    m2.forward(pow_m);
    break;
  case 0b0100:
    m1.forward(pow_m);
    m2.forward(pow_l);
    break;

  case 0b0011:
  case 0b0001:
    m1.forward(pow_l);
    m2.forward(pow_s);
    pre_dir = 1;
    break;
  case 0b1100:
  case 0b1000:
    m1.forward(pow_s);
    m2.forward(pow_l);
    pre_dir = -1;
    break;
  case 0b0111:
    m1.forward(pow_l);
    m2.forward(pow_m);
    pre_dir = 1;
    break;
  case 0b1110:
    m1.forward(pow_m);
    m2.forward(pow_l);
    pre_dir = -1;
    break;
  case 0b1111:
    m1.forward(pow_l);
    m2.forward(pow_l);
    break;
  default:
    m1.stop();
    m2.stop();
    break;
  }
  
  digitalWrite(2, pre_dir == -1);
  digitalWrite(4, pre_dir == 1);
}

#ifndef _motor_h
#define _motor_h

#include <Arduino.h>

class Motor
{
public:
  Motor(int left, int right);
  void setup();
  void forward(int speed);
  void backward(int speed);

private:
  int left, right;
};

Motor::Motor(int left, int right)
{
  this->left = left;
  this->right = right;
}

void Motor::setup()
{
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
}

void Motor::forward(int speed)
{
  speed = constrain(speed, -255, 255);
  if (speed < 0)
    backward(-speed);
  else if (speed == 0)
  {
    analogWrite(left, 80);
    analogWrite(right, 80);
  }
  else
  {
    digitalWrite(left,HIGH);
    analogWrite(right,255-speed);
  }
}

void Motor::backward(int speed)
{
  digitalWrite(right,HIGH);
  analogWrite(left,255-speed);
}

#endif
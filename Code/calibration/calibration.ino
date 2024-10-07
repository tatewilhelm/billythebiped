#include <Servo.h>
#define left_hip_pin 2
#define left_knee_pin 3
#define left_foot_pin 4
#define right_hip_pin 5
#define right_knee_pin 6
#define right_foot_pin 7

Servo left_hip;
Servo left_knee;
Servo left_foot;
Servo right_hip;
Servo right_knee;
Servo right_foot;

void setup() {
  left_hip.attach(left_hip_pin);
  left_knee.attach(left_knee_pin);
  left_foot.attach(left_foot_pin);
  right_hip.attach(right_hip_pin);
  right_knee.attach(right_knee_pin);
  right_foot.attach(right_foot_pin);
}

void loop() {
  left_hip.write(90);
  left_knee.write(90);
  left_foot.write(90);
  right_hip.write(90);
  right_knee.write(90);
  right_foot.write(90);
  
  

}

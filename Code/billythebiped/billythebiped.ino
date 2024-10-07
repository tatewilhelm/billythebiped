#include <Servo.h>
#include <Ramp.h>
// Constants
#define arm_section_length 1
#define left_hip_pin 2
#define left_knee_pin 3
#define left_foot_pin 4
#define right_hip_pin 5
#define right_knee_pin 6
#define right_foot_pin 7


// Servos 
Servo left_hip;
Servo left_knee;
Servo left_foot;
Servo right_hip;
Servo right_knee;
Servo right_foot;

// Math stuff
double phi;
double length;
double theta;
int a1;
int a2;

// Gamepad

// Modes for the inverse kinematics function
enum kinematics_mode
{
  LEFT, RIGHT, BOTH
};


void setup()
{
  Serial.begin(57600);
  left_hip.attach(left_hip_pin);
  left_knee.attach(left_knee_pin);
  left_foot.attach(left_foot_pin);
  right_hip.attach(right_hip_pin);
  right_knee.attach(right_knee_pin);
  right_foot.attach(right_foot_pin);

}

void inverse_kinematics(enum kinematics_mode mode, double target_x, double target_y, unsigned int foot_angle, int time_spent)
{

  Serial.println("Kinematics reached");

      
  // Phi represents the angle between the x axis and target coordinatee
  phi = atan(target_y / target_x);
  
  // The length from the origin to the target
  length = target_x / (cos(phi));
  
  // Theta represents the angle from phi to (the soon to be calculated) a1
  theta = acos((length / 2) / arm_section_length);

  Serial.println("Theta: " + String(theta));
  Serial.println("Phi: " + String(phi));
  Serial.println("P-T: " + String(phi - theta));
  Serial.println("Deg P-T: " + String(int(degrees(phi - theta))));
      
  if (length > arm_section_length * 2)
  {
    // If we cant reach it, get as close as possible, so essentially point towards it
    a1 = phi;
    a2 = phi;
    Serial.println("Cant reach");
  } else {
    // Our angles to go to to reach the point
    a1 = int(degrees(phi + theta));
    a2 = int(degrees(phi - theta));
    Serial.println("A2 P-T: " + String(phi - theta));
  }
  

  

  Serial.println("Angle 1: " + String(a1));
  Serial.println("Angle 2: " + String(a2));
      
  // a1 is the degrees from the x axis, since float is always positive, a1 is 0 - 180.
  // a2 is the angle FROM a1, so it can be negative. So we need to add 90 to a2, because the center of the srvos is 90 degrees.
  a2 += 90;

  // Go!
  ramp left_hip_ramp;
  ramp left_knee_ramp;
  ramp left_foot_ramp;
  ramp right_hip_ramp;
  ramp right_knee_ramp;
  ramp right_foot_ramp;

      
  switch (mode)
  {
    case LEFT:
      // Flip knee angle
      a2 = -(a2 - 90) + 90;

      Serial.println("Actual Angle 1: " + String(a1));
      Serial.println("Actual Angle 2: " + String(a2));

      
      // Get current servo positions
      left_hip_ramp.go(left_hip.read());
      left_knee_ramp.go(left_knee.read());
      left_foot_ramp.go(left_foot.read());
      
      // Go to new positions
      left_hip_ramp.go(a1, time_spent);
      left_knee_ramp.go(a2, time_spent);
      left_foot_ramp.go(foot_angle, time_spent);

      while (!left_hip_ramp.isFinished() && !left_knee_ramp.isFinished() && !left_foot_ramp.isFinished())
      {
        left_hip.write(left_hip_ramp.update());
        left_knee.write(left_knee_ramp.update());
        left_foot.write(left_foot_ramp.update());
      }
      
    case RIGHT:
      // Get current servo positions
      right_hip_ramp.go(right_hip.read());
      right_knee_ramp.go(right_knee.read());
      right_foot_ramp.go(right_foot.read());
      
      // Go to new positions
      right_hip_ramp.go(a1, time_spent);
      right_knee_ramp.go(a2, time_spent);
      right_foot_ramp.go(foot_angle, time_spent);

      while (!right_hip_ramp.isFinished() && !right_knee_ramp.isFinished() && !right_foot_ramp.isFinished())
      {
        right_hip.write(right_hip_ramp.update());
        right_knee.write(right_knee_ramp.update());
        right_foot.write(right_foot_ramp.update());
      }
      
    case BOTH:   
      // Get current servo positions
      left_hip_ramp.go(left_hip.read());
      left_knee_ramp.go(left_knee.read());
      left_foot_ramp.go(left_foot.read());
      right_hip_ramp.go(right_hip.read());
      right_knee_ramp.go(right_knee.read());
      right_foot_ramp.go(right_foot.read());
      
      // Go to new positions
      left_hip_ramp.go(a1, time_spent);
      left_knee_ramp.go(a2, time_spent);
      left_foot_ramp.go(foot_angle, time_spent);
      right_hip_ramp.go(a1, time_spent);
      right_knee_ramp.go(a2, time_spent);
      right_foot_ramp.go(foot_angle, time_spent);

      while (!left_hip_ramp.isFinished() && !left_knee_ramp.isFinished() && !left_foot_ramp.isFinished() && !right_hip_ramp.isFinished() && !right_knee_ramp.isFinished() && !right_foot_ramp.isFinished())
      {
        left_hip.write(left_hip_ramp.update());
        left_knee.write(left_knee_ramp.update());
        left_foot.write(left_foot_ramp.update());
        right_hip.write(right_hip_ramp.update());
        right_knee.write(right_knee_ramp.update());
        right_foot.write(right_foot_ramp.update());
      }
      
  }

  
}

void loop()
{
  Serial.println("Loop reached");
  inverse_kinematics(LEFT, 1, 0, 0, 300);

\
}

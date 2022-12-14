/*
 Robot car + obstacle mode

 The program's goal is to make the car automatically avoid obstacles that it finds on its way.

 The program's theme is the use of functions to simplify the program.
*/
#include <NewPing.h> // Includes the library "<NewPing.h>" to be able to use the ultrasonic sensor.

#define TRIGGER_PIN  13 // Trigger pin is 13
#define ECHO_PIN     12 // Echo pin is 12
#define MAX_DISTANCE 400 // Maximum distance we want to measure (in centimeters).

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#include <Servo.h> // Includes the library Servo motor to program the servo motor.

Servo myservo; // Creates servo object to control a servo.

int MotorA=7; // Motor A of the car connected to pin 7
int MotorB=8; // Motor B of the car connected to pin 8
int PWMA=5; // PWMA (Pulse With Modulation A) connected to pin 5 
int PWMB=6; // PWMB (Pulse With Modulation B) connected to pin 6
int Medium_Speed=127; // The car will run in a medium speed (100) to give time to the program to work properly.

void setup() {
  // put your setup code here, to run once:
pinMode(MotorA, OUTPUT); // Pin Motor A set as output
pinMode(MotorB, OUTPUT); // Pin Motor B set as output
pinMode(PWMA, OUTPUT); // Pin PWMA set as output
pinMode(PWMB, OUTPUT); // Pin PWMB set as output
pinMode(3, OUTPUT); // Pin 3 set as output
myservo.attach(10); // Sets the pin of the servo motor.
}

void loop() {
 int distance = sonar.ping_cm(); // Stores the distance's value.
 if (distance < 25) {
   /* If distance is less than 25, then the robot will stop, move backward and the servo motor will turn to the right (0°) and the left (180°),
      the variables "Distance_right" and "Distance_left" will store the values of the distance at the right and at the left.
   */
   Stop();
   delay(300);
   backward(Medium_Speed);
   delay(300);
   Stop();
   delay(300);
   int Distance_right = Rightdistance();
   delay(300);   
   int Distance_left = Leftdistance();
   delay(300);
    if ( Distance_right > Distance_left ) {
      // If the distance at the right is greater than the distance at the left, then the car will turn to the right and keep going forward
      right(Medium_Speed);
      delay(300);
      Stop();
      delay(300); 
      myservo.write(90);     
    } else if ( Distance_left > Distance_right ){
      // Else, if the distance at the left is greater than the distance at the right, then the car will turn to the left and keep going forward
      left(Medium_Speed);
      delay(300);
      Stop();
      delay(300);
      myservo.write(90);    
    } else if (( Distance_left<25 || Distance_right<25 )){
      // However, if both distances are lower than 25, it means that the car is in a corner, so it will turn 180° and move forward 
      right(Medium_Speed);
      delay(1000);
      Stop();
      delay(300);  
      myservo.write(90);        
    }   
 } else {
   // If the distance is not less than 25, the car will just move forward.
 forward(Medium_Speed);
 }
}

int Rightdistance(){ // Function called "Rightdistance" 
  // This function stores the value of the distance when the robot looks at the right.
  myservo.write(0);
  delay(300);
  int distance_right = sonar.ping_cm();
  delay(300);
}
int Leftdistance(){ // Function called "Leftdistance" 
  // This function stores the value of the distance when the robot looks at the left.
  myservo.write(180);
  delay(300);
  int distance_left = sonar.ping_cm();
  delay(300);
}
void forward(int x){ // Function called "fordward"
  /* The function "fordward" makes the car go forward by using this methode:
      1. The Motor A has to go forward, so we give high voltage (1) to its pin 
      2. The Motor B also has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x);
}
void left(int x){ // Function called "left"
  /* The function "left" makes the car turn to the left by using this methode:
      1. The Motor A has to go forward, so we give high voltage (1) to its pin 
      2. The Motor B has to go backwards, so we give low voltage (0) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(3, 1); 
  digitalWrite(MotorA,1); 
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 0);
  analogWrite(PWMB, x);
}
void right(int x){ // Function called "right"
  /* The function "right" makes the car turn to the right by using this methode:
      1. The Motor A has to go backward, so we give low voltage (0) to its pin 
      2. The Motor B has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,0);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x);
}
void Stop(){ // Function called "stop".
  /* The function "stop" stops the car by using this methode:
      1. The Motor A has to go fordward, so we give high voltage (1) to its pin 
      2. The Motor B also has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will have no speed as we want the car to stop.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, 0);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, 0);
}
void backward(int x){ // Function called "backward".
  /* The function "backward" makes the car go backwards by using this methode:
      1. The Motor A has to go backward, so we give low voltage (0) to its pin 
      2. The Motor B also has to go backward, so we give low voltage (0) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,0);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 0);
  analogWrite(PWMB, x);
}
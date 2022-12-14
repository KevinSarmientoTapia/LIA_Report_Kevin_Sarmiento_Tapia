/*
  Robot car + line tracker

  The program's goal is to make the car robot follow a black line without going out of it.

  The program's theme is the use of functions to use simplify the program.
*/
int MotorA=7; // Motor A of the car connected to pin 7
int MotorB=8; // Motor B of the car connected to pin 8
int PWMA=5; // PWMA (Pulse With Modulation A) connected to pin 5 
int PWMB=6; // PWMB (Pulse With Modulation B) connected to pin 6
int Low_Speed=100; // The car will run in a low speed (100) to give time to the program to work properly.

void setup() { // This program will run once:
pinMode(MotorA, OUTPUT); // Pin Motor A set as output
pinMode(MotorB, OUTPUT); // Pin Motor B set as output
pinMode(PWMA, OUTPUT); // Pin PWMA set as output
pinMode(PWMB, OUTPUT); // Pin PWMB set as output
pinMode(3, OUTPUT); // Pin 3 set as output
}

void loop() { // This program will run forever:
int Left_sensor=analogRead(A2); // Left sensor of the line tracker
int Middle_sensor=analogRead(A1); // Middle sensor of the line tracker
int Right_sensor=analogRead(A0); // Right sensor of the line tracker

if (Middle_sensor > 45){ 
  // If the middle sensor measurement is more than 45, go fordward at low speed by calling the function "forward"
  forward(Low_Speed);
} else if (Left_sensor > 50){ 
  // Else if the left sensor measurement is more than 50, turn to the left at low speed by calling the function "left"
  left(Low_Speed);
} else if (Right_sensor > 440){
  // Else if the right sensor measurement us more than 440, turn to the right at low speed by calling the function "right"
  right(Low_Speed);
}

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
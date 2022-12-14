/*
  Robot car + IR with all modes.

  The program's goal is to control the car by using an IR (Infrared Remote), we will be able to control the car and use all the
  functions (Line tracker and Obstacle mode) just using the IR.

  The program's theme is to include the library "<IRemote.h>" to configure the IR.
*/
#include <NewPing.h> // Includes the library "<NewPing.h>" to be able to use the ultrasonic sensor.

#define TRIGGER_PIN  13 // Trigger pin is 13
#define ECHO_PIN     12 // Echo pin is 12
#define MAX_DISTANCE 400 // Maximum distance we want to measure (in centimeters).

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#include <Servo.h> // Includes the library Servo motor to program the servo motor.

Servo myservo; // Creates servo object to control a servo.

#include <IRremote.h> // Includes the library "<IRemote.h>"" to configure the IR.
 
const int RECV_PIN = 9; // Define sensor pin. 
 
IRrecv irrecv(RECV_PIN); // Define IR Receiver and Results Objects.
decode_results results;

unsigned long lastCode; // Stores the value of the last code
int MotorA=7; // Motor A of the car connected to pin 7.
int MotorB=8;  // Motor B of the car connected to pin 8.
int PWMA=5; // PWMA (Pulse With Modulation A) connected to pin 5 .
int PWMB=6; // PWMB (Pulse With Modulation B) connected to pin 6.
int Speed=255; // Stores the values of the speed, inicially it is 255 (Max speed).
int Low_Speed=100; // The car will run in a low speed (100) to give time to the program to work properly.
int Medium_Speed=127; // The car will run in a medium speed (100) to give time to the program to work properly.

void setup() { // This program will run once:
irrecv.enableIRIn(); // Initialize the IR.
pinMode(MotorA, OUTPUT); // Pin Motor A set as output.
pinMode(MotorB, OUTPUT); // Pin Motor B set as output.
pinMode(PWMA, OUTPUT); // Pin PWMA set as output.
pinMode(PWMB, OUTPUT); // Pin PWMB set as output.
pinMode(3, OUTPUT); // Pin 3 set as output.
Serial.begin(9600); // Initialize the serial monitor.
myservo.attach(10); // Sets the pin of the servo motor.
}

void loop() { // This program will run forever:
if (irrecv.decode(&results)){ // this is to configure the buttons of the IR
  // The serial monitor will print the value of every button we press in HEX.
  Serial.print("HEX=");
  Serial.println(results.value, HEX);
      if(results.value == 0xFFFFFFFF){ // If we hold any button, it will run the code that was assigned to it.
            results.value = lastCode; 
       }
      if(results.value == 0xFF7A85){ // The button "3" (FF7A85 in HEX) has the action of changing the speed to the half.
          Speed=127; 
       }   
      if(results.value == 0xFF10EF){ // The button "4" (FF10EF in HEX) has the action of changing the speed to its maximum.
          Speed=255; 
       }      
        if(results.value == 0xFF629D){ // The button "VOL+" (FF629D in HEX) has the action of moving the car forward.
          forward(Speed);
       }
       if(results.value == 0xFFA857){ // The button "VOL-" (FFA857 in HEX) has the action of moving the car backward.
          backward(Speed);
       }
       if(results.value == 0xFFC23D){ // The button ">>|" (FFC23D in HEX) has the action of turning the car to the right.
          right(Speed);  
       }
       if(results.value == 0xFF22DD){ // The button "|<<" (FF22DD in HEX) has the action of turning the car to the left.
          left(Speed);
       }
       if(results.value == 0xFF02FD){ // The button ">||" (FF02FD in HEX) has the action of stopping the car.
          Stop();  
       }
       if(results.value == 0xFF30CF){ // The button "1" (FF30CF) has the action of putting the car in line tracker mode.
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
       if(results.value == 0xFF18E7){ // The button "2" (FF18E7) has the action of putting the car in obstacle avoiding mode.
         int distance = sonar.ping_cm(); // Stores the distance's value.
          if (distance < 20) {
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
            } else if (( Distance_left<20 || Distance_right<20 )){
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
     irrecv.resume(); // Resumes the IR.
}
}

void forward(int x){ // Function to called "forward".
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
void left(int x){ // Function called "left".
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
void right(int x){ // Function called "right".
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
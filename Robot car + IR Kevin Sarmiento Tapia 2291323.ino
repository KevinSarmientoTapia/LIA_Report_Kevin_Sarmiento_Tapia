/*
  Robot car + IR

  The program's goal is to control the car by using an IR (Infrared Remote).

  The program's theme is to include the library "<IRemote.h>" to configure the IR.
*/
#include <IRremote.h> // Includes the library "<IRemote.h>"" to configure the IR. 
 
const int RECV_PIN = 9; // Define sensor pin.
 
IRrecv irrecv(RECV_PIN); // Define IR Receiver and Results Objects.
decode_results results;

unsigned long lastCode; // Stores the value of the last code.
int MotorA=7; // Motor A of the car connected to pin 7.
int MotorB=8; // Motor B of the car connected to pin 8.
int PWMA=5; // PWMA (Pulse With Modulation A) connected to pin 5 .
int PWMB=6; // PWMB (Pulse With Modulation B) connected to pin 6.
int Speed=255; // Stores the values of the speed, inicially it is 255 (Max speed).

void setup() { // This program will run once:
irrecv.enableIRIn(); // Initialize the IR.
pinMode(MotorA, OUTPUT); // Pin Motor A set as output.
pinMode(MotorB, OUTPUT); // Pin Motor B set as output.
pinMode(PWMA, OUTPUT); // Pin PWMA set as output.
pinMode(PWMB, OUTPUT); // Pin PWMB set as output.
pinMode(3, OUTPUT); // Pin 3 set as output.
Serial.begin(9600); // Initialize the serial monitor.
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
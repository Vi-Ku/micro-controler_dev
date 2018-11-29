#include <Wire.h>
struct motorControl {
  byte right_front_speed;
  byte right_front_dir;
  byte right_middle_speed;
  byte right_middle_dir;
  byte right_rear_speed;
  byte right_rear_dir;

  byte left_front_speed;
  byte left_front_dir;
  byte left_middle_speed;
  byte left_middle_dir;
  byte left_rear_speed;
  byte left_rear_dir;
};

//this struct is used to communicate back to the jetson
//the actual state of the motors
//for each wheel we will send, its actual speed, 
//amps, and any error state
struct motorFeedback {
  byte right_front_speed;
  byte right_front_amps;
  byte right_front_error;
  
  byte right_middle_speed;
  byte right_middle_amps;
  byte right_middle_error;
  
  byte right_rear_speed;
  byte right_rear_amps;
  byte right_rear_error;

  byte left_front_speed;
  byte left_front_amps;
  byte left_front_error;

  byte left_middle_speed;
  byte left_middle_amps;
  byte left_middle_error;

  byte left_rear_speed;
  byte left_rear_amps;
  byte left_rear_error;
};

//init a struct for the bytes to control the motor
struct motorControl motorCommands = {0,0,0,0,0,0,0,0,0,0,0,0};

//struct to contain feedback of motor
struct motorFeedback feedback = {97,98,99,100,101,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(1000);
  //print status of right motors
  Serial.print(motorCommands.right_front_speed);
  Serial.print(' ');
  Serial.print(motorCommands.right_front_dir);
  Serial.print(' ');
  Serial.print(motorCommands.right_middle_speed);
  Serial.print(' ');
  Serial.print(motorCommands.right_middle_dir);
  Serial.print(' ');
  Serial.print(motorCommands.right_rear_speed);
  Serial.print(' ');
  Serial.print(motorCommands.right_rear_dir);
  Serial.print(' ');

  //print status of left motors
  Serial.print(motorCommands.left_front_speed);
  Serial.print(' ');
  Serial.print(motorCommands.left_front_dir);
  Serial.print(' ');
  Serial.print(motorCommands.left_middle_speed);
  Serial.print(' ');
  Serial.print(motorCommands.left_middle_dir);
  Serial.print(' ');
  Serial.print(motorCommands.left_rear_speed);
  Serial.print(' ');
  Serial.print(motorCommands.left_rear_dir);
  Serial.print('\n');
}

//function that is called when the jetson reads bytes
//here is where we will send it the feedback
void requestEvent() {
  Wire.write(feedback.right_front_speed);
  Wire.write(feedback.right_front_amps);
  Wire.write(feedback.right_front_error);

  Wire.write(feedback.right_middle_speed);
  Wire.write(feedback.right_middle_amps);
  Wire.write(feedback.right_middle_error);

  Wire.write(feedback.right_rear_speed);
  Wire.write(feedback.right_rear_amps);
  Wire.write(feedback.right_rear_error);

  Wire.write(feedback.left_front_speed);
  Wire.write(feedback.left_front_amps);
  Wire.write(feedback.left_front_error);

  Wire.write(feedback.left_middle_speed);
  Wire.write(feedback.left_middle_amps);
  Wire.write(feedback.left_middle_error);

  Wire.write(feedback.left_rear_speed);
  Wire.write(feedback.left_rear_amps);
  Wire.write(feedback.left_rear_error);
}

void receiveEvent(int howMany) {
  //the python i2c library has a preammble byte that we can set
  //as of the time of this writing it is set to 0
  
  for (int index = 0; Wire.available(); index++) {//if we have a message   
    byte c = Wire.read(); // receive byte as a character    
    //Serial.print(c);    
    //Serial.print(' ');

    switch (index) {//switch which byte we are extracting
      case 1:
        motorCommands.right_front_speed = c;
      break;

      case 2:
        motorCommands.right_front_dir = c;
      break;

      case 3:
        motorCommands.right_middle_speed = c;
      break;

      case 4:
        motorCommands.right_middle_dir = c;
      break;

      case 5:
        motorCommands.right_rear_speed = c;
      break;

      case 6:
        motorCommands.right_rear_dir = c;
      break;

      case 7:
        motorCommands.left_front_speed = c;
      break;

      case 8:
        motorCommands.left_front_dir = c;
      break;

      case 9:
        motorCommands.left_middle_speed = c;
      break;

      case 10:
        motorCommands.left_middle_dir = c;
      break;

      case 11:
        motorCommands.left_rear_speed = c;
      break;

      case 12:
        motorCommands.left_rear_dir = c;
      break;
    }
  } 
  //Serial.print('\n');
}

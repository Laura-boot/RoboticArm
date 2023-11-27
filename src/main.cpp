/*************************************************************
 * Line Follower Robot with Attached Arm
 * 
 * The robot will always move on the line. If it goes off the track, it will remain stationary.
 * If the 'esp' receives data from the load/unload sensor, it will remain stationary for a while.
 * In the latter case, the robotic arm should function while the car is stationary.
*************************************************************/

// Include the motor control library into the code
#include <RoboCore_Vespa.h>

VespaMotors motors;

/*************************************************************
 * Variables for the line-following car
*************************************************************/

#define LEFT_SENSOR 36
#define RIGHT_SENSOR 39

int left_reading = 0; // Readings from line sensors
int right_reading = 0;

#define CUTOFF_VALUE 3000  // Cutoff value for sensor readings
#define SPEED 90     // Straight-line speed of the robot
#define SPEED_ADDITION 10 // Value added to the motor rotation speed
#define SPEED_SUBTRACTION 70 // Value subtracted from the motor rotation speed
#define MAX_STOP_COUNT 10000 // Maximum stop count value
int stop_counter = 0; // Counter to stop the robot if it deviates from the track

/*************************************************************
 * Variables for the car's positioning
*************************************************************/

int load_reading = 0; // Readings from load and unload sensors

/*************************************************************
 * Variables for the robotic arm
*************************************************************/

void setup() {
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
}

void loop() {

  // Read line sensors
  left_reading = analogRead(LEFT_SENSOR);
  right_reading = analogRead(RIGHT_SENSOR);
  // Read positioning sensors
  // load_reading = information from another 'esp' in the load sector
  // unload_reading = information from another 'esp' in the unload sector

  // if(load_reading != 0) {motors.stop(); Arm(ArmState::LOAD));}
  // else if(unload_reading != 0) {motors.stop(); Arm(ArmState::UNLOAD));}

  if((left_reading > CUTOFF_VALUE) && (right_reading > CUTOFF_VALUE)) {
    // Move the robot forward
    motors.forward(SPEED);
    stop_counter = 0; // Reset stop counter
  }
  else if((left_reading < CUTOFF_VALUE) && (right_reading < CUTOFF_VALUE)){
    stop_counter++; // Increment stop counter
  }
  else if(right_reading > CUTOFF_VALUE) {
    // Rotate the robot left by adjusting motor speeds
    motors.turn(SPEED+SPEED_ADDITION, SPEED-SPEED_SUBTRACTION);
    stop_counter = 0; // Reset stop counter
  }
  else if(left_reading > CUTOFF_VALUE) {
    // Rotate the robot right by adjusting motor speeds
    motors.turn(SPEED-SPEED_SUBTRACTION, SPEED+SPEED_ADDITION);
    stop_counter = 0; // Reset stop counter
  }
  
  if(stop_counter >= MAX_STOP_COUNT){
    motors.stop(); // Stop the robot
    stop_counter = MAX_STOP_COUNT; // Set stop count
  }

  // Delay execution to control the code sensitivity
  delay(0); // Lowering this value decreases the robot's sensitivity
  
}

enum class ArmState {
  LOAD,
  UNLOAD
};

// Define arm function that receives the input 'load' or 'unload'
void Arm(ArmState state){
  switch (state) {
    case ArmState::LOAD: {
      // Functionality for load state
      break;
    }
    case ArmState::UNLOAD: {
      // Functionality for unload state
      break;
    }
  }
}

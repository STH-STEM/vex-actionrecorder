// Drivetrain Action Recorder by Seb Jensen
// (HEAP size increased to 8 MB)

#include "vex.h" // VEX Header File
using namespace vex; // VEX Namespace

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2            
// ---- END VEXCODE CONFIGURED DEVICES ----

float multiplier; // Declaring multiplier for use in Action Recorder (to enable shift buttons)
int lineCount = 0; // Declaring lineCount for use in Action Recorder (to start a new column)
bool nextColumn = false; // Declaring nextColumn for use in Action Recorder (to start a new column)

void actionRecorder(std::string action){ // Action Recorder
  if(Controller1.ButtonR1.pressing()){ // On R1 press
    multiplier = 0.5; // Set multiplier to 0.5 (precise)
  }
  else if(Controller1.ButtonR2.pressing()){ // On R2 press
    multiplier = 0.25; // Set multiplier to 0.25 (more precise)
  }
  else if(Controller1.ButtonL1.pressing()){ // On L1 press
    multiplier = 2; // Set multiplier to 2 (unprecise)
  }
  else if(Controller1.ButtonL2.pressing()){ // On L2 press
    multiplier = 4; // Set multiplier to 4 (more unprecise)
  }
  else{ // Otherwise
    multiplier = 1; // Default multiplier to 1 (general)
  }

  if(lineCount == 12){ // If rows maxed
    if(nextColumn == true){ // And second column maxed
      Controller1.Screen.print("[!] Actions Full"); // Tell user to stop
    }
    else{ // Otherwise
      nextColumn = true; // Go to second column
      lineCount = 0; // And reset lineCount
    }
  }

  if(action == "clear"){ // Clears screen
    Brain.Screen.clearScreen();
    nextColumn = false;
    lineCount = 0;
  }
  if(action == "fwd"){
    lineCount++; // Set up printing
    if(nextColumn == false){
      Brain.Screen.setCursor(lineCount, 1);
    }
    else{
      Brain.Screen.setCursor(lineCount, 25);
    }
    Drivetrain.driveFor(forward, 1 * multiplier, inches); // Do action
    Brain.Screen.print("Forward %2.2f inch/es", 1 * multiplier); // Record action
  }
  else if(action == "rev"){
    lineCount++; // Set up printing
    if(nextColumn == false){
      Brain.Screen.setCursor(lineCount, 1);
    }
    else{
      Brain.Screen.setCursor(lineCount, 25);
    }
    Drivetrain.driveFor(reverse, 1 * multiplier, inches); // Do action
    Brain.Screen.print("Reverse %2.2f inch/es", 1 * multiplier); // Record action
  }
  else if(action == "left"){
    lineCount++; // Set up printing
    if(nextColumn == false){
      Brain.Screen.setCursor(lineCount, 1);
    }
    else{
      Brain.Screen.setCursor(lineCount, 25);
    }
    Drivetrain.turnFor(left, 22.5 * multiplier, degrees); // Do action
    Brain.Screen.print("Left %2.2f degrees", 22.5 * multiplier); // Record action
  }
  else if(action == "right"){
    lineCount++; // Set up printing
    if(nextColumn == false){
      Brain.Screen.setCursor(lineCount, 1);
    }
    else{
      Brain.Screen.setCursor(lineCount, 25);
    }
    Drivetrain.turnFor(right, 22.5 * multiplier, degrees); // Do action
    Brain.Screen.print("Right %2.2f degrees", 22.5 * multiplier); // Record action
  }
}

int main() { // Main setup
  vexcodeInit(); // VEXcode Setup
  
  while(1 == 1){ // Main loop
    if(Controller1.ButtonUp.pressing()){ // Forward
      actionRecorder("fwd");
      wait(0.25, seconds); // Delay to prevent action spam
    }
    if(Controller1.ButtonDown.pressing()){ // Reverse
      actionRecorder("rev");
      wait(0.25, seconds); // Delay to prevent action spam
    }
    if(Controller1.ButtonLeft.pressing()){ // Left
      actionRecorder("left");
      wait(0.25, seconds); // Delay to prevent action spam
    }
    if(Controller1.ButtonRight.pressing()){ // Right
      actionRecorder("right");
      wait(0.25, seconds); // Delay to prevent action spam
    }
    if(Controller1.ButtonB.pressing()){ // Right
      actionRecorder("clear");
      wait(0.25, seconds); // Delay to prevent action spam
    }
    wait(0.050, seconds); // Delay to save resources
  }
}

#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
// AI Vision Color Descriptions
// AI Vision Code Descriptions
vex::aivision AIVision5(PORT5, aivision::ALL_TAGS);

motor RightWheel = motor(PORT1, ratio18_1, false);

motor LeftWheel = motor(PORT2, ratio18_1, false);

motor LazySusan = motor(PORT3, ratio6_1, false);

motor Lift = motor(PORT13, ratio18_1, false);



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration
#pragma region VEXcode Generated Robot Configuration

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vex.h"

using namespace vex;


#define waitUntil(condition) \
do { \
  wait(5, msec); \
} while (!(condition))

#define repeat(iterations) \
for (int iterator = 0; iterator < iterations; iterator++)




#pragma endregion


controller Controller1 = controller(primary);


// Stop both motors
void stopDrive() {
    RightWheel.stop(brake);
    LeftWheel.stop(brake);
}


// Drive forward at a specific speed
void driveForward(double speed) {
    RightWheel.setVelocity(speed + 10, percent);
    LeftWheel.setVelocity(-speed, percent);

    RightWheel.spin(forward);
    LeftWheel.spin(forward);
}


// Turn right
void turnRight(double speed) {
    RightWheel.setVelocity(speed, percent);
    LeftWheel.setVelocity(-speed, percent);

    RightWheel.spin(reverse);
    LeftWheel.spin(forward);
}


// Turn left
void turnLeft(double speed) {
    RightWheel.setVelocity(speed, percent);
    LeftWheel.setVelocity(-speed, percent);

    RightWheel.spin(forward);
    LeftWheel.spin(reverse);
}


// AprilTag autonomous movement
void autonomousAprilTag() {

    AIVision5.takeSnapshot(aivision::ALL_TAGS);

    bool tagFound = false;
    int tagX = 0;
    int tagWidth = 0;

    // Look for AprilTags
    for (int i = 0; i < AIVision5.objectCount; i++) {

        if (AIVision5.objects[i].id == 8 ||
            AIVision5.objects[i].id == 0 ||
            AIVision5.objects[i].id == 2 ||
            AIVision5.objects[i].id == 6) {

            tagX = AIVision5.objects[i].originX;
            tagWidth = AIVision5.objects[i].width;

            tagFound = true;
            break;
        }
    }


    // Stop if no tag is detected
    if (!tagFound) {
        stopDrive();
        return;
    }


    // Tag is to the right
    if (tagX > 175) {

        RightWheel.setVelocity(30, percent);
        LeftWheel.setVelocity(40, percent);

        RightWheel.spin(reverse);
        LeftWheel.spin(reverse);
    }


    // Tag is to the left
    else if (tagX < 150) {

        RightWheel.setVelocity(40, percent);
        LeftWheel.setVelocity(30, percent);

        RightWheel.spin(forward);
        LeftWheel.spin(forward);
    }


    // Tag is centered
    else {

        // Approach the tag
        if (tagWidth < 90) {

            RightWheel.setVelocity(65, percent);
            LeftWheel.setVelocity(-65, percent);

            RightWheel.spin(forward);
            LeftWheel.spin(forward);
        }

        // Stop when close enough
        else {
            stopDrive();
        }
    }
}


int main() {

    vexcodeInit();

    bool autoRunning = false;
    bool xWasPressed = false;
    bool bWasPressed = false;

    while (true) {

        // A button stops everything
        if (Controller1.ButtonA.pressing()) {

            autoRunning = false;
            stopDrive();
        }

        else {

            // ==========================================
            // X BUTTON
            // Drive forward -> turn RIGHT -> AprilTags
            // ==========================================

            if (Controller1.ButtonX.pressing() && !xWasPressed) {

                autoRunning = true;

                // Drive forward at 60% for 2.5 seconds
                driveForward(60);

                wait(2.5, seconds);


                // Turn RIGHT at 50% for 1.1 seconds
                turnRight(50);

                wait(1.1, seconds);

                driveForward(40);

                wait(0.5, seconds);


                stopDrive();

                // autoRunning stays TRUE
            }
 if (Controller1.ButtonY.pressing() && !xWasPressed) {

                autoRunning = true;

                // Drive forward at 60% for 6 seconds
                driveForward(60);

                wait(6, seconds);


                // Turn RIGHT at 50% for 1.1 seconds
                turnRight(90);

                wait(1.25, seconds);

                driveForward(40);

                wait(1, seconds);


                stopDrive();

                // autoRunning stays TRUE
            }


            // ==========================================
            // B BUTTON
            // Drive forward -> turn LEFT -> AprilTags
            // ==========================================

            if (Controller1.ButtonB.pressing() && !bWasPressed) {

                autoRunning = true;

                
                // Drive forward at 60% for 2.5 seconds
                driveForward(60);

                wait(2.75, seconds);


                // Turn RIGHT at 50% for 1.1 seconds
                turnLeft(50);

                wait(1.1, seconds);

                driveForward(40);

                wait(0.5, seconds);


                stopDrive();

                // autoRunning stays TRUE
            }


            //Lazy Susan Controls may want to use potentiometer for precision later
            if (Controller1.ButtonL1.pressing())
            {

            LazySusan.setVelocity(100,percent);  //Spin lazy susan one way
            LazySusan.spin(forward);
            }
            else if(Controller1.ButtonL2.pressing()) {

            LazySusan.setVelocity(100,percent);  //Spin lazy susan the other way
            LazySusan.spin(reverse);

            }
            else
            {
              LazySusan.stop(); //Nothing being pressed, dont move
            }

            //Lift Controls
            if (Controller1.ButtonR1.pressing())
            {

            Lift.setVelocity(100,percent);  //Lift up 
            Lift.spin(forward);
            }
            else if(Controller1.ButtonR2.pressing()) {

            Lift.setVelocity(100,percent);   //Lift down
            Lift.spin(reverse);

            }
            else
            {
              Lift.stop();  //Lift stopped
            }


     

            if (autoRunning) {
                autonomousAprilTag();
            }


           
            else {

                double rightSpeed =
                    Controller1.Axis3.position() -
                    Controller1.Axis4.position();

                double leftSpeed =
                    -Controller1.Axis3.position() -
                    Controller1.Axis4.position();

                RightWheel.setVelocity(rightSpeed, percent);
                LeftWheel.setVelocity(leftSpeed, percent);

                RightWheel.spin(forward);
                LeftWheel.spin(forward);
            }
        }


        // Remember button states
        xWasPressed = Controller1.ButtonX.pressing();
        bWasPressed = Controller1.ButtonB.pressing();

        wait(20, msec);
    }
}

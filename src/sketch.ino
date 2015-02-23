/* Libraries {{{ */

#include <math.h>

#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

/* }}} */
/* Pin Setup {{{ */

/* Stepper Pin Setup */
const byte DIR_PIN = 2;
const byte STEP_PIN = 3;
const byte SLEEP_PIN = 9;

/* Joystick Setup */
const byte JOYSTICK_X_PIN = 0; // Analog 0
const byte JOYSTICK_Y_PIN = 1; // Analog 1
const byte JOYSTICK_SELECT_PIN = 10; // Digital 10

/* LCD Setup */
LiquidCrystal lcd(0);

/* Camera Setup */
const byte SHUTTER_PIN = 7;
const byte FLASH_IN_PIN = 5;

/* Switch Setup */
const byte MOTOR_SWITCH_PIN = 4;
const byte END_SWITCH_PIN = 6;

/* }}} */
/* Global Variables {{{ */

/* Joystick Constants {{{ */

const byte LEFT = 1;
const byte RIGHT = 2;
const byte UP = 3;
const byte DOWN = 4;
const byte NONE = 0;

/* }}} */
/* Easing curves {{{ */

const byte LINEAR = 1;
const byte EASEIN = 2;
const byte EASEOUT = 3;
const byte FASTSLOWFAST = 4;
const byte SLOWFASTSLOW = 5;

/* }}} */
/* Menu Strings {{{ */

char holdSelToExit[17] = "Hold Sel to Exit";
char utilityString[17] = "";

/* Main Menu Strings {{{ */

const char selectModeString[17] = "Select Mode:    ";
const char timelapseStringSelected[17] = "1.Timelapse    >";
const char realtimeStringSelected[17] = "2.Realtime     >";
const char commandStringSelected[17] = "3.Commander    >";
const char directionStringSelected[17] = "4.Direction    >";
const char debugStringSelected[17] = "5.Debug        >";

/* }}} */
/* Timelapse Menu Strings {{{ */

char enteringTimelapseModeLineOne[17] = ">>> Timelapse   ";
/* char timelapseModeTrackLenLineOne[17] = "Find Track Len.."; */
char timelapseModeNumShotsLineOne[17] = "Number of Shots:";
char timelapseModeDurationLineOne[17] = "TL Duration:    ";
char timelapseModeIntervalLineOne[17] = "Avg Interval:   ";
char timelapseModeDelayLineOne[17] = "Start Delay:    ";
char timelapseModeLongestShutterLineOne[17] = "Longest Shutter:";
char timelapseModeSleepBetweenShotsLineOne[17] = "Sleep btw shots ";
char timelapseModeLCDLineOne[17] = "Backlight on?:  ";
char timelapseModeEasingCurveLineOne[17] = "Slide Ease Curv:";
char timelapseModeTimeEasingFunctionLineOne[17] = "Time Ease Func: ";
char timelapseModeTimeEasingCurveLineOne[17] = "Time Curve Func:";
char timelapseModeDirectionLineOne[17] = "Movement Dir:   ";
char timelapseModeDirectionLineTwoME[17] = "Motor -----> End";
char timelapseModeDirectionLineTwoEM[17] = "End -----> Motor";
char timelapseModeRunningTimelapseLineOne[17] = "Timelapse active";
char timelapseModeCompletedLineOne[17] = "Timelapse Done  ";

/* }}} */
/* Commander Menu Strings {{{ */

char enteringCommandModeLineOne[17] = ">>> Commander   ";
char commandModeLineOne[17] = "  Command Mode  ";
char commandModeLineTwoMotorToEnd[17] = "Motor <----> End";
char commandModeLineTwoEndToMotor[17] = "End <----> Motor";
char commandModeLineTwoChangingDirection[17] = "Reversing Dir <>";

/* }}} */
/* Direction Menu Strings ---------------------------------------- {{{ */

char enteringDirectionModeLineOne[17] = ">>> Direction   ";
char directionModeLineOne[17] = "Set EEPROM Dir: ";

/* }}} */
/* Status Menu Strings {{{ */

char enteringDebugModeLineOne[17] = ">>> Debug Mode  ";
char debugLineOne[17] = "";
char debugLineTwo[17] = "";
char switchOpen[2] = "O";
char switchPressed[2] = "P";
char switchError[2] = "X";

/* }}} */
/* Error Strings {{{ */

char genericErrorLineOne[17] = ">>> ERROR       ";
char genericErrorLineTwo[17] = "Returning Home  ";

/* }}} */
/* Realtime Menu Strings ---------------------------------------- {{{ */

char enteringRealtimeModeLineOne[17] = ">>>Realtime Mode";
char realtimeModeMinSpeedLineOne[17] = "Move Min Speed: ";
char realtimeModeMaxSpeedLineOne[17] = "Move Max Speed: ";
char realtimeModeEasingCurveLineOne[17] = "RT Ease Curve:  ";
char realtimeModeCompletedLineOne[17] = "Move Complete!  ";

/* }}} */

/* }}} */
/* EEPROM -------------------------------------------------- {{{ */

byte EEPROM_DIRECTION_LOC = 1;
byte EEPROM_DIRECTION = 1;

/* }}} */

/* }}} */
/* Joystick Functions {{{ */

/* readJoystick -------------------------------------------------- {{{ */

byte readJoystick(int buttonDelay){
    if (analogRead(JOYSTICK_X_PIN) > 600 ){
        delay(buttonDelay);
        if (analogRead(JOYSTICK_X_PIN) > 600){
            return RIGHT;
        } else {
            return NONE;
        }
    } else if (analogRead(JOYSTICK_X_PIN) < 400){
        delay(buttonDelay);
        if (analogRead(JOYSTICK_X_PIN) < 400){
            return LEFT;
        } else {
            return NONE;
        }
    } else if (analogRead(JOYSTICK_Y_PIN) > 600){
        delay(buttonDelay);
        if (analogRead(JOYSTICK_Y_PIN) > 600){
            return UP;
        } else {
            return NONE;
        }
    } else if (analogRead(JOYSTICK_Y_PIN) < 400){
        delay(buttonDelay);
        if (analogRead(JOYSTICK_Y_PIN) < 400){
            return DOWN;
        } else {
            return NONE;
        }
    } else {
        return NONE;
    }
}

/* }}} */

/* }}} */
/* Bezier Functions -------------------------------------------------- {{{ */

double easeAmount = 1.5;

double calculateCoefficient(int currentStep, int totalSteps, unsigned long trackLen, double exponent){
    double coefficient = trackLen / (pow(totalSteps, exponent));
    return coefficient * (pow(currentStep, exponent));
}

double calculateCoefficientStep(int currentStep, int totalSteps, unsigned long trackLen, double exponent){
    return calculateCoefficient(currentStep, totalSteps, trackLen, exponent) - calculateCoefficient(currentStep - 1, totalSteps, trackLen, exponent);
}

double preciseEaseInStep(int currentStep, int totalSteps, unsigned long len) {
    return calculateCoefficient(currentStep, totalSteps, len, easeAmount);
}

int easeInStep(int currentStep, int totalSteps, unsigned long trackLen){
    return round(calculateCoefficientStep(currentStep, totalSteps, trackLen, easeAmount));
}

double reverseCalculateCoefficient(int currentStep, int totalSteps, unsigned long trackLen, double exponent){
    double coefficient = -1 * (double(trackLen) / pow(double(totalSteps), exponent));
    return coefficient * pow(currentStep - totalSteps, exponent) + trackLen;
}

double reverseCalculateCoefficientStep(int currentStep, int totalSteps, unsigned long trackLen, double exponent) {
    return reverseCalculateCoefficient(currentStep, totalSteps, trackLen, exponent) - reverseCalculateCoefficient(currentStep - 1, totalSteps, trackLen, exponent);
}

double preciseEaseOutStep(int currentStep, int totalSteps, unsigned long len){
    return reverseCalculateCoefficient(currentStep, totalSteps, len, easeAmount);
}

int easeOutStep(int currentStep, int totalSteps, unsigned long trackLen){
    return round(reverseCalculateCoefficientStep(currentStep, totalSteps, trackLen, easeAmount));
}

double cubicBezier(int currentStep, int totalSteps, unsigned long trackLen, double control1Percent, double control2Percent){
    double t = (totalSteps - currentStep) / double(totalSteps);
    double b1 = t * t * t;
    double b2 = 3 * t * t * (1 - t);
    double b3 = 3 * t * (1 - t) * (1 - t);
    double b4 = (1 - t) * (1 - t) * (1 - t);
    double controlPoint1 = control1Percent * trackLen;
    double controlPoint2 = control2Percent * trackLen;
    return 0 * b1 + controlPoint1 * b2 + controlPoint2 * b3 + double(trackLen) * b4;
}

double cubicBezierStep(int currentStep, int totalSteps, unsigned long trackLen, double control1Percent, double control2Percent){
    return cubicBezier(currentStep, totalSteps, trackLen, control1Percent, control2Percent) - cubicBezier(currentStep - 1, totalSteps, trackLen, control1Percent, control2Percent);
}

double preciseSlowFastSlowStep(int currentStep, int totalSteps, unsigned long len){
    return cubicBezierStep(currentStep, totalSteps, len, 0.0, 1.0);
}

int slowFastSlowStep(int currentStep, int totalSteps, unsigned long trackLen){
    return round(cubicBezierStep(currentStep, totalSteps, trackLen, 0.0, 1.0));
}

double preciseFastSlowFastStep(int currentStep, int totalSteps, unsigned long len){
    return cubicBezierStep(currentStep, totalSteps, len, 1.0, 0.0);
}

int fastSlowFastStep(int currentStep, int totalSteps, unsigned long trackLen){
    return round(cubicBezierStep(currentStep, totalSteps, trackLen, 1.0, 0.0));
}

/* }}} */
/* Timelapse Functions {{{ */

/* rotate {{{ */
void rotate(int steps, byte speed){
    byte dir = (steps > 0)? HIGH:LOW;
    steps = abs(steps);
    digitalWrite(DIR_PIN, dir);
    // Not sure why * 70
    float floatSpeed = float(speed);
    float usDelay = (1 / (floatSpeed / 100)) * 70;

    for(int i = 0; i < steps; i++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
    }
}
/* }}} */
/* dampRotate -------------------------------------------------- {{{ */

void dampRotate(int steps) {
    byte dir = (steps > 0)? HIGH:LOW;
    steps = abs(steps);
    digitalWrite(DIR_PIN, dir);


    unsigned int dampDelay = 5000;
    unsigned int normalDelay = 3000;

    unsigned int dampSteps = 20;
    unsigned int dampChange = (dampDelay - normalDelay) / dampSteps;

    //Compensate if steps are less than dampSteps * 2
    if (steps < dampSteps * 2){
        dampSteps = steps / 2;
    }

    //Begin Rotate Slow to Fast
    for (int j = 0; j < dampSteps; j++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(dampDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(dampDelay);
        dampDelay -= dampChange;
    }

    // Full Speed rotations (7000)
    // 7000 corresponds to feeding 1 to rotate speed
    int fullSpeedSteps = steps - dampSteps * 2;
    for (int k = 0; k < fullSpeedSteps; k++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(normalDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(normalDelay);
    }

    // End Rotate Fast to Slow
    dampDelay = normalDelay;

    // Compensate for int division
    if (steps < dampSteps * 2 && dampSteps % 2 != 0){
        dampSteps += 1;
    }

    for (int j = 0; j < dampSteps; j++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(dampDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(dampDelay);
        dampDelay += dampChange;
    }
}

/* }}} */
/* sleepOn -------------------------------------------------- {{{ */

void sleepOn(){
    digitalWrite(SLEEP_PIN, HIGH);
}

/* }}} */
/* sleepOff -------------------------------------------------- {{{ */

void sleepOff(){
    digitalWrite(SLEEP_PIN, LOW);
    delay(5); // Recommended by Easy Driver manual
}

/* }}} */
/* findTrackLen {{{ */
void findTrackLen(){
    unsigned long maxTrackLen = 0;
    unsigned long currentTrackLen = 0;
    int direction = 1;
    /* lcdPrint(timelapseModeTrackLenLineOne, timelapseModeTrackLenLineTwo); */
    while(selectTrigger(2000)){
        if(digitalRead(MOTOR_SWITCH_PIN) != HIGH && digitalRead(END_SWITCH_PIN) != HIGH){
            rotate(direction, 25);
            currentTrackLen += 1;
            if (currentTrackLen > maxTrackLen){
                maxTrackLen = currentTrackLen;
            }
        } else if (digitalRead(MOTOR_SWITCH_PIN) == HIGH) {
            direction = 1;
            rotate(direction, 25);
            currentTrackLen = 0;
            /* sprintf(timelapseModeTrackLenLineTwo, "Max Len:%05ld   ", maxTrackLen); */
            /* lcdPrint(timelapseModeTrackLenLineOne, timelapseModeTrackLenLineTwo); */
        } else if (digitalRead(END_SWITCH_PIN) == HIGH){
            direction = -1;
            rotate(direction, 25);
            currentTrackLen = 0;
            /* sprintf(timelapseModeTrackLenLineTwo, "Max Len:%05ld   ", maxTrackLen); */
            /* lcdPrint(timelapseModeTrackLenLineOne, timelapseModeTrackLenLineTwo); */
        }
    }
}
/* }}} */
/* commanderMode {{{ */
void commanderMode(){
    byte currentSpeed = 20;
    lcdPrint(commandModeLineOne, commandModeLineTwoMotorToEnd);
    int direction = 1; // Odd is motor to end, Even is end to motor
    if (EEPROM_DIRECTION == 2){
        direction += 1;
    }
    while (selectTrigger(1000)){
        int xpos = analogRead(JOYSTICK_X_PIN);
        int ypos = analogRead(JOYSTICK_Y_PIN);
        if (ypos == 0){
            delay(500);
            if (analogRead(JOYSTICK_Y_PIN) == 0){ // Joystick down
                //Swap directions
                direction += 1;
                //Reprint lcd
                if (direction % 2 == 1){
                    lcdPrint(commandModeLineOne, commandModeLineTwoChangingDirection);
                    delay(1000);
                    lcdPrint(commandModeLineOne, commandModeLineTwoMotorToEnd);
                } else if (direction % 2 == 0){
                    lcdPrint(commandModeLineOne, commandModeLineTwoChangingDirection);
                    delay(1000);
                    lcdPrint(commandModeLineOne, commandModeLineTwoEndToMotor);
                }
            }
        }
        if (ypos == 1023){
            delay(300);
            if (analogRead(JOYSTICK_Y_PIN) == 1023){ // Joystick Up
                // Increase Speed
                currentSpeed += 10;
                //Reprint lcd
                currentSpeed = reflow(currentSpeed, 1, 100);
                sprintf(utilityString, "Speed: %02d       ", currentSpeed);
                lcdPrint(commandModeLineOne, utilityString);
            } else {
                if (direction % 2 == 1){
                    delay(1000);
                    lcdPrint(commandModeLineOne, commandModeLineTwoMotorToEnd);
                } else if (direction % 2 == 0){
                    delay(1000);
                    lcdPrint(commandModeLineOne, commandModeLineTwoEndToMotor);
                }
            }
        }
        if (xpos > 523){
            if (direction % 2 == 1) {
                 // Motor to end
                if (digitalRead(END_SWITCH_PIN) != HIGH){
                    rotate(1, calcSpeed(xpos - 523, 500, currentSpeed));
                }
            } else if (direction % 2 == 0){
                //End to motor
                if (digitalRead(MOTOR_SWITCH_PIN) != HIGH){
                    rotate(-1, calcSpeed(xpos - 523, 500, currentSpeed));
                }
            }
        } else if (xpos < 500){
            if (direction % 2 == 1){
                // Motor to end
                if (digitalRead(MOTOR_SWITCH_PIN) != HIGH){
                    rotate(-1, calcSpeed(abs(500 - xpos), 500, currentSpeed));
                }
            } else if (direction % 2 == 0){
                // End to Motor
                if (digitalRead(END_SWITCH_PIN) != HIGH){
                    rotate(1, calcSpeed(abs(500 - xpos), 500, currentSpeed));
                }
            }
        }
    }
}
/* calcSpeed {{{ */

byte calcSpeed(int input, int maxInput, byte maxOutput){
    //returns a byte proportional to the input / max
    return (maxOutput * input) / maxInput;
}

/* }}} */
/* }}} End commanderMode */
/* Joystick Helper Functions {{{ */
int joystickX(){
    return analogRead(JOYSTICK_X_PIN);
}

int joystickY(){
    return analogRead(JOYSTICK_Y_PIN);
}

bool select(){
    return !digitalRead(JOYSTICK_SELECT_PIN);
}

bool xHigh(){
    if (joystickX() > 1000){
        return true;
    } else {
        return false;
    }
}

bool xLow(){
    if (joystickX() < 50){
        return true;
    } else {
        return false;
    }
}

bool yHigh(){
    if (joystickY() > 1000){
        return true;
    }
    return false;
}

bool yLow(){
    if (joystickY() < 50){
        return true;
    }
    return false;
}
/* }}} */
/* Timelapse Menu Global Variables -------------------------------- {{{ */

byte timelapseMenuLocation = 1;
byte timelapseMenuMax = 12;
byte timelapseMenuMin = 1;
unsigned int trackLen = 34800;
int numShots = 240;
int maxShots = 9999;
int minShots = 5;
unsigned int maxShutter = 1000;
unsigned int minMaxShutter = 100;
unsigned int maxMaxShutter = 31000;
unsigned long minDelay = 1; // Seconds
unsigned long maxDelay = 3600; // Seconds
unsigned long currentDelay = 10;
byte sleep = 1;
byte LCDOn = 1;
byte speed = 25;
long currentTime = 1500; //25 min
long minTime = 60; // 1 min
unsigned long maxTime = 86400; // 24hrs
byte easingCurve = LINEAR;
byte easingCurveMin = 1;
byte easingCurveMax = 5;
byte timingEasingCurve = LINEAR;
byte timingEasingCurveMin = 1;
byte timingEasingCurveMax = 5;
byte timelapseDirection = 2;
int minInterval = 1000; // 1 sec

/* }}} */
/* configureTimelapse {{{ */
void configureTimelapse(){
    //Print current menu
    incrementTimelapseMenu(0, timelapseMenuLocation, 0);
    int counter = 0;
    while(selectTrigger(1000)){
        int buttonDelay = 150;
        if (xHigh() || xLow()){
            delay(buttonDelay);
            counter += 1;
            if (xLow()){
                timelapseMenuLocation = reflow(timelapseMenuLocation - 1, timelapseMenuMin, timelapseMenuMax);

                incrementTimelapseMenu(0, timelapseMenuLocation, counter);
            } else if (xHigh()){
                timelapseMenuLocation = reflow(timelapseMenuLocation + 1, timelapseMenuMin, timelapseMenuMax);
                incrementTimelapseMenu(0, timelapseMenuLocation, counter);
            }
        } else if (yHigh() || yLow()){
            delay(buttonDelay);
            counter += 1;
            if (yLow()){
                incrementTimelapseMenu(-1, timelapseMenuLocation, counter);
            } else if (yHigh()){
                incrementTimelapseMenu(1, timelapseMenuLocation, counter);
            }
        } else {
            counter = 0;
        }
    }
    lcd.setBacklight(HIGH);
    sleepOff();
}
/* }}} */
/* incrementTimelapseMenu {{{ */
void incrementTimelapseMenu(int input, int currentMenu, int counter){
    switch(currentMenu){
        case 1: //Num of Shots
            numShots += incrementVar(input, counter);
            numShots = reflow(numShots, minShots, maxShots);
            sprintf(utilityString, "%04d            ", numShots);
            lcdPrint(timelapseModeNumShotsLineOne, utilityString);
            break;
        case 2: //Duration
            currentTime += incrementVar(input, counter) * 60;
            currentTime = reflow(currentTime, minTime, maxTime);
            sprintf(utilityString, "%04u minutes   ", currentTime / 60);
            lcdPrint(timelapseModeDurationLineOne, utilityString);
            break;
        case 3: // Show Interval
            sprintf(utilityString, "%04d seconds    ", currentTime / numShots);
            lcdPrint(timelapseModeIntervalLineOne, utilityString);
            break;
        case 4: //Longest Shutter
            maxShutter += incrementVar(input, counter) * 1000;
            maxShutter = reflow(maxShutter, minMaxShutter, maxMaxShutter);
            sprintf(utilityString, "%02u seconds   ", maxShutter / 1000);
            lcdPrint(timelapseModeLongestShutterLineOne, utilityString);
            break;
        case 5: // Start Delay
            if (currentDelay < 60){
                currentDelay += incrementVar(input, counter);
            } else {
                currentDelay += incrementVar(input, counter) * 60;
            }
            currentDelay = reflow(currentDelay, minDelay, maxDelay);

            if (currentDelay < 60){
                sprintf(utilityString, "%d seconds   ", currentDelay);
            } else {
                sprintf(utilityString, "%d minutes   ", currentDelay / 60);
            }
            lcdPrint(timelapseModeDelayLineOne, utilityString);
            break;
        case 6: // Sleep between shots
            sleep += incrementVar(input, 0);
            sleep = reflow(sleep, 1, 2);
            sprintf(utilityString, "%s             ", yesOrNo(sleep));
            lcdPrint(timelapseModeSleepBetweenShotsLineOne, utilityString);
            break;
        case 7: // LCD on / off
            LCDOn += incrementVar(input, 0);
            LCDOn = reflow(LCDOn, 1, 2);
            sprintf(utilityString, "%s             ", yesOrNo(LCDOn));
            lcdPrint(timelapseModeLCDLineOne, utilityString);
            break;
        case 8: //Easing Curve
            easingCurve -= incrementVar(input, 0);
            easingCurve = reflow(easingCurve, easingCurveMin, easingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(easingCurve));
            lcdPrint(timelapseModeEasingCurveLineOne, utilityString);
            break;
        case 9: //Time Easing Curve
            timingEasingCurve -= incrementVar(input, 0);
            timingEasingCurve = reflow(timingEasingCurve , timingEasingCurveMin, timingEasingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(timingEasingCurve));
            lcdPrint(timelapseModeTimeEasingCurveLineOne, utilityString);
            break;
        case 10://Direction
            timelapseDirection += incrementVar(input, 0);
            timelapseDirection = reflow(timelapseDirection, 1, 2);
            if (timelapseDirection == 1){
                lcdPrint("Movement Dir:   ", timelapseModeDirectionLineTwoME);
            } else {
                lcdPrint(timelapseModeDirectionLineOne, timelapseModeDirectionLineTwoEM);
            }
            break;
        case 11: //
            lcdPrint("Move Right to   ", "start timelapse>");
            break;
        case 12:
            lcdPrint("Starting TL...  ", "Sel to cancel   ");
            startTimelapse();
            break;
    }
}
/* }}} */
/* incrementVar {{{ */
int incrementVar(int input, int counter){
    if (input > 0){
        if (counter > 10){
            return 10;
        } else {
            return 1;
        }
    } else if (input < 0){
        if (counter > 10){
            return -10;
        } else {
            return -1;
        }
    }
    return 0;
}
/* }}} */
/* easingCurveName {{{ */
const char* easingCurveName(byte input){
    switch(input){
        case 1:
            return "1. Linear       ";
            break;
        case 2:
            return "2. Ease In      ";
            break;
        case 3:
            return "3. Ease Out     ";
            break;
        case 4:
            return "4. FastSlowFast ";
            break;
        case 5:
            return "5. SlowFastSlow ";
            break;
    }
}
/* }}} */
/* yesOrNo -------------------------------------------------- {{{ */

const char* yesOrNo(byte input){
    switch(input){
        case 1:
            return "Yes";
            break;
        case 2:
            return "No ";
            break;
    }
}

/* }}} */
/* startTimelapse -------------------------------------------------- {{{ */

void startTimelapse(){
    timelapse(timelapseDirection, numShots, currentTime);
    timelapseMenuLocation = 1;
    lcdPrint(timelapseModeCompletedLineOne, holdSelToExit);
    return;
}

/* }}} */
/* timelapse -------------------------------------------------- {{{ */

void timelapse(byte dir, int shots, unsigned long instanceTime){
    unsigned long shotDelay = instanceTime * 1000 / shots;

    unsigned long stepStart = 0;
    unsigned long stepLen = 0;
    byte counter = 0;
    int baseStepInterval = trackLen / shots;
    int stepInterval = 0;

    // Pre Delay
    delay(currentDelay * 1000);

    if (LCDOn == 2){
        lcd.setBacklight(LOW);
    }

    // Starting Loop
    for (int i = 1; i <= shots; i++){
        int revI = shots - i;
        stepInterval = baseStepInterval;
        stepStart = millis();
        showTimelapseProgress(i, shots);
        takePicture();
        delay(maxShutter);

        /* Slider Easing ----------------------------------------- {{{ */
        switch(easingCurve){
            case EASEIN:
                stepInterval = easeInStep(i, shots, trackLen);
                break;
            case EASEOUT:
                stepInterval = easeOutStep(i, shots, trackLen);
                break;
            case FASTSLOWFAST:
                stepInterval = fastSlowFastStep(i, shots, trackLen);
                break;
            case SLOWFASTSLOW:
                stepInterval = slowFastSlowStep(i, shots, trackLen);
                break;
        }
        /* }}} */
        if (dir > 1){
            stepInterval *= -1;
        }
        // Account for random direction changes
        if(EEPROM_DIRECTION == 2){
            stepInterval *= -1;
        }
        //turn off sleep
        if(sleep == 1){
            sleepOff();
        }

        dampRotate(stepInterval);

        /* turn on sleep */
        if(sleep == 1){
            sleepOn();
        }
        if(select()){
            counter += 1;
            if(counter > 2){
                break;
            }
        } else {
            counter = 0;
        }
        stepLen = millis() - stepStart;

        /* time easing ------------------------------------------ {{{ */
        switch(timingEasingCurve){
            case EASEIN:
                shotDelay = easeInStep(i, shots, instanceTime);
                break;
            case EASEOUT:
                shotDelay = easeOutStep(i, shots, instanceTime);
                break;
            case FASTSLOWFAST:
                shotDelay = fastSlowFastStep(i, shots, instanceTime);
                break;
            case SLOWFASTSLOW:
                shotDelay = slowFastSlowStep(i, shots, instanceTime);
                break;
        }
        /* }}} */
        if (stepLen < (shotDelay)){
            delay((shotDelay) - stepLen);
        }
    }
}

/* }}} */
/* showTimelapseProgress ---------------------------------------- {{{ */

void showTimelapseProgress(unsigned long currentShot, int totalShots){
    sprintf(utilityString, "Progress: %02d%%  ",int( currentShot * 100 / totalShots));
    lcdPrint(timelapseModeRunningTimelapseLineOne, utilityString);
}

/* }}} */

/* }}} */
/* Realtime Movements ------------------------------------------ {{{ */

/* Realtime Menu Global Variables -------------------------------- {{{ */

byte realtimeMenuLocation = 1;
byte realtimeMenuMax = 6;
byte realtimeMenuMin = 1;
int realtimeNumShots = 500;
byte realtimeCurrentMaxSpeed = 25;
byte realtimeCurrentMinSpeed = 10;
byte realtimeMaxMaxSpeed = 99;
byte realtimeMaxMinSpeed = 1;
byte realtimeMinMaxSpeed = 99;
byte realtimeMinMinSpeed = 1;
byte realtimeEasingCurve = LINEAR;
byte realtimeEasingCurveMin = 1;
byte realtimeEasingCurveMax = 5;
byte realtimeDirection = 1;

/* }}} */
/* configureRealtime {{{ */
void configureRealtime(){
    //Print current menu
    incrementRealtimeMenu(0, realtimeMenuLocation, 0);
    int counter = 0;
    while(selectTrigger(1000)){
        int buttonDelay = 150;
        if (xHigh() || xLow()){
            delay(buttonDelay);
            counter += 1;
            if (xLow()){
                realtimeMenuLocation = reflow(realtimeMenuLocation - 1, realtimeMenuMin, realtimeMenuMax);

                incrementRealtimeMenu(0, realtimeMenuLocation, counter);
            } else if (xHigh()){
                realtimeMenuLocation = reflow(realtimeMenuLocation + 1, realtimeMenuMin, realtimeMenuMax);
                incrementRealtimeMenu(0, realtimeMenuLocation, counter);
            }
        } else if (yHigh() || yLow()){
            delay(buttonDelay);
            counter += 1;
            if (yLow()){
                incrementRealtimeMenu(-1, realtimeMenuLocation, counter);
            } else if (yHigh()){
                incrementRealtimeMenu(1, realtimeMenuLocation, counter);
            }
        } else {
            counter = 0;
        }
    }
}
/* }}} */
/* incrementRealtimeMenu {{{ */
void incrementRealtimeMenu(int input, int currentMenu, int counter){
    switch(currentMenu){
        case 1: //Min Speed
            realtimeCurrentMinSpeed += incrementVar(input, counter);
            realtimeCurrentMinSpeed = reflow(realtimeCurrentMinSpeed, realtimeMinMinSpeed, realtimeMinMaxSpeed);
            sprintf(utilityString, "%02d              ", realtimeCurrentMinSpeed);
            lcdPrint(realtimeModeMinSpeedLineOne, utilityString);
            break;
        case 2: //Speed
            if (realtimeCurrentMaxSpeed < realtimeCurrentMinSpeed) {
                realtimeCurrentMaxSpeed = realtimeCurrentMinSpeed + 1;
            }
            realtimeCurrentMaxSpeed += incrementVar(input, counter);
            realtimeCurrentMaxSpeed = reflow(realtimeCurrentMaxSpeed, realtimeCurrentMinSpeed + 1, realtimeMaxMaxSpeed);
            sprintf(utilityString, "%02d              ", realtimeCurrentMaxSpeed);
            lcdPrint(realtimeModeMaxSpeedLineOne, utilityString);
            break;
        case 3: //Easing Curve
            realtimeEasingCurve -= incrementVar(input, 0);
            realtimeEasingCurve = reflow(realtimeEasingCurve, realtimeEasingCurveMin, realtimeEasingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(realtimeEasingCurve));
            lcdPrint(realtimeModeEasingCurveLineOne, utilityString);
            break;
        case 4://Direction
            realtimeDirection += incrementVar(input, 0);
            realtimeDirection = reflow(realtimeDirection, 1, 2);
            if (realtimeDirection == 1){
                lcd.clear();
                lcdPrint("Movement Dir:   ", timelapseModeDirectionLineTwoME);
            } else {
                lcdPrint(timelapseModeDirectionLineOne, timelapseModeDirectionLineTwoEM);
            }
            break;
        case 5: //
            lcdPrint("Move Right to   ", "start RT move  >");
            break;
        case 6:
            lcdPrint("Starting Move...", "Sel to cancel   ");
            startRealtime();
            break;
    }
}
/* }}} */
/* startRealtime ------------------------------------------------- {{{ */

void startRealtime(){
    realtime(realtimeDirection, realtimeNumShots);
    realtimeMenuLocation = 1;
    lcdPrint(realtimeModeCompletedLineOne, holdSelToExit);

}

/* }}} */
/* realtime -------------------------------------------------- {{{ */

void realtime(byte dir, int shots){
    float realtimeSpeedDiff = (float(realtimeCurrentMaxSpeed * 1.0) - float(realtimeCurrentMinSpeed * 1.0)) * 1000.0;

    long stepInterval = 1;
    long baseStepInterval = (trackLen - 2500) / shots; // Accounting for rev up / down
    byte counter = 0;
    float instanceSpeed = 1.0;
    instanceSpeed = float(realtimeCurrentMaxSpeed) * 1000.0;
    float minSpeed = float(realtimeCurrentMinSpeed) * 1000.0;

    takeVideo();
    delay(3000); // Add editing time before shot

    for (int i = 1; i <= shots; i++){
        stepInterval = baseStepInterval;
        int revI = (shots + 1) - i;

        /* Slider Easing ----------------------------------------- {{{ */
        switch(realtimeEasingCurve){
            case EASEIN:
                instanceSpeed = float(preciseEaseInStep(i, shots, realtimeSpeedDiff));
                break;
            case EASEOUT:
                instanceSpeed = float(preciseEaseOutStep(i, shots, realtimeSpeedDiff));
                break;
            case FASTSLOWFAST:
                instanceSpeed = float(preciseFastSlowFastStep(i, shots, realtimeSpeedDiff) * 1000.0);
                break;
            case SLOWFASTSLOW:
                instanceSpeed = float(preciseSlowFastSlowStep(i, shots, realtimeSpeedDiff) * 1000.0);
                break;
        }
        /* }}} */
        if (dir > 1){
            stepInterval *= -1;
        }

        // Account for random direction changes
        if(EEPROM_DIRECTION == 2){
            stepInterval *= -1;
        }

        if (i == 1){
            dampStart(stepInterval, (instanceSpeed + minSpeed));
        }

        preciseRotate(stepInterval, (instanceSpeed + minSpeed));

        if (i == shots){
            dampEnd(stepInterval, (instanceSpeed + minSpeed));
        }

        if(select()){
            counter += 1;
            if(counter > 4){
                break;
            }
        } else {
            counter = 0;
        }
    }

    delay(3000); // Edit time after shot
    takeVideo();
    sleepOff();
}

/* }}} */
/* preciseRotate -------------------------------------------------- {{{ */

void preciseRotate(int steps, float speed){
    byte dir = (steps > 0)? HIGH:LOW;
    steps = abs(steps);
    digitalWrite(DIR_PIN, dir);
    // Not sure why * 70
    float speedDivisor = speed / 100000.0;
    float speedQuotient = 1.0 / speedDivisor;
    float usDelay = speedQuotient * 70.0;

    for(int i = 0; i < steps; i++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
    }
}

/* }}} */
/* dampStart -------------------------------------------------- {{{ */

void dampStart(int steps, float dampEndSpeed) {
    byte dir = (steps > 0)? HIGH:LOW;
    steps = abs(steps);
    digitalWrite(DIR_PIN, dir);

    float speedDivisor = dampEndSpeed / 100000.0;
    float speedQuotient = 1.0 / speedDivisor;
    float usDelay = speedQuotient * 70.0;

    float dampDelay = 1500.0;
    float dampChange = 1.0;

    //Begin Rotate Slow to Fast
    while(dampDelay > usDelay){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(dampDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(dampDelay);
        dampDelay -= dampChange;
    }
    return;
}

/* }}} */
/* dampEnd -------------------------------------------------- {{{ */

void dampEnd(int steps, float dampEndSpeed) {
    byte dir = (steps > 0)? HIGH:LOW;
    steps = abs(steps);
    digitalWrite(DIR_PIN, dir);

    float speedDivisor = dampEndSpeed / 100000.0;
    float speedQuotient = 1.0 / speedDivisor;
    float usDelay = speedQuotient * 70.0;

    float dampDelay = 1500.0;
    float dampChange = 1.0;

    //Begin Rotate Fast to Slow
    while(dampDelay > usDelay){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
        usDelay += dampChange;
    }
    return;
}
/* }}} */

/* }}} */
// Camera Functions {{{

void takePicture(){
    digitalWrite(SHUTTER_PIN, HIGH);
    delay(150);
    digitalWrite(SHUTTER_PIN, LOW);
}

void takeVideo(){
    digitalWrite(SHUTTER_PIN, HIGH);
    delay(1100);
    digitalWrite(SHUTTER_PIN, LOW);
}

/* }}} */
/* Direction EEPROM Functions ------------------------------------- {{{ */

void directionChanger(){
    byte instanceEEDir = EEPROM_DIRECTION;
    // Print Current Status
    sprintf(utilityString, "%s %s  ", directionSettings(instanceEEDir), directionSelected(instanceEEDir));
    lcdPrint(directionModeLineOne, utilityString);

    while(selectTrigger(1000)){
        if (yHigh() || yLow()){
            delay(150);
            if(yHigh()){
                instanceEEDir += 1;
                instanceEEDir = reflow(instanceEEDir, 1, 2);
            }
            if(yLow()){
                instanceEEDir -= 1;
                instanceEEDir = reflow(instanceEEDir, 1, 2);
            }
            sprintf(utilityString, "%s %s  ", directionSettings(instanceEEDir), directionSelected(instanceEEDir));
            lcdPrint(directionModeLineOne, utilityString);
        }
    }
    if (instanceEEDir != EEPROM_DIRECTION){
        EEPROM_DIRECTION = instanceEEDir;
        //Write to EEProm
        EEPROM.write(EEPROM_DIRECTION_LOC, EEPROM_DIRECTION);
    }
}

const char* directionSettings(int setting){
    if (setting == 1){
        return "1. Setting A";
    }else if (setting == 2){
        return "2. Setting B";
    }
}

const char* directionSelected(int choice){
    if (choice == EEPROM_DIRECTION){
        return "*";
    } else {
        return " ";
    }
}

/* }}} */
/* Event Functions {{{ */

/* selectTrigger {{{ */
unsigned long selectTimerStart = 0;
bool selectTrigger(int duration){
    // Returns false when button is pressed for the duration
    byte selectStatus = digitalRead(JOYSTICK_SELECT_PIN); // 0 is pressed

    if (selectStatus == LOW){
        if (selectTimerStart > 0){
            unsigned long interval = millis() - selectTimerStart;
            if (interval > duration){
                return false;
            } else {
                return true;
            }
        } else if (selectTimerStart == 0){
            selectTimerStart = millis();
            return true;
        }
    } else {
        selectTimerStart = 0;
        return true;
    }
}
/* }}} */
/* directionTrigger {{{ */
unsigned long directionTimerStart = 0;
int directionStatus = 512;
bool directionTrigger(unsigned long duration, int direction){
    // Return false when direction is triggered for duration
    if (direction == RIGHT || direction == LEFT){
        directionStatus = analogRead(JOYSTICK_X_PIN);
    } else if (direction == UP || direction == DOWN){
        directionStatus = analogRead(JOYSTICK_Y_PIN);
    }

    if (directionStatus > 550 || directionStatus < 450){
        if (directionTimerStart > 0){
            unsigned long interval = millis() - directionTimerStart;
            if(interval > duration){
                return false;
            } else {
                return true;
            }
        } else if (directionTimerStart == 0){
            directionTimerStart = millis();
            return true;
        }
    } else {
        directionTimerStart = 0;
        return true;
    }
}
/* }}} */

/* }}} */
/* LCD & Menu Functions {{{ */

/* status {{{ */

char* formattedSwitch(byte status){
    if (status == HIGH){
        return switchPressed;
    } else if (status == LOW){
        return switchOpen;
    } else{
        return switchError;
    }
}

char* formattedReverseSwitch(byte status){
    if (status == LOW){
        return switchPressed;
    } else if (status == HIGH){
        return switchOpen;
    } else {
        return switchError;
    }
}

void status(){
    while (selectTrigger(1000)){
    /* Reading sensors */
        int xpos = analogRead(A0);
        int ypos = analogRead(A1);
        byte selectStatus = digitalRead(JOYSTICK_SELECT_PIN);
        byte motorSwitchStatus = digitalRead(MOTOR_SWITCH_PIN);
        byte endSwitchStatus = digitalRead(END_SWITCH_PIN);

        sprintf(debugLineOne, "X:%4d Sel:%s    ", xpos, formattedReverseSwitch(selectStatus));
        sprintf(debugLineTwo, "Y:%4d M:%s E:%s  ", ypos, formattedSwitch(motorSwitchStatus), formattedSwitch(endSwitchStatus));

        lcdPrint(debugLineOne, debugLineTwo);
    }
    /* menuShow(); */
    return;
}
/* }}} end of status */
/* joystickPosition {{{ */
void joystickPosition(int buttonDelay){
    lcd.setCursor(0, 0);
    lcd.print("    ");
    lcd.print(readJoystick(buttonDelay));
    lcd.setCursor(0, 1);
    lcd.print("                ");
}

/* }}} */
/* lcd Print {{{ */
void lcdPrint(char* line1, char* line2){
    //Prints two 16 char lines to the lcd

    /* Line 1 */
    lcd.setCursor(0, 0); //Cursor Position, Line Number
    lcd.print(line1);

    /* Line 2 */
    lcd.setCursor(0, 1);
    lcd.print(line2);
}
/* }}} */
/* constLcdPrint {{{ */
void constLcdPrint(const char* line1, const char* line2){
    //Prints two 16 char lines to the lcd

    /* Line 1 */
    lcd.setCursor(0, 0); //Cursor Position, Line Number
    lcd.print(line1);

    /* Line 2 */
    lcd.setCursor(0, 1);
    lcd.print(line2);
}
/* }}} */
/* menuOptions {{{ */
const char* menuOptions(int input){
    switch(input){
        case 1:
            return timelapseStringSelected;
            break;
        case 2:
            return realtimeStringSelected;
            break;
        case 3:
            return commandStringSelected;
            break;
        case 4:
            return directionStringSelected;
            break;
        case 5:
            return debugStringSelected;
            break;
        default:
            return genericErrorLineOne;
            break;
    }
}
/* }}} */
/* menuShow {{{ */
byte currentMenuPosition = 1;
byte minMenuPosition = 1;
byte maxMenuPosition = 5;

void menuShow(){
    constLcdPrint(selectModeString, menuOptions(currentMenuPosition));
    while (directionTrigger(50, RIGHT) == true){
        int currentJoystickPosition = readJoystick(50);
        if (currentJoystickPosition == UP){
            currentMenuPosition -= 1;
            currentMenuPosition = reflow(currentMenuPosition, minMenuPosition, maxMenuPosition);
            constLcdPrint(selectModeString, menuOptions(currentMenuPosition));
        } else if (currentJoystickPosition == DOWN) {
            currentMenuPosition += 1;
            currentMenuPosition = reflow(currentMenuPosition, minMenuPosition, maxMenuPosition);
            constLcdPrint(selectModeString, menuOptions(currentMenuPosition));
        }
    }
    secondaryMenuShow(currentMenuPosition);
    return;
}
/* }}} */
/* reflow {{{ */
int reflow(int input, int minOutput, int maxOutput){
    if (input > maxOutput){
        return minOutput;
    } else if (input < minOutput){
        return maxOutput;
    } else {
        return input;
    }
}
/* }}} */
/* secondaryMenuShow ---------------------------------------------- {{{ */

void secondaryMenuShow(int input){
    int flashDelay = 250;
    switch(input){
        case 1: // Timelapse
            lcdPrint(enteringTimelapseModeLineOne, holdSelToExit);
            delay(flashDelay);
            configureTimelapse();
            break;
        case 2: // Realtime
            lcdPrint(enteringRealtimeModeLineOne, holdSelToExit);
            delay(flashDelay);
            configureRealtime();
            break;
        case 3: // Command
            lcdPrint(enteringCommandModeLineOne, holdSelToExit);
            delay(flashDelay);
            commanderMode();
            break;
        case 4: // Direction
            lcdPrint(enteringDirectionModeLineOne, holdSelToExit);
            delay(flashDelay);
            directionChanger();
            break;
        case 5: // Debug
            lcdPrint(enteringDebugModeLineOne, holdSelToExit);
            delay(flashDelay);
            status();
            break;
        default:
            lcdPrint(genericErrorLineOne, genericErrorLineTwo);
            delay(flashDelay);
            menuShow();
            break;
    }
}

/* }}} */

/* }}} */
/* Helper Functions ------------------------------------------------ {{{ */


/* }}} */
/* Setup {{{ */

void setup()
{
    /* Stepper Pin Setup */
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(SLEEP_PIN, OUTPUT);
    digitalWrite(SLEEP_PIN, HIGH);

    /* Serial */
    /* Serial.begin(9600); */
    /* Serial.print("Beginning Serial!"); */

    /* Camera Pin Setup */
    pinMode(SHUTTER_PIN, OUTPUT);

    /* LCD Pin Setup */
    lcd.begin(16, 2);
    lcd.print("   Slidelapse");
    lcd.setCursor(0, 1);
    lcd.print(" Version 0.8.0");
    delay(1500);
    lcd.clear();

    /* EEPROM Direction Read */
    /* EEPROM.write(EEPROM_DIRECTION_LOC, 2); */
    EEPROM_DIRECTION = EEPROM.read(EEPROM_DIRECTION_LOC);

    /* Joystick Pin Setup */
    pinMode(JOYSTICK_SELECT_PIN, INPUT_PULLUP);

    /* Switch Pin Setup */
    pinMode(MOTOR_SWITCH_PIN, INPUT);
    pinMode(END_SWITCH_PIN, INPUT);

    sleepOff();
}

/* }}} */
/* Loop {{{ */

void loop(){
    menuShow();
}

/* }}} */
/* Folding Setup {{{ */
// vim:foldmethod=marker:foldlevel=0
/* }}} */

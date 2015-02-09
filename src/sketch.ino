/* Libraries {{{ */

#include <math.h>

#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
/* #include "QuadraticEase.h" */
/* #include "SineEase.h" */
/* #include "CubicEase.h" */

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
/* Easing functions {{{ */

/* const byte LINEAR = 1; */
/* const byte QUADRATIC = 2; */
/* const byte SINE = 3; */
/* const byte CUBIC = 4; */

/* }}} */
/* Easing curves {{{ */

const byte LINEAR = 1;
const byte EASEIN = 2;
const byte EASEOUT = 3;
const byte EASEINOUT = 4;
const byte EASEOUTIN = 5;

/* }}} */
/* Menu Strings {{{ */

char holdSelToExit[17] = "Hold Sel to Exit";
char utilityString[17] = "";

/* Main Menu Strings {{{ */

char selectModeString[17] = "Select Mode:    ";
char timelapseStringSelected[17] = "1.Timelapse    >";
char realtimeStringSelected[17] = "2.Realtime     >";
char commandStringSelected[17] = "3.Commander    >";
char directionStringSelected[17] = "4.Direction    >";
char debugStringSelected[17] = "5.Debug        >";

/* }}} */
/* Timelapse Menu Strings {{{ */
char enteringTimelapseModeLineOne[17] = ">>> Timelapse   ";
/* char enteringTimelapseModeLineTwo[17] = "Hold Sel to exit"; */

/* char timelapseModeTrackLenLineOne[17] = "Find Track Len.."; */
/* char timelapseModeTrackLenLineTwo[17] = ""; */

char timelapseModeNumShotsLineOne[17] = "Number of Shots:";
/* char timelapseModeNumShotsLineTwo[17] = ""; */

char timelapseModeDurationLineOne[17] = "TL Duration:    ";
/* char timelapseModeDurationLineTwo[17] = ""; */

char timelapseModeIntervalLineOne[17] = "Avg Interval:   ";
/* char timelapseModeIntervalLineTwo[17] = ""; */

char timelapseModeDelayLineOne[17] = "Start Delay:    ";
/* char timelapseModeDelayLineTwo[17] = ""; */

char timelapseModeLongestShutterLineOne[17] = "Longest Shutter:";
/* char timelapseModeLongestShutterLineTwo[17] = ""; */

char timelapseModeSleepBetweenShotsLineOne[17] = "Sleep btw shots ";
/* char timelapseModeSleepBetweenShotsLineTwo[17] = ""; */

char timelapseModeLCDLineOne[17] = "Backlight on?:  ";
/* char timelapseModeLCDLineTwo[17] = ""; */

/* char timelapseModeEasingFunctionLineOne[17] = "Slide Ease Func:"; */
/* char timelapseModeEasingFunctionLineTwo[17] = ""; */

char timelapseModeEasingCurveLineOne[17] = "Slide Ease Curv:";
/* char timelapseModeEasingCurveLineTwo[17] = ""; */

char timelapseModeTimeEasingFunctionLineOne[17] = "Time Ease Func: ";
/* char timelapseModeTimeEasingFunctionLineTwo[17] = ""; */

char timelapseModeTimeEasingCurveLineOne[17] = "Time Curve Func:";
/* char timelapseModeTimeEasingCurveLineTwo[17] = ""; */

char timelapseModeDirectionLineOne[17] = "Movement Dir:   ";
char timelapseModeDirectionLineTwoME[17] = "Motor -----> End";
char timelapseModeDirectionLineTwoEM[17] = "End -----> Motor";

/* char timelapseModeStartingTimelapseLineOne[17] = "Start Timelapse "; */
/* char timelapseModeStartingTimelapseLineTwo[17] = "Hold Sel to exit"; */

char timelapseModeRunningTimelapseLineOne[17] = "Timelapse active";
/* char timelapseModeRunningTimelapseLineTwo[17] = ""; */

char timelapseModeCompletedLineOne[17] = "Timelapse Done  ";
/* char timelapseModeCompletedLineTwo[17] = "Hold Sel to exit"; */

/* }}} */
/* Commander Menu Strings {{{ */

char enteringCommandModeLineOne[17] = ">>> Commander   ";
/* char enteringCommandModeLineTwo[17] = "Hold Sel to exit"; */

char commandModeLineOne[17] = "  Command Mode  ";
char commandModeLineTwoMotorToEnd[17] = "Motor <----> End";
char commandModeLineTwoEndToMotor[17] = "End <----> Motor";
char commandModeLineTwoChangingDirection[17] = "Reversing Dir <>";

/* }}} */
/* Direction Menu Strings ---------------------------------------- {{{ */

char enteringDirectionModeLineOne[17] = ">>> Direction   ";
/* char enteringDirectionModeLineTwo[17] = "Hold Sel to exit"; */

char directionModeLineOne[17] = "Set EEPROM Dir: ";
/* char directionModeLineTwo[17] = ""; */

/* }}} */
/* Status Menu Strings {{{ */

char enteringDebugModeLineOne[17] = ">>> Debug Mode  ";
/* char enteringDebugModeLineTwo[17] = "Hold Sel to exit"; */
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
/* char enteringRealtimeModeLineTwo[17] = "Hold Sel to exit"; */

char realtimeModeSpeedLineOne[17] = "Movement Speed: ";
/* char realtimeModeSpeedLineTwo[17] = ""; */

/* char realtimeModeDelayLineTwo[17] = ""; */

char realtimeModeEasingFunctionLineOne[17] = "RT Ease Func:   ";
/* char realtimeModeEasingFunctionLineTwo[17] = ""; */

char realtimeModeEasingCurveLineOne[17] = "RT Ease Curve:  ";
/* char realtimeModeEasingCurveLineTwo[17] = ""; */

char realtimeModeCompletedLineOne[17] = "Move Complete!  ";
/* char realtimeModeCompletedLineTwo[17] = "Hold Sel to exit"; */

/* char realtimeModeProgressLineOne[17] = "Current Speed:  "; */
/* char realtimeModeProgressLineTwo[17] = ""; */

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

double calculateCoefficient(int currentStep, int totalSteps, unsigned long trackLen, double exponent){
    double coefficient = trackLen / (pow(totalSteps, exponent));
    return coefficient * (pow(currentStep, exponent));
}

int calculateCoefficientStep(int currentStep, int totalSteps, unsigned long trackLen, double exponent){
    return round(calculateCoefficient(currentStep, totalSteps, trackLen, exponent) - calculateCoefficient(currentStep - 1, totalSteps, trackLen, exponent));
}

int easeInStep(int currentStep, int totalSteps, unsigned long trackLen){
    return calculateCoefficientStep(currentStep, totalSteps, trackLen, 2.0);
}

double reverseCalculateCoefficient(int currentStep, int totalSteps, unsigned long trackLen, double exponent){
    double coefficient = -1 * (double(trackLen) / pow(double(totalSteps), exponent));
    return coefficient * pow(currentStep - totalSteps, exponent) + trackLen;
}

int reverseCalculateCoefficientStep(int currentStep, int totalSteps, unsigned long trackLen, double exponent) {
    return round(reverseCalculateCoefficient(currentStep, totalSteps, trackLen, exponent) - reverseCalculateCoefficient(currentStep - 1, totalSteps, trackLen, exponent));
}

int easeOutStep(int currentStep, int totalSteps, unsigned long trackLen){
    return reverseCalculateCoefficientStep(currentStep, totalSteps, trackLen, 2.0);
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

int cubicBezierStep(int currentStep, int totalSteps, unsigned long trackLen, double control1Percent, double control2Percent){
    return round(cubicBezier(currentStep, totalSteps, trackLen, control1Percent, control2Percent) - cubicBezier(currentStep - 1, totalSteps, trackLen, control1Percent, control2Percent));
}

int slowFastSlowStep(int currentStep, int totalSteps, unsigned long trackLen){
    return cubicBezierStep(currentStep, totalSteps, trackLen, 0.0, 1.0);
}

int fastSlowFastStep(int currentStep, int totalSteps, unsigned long trackLen){
    return cubicBezierStep(currentStep, totalSteps, trackLen, 1.0, 0.0);
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

    /* unsigned int dampChange = 100; */
    unsigned int dampSteps = 20;
    unsigned int dampChange = (dampDelay - normalDelay) / dampSteps;
    // 7000 corresponds to feeding 1 to rotate speed

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

    /* // Not sure why * 70 */
    /* float floatSpeed = float(maxSpeed); */
    /* float usDelay = (1 / (floatSpeed / 100)) * 70; */

    /* int quarterSteps = steps / 4; */

    /* usDelay += quarterSteps * 5; */
    /* for(int j = 0; j < quarterSteps; j++){ */
    /*     usDelay -= 5; */
    /*     digitalWrite(STEP_PIN, HIGH); */
    /*     delayMicroseconds(usDelay); */
    /*     digitalWrite(STEP_PIN, LOW); */
    /*     delayMicroseconds(usDelay); */
    /* } */

    /* for(int i = 0; i < steps - quarterSteps * 2; i++){ */
    /*     digitalWrite(STEP_PIN, HIGH); */
    /*     delayMicroseconds(usDelay); */
    /*     digitalWrite(STEP_PIN, LOW); */
    /*     delayMicroseconds(usDelay); */
    /* } */

    /* for(int j = 0; j < quarterSteps; j++){ */
    /*     usDelay += 5; */
    /*     digitalWrite(STEP_PIN, HIGH); */
    /*     delayMicroseconds(usDelay); */
    /*     digitalWrite(STEP_PIN, LOW); */
    /*     delayMicroseconds(usDelay); */
    /* } */
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
    delay(5);
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
    lcdPrint(commandModeLineOne, commandModeLineTwoMotorToEnd);
    int direction = 1; // Odd is motor to end, Even is end to motor
    if (EEPROM_DIRECTION == 2){
        direction += 1;
    }
    while (selectTrigger(1000)){
        int xpos = analogRead(JOYSTICK_X_PIN);
        int ypos = analogRead(JOYSTICK_Y_PIN);
        if (ypos == 1023){
            delay(500);
            if (analogRead(JOYSTICK_Y_PIN) == 1023){
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
        if (xpos > 523){
            if (direction % 2 == 1) {
                 // Motor to end
                if (digitalRead(END_SWITCH_PIN) != HIGH){
                    rotate(1, calcSpeed(xpos - 523, 500, 25));
                }
            } else if (direction % 2 == 0){
                //End to motor
                if (digitalRead(MOTOR_SWITCH_PIN) != HIGH){
                    rotate(-1, calcSpeed(xpos - 523, 500, 25));
                }
            }
        } else if (xpos < 500){
            if (direction % 2 == 1){
                // Motor to end
                if (digitalRead(MOTOR_SWITCH_PIN) != HIGH){
                    rotate(-1, calcSpeed(abs(500 - xpos), 500, 25));
                }
            } else if (direction % 2 == 0){
                // End to Motor
                if (digitalRead(END_SWITCH_PIN) != HIGH){
                    rotate(1, calcSpeed(abs(500 - xpos), 500, 25));
                }
            }
        }
    }
}
/* }}} End commanderMode */
/* calcSpeed {{{ */
byte calcSpeed(int input, int maxInput, byte maxOutput){
    //returns a byte proportional to the input / max
    return (maxOutput * input) / maxInput;
}
/* }}} */
/* rotateDeg {{{ */
/* void rotatedeg(float deg, float speed){ */
/*     int dir = (deg > 0)? high:low; */
/*     digitalwrite(dir_pin, dir); */
/*     int steps = abs(deg) * (1 / 0.225); */
/*     float usdelay = (1 / speed) * 70; */

/*     for(int i = 0; i < steps; i++){ */
/*         digitalwrite(step_pin, high); */
/*         delaymicroseconds(usdelay); */
/*         digitalwrite(step_pin, low); */
/*         delaymicroseconds(usdelay); */
/*     } */
/* } */
/* }}} */
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
/* byte easingFunction = LINEAR; */
/* byte easingFunctionMin = 1; */
/* byte easingFunctionMax = 4; */
byte easingCurve = LINEAR;
byte easingCurveMin = 1;
byte easingCurveMax = 5;
/* byte timingEasingFunction = LINEAR; */
/* byte timingEasingFunctionMin = 1; */
/* byte timingEasingFunctionMax = 4; */
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
        /* case 8: //Easing Function */
        /*     easingFunction -= incrementVar(input, 0); */
        /*     easingFunction = reflow(easingFunction, easingFunctionMin, easingFunctionMax); */
        /*     sprintf(utilityString, "%s       ", easingFunctionName(easingFunction)); */
        /*     lcdPrint(timelapseModeEasingFunctionLineOne, utilityString); */
        /*     break; */
        case 8: //Easing Curve
            easingCurve -= incrementVar(input, 0);
            easingCurve = reflow(easingCurve, easingCurveMin, easingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(easingCurve));
            lcdPrint(timelapseModeEasingCurveLineOne, utilityString);
            break;
        /* case 10: // Time Easing Function */
        /*     timingEasingFunction -= incrementVar(input, 0); */
        /*     timingEasingFunction = reflow(timingEasingFunction, timingEasingFunctionMin, timingEasingFunctionMax); */
        /*     sprintf(utilityString, "%s       ", easingFunctionName(timingEasingFunction)); */
        /*     lcdPrint(timelapseModeTimeEasingFunctionLineOne, utilityString); */
        /*     break; */
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
                lcd.clear();
                lcdPrint("Movement Dir:   ", timelapseModeDirectionLineTwoME);
            } else {
                /* lcd.clear(); */
                /* lcdPrint("Movement Dir:   ", timelapseModeDirectionLineTwoEM); */
                lcdPrint(timelapseModeDirectionLineOne, timelapseModeDirectionLineTwoEM);
            }
            break;
        case 11: //
            lcdPrint("Move Right to   ", "start timelapse>");
            break;
        case 12:
            lcdPrint("Starting TL...  ", "Sel to cancel   ");
            /* delay(1000); */
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
/* easingFunctionName {{{ */
/* const char* easingFunctionName(byte input){ */
/*     switch(input){ */
/*         case 1: */
/*             return "1. Linear"; */
/*             break; */
/*         case 2: */
/*             return "2. Quad  "; */
/*             break; */
/*         case 3: */
/*             return "3. Sine  "; */
/*             break; */
/*         case 4: */
/*             return "4. Cubic "; */
/*             break; */
/*     } */
/* } */
/* }}} */
/* easingCurveName {{{ */
const char* easingCurveName(byte input){
    switch(input){
        case 1:
            return "1. Linear   ";
            break;
        case 2:
            return "2. Ease In  ";
            break;
        case 3:
            return "3. Ease Out ";
            break;
        case 4:
            return "4. EaseInOut";
            break;
        case 5:
            return "5. EaseOutIn";
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

    // Slider Easing
    /* QuadraticEase quadEase; */
    /* quadEase.setDuration(shots); */
    /* quadEase.setTotalChangeInPosition(trackLen); */
    /* SineEase sineEase; */
    /* sineEase.setDuration(shots); */
    /* sineEase.setTotalChangeInPosition(trackLen); */
    /* CubicEase cubicEase; */
    /* cubicEase.setDuration(shots); */
    /* cubicEase.setTotalChangeInPosition(trackLen); */

    // Time Easing
    /* QuadraticEase quadTimeEase; */
    /* quadTimeEase.setDuration(shots); */
    /* quadTimeEase.setTotalChangeInPosition(instanceTime * 1000); */
    /* SineEase sineTimeEase; */
    /* sineTimeEase.setDuration(shots); */
    /* sineTimeEase.setTotalChangeInPosition(instanceTime * 1000); */
    /* CubicEase cubicTimeEase; */
    /* cubicTimeEase.setDuration(shots); */
    /* cubicTimeEase.setTotalChangeInPosition(instanceTime * 1000); */
    double timeEaseDelay = 0;

    long baseStepInterval = trackLen / shots;
    unsigned long stepStart = 0;
    unsigned long stepLen = 0;
    byte counter = 0;
    long stepInterval = 0;

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
            case EASEINOUT:
                stepInterval = fastSlowFastStep(i, shots, trackLen);
                break;
            case EASEOUTIN:
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
                shotDelay = easeInStep(i, shots, trackLen);
                break;
            case EASEOUT:
                shotDelay = easeOutStep(i, shots, trackLen);
                break;
            case EASEINOUT:
                shotDelay = fastSlowFastStep(i, shots, trackLen);
                break;
            case EASEOUTIN:
                shotDelay = slowFastSlowStep(i, shots, trackLen);
                break;
        }
        /* }}} */
        if (stepLen < (shotDelay)){
            delay((shotDelay) - stepLen);
        }
    }
    /* if(sleep == 1){ */
    /*     sleepOn(); */
    /* } */
    return;
}

/* }}} */
/* showTimelapseProgress ---------------------------------------- {{{ */

void showTimelapseProgress(unsigned long currentShot, int totalShots){
    sprintf(utilityString, "Progress: %02d%%  ",int( currentShot * 100 / totalShots));
    lcdPrint(timelapseModeRunningTimelapseLineOne, utilityString);
}

/* }}} */
/* quadraticEase {{{ */
/* void quadraticEase(int dir, int steps, float speed, unsigned long time){ */
/*     QuadraticEase quadEase; */
/*     QuadraticEase timeEase; */
/*     quadEase.setDuration(steps); */
/*     quadEase.setTotalChangeInPosition(35000); */
/*     timeEase.setDuration(steps); */
/*     unsigned long total_time = time * 1000; */
/*     timeEase.setTotalChangeInPosition(total_time); */
/*     unsigned long counter = 0; */
/*     unsigned long time_counter = 0; */
/*     unsigned long time_in_millis = time * 1000; */
/*     for(float i = 1; i <= steps; i++){ */
/*         float move_steps = quadEase.easeInOut(i) - quadEase.easeInOut(i - 1); */
/*         unsigned long move_start = millis(); */
/*         rotate(int(move_steps * dir), speed); */
/*         delay(150); */
/*         takePicture(); */
/*         counter += int(move_steps); */
/*         unsigned long move_end = millis(); */
/*         unsigned long move_time = move_end - move_start; */

/*         float time_delay = timeEase.easeInOut(i) - timeEase.easeInOut(i - 1); */
/*         /1* unsigned long time_delay = time_in_millis / steps; *1/ */
/*         time_counter += time_delay; */

/*         if (time_delay < move_time){ */
/*             delay(0); */
/*         } else { */
/*             delay(int(time_delay) - move_time); */
/*         } */
/*     } */
/* } */
/* }}} */

/* }}} */
/* Realtime Movements ------------------------------------------ {{{ */

/* Realtime Menu Global Variables -------------------------------- {{{ */

byte realtimeMenuLocation = 1;
byte realtimeMenuMax = 4;
byte realtimeMenuMin = 1;
/* unsigned int trackLen = 34800; */
int realtimeNumShots = 500;
/* unsigned long realtimeMinDelay = 1; // Seconds */
/* unsigned long realtimeMaxDelay = 3600; // Seconds */
/* unsigned long realtimeCurrentDelay = 10; */
byte realtimeCurrentMaxSpeed = 25;
byte realtimeCurrentMinSpeed = 10;
byte realtimeMaxSpeed = 99;
byte realtimeMinSpeed = 1;
/* byte realtimeEasingFunction = LINEAR; */
/* byte realtimeEasingFunctionMin = 1; */
/* byte realtimeEasingFunctionMax = 4; */
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
        case 1: //Speed
            realtimeCurrentMaxSpeed += incrementVar(input, counter);
            realtimeCurrentMaxSpeed = reflow(realtimeCurrentMaxSpeed, realtimeMinSpeed, realtimeMaxSpeed);
            sprintf(utilityString, "%02d              ", realtimeCurrentMaxSpeed);
            lcdPrint(realtimeModeSpeedLineOne, utilityString);
            break;
        /* case 2: // Start Delay {{{ */
        /*     if (realtimeCurrentDelay < 60){ */
        /*         realtimeCurrentDelay += incrementVar(input, counter); */
        /*     } else { */
        /*         realtimeCurrentDelay += incrementVar(input, counter) * 60; */
        /*     } */
        /*     realtimeCurrentDelay = reflow(realtimeCurrentDelay, realtimeMinDelay, realtimeMaxDelay); */

        /*     if (realtimeCurrentDelay < 60){ */
        /*         sprintf(utilityString, "%d seconds   ", realtimeCurrentDelay); */
        /*     } else { */
        /*         sprintf(utilityString, "%d minutes   ", realtimeCurrentDelay / 60); */
        /*     } */
        /*     lcdPrint(timelapseModeDelayLineOne, utilityString); */
        /*     break; // }}} */
        /* case 2: //Easing Function */
        /*     realtimeEasingFunction -= incrementVar(input, 0); */
        /*     realtimeEasingFunction = reflow(realtimeEasingFunction, realtimeEasingFunctionMin, realtimeEasingFunctionMax); */
        /*     sprintf(utilityString, "%s       ", easingFunctionName(realtimeEasingFunction)); */
        /*     lcdPrint(realtimeModeEasingFunctionLineOne, utilityString); */
        /*     break; */
        case 2: //Easing Curve
            realtimeEasingCurve -= incrementVar(input, 0);
            realtimeEasingCurve = reflow(realtimeEasingCurve, realtimeEasingCurveMin, realtimeEasingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(realtimeEasingCurve));
            lcdPrint(realtimeModeEasingCurveLineOne, utilityString);
            break;
        case 3://Direction
            realtimeDirection += incrementVar(input, 0);
            realtimeDirection = reflow(realtimeDirection, 1, 2);
            if (realtimeDirection == 1){
                lcd.clear();
                lcdPrint("Movement Dir:   ", timelapseModeDirectionLineTwoME);
            } else {
                lcdPrint(timelapseModeDirectionLineOne, timelapseModeDirectionLineTwoEM);
            }
            break;
        case 4: //
            lcdPrint("Move Right to   ", "start RT move  >");
            break;
        case 5:
            lcdPrint("Starting Move...", "Sel to cancel   ");
            /* delay(1000); */
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
    return;
}

/* }}} */
/* realtime -------------------------------------------------- {{{ */

void realtime(byte dir, int shots){

    float realtimeSpeedDiff = (float(realtimeCurrentMaxSpeed * 1.0) - float(realtimeCurrentMinSpeed * 1.0)) * 1000.0;

    // Slider Easing
    /* QuadraticEase realtimeQuadEase; */
    /* realtimeQuadEase.setDuration(shots); */
    /* realtimeQuadEase.setTotalChangeInPosition(realtimeSpeedDiff); */
    /* SineEase sineEase; */
    /* sineEase.setDuration(shots); */
    /* sineEase.setTotalChangeInPosition(realtimeSpeedDiff); */
    /* CubicEase cubicEase; */
    /* cubicEase.setDuration(shots); */
    /* cubicEase.setTotalChangeInPosition(realtimeSpeedDiff); */

    long stepInterval = 1;
    long baseStepInterval = (trackLen - 2500) / shots;
    /* unsigned long stepStart = 0; */
    /* unsigned long stepLen = 0; */
    byte counter = 0;
    float instanceSpeed = 1.0;
    instanceSpeed = float(realtimeCurrentMaxSpeed) * 1000.0;
    float minSpeed = float(realtimeCurrentMinSpeed) * 1000.0;

    takeVideo();
    delay(3000);
    /* takePicture(); */
    /* delay(500); */


    for (int i = 1; i <= shots; i++){
        stepInterval = baseStepInterval;
        int revI = (shots + 1) - i;

        /* Slider Easing ----------------------------------------- {{{ */
        switch(realtimeEasingCurve){
            case LINEAR:
                instanceSpeed = realtimeSpeedDiff;
                break;
            case EASEIN:
                /* instanceSpeed = realtimeQuadEase.easeIn(i); */
                instanceSpeed = easeInStep(i, shots, trackLen);
                break;
            case EASEOUT:
                /* instanceSpeed = realtimeQuadEase.easeOut(i); */
                instanceSpeed = easeOutStep(i, shots, trackLen);
                break;
            case EASEINOUT:
                /* instanceSpeed = realtimeQuadEase.easeInOut(i); */
                instanceSpeed = slowFastSlowStep(i, shots, trackLen);
                break;
            case EASEOUTIN:
                /* instanceSpeed = realtimeQuadEase.easeIn(revI); */
                instanceSpeed = fastSlowFastStep(i, shots, trackLen);
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

    delay(3000);
    takeVideo();
    sleepOff();
    return;
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
/* menuOptions {{{ */
char* menuOptions(int input){
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
int currentMenuPosition = 1;
int minMenuPosition = 1;
int maxMenuPosition = 5;

void menuShow(){
    while (directionTrigger(50, RIGHT) == true){
        int currentJoystickPosition = readJoystick(50);
        if (currentJoystickPosition == UP){
            currentMenuPosition -= 1;
        } else if (currentJoystickPosition == DOWN) {
            currentMenuPosition += 1;
        }

        currentMenuPosition = reflow(currentMenuPosition, minMenuPosition, maxMenuPosition);

        lcdPrint(selectModeString, menuOptions(currentMenuPosition));
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
    lcd.print(" Version 0.7.0");
    delay(3000);
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

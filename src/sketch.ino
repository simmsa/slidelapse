/* Libraries {{{ */

#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "QuadraticEase.h"
#include "SineEase.h"
#include "CubicEase.h"

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

const byte LINEAR = 1;
const byte QUADRATIC = 2;
const byte SINE = 3;
const byte CUBIC = 4;

/* }}} */
/* Easing curves {{{ */

const byte EASEIN = 1;
const byte EASEOUT = 2;
const byte EASEINOUT = 3;
const byte REVEASEIN = 4;
const byte REVEASEOUT = 5;

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

char timelapseModeEasingFunctionLineOne[17] = "Slide Ease Func:";
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
/* Timelapse Functions {{{ */

/* rotate {{{ */
void rotate(int steps, byte speed){
    int dir = (steps > 0)? HIGH:LOW;
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

void dampRotate(int steps, byte maxSpeed) {
    int dir = (steps > 0)? HIGH:LOW;
    steps = abs(steps);
    digitalWrite(DIR_PIN, dir);
    // Not sure why * 70
    float floatSpeed = float(maxSpeed);
    float usDelay = (1 / (floatSpeed / 100)) * 70;

    int quarterSteps = steps / 4;

    usDelay += quarterSteps * 5;
    for(int j = 0; j < quarterSteps; j++){
        usDelay -= 5;
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
    }

    for(int i = 0; i < steps - quarterSteps * 2; i++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
    }

    for(int j = 0; j < quarterSteps; j++){
        usDelay += 5;
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
    }
}

/* }}} */
/* sleepOn -------------------------------------------------- {{{ */

void sleepOn(){
    digitalWrite(SLEEP_PIN, LOW);
}

/* }}} */
/* sleepOff -------------------------------------------------- {{{ */

void sleepOff(){
    digitalWrite(SLEEP_PIN, HIGH);
    delay(2);
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
byte timelapseMenuMax = 14;
byte timelapseMenuMin = 1;
unsigned int trackLen = 34800;
int numShots = 240;
int maxShots = 9999;
int minShots = 5;
unsigned int maxShutter = 1000;
unsigned int minMaxShutter = 100;
unsigned int maxMaxShutter = 30000;
unsigned long minDelay = 1; // Seconds
unsigned long maxDelay = 3600; // Seconds
unsigned long currentDelay = 10;
byte sleep = 1;
byte LCDOn = 1;
byte speed = 25;
long currentTime = 600; //10 min
long minTime = 60; // 1 min
long maxTime = 86400; // 24hrs
byte easingFunction = LINEAR;
byte easingFunctionMin = 1;
byte easingFunctionMax = 4;
byte easingCurve = EASEIN;
byte easingCurveMin = 1;
byte easingCurveMax = 5;
byte timingEasingFunction = LINEAR;
byte timingEasingFunctionMin = 1;
byte timingEasingFunctionMax = 4;
byte timingEasingCurve = EASEIN;
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
            sprintf(utilityString, "%04d minutes   ", currentTime / 60);
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
        case 8: //Easing Function
            easingFunction -= incrementVar(input, 0);
            easingFunction = reflow(easingFunction, easingFunctionMin, easingFunctionMax);
            sprintf(utilityString, "%s       ", easingFunctionName(easingFunction));
            lcdPrint(timelapseModeEasingFunctionLineOne, utilityString);
            break;
        case 9: //Easing Curve
            easingCurve -= incrementVar(input, 0);
            easingCurve = reflow(easingCurve, easingCurveMin, easingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(easingCurve));
            lcdPrint(timelapseModeEasingCurveLineOne, utilityString);
            break;
        case 10: // Time Easing Function
            timingEasingFunction -= incrementVar(input, 0);
            timingEasingFunction = reflow(timingEasingFunction, timingEasingFunctionMin, timingEasingFunctionMax);
            sprintf(utilityString, "%s       ", easingFunctionName(timingEasingFunction));
            lcdPrint(timelapseModeTimeEasingFunctionLineOne, utilityString);
            break;
        case 11: //Time Easing Curve
            timingEasingCurve -= incrementVar(input, 0);
            timingEasingCurve = reflow(timingEasingCurve , timingEasingCurveMin, timingEasingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(timingEasingCurve));
            lcdPrint(timelapseModeTimeEasingCurveLineOne, utilityString);
            break;
        case 12://Direction
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
        case 13: //
            lcdPrint("Move Right to   ", "start timelapse>");
            break;
        case 14:
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
const char* easingFunctionName(byte input){
    switch(input){
        case 1:
            return "1. Linear";
            break;
        case 2:
            return "2. Quad  ";
            break;
        case 3:
            return "3. Sine  ";
            break;
        case 4:
            return "4. Cubic ";
            break;
    }
}
/* }}} */
/* easingCurveName {{{ */
const char* easingCurveName(byte input){
    switch(input){
        case 1:
            return "1. Ease In  ";
            break;
        case 2:
            return "2. Ease Out ";
            break;
        case 3:
            return "3. EaseInOut";
            break;
        case 4:
            return "4. RevEaseIn";
            break;
        case 5:
            return "5.RevEaseOut";
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
    int shotDelay = instanceTime * 1000 / shots;

    // Slider Easing
    QuadraticEase quadEase;
    quadEase.setDuration(shots);
    quadEase.setTotalChangeInPosition(trackLen);
    SineEase sineEase;
    sineEase.setDuration(shots);
    sineEase.setTotalChangeInPosition(trackLen);
    CubicEase cubicEase;
    cubicEase.setDuration(shots);
    cubicEase.setTotalChangeInPosition(trackLen);

    // Time Easing
    QuadraticEase quadTimeEase;
    quadTimeEase.setDuration(shots);
    quadTimeEase.setTotalChangeInPosition(instanceTime * 1000);
    SineEase sineTimeEase;
    sineTimeEase.setDuration(shots);
    sineTimeEase.setTotalChangeInPosition(instanceTime * 1000);
    CubicEase cubicTimeEase;
    cubicTimeEase.setDuration(shots);
    cubicTimeEase.setTotalChangeInPosition(instanceTime * 1000);
    unsigned long timeEaseDelay = 0;

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
        switch(easingFunction){
            case QUADRATIC:
                switch(easingCurve){
                    case EASEIN:
                        stepInterval = long(quadEase.easeIn(i) - quadEase.easeIn(i - 1));
                        break;
                    case EASEOUT:
                        stepInterval = long(quadEase.easeOut(i) - quadEase.easeOut(i - 1));
                        break;
                    case EASEINOUT:
                        stepInterval = long(quadEase.easeInOut(i) - quadEase.easeInOut(i - 1));
                        break;
                    case REVEASEIN:
                        stepInterval = long(quadEase.easeIn(revI) - quadEase.easeIn(revI - 1));
                        break;
                    case REVEASEOUT:
                        stepInterval = long(quadEase.easeOut(revI) - quadEase.easeOut(revI - 1));
                        break;
                }
                break;
            case SINE:
                switch(easingCurve){
                    case EASEIN:
                        stepInterval = long(sineEase.easeIn(i) - sineEase.easeIn(i - 1));
                        break;
                    case EASEOUT:
                        stepInterval = long(sineEase.easeOut(i) - sineEase.easeOut(i - 1));
                        break;
                    case EASEINOUT:
                        stepInterval = long(sineEase.easeInOut(i) - sineEase.easeInOut(i - 1));
                        break;
                    case REVEASEIN:
                        stepInterval = long(sineEase.easeIn(revI) - sineEase.easeIn(revI - 1));
                        break;
                    case REVEASEOUT:
                        stepInterval = long(sineEase.easeOut(revI) - sineEase.easeOut(revI - 1));
                        break;
                }
                break;
            case CUBIC:
                switch(easingCurve){
                    case EASEIN:
                        stepInterval = long(cubicEase.easeIn(i) - cubicEase.easeIn(i - 1));
                        break;
                    case EASEOUT:
                        stepInterval = long(cubicEase.easeOut(i) - cubicEase.easeOut(i - 1));
                        break;
                    case EASEINOUT:
                        stepInterval = long(cubicEase.easeInOut(i) - cubicEase.easeInOut(i - 1));
                        break;
                    case REVEASEIN:
                        stepInterval = long(cubicEase.easeIn(revI) - cubicEase.easeIn(revI - 1));
                        break;
                    case REVEASEOUT:
                        stepInterval = long(cubicEase.easeOut(revI) - cubicEase.easeOut(revI - 1));
                        break;
                }
                break;
        }
        /* }}} */
        //turn off sleep
        if(sleep == 1){
            sleepOff();
        }
        if (dir > 1){
            stepInterval *= -1;
        }
        // Account for random direction changes
        if(EEPROM_DIRECTION == 2){
            stepInterval *= -1;
        }

        dampRotate(stepInterval, 15);
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
        switch(timingEasingFunction){
            case LINEAR:
                /* delay((shotDelay * 1000) - stepLen); */
                // Shot delay already calculated
                break;
            case QUADRATIC:
                switch(timingEasingCurve){
                    case EASEIN:
                        shotDelay = quadTimeEase.easeIn(i) - quadTimeEase.easeIn(i - 1);
                        break;
                    case EASEOUT:
                        shotDelay = quadTimeEase.easeOut(i) - quadTimeEase.easeOut(i - 1);
                        break;
                    case EASEINOUT:
                        shotDelay = quadTimeEase.easeInOut(i) - quadTimeEase.easeInOut(i - 1);
                        break;
                    case REVEASEIN:
                        stepInterval = long(quadTimeEase.easeIn(revI) - quadEase.easeIn(revI - 1));
                        break;
                    case REVEASEOUT:
                        stepInterval = long(quadTimeEase.easeOut(revI) - quadEase.easeOut(revI - 1));
                        break;
                }
                break;
            case SINE:
                switch(timingEasingCurve){
                    case EASEIN:
                        shotDelay = sineTimeEase.easeIn(i) - sineTimeEase.easeIn(i - 1);
                        break;
                    case EASEOUT:
                        shotDelay = sineTimeEase.easeOut(i) - sineTimeEase.easeOut(i - 1);
                        break;
                    case EASEINOUT:
                        shotDelay = sineTimeEase.easeInOut(i) - sineTimeEase.easeInOut(i - 1);
                        break;
                    case REVEASEIN:
                        stepInterval = long(sineTimeEase.easeIn(revI) - sineTimeEase.easeIn(revI - 1));
                        break;
                    case REVEASEOUT:
                        stepInterval = long(sineTimeEase.easeOut(revI) - sineTimeEase.easeOut(revI - 1));
                        break;
                }
                break;
            case CUBIC:
                switch(timingEasingCurve){
                    case EASEIN:
                        shotDelay = cubicTimeEase.easeIn(i) - cubicTimeEase.easeIn(i - 1);
                        break;
                    case EASEOUT:
                        shotDelay = cubicTimeEase.easeOut(i) - cubicTimeEase.easeOut(i - 1);
                        break;
                    case EASEINOUT:
                        shotDelay = cubicTimeEase.easeInOut(i) - cubicTimeEase.easeInOut(i - 1);
                        break;
                    case REVEASEIN:
                        stepInterval = long(cubicTimeEase.easeIn(revI) - cubicTimeEase.easeIn(revI - 1));
                        break;
                    case REVEASEOUT:
                        stepInterval = long(cubicTimeEase.easeOut(revI) - cubicTimeEase.easeOut(revI - 1));
                        break;
                }
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
    lcd.setBacklight(HIGH);
    sleepOff();
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
void quadraticEase(int dir, int steps, float speed, unsigned long time){
    QuadraticEase quadEase;
    QuadraticEase timeEase;
    quadEase.setDuration(steps);
    quadEase.setTotalChangeInPosition(35000);
    timeEase.setDuration(steps);
    unsigned long total_time = time * 1000;
    timeEase.setTotalChangeInPosition(total_time);
    unsigned long counter = 0;
    unsigned long time_counter = 0;
    unsigned long time_in_millis = time * 1000;
    for(float i = 1; i <= steps; i++){
        float move_steps = quadEase.easeInOut(i) - quadEase.easeInOut(i - 1);
        unsigned long move_start = millis();
        rotate(int(move_steps * dir), speed);
        delay(150);
        takePicture();
        counter += int(move_steps);
        unsigned long move_end = millis();
        unsigned long move_time = move_end - move_start;

        float time_delay = timeEase.easeInOut(i) - timeEase.easeInOut(i - 1);
        /* unsigned long time_delay = time_in_millis / steps; */
        time_counter += time_delay;

        if (time_delay < move_time){
            delay(0);
        } else {
            delay(int(time_delay) - move_time);
        }
    }
}
/* }}} */

/* }}} */
/* Realtime Movements ------------------------------------------ {{{ */

/* Realtime Menu Global Variables -------------------------------- {{{ */

byte realtimeMenuLocation = 1;
byte realtimeMenuMax = 7;
byte realtimeMenuMin = 1;
/* unsigned int trackLen = 34800; */
int realtimeNumShots = 500;
unsigned long realtimeMinDelay = 1; // Seconds
unsigned long realtimeMaxDelay = 3600; // Seconds
unsigned long realtimeCurrentDelay = 10;
byte realtimeCurrentMaxSpeed = 25;
byte realtimeCurrentMinSpeed = 10;
byte realtimeMaxSpeed = 99;
byte realtimeMinSpeed = 1;
byte realtimeEasingFunction = LINEAR;
byte realtimeEasingFunctionMin = 1;
byte realtimeEasingFunctionMax = 4;
byte realtimeEasingCurve = EASEIN;
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
        case 2: // Start Delay {{{
            if (realtimeCurrentDelay < 60){
                realtimeCurrentDelay += incrementVar(input, counter);
            } else {
                realtimeCurrentDelay += incrementVar(input, counter) * 60;
            }
            realtimeCurrentDelay = reflow(realtimeCurrentDelay, realtimeMinDelay, realtimeMaxDelay);

            if (realtimeCurrentDelay < 60){
                sprintf(utilityString, "%d seconds   ", realtimeCurrentDelay);
            } else {
                sprintf(utilityString, "%d minutes   ", realtimeCurrentDelay / 60);
            }
            lcdPrint(timelapseModeDelayLineOne, utilityString);
            break; // }}}
        case 3: //Easing Function
            realtimeEasingFunction -= incrementVar(input, 0);
            realtimeEasingFunction = reflow(realtimeEasingFunction, realtimeEasingFunctionMin, realtimeEasingFunctionMax);
            sprintf(utilityString, "%s       ", easingFunctionName(realtimeEasingFunction));
            lcdPrint(realtimeModeEasingFunctionLineOne, utilityString);
            break;
        case 4: //Easing Curve
            realtimeEasingCurve -= incrementVar(input, 0);
            realtimeEasingCurve = reflow(realtimeEasingCurve, realtimeEasingCurveMin, realtimeEasingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(realtimeEasingCurve));
            lcdPrint(realtimeModeEasingCurveLineOne, utilityString);
            break;
        case 5://Direction
            realtimeDirection += incrementVar(input, 0);
            realtimeDirection = reflow(realtimeDirection, 1, 2);
            if (realtimeDirection == 1){
                lcd.clear();
                lcdPrint("Movement Dir:   ", timelapseModeDirectionLineTwoME);
            } else {
                lcdPrint(timelapseModeDirectionLineOne, timelapseModeDirectionLineTwoEM);
            }
            break;
        case 6: //
            lcdPrint("Move Right to   ", "start RT move  >");
            break;
        case 7:
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

    int realtimeSpeedDiff = realtimeCurrentMaxSpeed - realtimeCurrentMinSpeed;

    // Slider Easing
    QuadraticEase realtimeQuadEase;
    realtimeQuadEase.setDuration(shots);
    realtimeQuadEase.setTotalChangeInPosition(realtimeSpeedDiff);
    SineEase sineEase;
    sineEase.setDuration(shots);
    sineEase.setTotalChangeInPosition(realtimeSpeedDiff);
    CubicEase cubicEase;
    cubicEase.setDuration(shots);
    cubicEase.setTotalChangeInPosition(realtimeSpeedDiff);

    long stepInterval = 1;
    long baseStepInterval = trackLen / shots;
    /* unsigned long stepStart = 0; */
    /* unsigned long stepLen = 0; */
    byte counter = 0;
    byte instanceSpeed = 1;
    instanceSpeed = realtimeCurrentMaxSpeed;

    //LCD Print Execute

    // Pre Delay
    /* delay(realtimeCurrentDelay * 1000); */

    for (int i = 1; i <= shots; i++){
        stepInterval = baseStepInterval;
        int revI = (shots + 1) - i;

        /* Slider Easing ----------------------------------------- {{{ */
        switch(realtimeEasingFunction){
            case LINEAR:
                instanceSpeed = realtimeCurrentMaxSpeed - realtimeCurrentMinSpeed;
                break;
            case QUADRATIC:
                switch(realtimeEasingCurve){
                    case EASEIN:
                        instanceSpeed = realtimeQuadEase.easeIn(i);
                        break;
                    case EASEOUT:
                        instanceSpeed = realtimeQuadEase.easeOut(i);
                        break;
                    case EASEINOUT:
                        instanceSpeed = realtimeQuadEase.easeInOut(i);
                        break;
                    case REVEASEIN:
                        instanceSpeed = realtimeQuadEase.easeIn(revI);
                        break;
                    case REVEASEOUT:
                        instanceSpeed = realtimeQuadEase.easeOut(revI);
                        break;
                }
                break;
            case SINE:
                switch(realtimeEasingCurve){
                    case EASEIN:
                        instanceSpeed = sineEase.easeIn(i);
                        break;
                    case EASEOUT:
                        instanceSpeed = sineEase.easeOut(i);
                        break;
                    case EASEINOUT:
                        instanceSpeed = sineEase.easeInOut(i);
                        break;
                    case REVEASEIN:
                        instanceSpeed = sineEase.easeIn(revI);
                        break;
                    case REVEASEOUT:
                        instanceSpeed = sineEase.easeOut(revI);
                        break;
                }
                break;
            case CUBIC:
                switch(realtimeEasingCurve){
                    case EASEIN:
                        instanceSpeed = cubicEase.easeIn(i);
                        break;
                    case EASEOUT:
                        instanceSpeed = cubicEase.easeOut(i);
                        break;
                    case EASEINOUT:
                        instanceSpeed = cubicEase.easeInOut(i);
                        break;
                    case REVEASEIN:
                        instanceSpeed = cubicEase.easeIn(revI);
                        break;
                    case REVEASEOUT:
                        instanceSpeed = cubicEase.easeOut(revI);
                        break;
                }
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
        /* sprintf(utilityString, "%2d              ", instanceSpeed + realtimeCurrentMinSpeed); */
        /* lcdPrint(realtimeModeProgressLineOne, utilityString); */

        rotate(stepInterval, instanceSpeed + realtimeCurrentMinSpeed);
        if(select()){
            counter += 1;
            if(counter > 4){
                break;
            }
        } else {
            counter = 0;
        }
    }
    sleepOff();
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
    int flashDelay = 2500;
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
    lcd.print(" Version 0.5.0");
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

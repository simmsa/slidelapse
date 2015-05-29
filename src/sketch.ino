/* Macros ----------------------------------------- {{{ */

/* #define DEBUG_ON */

/* }}} */
/* Libraries {{{ */

#include <math.h>
#include <stdlib.h>

#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#ifdef DEBUG_ON
#include <MemoryFree.h>
#endif
#include <avr/pgmspace.h>

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

/* Booleans {{{*/

const byte YES = 1;
const byte NO = 0;

/* }}} */
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

const char holdSelToExitProgmem[17] PROGMEM = "Hold Sel to Exit";
const char* selPointer[] PROGMEM = {
    holdSelToExitProgmem
};

/* Main Menu Strings {{{ */

const char selectModeString[17] PROGMEM        = "Select Mode:    ";
const char timelapseStringSelected[17] PROGMEM = "1.Timelapse    >";
const char realtimeStringSelected[17] PROGMEM  = "2.Video        >";
const char commandStringSelected[17] PROGMEM   = "3.Joystick     >";
const char directionStringSelected[17] PROGMEM = "4.Set Direction>";
const char debugStringSelected[17] PROGMEM     = "5.Debug        >";
const char* mainMenuStringPointers[] PROGMEM =
{
    selectModeString,
    timelapseStringSelected,
    realtimeStringSelected,
    commandStringSelected,
    directionStringSelected,
    debugStringSelected
};

/* }}} */
/* Timelapse Menu Strings {{{ */

const char enteringTlMode[17] PROGMEM           = ">>> Timelapse   ";
/* const char tlModeTrackLen[17] PROGMEM        = "Find Track Len.."; */
const char tlModeNumShots[17] PROGMEM           = "Number of Shots:";
const char tlModeDuration[17] PROGMEM           = "TL Duration:    ";
const char tlModeInterval[17] PROGMEM           = "Avg Interval:   ";
const char tlModeDelay[17] PROGMEM              = "Start Delay:    ";
const char tlModeLongestShutter[17] PROGMEM     = "Longest Shutter:";
const char tlModeSleepBetweenShots[17] PROGMEM  = "Sleep btw shots:";
const char tlModeLCD[17] PROGMEM                = "Backlight on?:  ";
const char tlModeEasingCurve[17] PROGMEM        = "Slide Ease Curv:";
const char tlModeCustomEaseAmt[17] PROGMEM      = "Slide Ease Amt: ";
const char tlModeTimeEasingCurve[17] PROGMEM    = "Time Ease Curve:";
const char tlModeTimeEasingAmt[17] PROGMEM      = "Time Ease Amt:  ";
const char tlModeDirectionLineOne[17] PROGMEM   = "Movement Dir:   ";
const char tlModeDirectionLineTwoME[17] PROGMEM = "Motor -----> End";
const char tlModeDirectionLineTwoEM[17] PROGMEM = "End -----> Motor";
const char tlModeRunningTl[17] PROGMEM          = "Timelapse active";
const char tlModeCompleted[17] PROGMEM          = "Timelapse Done! ";
const char *tlStringPointers[] PROGMEM = {
    enteringTlMode           , // 0
    tlModeNumShots           , // 1
    tlModeDuration           , // 2
    tlModeInterval           , // 3
    tlModeDelay              , // 4
    tlModeLongestShutter     , // 5
    tlModeSleepBetweenShots  , // 6
    tlModeLCD                , // 7
    tlModeEasingCurve        , // 8
    tlModeTimeEasingCurve    , // 9
    tlModeDirectionLineOne   , // 10
    tlModeDirectionLineTwoME , // 11
    tlModeDirectionLineTwoEM , // 12
    tlModeRunningTl          , // 13
    tlModeCompleted          , // 14
    tlModeCustomEaseAmt      , // 15
    tlModeTimeEasingAmt      , // 16
};

/* }}} */
/* Commander Menu Strings {{{ */

const char enteringCommandModeLineOne[17] PROGMEM = ">>> Commander   ";
const char cmdModeLineOne[17] PROGMEM             = "  Command Mode  ";
const char cmdModeLineTwoMotorToEnd[17] PROGMEM   = "Motor <----> End";
const char cmdModeLineTwoEndToMotor[17] PROGMEM   = "End <----> Motor";
const char cmdModeLineTwoChangeDir[17] PROGMEM    = "Reversing Dir <>";
const char *cmdPointers[] PROGMEM = {
    enteringCommandModeLineOne,
    cmdModeLineOne,
    cmdModeLineTwoMotorToEnd,
    cmdModeLineTwoEndToMotor,
    cmdModeLineTwoChangeDir
};

/* }}} */
/* Direction Menu Strings ---------------------------------------- {{{ */

const char enteringDirectionModeLineOne[17] PROGMEM = ">>> Direction   ";
const char directionModeLineOne[17] PROGMEM = "Set EEPROM Dir: ";
const char *dirPointers[] PROGMEM = {
    enteringDirectionModeLineOne,
    directionModeLineOne
};

/* }}} */
/* Status Menu Strings {{{ */

const char enteringDebugModeLineOne[17] PROGMEM = ">>> Debug Mode  ";
// Keep these as variables
char debugLineOne[17] = "";
char debugLineTwo[17] = "";
char switchOpen[2] = "O";
char switchPressed[2] = "P";
char switchError[2] = "X";

const char *statusPointers[] PROGMEM = {
    enteringDebugModeLineOne,
};

/* }}} */
/* Error Strings {{{ */

/* char genericErrorLineOne[17] = ">>> ERROR       "; */
/* char genericErrorLineTwo[17] = "Returning Home  "; */
const char genericErrorLineOne[17] PROGMEM = ">>> ERROR       ";
const char genericErrorLineTwo[17] PROGMEM = "Returning Home  ";

const char *errorPointers[] PROGMEM = {
    genericErrorLineOne,
    genericErrorLineTwo
};

/* }}} */
/* Realtime Menu Strings ---------------------------------------- {{{ */

const char enteringRealtimeModeLineOne[17] PROGMEM = ">>>Video Mode   ";
const char realtimeModeMinSpeedLineOne[17] PROGMEM = "Move Seconds:   ";
const char realtimeModeMaxSpeedLineOne[17] PROGMEM = "Move Max Speed: ";
const char realtimeModeEasingCurveLineOne[17] PROGMEM = "Vid Ease Curve: ";
const char realtimeModeEasingCurveAmt[17] PROGMEM = "Vid Ease Amt:   ";
const char realtimeModeCompletedLineOne[17] PROGMEM = "Move Complete!  ";

const char *realtimePointers[] PROGMEM = {
    enteringRealtimeModeLineOne,    // 0
    realtimeModeMinSpeedLineOne,    // 1
    realtimeModeMaxSpeedLineOne,    // 2
    realtimeModeEasingCurveLineOne, // 3
    realtimeModeCompletedLineOne,   // 4
    realtimeModeEasingCurveAmt,     // 5
};

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
/* Bezier Functions ------------------------------------------ {{{ */

double bezierOneControlPoint(unsigned long currentStep, unsigned long totalSteps, unsigned long maxValue, double easeFactor){
    double t = ((double) currentStep) / ((double) totalSteps);
    double y2 = (double) maxValue;
    // Linear ease factor = 0.5
    // Ease Out ease factor 1 > x > 0.5
    // Ease In ease factor 0.5 > x > 0.0
    double cpY = (double)maxValue * easeFactor;
    return (2 * cpY * (1 - t) * t) + (y2 * (t * t));
}

double optimizedBezierOneControlPointCpyValue(unsigned long maxValue, double easeFactor){
    return 2 * ((double) maxValue * easeFactor);
}

double optimizedBezierOneControlPoint(unsigned long currentStep, unsigned long totalSteps, unsigned long maxValue, unsigned long cpY1){
    double t = ((double) currentStep) / ((double) totalSteps);
    // Same as bezierOneControlPoint, but with precalculated
    // values for speed.
    return (cpY1 * (1 - t) * t) + (maxValue * (t * t));
}

unsigned int bezierOneControlPointStep(unsigned long currentStep, unsigned long totalSteps, unsigned long maxValue, double easeFactor){
    return (unsigned int) round(bezierOneControlPoint(currentStep, totalSteps, maxValue, easeFactor) - bezierOneControlPoint(currentStep - 1, totalSteps, maxValue, easeFactor));
}

struct easeData {
    unsigned long totalSteps;
    unsigned long maxValue;
    unsigned long cpY1;
    unsigned long cpY2;
};

struct easeData preCalcEaseInData(unsigned long totalSteps, unsigned long maxValue, double easeFactor){
    struct easeData result;
    result.totalSteps = totalSteps;
    result.maxValue = maxValue;
    result.cpY1 = (unsigned long) optimizedBezierOneControlPointCpyValue(maxValue, (0.5 - easeFactor / 2.0));
    return result;
}

struct easeData preCalcEaseOutData(unsigned long totalSteps, unsigned long maxValue, double easeFactor){
    struct easeData result;
    result.totalSteps = totalSteps;
    result.maxValue = maxValue;
    result.cpY1 = (unsigned long) optimizedBezierOneControlPointCpyValue(maxValue, (0.5 + easeFactor / 2.0));
    return result;
}

unsigned long easePos(unsigned long currentStep, struct easeData curve){
    return (unsigned long) optimizedBezierOneControlPoint(currentStep, curve.totalSteps, curve.maxValue, curve.cpY1);
}

double cubicBezier(unsigned long currentStep, unsigned long totalSteps, unsigned long trackLen, double control1Percent, double control2Percent){
    /* double t = (totalSteps - currentStep) / double(totalSteps); */
    double t = (double) currentStep / double(totalSteps);
    double b1 = t * t * t;
    double b2 = 3 * t * t * (1 - t);
    double b3 = 3 * t * (1 - t) * (1 - t);
    double b4 = (1 - t) * (1 - t) * (1 - t);
    double controlPoint1 = control1Percent * trackLen;
    double controlPoint2 = control2Percent * trackLen;
    return 0 * b1 + controlPoint1 * b2 + controlPoint2 * b3 + double(trackLen) * b4;
}

struct easeData preCalcFastSlowFast(unsigned long totalSteps, unsigned long maxValue, double easeFactor){
    struct easeData result;
    result.totalSteps = totalSteps;
    result.maxValue = maxValue;
    // p1 > p2
    result.cpY1 = (1 - ((1 - easeFactor) * 0.6667)) * (double) maxValue;
    result.cpY2 = ((1 - easeFactor) * 0.6667) * (double) maxValue;
    return result;
}

struct easeData preCalcSlowFastSlow(unsigned long totalSteps, unsigned long maxValue, double easeFactor){
    struct easeData result;
    result.totalSteps = totalSteps;
    result.maxValue = maxValue;
    // p2 > p1
    result.cpY1 = ((1 - easeFactor) * 0.3333) * (double) maxValue;
    result.cpY2 = (1 - ((1 - easeFactor) * 0.3333)) * (double) maxValue;
    return result;
}

double optimizedCubicBezier(unsigned long currentStep, struct easeData curve){
    double t = (double) currentStep / double(curve.totalSteps);
    double b2 = 3 * t * (1 - t) * (1 - t);
    double b3 = 3 * t * t * (1 - t);
    double b4 = t * t * t;
    return (curve.cpY1 * b2) + (curve.cpY2 * b3) + (curve.maxValue * b4);
}

unsigned long bezEasePos(unsigned long currentStep, struct easeData curve){
    return (unsigned long) optimizedCubicBezier(currentStep, curve);
}

struct easeData preCalcAllEaseData(unsigned long totalSteps, unsigned long maxValue, double easeAmount, byte easingCurve, byte timeEasing){
    // To achieve the same effect with time easing the easing curve
    // is inverted. To achieve this here we use the opposite function
    // i.e. time ease in == ease out.
    switch(easingCurve){
        case(EASEIN):
            if(timeEasing != 1){
                return preCalcEaseInData(totalSteps, maxValue, easeAmount);
            } else {
                return preCalcEaseOutData(totalSteps, maxValue, easeAmount);
            }
        case(EASEOUT):
            if(timeEasing != 1){
                return preCalcEaseOutData(totalSteps, maxValue, easeAmount);
            } else {
                return preCalcEaseInData(totalSteps, maxValue, easeAmount);
            }
        case(FASTSLOWFAST):
            if(timeEasing != 1){
                return preCalcFastSlowFast(totalSteps, maxValue, easeAmount);
            } else {
                return preCalcSlowFastSlow(totalSteps, maxValue, easeAmount);
            }
        case(SLOWFASTSLOW):
            if(timeEasing != 1){
                return preCalcSlowFastSlow(totalSteps, maxValue, easeAmount);
            } else {
                return preCalcFastSlowFast(totalSteps, maxValue, easeAmount);
            }
    }
}


struct easeData preCalcEaseData(unsigned long totalSteps, unsigned long maxValue, double easeAmount, byte easingCurve){
    return preCalcAllEaseData(totalSteps, maxValue, easeAmount, easingCurve, 0);
}

struct easeData preCalcTimeEaseData(unsigned long totalSteps, unsigned long maxValue, double easeAmount, double easingCurve){
    return preCalcAllEaseData(totalSteps, maxValue, easeAmount, easingCurve, 1);
}

unsigned long calcEasePos(unsigned long currentStep, struct easeData curveData, byte easingCurveType, unsigned long thisStep){
    switch(easingCurveType){
        case(EASEIN):
        case(EASEOUT):
            return easePos(currentStep, curveData);
        case(FASTSLOWFAST):
        case(SLOWFASTSLOW):
            return bezEasePos(currentStep, curveData);
    }
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
    constProgmemLcdPrint(cmdPointers, 1, cmdPointers, 2);
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
                    constProgmemLcdPrint(cmdPointers, 1, cmdPointers, 4);
                    delay(1000);
                    constProgmemLcdPrint(cmdPointers, 1, cmdPointers, 2);
                } else if (direction % 2 == 0){
                    constProgmemLcdPrint(cmdPointers, 1, cmdPointers, 4);
                    delay(1000);
                    constProgmemLcdPrint(cmdPointers, 1, cmdPointers, 3);
                }
            }
        }
        if (ypos == 1023){
            delay(400);
            if (analogRead(JOYSTICK_Y_PIN) == 1023){ // Joystick Up
                // Increase Speed
                currentSpeed += 10;
                //Reprint lcd
                currentSpeed = reflow(currentSpeed, 1, 100);
                sprintf(utilityString, "Speed: %02d       ", currentSpeed);
                constProgmemFirstLineLcdPrint(cmdPointers, 1, utilityString);
            } else {
                if (direction % 2 == 1){
                    /* delay(1000); */
                    constProgmemLcdPrint(cmdPointers, 1, cmdPointers, 2);
                } else if (direction % 2 == 0){
                    /* delay(1000); */
                    constProgmemLcdPrint(cmdPointers, 1, cmdPointers, 3);
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
byte timelapseMenuMax = 14;
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
byte sleep = YES;
byte LCDOn = YES;
byte speed = 25;
long currentTime = 1500; //25 min
long minTime = 60; // 1 min
unsigned long maxTime = 86400; // 24hrs
byte customizeCurve = NO;
byte easingCurve = LINEAR;
byte easingCurveMin = 1;
byte easingCurveMax = 5;
byte timingEasingCurve = LINEAR;
byte timingEasingCurveMin = 1;
byte timingEasingCurveMax = 5;
double customEasingCurveAmt = 0.5;
double customEasingCurveAmtMin = 0.01;
double customEasingCurveAmtMax = 0.99;
double customTimeEasingCurveAmt = 0.5;
double customTimeEasingCurveAmtMin = 0.01;
double customTimeEasingCurveAmtMax = 0.99;
byte timelapseDirection = 1;
int minInterval = 1000; // 1 sec

/* }}} */
/* configureTimelapse {{{ */
void configureTimelapse(){
    //Print current menu
    incrementTimelapseMenu(0, timelapseMenuLocation, 0, 0);
    int counter = 0;
    while(selectTrigger(1000)){
        int buttonDelay = 150;
        if (xHigh() || xLow()){
            delay(buttonDelay);
            counter += 1;
            if (xLow()){
                timelapseMenuLocation = reflow(timelapseMenuLocation - 1, timelapseMenuMin, timelapseMenuMax);
                incrementTimelapseMenu(0, timelapseMenuLocation, counter, -1);
            } else if (xHigh()){
                timelapseMenuLocation = reflow(timelapseMenuLocation + 1, timelapseMenuMin, timelapseMenuMax);
                incrementTimelapseMenu(0, timelapseMenuLocation, counter, 1);
            }
        } else if (yHigh() || yLow()){
            delay(buttonDelay);
            counter += 1;
            if (yLow()){
                incrementTimelapseMenu(-1, timelapseMenuLocation, counter, -1);
            } else if (yHigh()){
                incrementTimelapseMenu(1, timelapseMenuLocation, counter, 1);
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
// Dir:
//   -1 = Left
//   1 = Right
void incrementTimelapseMenu(int input, int currentMenu, int counter, int dir){
    switch(currentMenu){
        case 1: //Num of Shots
            numShots += incrementVar(input, counter);
            numShots = reflow(numShots, minShots, maxShots);
            sprintf(utilityString, "%04d            ", numShots);
            constProgmemFirstLineLcdPrint(tlStringPointers, 1, utilityString);
            break;
        case 2: //Duration
            currentTime += incrementVar(input, counter) * 60;
            currentTime = reflowUnsignedLong(currentTime, minTime, maxTime);
            sprintf(utilityString, "%04lu minutes   ", currentTime / 60L);
            constProgmemFirstLineLcdPrint(tlStringPointers, 2, utilityString);
            break;
        case 3: // Show Interval
            sprintf(utilityString, "%04d seconds    ", currentTime / numShots);
            constProgmemFirstLineLcdPrint(tlStringPointers, 3, utilityString);
            break;
        case 4: //Longest Shutter
            maxShutter += incrementVar(input, counter) * 1000;
            maxShutter = reflow(maxShutter, minMaxShutter, maxMaxShutter);
            sprintf(utilityString, "%02u seconds   ", maxShutter / 1000);
            constProgmemFirstLineLcdPrint(tlStringPointers, 5, utilityString);
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
            constProgmemFirstLineLcdPrint(tlStringPointers, 4, utilityString);
            break;
        case 6: // Sleep between shots
            sleep += incrementVar(input, 0);
            sleep = reflow(sleep, NO, YES);
            sprintf(utilityString, "%s             ", yesOrNo(sleep));
            constProgmemFirstLineLcdPrint(tlStringPointers, 6, utilityString);
            break;
        case 7: // LCD on / off
            LCDOn += incrementVar(input, 0);
            LCDOn = reflow(LCDOn, NO, YES);
            sprintf(utilityString, "%s             ", yesOrNo(LCDOn));
            constProgmemFirstLineLcdPrint(tlStringPointers, 7, utilityString);
            break;
        case 8: //Easing Curve
            EasingCurve:
            easingCurve -= incrementVar(input, 0);
            easingCurve = reflow(easingCurve, easingCurveMin, easingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(easingCurve));
            constProgmemFirstLineLcdPrint(tlStringPointers, 8, utilityString);
            break;
        case 9:
            if(easingCurve == LINEAR){
                // Skip this section
                if(dir > 0){
                    timelapseMenuLocation++;
                    goto TimeEasingCurve;
                } else {
                    timelapseMenuLocation--;
                    goto EasingCurve;
                }
                return;
            } else {
                customEasingCurveAmt += incrementDoubleVar(input, counter);
                customEasingCurveAmt = doubleReflow(customEasingCurveAmt, customEasingCurveAmtMin, customEasingCurveAmtMax);
                sprintf(utilityString, "0.%02d            ", (int) round(customEasingCurveAmt * 100));
                constProgmemFirstLineLcdPrint(tlStringPointers, 15, utilityString);
                break;
            }
        case 10: //Time Easing Curve
            TimeEasingCurve:
            timingEasingCurve -= incrementVar(input, 0);
            timingEasingCurve = reflow(timingEasingCurve , timingEasingCurveMin, timingEasingCurveMax);
            sprintf(utilityString, "%s    ", timeEasingCurveName(timingEasingCurve));
            constProgmemFirstLineLcdPrint(tlStringPointers, 9, utilityString);
            break;
        case 11:
            if(timingEasingCurve == LINEAR){
                // Skip this section
                if(dir > 0){
                    timelapseMenuLocation++;
                    goto TimelapseDirection;
                } else {
                    timelapseMenuLocation--;
                    goto TimeEasingCurve;
                }
                return;
            } else {
                customTimeEasingCurveAmt += incrementDoubleVar(input, counter);
                customTimeEasingCurveAmt = doubleReflow(customTimeEasingCurveAmt, customTimeEasingCurveAmtMin, customTimeEasingCurveAmtMax);
                sprintf(utilityString, "0.%02d            ", (int) round(customTimeEasingCurveAmt * 100));
                constProgmemFirstLineLcdPrint(tlStringPointers, 16, utilityString);
                break;
            }
        case 12://Direction
            TimelapseDirection:
            timelapseDirection += incrementVar(input, 0);
            timelapseDirection = reflow(timelapseDirection, 1, 2);
            if (timelapseDirection == 1){
                constProgmemLcdPrint(tlStringPointers, 10, tlStringPointers, 11);
            } else {
                constProgmemLcdPrint(tlStringPointers, 10, tlStringPointers, 12);
            }
            break;
        case 13: //
            lcdPrint("Move Right to   ", "start timelapse>");
            break;
        case 14:
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

double incrementDoubleVar(int input, int counter){
    if (input > 0){
        if (counter > 10){
            return 0.10;
        } else {
            return 0.01;
        }
    } else if (input < 0){
        if (counter > 10){
            return -0.10;
        } else {
            return -0.01;
        }
    }
    return 0.0;
}
/* }}} */
/* easingCurveName {{{ */
const char* easingCurveName(byte input){
    switch(input){
        case 1:
            return "1. Linear       ";
            break;
        case 2:
            return "2. Big -> Small ";
            break;
        case 3:
            return "3. Small -> Big ";
            break;
        case 4:
            return "4.Big>Small>Big ";
            break;
        case 5:
            return "5.Small>Big>Sml";
            break;
    }
}

const char* timeEasingCurveName(byte input){
    switch(input){
        case 1:
            return "1. Linear       ";
            break;
        case 2:
            return "2. Long -> Short";
            break;
        case 3:
            return "3. Short -> Long";
            break;
        case 4:
            return "4.Long>Shrt>Long";
            break;
        case 5:
            return "5.Shrt>Long>Shrt";
            break;
    }
}
/* }}} */
/* yesOrNo -------------------------------------------------- {{{ */

const char* yesOrNo(byte input){
    switch(input){
        case YES:
            return "Yes";
            break;
        case NO:
            return "No ";
            break;
    }
}

/* }}} */
/* startTimelapse -------------------------------------------------- {{{ */

void startTimelapse(){
    timelapse(timelapseDirection, numShots, currentTime);
    timelapseMenuLocation = 1;
    constProgmemLcdPrint(tlStringPointers, 14, selPointer, 0);
    return;
}

/* }}} */
/* timelapse -------------------------------------------------- {{{ */

void timelapse(byte dir, unsigned long shots, unsigned long instanceTime){
    // Total milliseconds of a timelapse. Milliseconds less accurate
    // than microseconds but the overflow for milliseconds is
    // ~ 70 minutes, too short for some timelapse intervals.
    unsigned long totalTime = instanceTime * 1000;


    struct easeData slideEaseData = preCalcEaseData(shots, trackLen,customEasingCurveAmt, easingCurve);
    struct easeData timeEaseData = preCalcTimeEaseData(shots, totalTime,customTimeEasingCurveAmt, timingEasingCurve);

    // Pre Delay
    delay(currentDelay * 1000);

    if (LCDOn == 2){
        lcd.setBacklight(LOW);
    }

    unsigned long stepStart = 0;
    unsigned long stepLen = 0;
    byte counter = 0;

    // Keeping track of the slide and time positions
    unsigned long prevSlides = 0;
    unsigned int thisSlide = trackLen / shots;
    unsigned long prevTime = 0;
    // How long the interval should be if each shot takes O time
    // The time to move and shoot is subtracted to calculate the
    // exact time of a timelapse
    unsigned long thisDelay = totalTime / shots;

    // Set the direction
    setDir(dir);

    // Starting Loop
    for (unsigned long i = 1; i <= shots; i++){
        stepStart = millis();
        showTimelapseProgress(i, shots);
        takePicture();
        delay(maxShutter);

        if(easingCurve > LINEAR){
            thisSlide = calcEasePos(i, slideEaseData, easingCurve, thisSlide) - prevSlides;
            prevSlides += thisSlide;
        }

        if(sleep == 1){
            sleepOff();
        }

        dampRotate(thisSlide);

        if(sleep == 1){
            sleepOn();
        }

        if(select()){
            counter += 1;
            if(counter >= 2){
                break;
            }
        } else {
            counter = 0;
        }

        stepLen = millis() - stepStart;

        if(timingEasingCurve > LINEAR){
            thisDelay = calcEasePos(i, timeEaseData, timingEasingCurve, thisDelay) - prevTime;
            prevTime += thisDelay;
        }

        // Only delay the shot if the elapsed time from shooting and
        // moving is less than the calculated interval. Subtract this
        // time from the interval before delaying
        if (stepLen < thisDelay){
            delay((thisDelay) - stepLen);
        }
    }
}

/* }}} */
/* showTimelapseProgress ---------------------------------------- {{{ */

void showTimelapseProgress(unsigned long currentShot, unsigned long totalShots){
    sprintf(utilityString, "Progress: %02d%%  ",int( currentShot * 100 / totalShots));
    constProgmemFirstLineLcdPrint(tlStringPointers, 13, utilityString);
}

/* }}} */

/* }}} */
/* Realtime Movements ------------------------------------------ {{{ */

/* Realtime Menu Global Variables -------------------------------- {{{ */

byte realtimeMenuLocation = 1;
byte realtimeMenuMax = 6;
byte realtimeMenuMin = 1;
int realtimeNumShots = 1000;
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
double realtimeCustomEasingAmt = 0.50;
double realtimeCustomEasingAmtMin = 0.00;
double realtimeCustomEasingAmtMax = 0.99;
long realtimeTotalSeconds = 15;
long realtimeTotalSecondsMin = 1;
long realtimeTotalSecondsMax = 300;

/* }}} */
/* configureRealtime {{{ */
void configureRealtime(){
    //Print current menu
    incrementRealtimeMenu(0, realtimeMenuLocation, 0, 0);
    int counter = 0;
    while(selectTrigger(1000)){
        int buttonDelay = 150;
        if (xHigh() || xLow()){
            delay(buttonDelay);
            counter += 1;
            if (xLow()){
                realtimeMenuLocation = reflow(realtimeMenuLocation - 1, realtimeMenuMin, realtimeMenuMax);

                incrementRealtimeMenu(0, realtimeMenuLocation, counter, -1);
            } else if (xHigh()){
                realtimeMenuLocation = reflow(realtimeMenuLocation + 1, realtimeMenuMin, realtimeMenuMax);
                incrementRealtimeMenu(0, realtimeMenuLocation, counter, 1);
            }
        } else if (yHigh() || yLow()){
            delay(buttonDelay);
            counter += 1;
            if (yLow()){
                incrementRealtimeMenu(-1, realtimeMenuLocation, counter, 0);
            } else if (yHigh()){
                incrementRealtimeMenu(1, realtimeMenuLocation, counter, 0);
            }
        } else {
            counter = 0;
        }
    }
}
/* }}} */
/* incrementRealtimeMenu {{{ */
/* dir */
/* -1 = left */
/* 1 = right */
void incrementRealtimeMenu(int input, int currentMenu, int counter, int dir){
    switch(currentMenu){
        case 1: // Move Time
            realtimeTotalSeconds += incrementVar(input, counter);
            realtimeTotalSeconds = reflowLong(realtimeTotalSeconds, realtimeTotalSecondsMin, realtimeTotalSecondsMax);
            sprintf(utilityString, "%3ld seconds     ", realtimeTotalSeconds);
            constProgmemFirstLineLcdPrint(realtimePointers, 1, utilityString);
            break;
        case 2: //Easing Curve
            RTEasingCurve:
            realtimeEasingCurve -= incrementVar(input, 0);
            realtimeEasingCurve = reflow(realtimeEasingCurve, realtimeEasingCurveMin, realtimeEasingCurveMax);
            sprintf(utilityString, "%s    ", easingCurveName(realtimeEasingCurve));
            constProgmemFirstLineLcdPrint(realtimePointers, 3, utilityString);
            break;
        case 3: // Easing Amount
            if(realtimeEasingCurve == LINEAR){
                if(dir > 0){
                    realtimeMenuLocation++;
                    goto RTDirection;
                } else {
                    realtimeMenuLocation--;
                    goto RTEasingCurve;
                }
            } else {
                realtimeCustomEasingAmt += incrementDoubleVar(input, counter);
                realtimeCustomEasingAmt = doubleReflow(realtimeCustomEasingAmt, realtimeCustomEasingAmtMin, realtimeCustomEasingAmtMax);
                sprintf(utilityString, "0.%02d            ", (int) round(realtimeCustomEasingAmt * 100));
                constProgmemFirstLineLcdPrint(realtimePointers, 5, utilityString);
                break;
            }
        case 4://Direction
            RTDirection:
            realtimeDirection += incrementVar(input, 0);
            realtimeDirection = reflow(realtimeDirection, 1, 2);
            if (realtimeDirection == 1){
                constProgmemLcdPrint(tlStringPointers, 10, tlStringPointers, 11);
            } else {
                constProgmemLcdPrint(tlStringPointers, 10, tlStringPointers, 12);
            }
            break;
        case 5: //
            lcdPrint("Move Right to   ", "start Vid move >");
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
    constProgmemLcdPrint(realtimePointers, 4, selPointer, 0);

}

/* }}} */
/* realtime -------------------------------------------------- {{{ */

void realtime(byte dir, int shots){
    // Keeps track of how many loops the select button was pressed
    byte counter = 0;

    // Time in microseconds (millionths of a second) of the move.
    unsigned long totalTime = (unsigned long) (realtimeTotalSeconds * 1000000);

    struct easeData rtEaseData = preCalcTimeEaseData(trackLen, totalTime, realtimeCustomEasingAmt, realtimeEasingCurve);

    unsigned long prevSteps = 0;
    unsigned long thisStep = totalTime / trackLen;
    unsigned long calcStart = 0;

    sleepOff();
    setDir(dir);
    takeVideo();
    /* delay(3000); // Add editing time before shot */

    for (unsigned long i = 1; i <= trackLen; i++){
        calcStart = micros();
        if(realtimeEasingCurve > LINEAR){
            thisStep = calcEasePos(i, rtEaseData, realtimeEasingCurve, thisStep) - prevSteps;
            prevSteps += thisStep;
        }

        absoluteRotate((int)(thisStep - (micros() - calcStart)), 1);

        if(select()){
            counter += 1;
            if(counter > 4){
                break;
            }
        } else {
            counter = 0;
        }
    }

    /* delay(3000); // Edit time after shot */
    takeVideo();
    sleepOff();
}

/* }}} */
/* absoluteRotate --------------------------------------------- {{{ */

void absoluteRotate(int usDelay){

    if(usDelay < 6){
        // The arduino docs state that a 3 microsecond delay is the
        // smallest microsecond delay that is accurate. 6 / 2 = 3.
        usDelay = 6;
    }

    unsigned int firstDelay = usDelay / 2;
    unsigned int lastDelay = usDelay - firstDelay;

    for(unsigned int i = 0; i < steps; i++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(firstDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(lastDelay);
    }
}

void setDir(byte inputDir){
    int rotateDir = 1;
    if (inputDir == 2){
        rotateDir *= -1;
    }

    // Account for random direction changes
    if(EEPROM_DIRECTION == 2){
        rotateDir *= -1;
    }
    if(rotateDir > 0){
        digitalWrite(DIR_PIN, HIGH);
    } else {
        digitalWrite(DIR_PIN, LOW);
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
    constProgmemFirstLineLcdPrint(dirPointers, 1, utilityString);

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
            constProgmemFirstLineLcdPrint(dirPointers, 1, utilityString);
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
/* PROGMEM -------------------------------------------------- {{{ */

char strBuffer[17];
void convertArrayString(const char** strArray, byte position){
    strcpy_P(strBuffer, (char*)pgm_read_word(&(strArray[position])));
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
/* constProgmemLcdPrint --------------------------------------- {{{ */

void constProgmemLcdPrint(const char** strArray1, byte pos1, const char** strArray2, byte pos2){
    lcd.setCursor(0, 0);
    convertArrayString(strArray1, pos1);
    lcd.print(strBuffer);

    lcd.setCursor(0,1);
    convertArrayString(strArray2, pos2);
    lcd.print(strBuffer);
}

/* }}} */
/* constProgmemFirstLineLcdPrint --------------------------------- {{{ */

void constProgmemFirstLineLcdPrint(const char** strArray, byte pos, char* line2){
    lcd.setCursor(0, 0);
    convertArrayString(strArray, pos);
    lcd.print(strBuffer);

    lcd.setCursor(0, 1);
    lcd.print(line2);
}

/* }}} */
/* constLcdPrint {{{ */
void constLcdPrint(const char* line1, const char* line2){

    /* Line 1 */
    lcd.setCursor(0, 0); //Cursor Position, Line Number
    lcd.print(line1);

    /* Line 2 */
    lcd.setCursor(0, 1);
    lcd.print(line2);
}
void constFirstLcdPrint(const char* line1, char* line2){
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
    constProgmemLcdPrint(mainMenuStringPointers, 0, mainMenuStringPointers, currentMenuPosition);
#ifdef DEBUG_ON
    printMemory();
#endif
    while (directionTrigger(50, RIGHT) == true){
        int currentJoystickPosition = readJoystick(50);
        if (currentJoystickPosition == UP){
            currentMenuPosition -= 1;
            currentMenuPosition = reflow(currentMenuPosition, minMenuPosition, maxMenuPosition);
            constProgmemLcdPrint(mainMenuStringPointers, 0, mainMenuStringPointers, currentMenuPosition);
        } else if (currentJoystickPosition == DOWN) {
            currentMenuPosition += 1;
            currentMenuPosition = reflow(currentMenuPosition, minMenuPosition, maxMenuPosition);
            constProgmemLcdPrint(mainMenuStringPointers, 0, mainMenuStringPointers, currentMenuPosition);
        }
    }
#ifdef DEBUG_ON
    printMemory();
#endif
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

unsigned long reflowUnsignedLong(unsigned long input, unsigned long minOutput, unsigned long maxOutput){
    if (input > maxOutput){
        return minOutput;
    } else if (input < minOutput){
        return maxOutput;
    } else {
        return input;
    }
}

long reflowLong(long input, long minOutput, long maxOutput){
    if (input > maxOutput){
        return minOutput;
    } else if (input < minOutput){
        return maxOutput;
    } else {
        return input;
    }
}

double doubleReflow(double input, double minOutput, double maxOutput){
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
            constProgmemLcdPrint(tlStringPointers, 0, selPointer, 0);
            delay(flashDelay);
            configureTimelapse();
            break;
        case 2: // Realtime
            constProgmemLcdPrint(realtimePointers, 0, selPointer, 0);
            delay(flashDelay);
            configureRealtime();
            break;
        case 3: // Command
            constProgmemLcdPrint(cmdPointers, 0, selPointer, 0);
            delay(flashDelay);
            commanderMode();
            break;
        case 4: // Direction
            constProgmemLcdPrint(dirPointers, 0, selPointer, 0);
            delay(flashDelay);
            directionChanger();
            break;
        case 5: // Debug
            constProgmemLcdPrint(statusPointers, 0, selPointer, 0);
            delay(flashDelay);
            status();
            break;
        default:
            constProgmemLcdPrint(errorPointers, 0, errorPointers, 1);
            delay(flashDelay);
            menuShow();
            break;
    }
}

/* }}} */

/* }}} */
/* Helper Functions ------------------------------------------------ {{{ */

#ifdef DEBUG_ON
void printMemory(){
    Serial.print(F("Free Memory: "));
    Serial.print(freeMemory());
    Serial.print(F(" bytes.\r\n"));
}
#endif

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
#ifdef DEBUG_ON
    Serial.begin(115200);
    Serial.print(F("Beginning Serial!\r\n"));
#endif

    /* Camera Pin Setup */
    pinMode(SHUTTER_PIN, OUTPUT);

    /* LCD Pin Setup */
    lcd.begin(16, 2);
    lcd.print(F("   Slidelapse"));
    lcd.setCursor(0, 1);
    lcd.print(F(" Version 0.9.0"));
    delay(1000);
    lcd.clear();

    /* EEPROM Direction Read */
    /* EEPROM.write(EEPROM_DIRECTION_LOC, 2); */
    EEPROM_DIRECTION = EEPROM.read(EEPROM_DIRECTION_LOC);

    /* Joystick Pin Setup */
    pinMode(JOYSTICK_SELECT_PIN, INPUT_PULLUP);

    /* Switch Pin Setup */
    pinMode(MOTOR_SWITCH_PIN, INPUT);
    pinMode(END_SWITCH_PIN, INPUT);

    /* Testing Memory */
#ifdef DEBUG_ON
    printMemory();
#endif

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

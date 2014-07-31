#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "QuadraticEase.h"
#include "SineEase.h"
#include "CubicEase.h"
byte readJoystick(int buttonDelay);
void rotate(int steps, byte speed);
void dampRotate(int steps, byte maxSpeed);
void sleepOn();
void sleepOff();
void findTrackLen();
void commanderMode();
byte calcSpeed(int input, int maxInput, byte maxOutput);
int joystickX();
int joystickY();
bool select();
bool xHigh();
bool xLow();
bool yHigh();
bool yLow();
void configureTimelapse();
void incrementTimelapseMenu(int input, int currentMenu, int counter);
int incrementVar(int input, int counter);
const char* easingFunctionName(byte input);
const char* easingCurveName(byte input);
const char* yesOrNo(byte input);
void startTimelapse();
void timelapse(byte dir, int shots, unsigned long time);
void showTimelapseProgress(int currentShot, int totalShots);
void quadraticEase(int dir, int steps, float speed, unsigned long time);
void takePicture();
bool selectTrigger(int duration);
bool directionTrigger(unsigned long duration, int direction);
char* formattedSwitch(byte status);
char* formattedReverseSwitch(byte status);
void status();
void joystickPosition(int buttonDelay);
void lcdPrint(char* line1, char* line2);
char* menuOptions(int input);
void menuShow();
int reflow(int input, int minOutput, int maxOutput);
void secondaryMenuShow(int input);
void setup();
void loop();
#line 1 "src/sketch.ino"
/* Libraries {{{ */

//#include <Wire.h>
//#include <LiquidCrystal.h>
//#include "QuadraticEase.h"
//#include "SineEase.h"
//#include "CubicEase.h"

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

/* }}} */
/* Menu Strings {{{ */

/* Main Menu Strings {{{ */

char selectModeString[17] = "Select Mode:    ";
char timelapseStringSelected[17] = "1.Timelapse    >";
char commandStringSelected[17] = "2.Commander    >";
char debugStringSelected[17] = "3.Debug        >";

/* }}} */
/* Timelaspe Menu Strings {{{ */
char enteringTimelapseModeLineOne[17] = ">>> Timelapse   ";
char enteringTimelapseModeLineTwo[17] = "Hold Sel to exit";

char timelapseModeTrackLenLineOne[17] = "Find Track Len..";
char timelapseModeTrackLenLineTwo[17] = "";

char timelapseModeNumShotsLineOne[17] = "Number of Shots:";
char timelapseModeNumShotsLineTwo[17] = "";

char timelapseModeDurationLineOne[17] = "TL Duration:    ";
char timelapseModeDurationLineTwo[17] = "";

char timelapseModeIntervalLineOne[17] = "Avg Interval:   ";
char timelapseModeIntervalLineTwo[17] = "";

char timelapseModeLongestShutterLineOne[17] = "Longest Shutter:";
char timelapseModeLongestShutterLineTwo[17] = "";

char timelapseModeSleepBetweenShotsLineOne[17] = "Sleep btw shots ";
char timelapseModeSleepBetweenShotsLineTwo[17] = "";

char timelapseModeEasingFunctionLineOne[17] = "Easing function:";
char timelapseModeEasingFunctionLineTwo[17] = "";

char timelapseModeEasingCurveLineOne[17] = "Easing Curve:   ";
char timelapseModeEasingCurveLineTwo[17] = "";

char timelapseModeDirectionLineOne[17] = "Movement Dir:   ";
char timelapseModeDirectionLineTwoME[17] = "Motor -----> End";
char timelapseModeDirectionLineTwoEM[17] = "End -----> Motor";

char timelapseModeStartingTimelapseLineOne[17] = "Start Timelapse ";
char timelapseModeStartingTimelapseLineTwo[17] = "Hold Sel to exit";

char timelapseModeRunningTimelapseLineOne[17] = "Timelapse active";
char timelapseModeRunningTimelapseLineTwo[17] = "";

char timelapseModeCompletedLineOne[17] = "Timelapse Done  ";
char timelapseModeCompletedLineTwo[17] = "Hold Sel to exit";
/* }}} */
/* Commander Menu Strings {{{ */

char enteringCommandModeLineOne[17] = ">>> Commander   ";
char enteringCommandModeLineTwo[17] = "Hold Sel to exit";

char commandModeLineOne[17] = "  Command Mode  ";
char commandModeLineTwoMotorToEnd[17] = "Motor <----> End";
char commandModeLineTwoEndToMotor[17] = "End <----> Motor";
char commandModeLineTwoChangingDirection[17] = "Reversing Dir <>";

/* }}} */
/* Status Menu Strings {{{ */

char enteringDebugModeLineOne[17] = ">>> Debug Mode  ";
char enteringDebutModeLineTwo[17] = "Hold Sel to exit";
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
    lcdPrint(timelapseModeTrackLenLineOne, timelapseModeTrackLenLineTwo);
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
            sprintf(timelapseModeTrackLenLineTwo, "Max Len:%05ld   ", maxTrackLen);
            lcdPrint(timelapseModeTrackLenLineOne, timelapseModeTrackLenLineTwo);
        } else if (digitalRead(END_SWITCH_PIN) == HIGH){
            direction = -1;
            rotate(direction, 25);
            currentTrackLen = 0;
            sprintf(timelapseModeTrackLenLineTwo, "Max Len:%05ld   ", maxTrackLen);
            lcdPrint(timelapseModeTrackLenLineOne, timelapseModeTrackLenLineTwo);
        }
    }
}
/* }}} */
/* commanderMode {{{ */
void commanderMode(){
    lcdPrint(commandModeLineOne, commandModeLineTwoMotorToEnd);
    int direction = 1; // Odd is motor to end, Even is end to motor
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
byte timelapseMenuMax = 10;
byte timelapseMenuMin = 1;
unsigned int trackLen = 34800;
int numShots = 20;
int maxShots = 9999;
int minShots = 5;
unsigned int maxShutter = 1000;
unsigned int minMaxShutter = 100;
unsigned int maxMaxShutter = 30000;
byte sleep = 1;
byte speed = 25;
long time = 120; //30 min
long minTime = 60; // 1 min
long maxTime = 86400; // 24hrs
byte easingFunction = LINEAR;
byte easingFunctionMin = 1;
byte easingFunctionMax = 4;
byte easingCurve = EASEIN;
byte easingCurveMin = 1;
byte easingCurveMax = 3;
byte timelapseDirection = 1;
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
            sprintf(timelapseModeNumShotsLineTwo, "%04d            ", numShots);
            lcdPrint(timelapseModeNumShotsLineOne, timelapseModeNumShotsLineTwo);
            break;
        case 2: //Duration
            time += incrementVar(input, counter) * 60;
            time = reflow(time, minTime, maxTime);
            sprintf(timelapseModeDurationLineTwo, "%04d minutes   ", time / 60);
            lcdPrint(timelapseModeDurationLineOne, timelapseModeDurationLineTwo);
            break;
        case 3: //Longest Shutter
            maxShutter += incrementVar(input, counter) * 1000;
            maxShutter = reflow(maxShutter, minMaxShutter, maxMaxShutter);
            sprintf(timelapseModeLongestShutterLineTwo, "%02u seconds   ", maxShutter / 1000);
            lcdPrint(timelapseModeLongestShutterLineOne, timelapseModeLongestShutterLineTwo);
            break;
        case 4: // Show Interval
            sprintf(timelapseModeIntervalLineTwo, "%04d seconds    ", time / numShots);
            lcdPrint(timelapseModeIntervalLineOne, timelapseModeIntervalLineTwo);
            break;
        case 5: // Sleep between shots
            sleep += incrementVar(input, 0);
            sleep = reflow(sleep, 1, 2);
            sprintf(timelapseModeSleepBetweenShotsLineTwo, "%s             ", yesOrNo(sleep));
            lcdPrint(timelapseModeSleepBetweenShotsLineOne, timelapseModeSleepBetweenShotsLineTwo);
            break;
        case 6: //Easing Function
            easingFunction -= incrementVar(input, 0);
            easingFunction = reflow(easingFunction, easingFunctionMin, easingFunctionMax);
            sprintf(timelapseModeEasingFunctionLineTwo, "%s       ", easingFunctionName(easingFunction));
            lcdPrint(timelapseModeEasingFunctionLineOne, timelapseModeEasingFunctionLineTwo);
            break;
        case 7: //Easing Curve
            easingCurve -= incrementVar(input, 0);
            easingCurve = reflow(easingCurve, easingCurveMin, easingCurveMax);
            sprintf(timelapseModeEasingCurveLineTwo, "%s    ", easingCurveName(easingCurve));
            lcdPrint(timelapseModeEasingCurveLineOne, timelapseModeEasingCurveLineTwo);
            break;
        case 8://Direction
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
        case 9: //
            lcdPrint("Move Right to   ", "start timelapse>");
            break;
        case 10:
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
    (timelapseDirection, numShots, time * 1000);
    timelapseMenuLocation = 1;
    lcdPrint(timelapseModeCompletedLineOne, timelapseModeCompletedLineTwo);
    return;
}

/* }}} */
/* timelapse -------------------------------------------------- {{{ */

void timelapse(byte dir, int shots, unsigned long time){
    int shotDelay = time / shots;
    QuadraticEase quadEase;
    quadEase.setDuration(shots);
    quadEase.setTotalChangeInPosition(trackLen);
    SineEase sineEase;
    sineEase.setDuration(shots);
    sineEase.setTotalChangeInPosition(trackLen);
    CubicEase cubicEase;
    cubicEase.setDuration(shots);
    cubicEase.setTotalChangeInPosition(trackLen);
    int stepInterval = trackLen / shots;
    unsigned long stepStart = 0;
    unsigned long stepLen = 0;
    byte counter = 0;
    for (int i = 1; i <= shots; i++){
        stepStart = millis();
        showTimelapseProgress(i, shots);
        takePicture();
        delay(maxShutter);
        switch(easingFunction){
            case QUADRATIC:
                switch(easingCurve){
                    case EASEIN:
                        stepInterval = int(quadEase.easeIn(i) - quadEase.easeIn(i - 1));
                        break;
                    case EASEOUT:
                        stepInterval = int(quadEase.easeOut(i) - quadEase.easeOut(i - 1));
                        break;
                    case EASEINOUT:
                        stepInterval = int(quadEase.easeInOut(i) - quadEase.easeInOut(i - 1));
                        break;
                }
                break;
            case SINE:
                switch(easingCurve){
                    case EASEIN:
                        stepInterval = int(sineEase.easeIn(i) - sineEase.easeIn(i - 1));
                        break;
                    case EASEOUT:
                        stepInterval = int(sineEase.easeOut(i) - sineEase.easeOut(i - 1));
                        break;
                    case EASEINOUT:
                        stepInterval = int(sineEase.easeInOut(i) - sineEase.easeInOut(i - 1));
                        break;
                }
                break;
            case CUBIC:
                switch(easingCurve){
                    case EASEIN:
                        stepInterval = int(cubicEase.easeIn(i) - cubicEase.easeIn(i - 1));
                        break;
                    case EASEOUT:
                        stepInterval = int(cubicEase.easeOut(i) - cubicEase.easeOut(i - 1));
                        break;
                    case EASEINOUT:
                        stepInterval = int(cubicEase.easeInOut(i) - cubicEase.easeInOut(i - 1));
                        break;
                }
                break;
        }
        //turn off sleep
        if(sleep == 1){
            sleepOff();
        }
        if (dir > 1){
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
        if (stepLen < shotDelay){
            delay(shotDelay - stepLen);
        }
    }
    /* if(sleep == 1){ */
    /*     sleepOn(); */
    /* } */
    sleepOff();
    return;
}

/* }}} */
/* showTimelapseProgress ---------------------------------------- {{{ */

void showTimelapseProgress(int currentShot, int totalShots){
    sprintf(timelapseModeRunningTimelapseLineTwo, "Progress: %02d%%  ",int( currentShot * 100 / totalShots));
    lcdPrint(timelapseModeRunningTimelapseLineOne, timelapseModeRunningTimelapseLineTwo);
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
// Camera Functions {{{

void takePicture(){
    digitalWrite(SHUTTER_PIN, HIGH);
    delay(150);
    digitalWrite(SHUTTER_PIN, LOW);
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
    menuShow();
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
            return commandStringSelected;
            break;
        case 3:
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
int maxMenuPosition = 3;

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
        case 1:
            lcdPrint(enteringTimelapseModeLineOne, enteringTimelapseModeLineTwo);
            delay(flashDelay);
            configureTimelapse();
            break;
        case 2:
            lcdPrint(enteringCommandModeLineOne, enteringCommandModeLineTwo);
            delay(flashDelay);
            commanderMode();
            break;
        case 3:
            lcdPrint(enteringDebugModeLineOne, enteringDebutModeLineTwo);
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
    lcd.print(" Version 0.4.0");
    delay(3000);
    lcd.clear();

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

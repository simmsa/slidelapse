#include <Arduino.h>
#include <Button.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "QuadraticEase.h"
void rotate(int steps, float speed);
void rotateDeg(float deg, float speed);
void quadraticEase(int dir, int steps, float speed, unsigned long time);
void takePicture();
void setup();
void loop();
#line 1 "src/sketch.ino"
// Libraries {{{
//#include <Button.h>
//#include <Wire.h>
//#include <LiquidCrystal.h>
//#include "QuadraticEase.h"
/* }}} */

/* Pin Setup {{{ */
/* Stepper Pin Setup */
const int DIR_PIN = 2;
const int STEP_PIN = 3;
const int SLEEP_PIN = 9;

// Button Setup
/* const int BUTTON_GO = 8; */
/* Button goButton = Button(BUTTON_GO, BUTTON_PULLDOWN); */
/* bool buttonState = false; */

// Joystick Setup
const int JOYSTICK_X_PIN = 0; // Analog 0
const int JOYSTICK_Y_PIN = 1; // Analog 1
const int JOYSTICK_SELECT_PIN = 10; // Digital 8

// LCD Setup
LiquidCrystal lcd(0);

// Camera Setup
const int SHUTTER_PIN = 7;
const int FLASH_IN_PIN = 5;

// Switch Setup
const int MOTOR_SWITCH_PIN = 4;
const int END_SWITCH_PIN = 6;

/* }}} */

// Stepper direction
int stepperDirection = 1;

// Button Callbacks
/* void goPush(Button& b) { */
/*     buttonState = !buttonState; */
/*     stepperDirection += 1; */
/* } */

//Joystick Functions {{{
int x_neutral = 508;
int y_neutral = 658; // Is this button fucked?
unsigned long x_press_start = 0;

/* void readJoystick(){ */
/*     //X Reads */
/*     x_pos = analogRead(JOYSTICK_X); */
/*     if (x_pos > x_neutral + 2 || x_pos < x_neutral - 2){ */
/*         if (x_pos == 1023 || x_pos == 0){ */
/*             x_press_start = millis(); */
/*             if () */
/*         } */

/*     } */
/* } */
/* }}} */

// Stepper Functions {{{

void rotate(int steps, float speed){
    int dir = (steps > 0)? HIGH:LOW;
    steps = abs(steps);
    digitalWrite(DIR_PIN, dir);
    // Not sure why * 70
    float usDelay = (1 / speed) * 70;

    for(int i = 0; i < steps; i++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
    }
}

void rotateDeg(float deg, float speed){
    int dir = (deg > 0)? HIGH:LOW;
    digitalWrite(DIR_PIN, dir);
    int steps = abs(deg) * (1 / 0.225);
    float usDelay = (1 / speed) * 70;

    for(int i = 0; i < steps; i++){
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(usDelay);
    }
}

void quadraticEase(int dir, int steps, float speed, unsigned long time){
    QuadraticEase quadEase;
    QuadraticEase timeEase;
    quadEase.setDuration(steps);
    quadEase.setTotalChangeInPosition(35000);
    timeEase.setDuration(steps);
    unsigned long total_time = time * 1000;
    timeEase.setTotalChangeInPosition(total_time);
    Serial.println(total_time);
    unsigned long counter = 0;
    unsigned long time_counter = 0;
    unsigned long time_in_millis = time * 1000;
    for(float i = 1; i <= steps; i++){
        float move_steps = quadEase.easeInOut(i) - quadEase.easeInOut(i - 1);
        /* Serial.println("Num of moves:"); */
        /* Serial.println(int(move_steps * dir)); */
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
        /* Serial.println("Time delay:"); */
        /* Serial.println(time_delay); */

        if (time_delay < move_time){
            delay(0);
        } else {
            delay(int(time_delay) - move_time);
        }
        /* Serial.println(int(move_time)); */
        /* Serial.println(int(time_delay)); */
        /* Serial.println(; */
        /* Serial.println("Move time:"); */
        /* Serial.println(move_time); */
        /* Serial.println("Time delay - move time:"); */
        /* Serial.println(time_delay - move_time); */
        /* Serial.println("Time counter:"); */
        /* Serial.println(time_counter); */
        /* delay(1000); */
    }
}
/* }}} */

// Camera Functions {{{
void takePicture(){
    digitalWrite(SHUTTER_PIN, HIGH);
    delay(150);
    digitalWrite(SHUTTER_PIN, LOW);
}
/* }}} */

// Setup {{{
void setup()
{
    /* goButton.pressHandler(goPush); */
    
    //Steppers
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(SLEEP_PIN, OUTPUT);
    digitalWrite(SLEEP_PIN, LOW);

    //Serial Stuff
    Serial.begin(9600);

    //Camera Stuff
    pinMode(SHUTTER_PIN, OUTPUT);

    //LCD Stuff
    lcd.begin(16, 2);
    lcd.print("< Left Up");
    lcd.setCursor(0, 1);
    lcd.print("> Right Down");
    delay(3000);
    lcd.clear();

    // Joystick Stuff
    pinMode(JOYSTICK_SELECT_PIN, INPUT_PULLUP);

    //Switch setup
    pinMode(MOTOR_SWITCH_PIN, INPUT);
    pinMode(END_SWITCH_PIN, INPUT);
}
/* }}} */

float trackLength = 35000;
int dir = -1;
int joystick_x_pos = 507;
int joystick_y_pos = 495;

/* Loop {{{ */
void loop()
{
    /* Unused {{{ */
    /* delay(5000); */
    /* digitalWrite(led, HIGH); */
    /* goButton.process(); */

    /* if(buttonState == true){ */
    /*     digitalWrite(led, HIGH); */
    /*     if(stepperDirection % 4 == 0){ */
    /*         rotate(1, .5); */
    /*     } else { */
    /*         rotate(-1, .5); */
    /*         counter += 1; */
    /*     } */
    /*     /1* Serial.println(stepperDirection); *1/ */
    /* } else { */
    /*     digitalWrite(led, LOW); */
    /*     /1* Serial.println(stepperDirection); *1/ */
    /*     Serial.println("The counter is: "); */
    /*     Serial.print(counter); */
    /*     Serial.print("\n"); */
 /* } */
 
  /* delay(5000); */
  /* float steps = 300; */
  /* double coefficient = trackLength / (steps * steps); */
  /* int move = 0; */

      /* for(double x = 1; x <= steps; x++){ */
      /*   double position = coefficient * (x * x); */
      /*   double previous_position = coefficient * ((x - 1) * (x - 1)); */
      /*   move = int(position - previous_position); */
      /*   rotate(move * dir, .1); */
      /*   lcd.clear(); */
      /*   lcd.setBacklight(LOW); */
      /*   lcd.print(int(x)); */
      /*   /1* Serial.println(x); *1/ */
      /*   /1* Serial.println(position); *1/ */
      /*   /1* Serial.println(previous_position); *1/ */
      /*   /1* Serial.println(move); *1/ */
      /*   digitalWrite(SHUTTER_PIN, HIGH); */
      /*   digitalWrite(led, HIGH); */
      /*   delay(150); */
      /*   digitalWrite(SHUTTER_PIN, LOW); */
      /*   digitalWrite(led, LOW); */
      /*   delay(4500); */
        /* } */
        /* }}} */

        int xpos = analogRead(A0);
        int ypos = analogRead(A1);

        /* if (xpos > joystick_x_pos + 2 || xpos < joystick_x_pos - 2 || ypos > joystick_y_pos + 12 || ypos < joystick_y_pos - 12){ */
            /* lcd.clear(); */
            lcd.setBacklight(HIGH);
            lcd.print("X:");
            lcd.setCursor(3, 0);
            if (xpos < 1000){
                lcd.print(xpos);
                lcd.print(" ");
            } else if (xpos < 100){
                lcd.print(xpos);
                lcd.print("  ");
            } else if (xpos < 10){
                lcd.print(xpos);
                lcd.print("    ");
            } else {
                lcd.print(xpos);
            }
            lcd.setCursor(8, 0);
            lcd.print("Sel:");
            lcd.setCursor(12, 0);
            if (digitalRead(JOYSTICK_SELECT_PIN) == LOW){
                lcd.print("P");
            } else if (digitalRead(JOYSTICK_SELECT_PIN) == HIGH){
                lcd.print("O");
            } else {
                lcd.print("X");
            }
            lcd.setCursor(0, 1);
            lcd.print("Y:");
            lcd.setCursor(3, 1);
            lcd.print(ypos);
            lcd.setCursor(8, 1);
            lcd.print("M:");
                if (digitalRead(MOTOR_SWITCH_PIN) == HIGH){
                    lcd.print("P");
                } else {
                    lcd.print("O");
                }
            lcd.print(" E:");
                if(digitalRead(END_SWITCH_PIN) == HIGH){
                    lcd.print("P");
                } else {
                    lcd.print("O");
                }
            lcd.print(" ");
        /* if (xpos > 515){ */
        /*     float num_positions = 1023 - 516; */
        /*     float pos_speed = (float(xpos) - 516.0) / 516.0; */
        /*     float max_speed = 0.5; */
        /*     float speed = pos_speed * max_speed; */
        /*     /1* rotate(1, speed); *1/ */
        /* } else if (xpos < 500){ */
        /*     float pos_speed = (500.0 - float(xpos) + 1.0) / 501; */
        /*     float max_speed = 0.5; */
        /*     float speed = pos_speed * max_speed; */
            /* rotate(-1, speed); */
        /* } */
        joystick_x_pos = xpos;
        joystick_y_pos = ypos;
        /* delay(10); */
    /* } */
    /* /1* delay(100); *1/ */
    
    /* delay(5000); */

    /* quadraticEase(dir, 300, .05, 300); */

  /* float reverse_steps = 400; */
  /* dir = dir * -1; */
}
/* }}} */

// vim:foldmethod=marker:foldlevel=1

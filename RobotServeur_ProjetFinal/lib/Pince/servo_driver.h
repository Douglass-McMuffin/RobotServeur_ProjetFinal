/*
 * File: servo_driver.h
 * Author: Maxime Gravel
 * Date: November 22, 2023
 * Description: Control the claw for the S1 project of a server robot.
 */
#ifndef servo_driver_h
#define servo_driver_h
#include <arduino.h>

#define PIN_STEP 44
#define PIN_DIR 46
typedef enum STEPPER_DIR {PUSH_CAN = 1,PULL_CAN = 0};

//Intervalle:Valeur entre 10 et 250
void activate_stepper(int intervalle);
void deactivate_stepper();
void set_stepper_dir(STEPPER_DIR dir);

#endif

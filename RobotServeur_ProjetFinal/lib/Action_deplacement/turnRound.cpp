/***********************************************************************************************|
File:           turn.cpp                                                                    	|
Author:         Maxime Gravel: gram1811 UdeS                                                    |
Date:           10/10/2023		                                                                |
Last Updated:   10/10/2023  																	|
By:             Maxime Gravel: gram1811 UdeS                                                    |
Description:    Allows Robus to turn with acceleration                                          |
************************************************************************************************/
#include "TurnRound.h"
#include "forward.h"
#include "commande_direction.h"
/**
 * The function "turnSquare" makes the robot go a certain distance after rotating 45 degrees and the rotates again to be straight.
 * 
 * @param distance The distance between the rotations in cm.
 * @param rotation The number of pulses for a 45 degree rotation.
 * @param maxSpeed The maximum speed at which the motors can rotate.
 */
void turnSquare(double distance, double rotation, double maxSpeed){
    turnRight(rotation, maxSpeed);
    moveForward1(maxSpeed, distance);
    turnRight(rotation, maxSpeed);
}
/**
 * The function "turnRound" makes the robot go a quarter of a circle depending on its position(Green or Yellow).
 * 
 * @param maxSpeed The maximum speed at which the motors can rotate.
 * @param color The starting color
 */
void turnRound(int color, double speed, double* state){
    ENCODER_Reset(0);
    ENCODER_Reset(1);
    int dist_gauche;
    int dist_droite;
    double speed_left;
    if (color == 0) // Green
    { 
        //Delay because the sensor is off by 30 degrees
        while(ENCODER_Read(0)<1650)
        {
            MOTOR_SetSpeed(0, speed);
            MOTOR_SetSpeed(1, speed);
        }
        ENCODER_Reset(0);
        ENCODER_Reset(1);
        dist_gauche = 10587; //en pulse , 11605
        dist_droite = 6950; // 7595
        speed_left = (dist_gauche)/(dist_droite/speed);
    }
    if (color == 1) // Yellow
    { 
        //Delay because the sensor is off by 30 degrees
        while(ENCODER_Read(0)<3300){
            MOTOR_SetSpeed(0, speed);
            MOTOR_SetSpeed(1, speed);
        }
        ENCODER_Reset(0);
        ENCODER_Reset(1);
        dist_gauche =  18150; //en pulse , 18007
        dist_droite = 14625; // 13996
        speed_left = (dist_gauche)/(dist_droite/speed);
    }
    do {
        MOTOR_SetSpeed(0, speed_left); // roue gauche
        MOTOR_SetSpeed(1, speed); // roue droite
    }while (ENCODER_Read(0)<dist_gauche);
    
    MOTOR_SetSpeed (0, speed);
    *state += 1;
}
/**
 * The function "turnRight" rotates the robot to the right by a specified angle at a maximum speed.
 * 
 * @param angle The angle parameter represents the desired angle of rotation.
 * @param maxSpeed The maximum speed at which the motors can rotate.
 */
void turnRight(double angle, double maxSpeed)
{
    //angle = angle + 5;
    double leftEnc = 0;
    double rightEnc = 0;
    double speedLeft;
    double speedRight;
    double A = -maxSpeed/(angle*angle/4);
    ENCODER_Reset(LEFT_MOTOR_ENC);
    ENCODER_Reset(RIGHT_MOTOR_ENC);
    while(leftEnc < angle || rightEnc > (0 - angle))
    {
        if(leftEnc < angle)
        {
            speedLeft = (A * abs(leftEnc) * (abs(leftEnc) - angle)) + vitMin;
        }
        else{
            speedLeft = 0;
        }
        if(rightEnc > 0 - angle)
        {
            speedRight =  (A * abs(rightEnc) * (abs(rightEnc) - angle)) + vitMin;
        }
        else{
            speedRight = 0;
        }
        MOTOR_SetSpeed(LEFT_MOTOR_ENC, speedLeft);
        MOTOR_SetSpeed(RIGHT_MOTOR_ENC, -speedRight);
        leftEnc = ENCODER_Read(LEFT_MOTOR_ENC);
        rightEnc = ENCODER_Read(RIGHT_MOTOR_ENC);
    }
    MOTOR_SetSpeed(LEFT_MOTOR_ENC, 0);
    MOTOR_SetSpeed(RIGHT_MOTOR_ENC, 0);

}
/**
 * The function "turnLeft" rotates the robot to the left by a specified angle at a maximum speed.
 * 
 * @param angle The angle parameter represents the desired angle of rotation.
 * @param maxSpeed The `maxSpeed` parameter represents the maximum speed at which the motors can
 * rotate.
 */
void turnLeft(double angle, double maxSpeed)
{
    //angle = angle-5;
    double leftEnc = 0;
    double rightEnc = 0;
    double speedLeft;
    double speedRight;
    double A = -maxSpeed/(angle*angle/4);
    ENCODER_Reset(LEFT_MOTOR_ENC);
    ENCODER_Reset(RIGHT_MOTOR_ENC);
    while(rightEnc < angle || leftEnc > (0 - angle))
    {
        if(rightEnc < angle)
        {
            speedRight = (A * abs(rightEnc) * (abs(rightEnc) - angle)) + vitMin;
        }
        else{
            speedRight = 0;
        }
        if(leftEnc > 0 - angle)
        {
            speedLeft =  (A * abs(leftEnc) * (abs(leftEnc) - angle)) + vitMin;
        }
        else{
            speedLeft = 0;
        }
        MOTOR_SetSpeed(LEFT_MOTOR_ENC, -speedLeft);
        MOTOR_SetSpeed(RIGHT_MOTOR_ENC, speedRight);
        leftEnc = ENCODER_Read(LEFT_MOTOR_ENC);
        rightEnc = ENCODER_Read(RIGHT_MOTOR_ENC);
    }
    MOTOR_SetSpeed(LEFT_MOTOR_ENC, 0);
    MOTOR_SetSpeed(RIGHT_MOTOR_ENC, 0);
}
/**
* @param action The action parameter represents the movement we want to give to the robot ->
* 0 = left ;
* 1 = straight ;
* 2 = right.
*/
void deplacement_intersection(int action)
{
    if (action == LEFT){
        turnLeft(90,0.5);
    }

    if (action == STRAIGHT){
        delay(100);
    }

    if (action == RIGHT){
        turnRight(90,0.5);

    }
    
}
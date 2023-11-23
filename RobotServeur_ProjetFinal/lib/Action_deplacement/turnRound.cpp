/***********************************************************************************************|
File:           turn.cpp                                                                    	|
Author:         Maxime Gravel: gram1811 UdeS                                                    |
Date:           10/10/2023		                                                                |
Last Updated:   10/10/2023  																	|
By:             Maxime Gravel: gram1811 UdeS                                                    |
Description:    Allows Robus to turn with acceleration                                          |
************************************************************************************************/
#include "turnRound.h"
#include "commande_direction.h"

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
        turnLeft((2*turn45),0.20);
        Serial.print("turnleft");
    }

    if (action == STRAIGHT){
        Serial.print("staight");
        MOTOR_SetSpeed(0,0.25);
        MOTOR_SetSpeed(1,0.25);
        delay(400); 
    }

    if (action == DROITE){
        turnRight((2*turn45),0.20);
        Serial.print("turnright");

    }
    
}


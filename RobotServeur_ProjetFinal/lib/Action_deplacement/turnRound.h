

#include "LibRobus.h"

#define LEFT_MOTOR_ENC   0
#define RIGHT_MOTOR_ENC  1
#define turn45 1003 // Pulses for 45 degree rotation
#define vitMin 0.08

void turnRight(double angle, double maxSpeed);
void turnLeft(double angle, double maxSpeed);
void deplacement_intersection(int action);


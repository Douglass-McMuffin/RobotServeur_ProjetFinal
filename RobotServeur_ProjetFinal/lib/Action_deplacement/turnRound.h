#ifndef turn_h
#define turn_h

    #include <librobus.h>
    #define LEFT_MOTOR_ENC   0
    #define RIGHT_MOTOR_ENC  1
    #define turn45 1003 // Pulses for 45 degree rotation
    #define turnGreenRight 7595 // Pulses for right encoder when turning in the green zone.
    #define turnGreenLeft 11605 // Pulses for left encoder when turning in the green zone.
    #define turnYellowRight 1 // Pulses for right encoder when turning in the Yellow zone.
    #define turnYellowLeft 1 // Pulses for right encoder when turning in the Yellow zone.
    #define vitMin 0.08
    void turnSquare(double distance, double rotation, double maxSpeed);
    void turnRound(int color, double speed, double* state);
    void turnRight(double angle, double maxSpeed);
    void turnLeft(double angle, double maxSpeed);
    void deplacement_intersection(int action);

#endif
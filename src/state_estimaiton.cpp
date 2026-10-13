#include "Arduino.h"
#include "state_estimation.h"
#include "math.h"

//define kalman state variable here for use throughout this file

typedef struct {
    float X[2]; //this is the current state [1] is alt, [2] is the velocity
    float P[2][2]; //estimated covarience matrix
    float P_ground;//current ground pressure (replaced by average reading from sensor)

} kalman_t;

kalman_t kalman {
    {0.0f, 0.0f},                      // X
    {{2.0f, 0.0f}, {0.0f, 0.5f}},      // P
    101325.0f                          // P_ground
};

//set kalman filter trust values (for noise covarience Q)
float sigma_acc = 0.5f;
float sigma_vel = 0.5f;
float R_baro = 4.0f; //baro trust due to accuracy

void kalman_predict(float accel_z, float dt){

    //Predict the altitude and velocity 
    kalman.X[0] = kalman.X[0] + kalman.X[1] * dt + 0.5f*accel_z*dt*dt; //predicted altitude y = y + v*dt + 0.5*a*t^2
    kalman.X[1] = kalman.X[1] + accel_z*dt; //predicted velocity v =  v + a*dt

    //predicted process noise covariance calculation 
    //matrix is as follows [00 01, 10 11]
    float Q00 = sigma_acc*sigma_acc;
    float Q01 = 0;
    float Q10 = 0;
    float Q11 = sigma_vel*sigma_vel;
}

void kalman_update(float pressure){

    kalman.P_ground = 0.99f * kalman.P_ground + 0.01f * pressure; //update pressure with the current ground pressure

}
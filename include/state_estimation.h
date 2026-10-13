#include "Arduino.h"

//this is from airbrakes

void state_estimation(float dt);

//TODO: body transformations -> use NED transformation (x is vertical)
void get_imu_b(float out_accel_b[3], float out_omega_b[3]);
void get_mag_b(float out_mag_b[3]);

//TODO: Kalman filter
void kalman_predict(float accel_z, float dt);
void kalman_update(float pressure);

void launch_detect(float accel_b_x); //x of body frame is up
void apogee_detect(); //will need vertical acceleration, and preferably vertical velocity
void landing_detect();
#include "Arduino.h"

//this is from airbrakes

void state_estimation(float dt);
//arm_status get_imu_b(arm_matrix_instance_f32 *out_accel, arm_matrix_instance_f32 *out_omega);
//arm_status get_mag_b(arm_matrix_instance_f32 *out_mag);

void get_imu_b(float out_accel_b[3], float out_omega_b[3]);
void get_mag_b(float out_mag_b[3]);


void kalman_predict(float accel_z, float dt);
void kalman_update(float pressure);

void launch_detect(float accel_b_x);
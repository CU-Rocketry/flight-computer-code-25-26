#include "Arduino.h"
#include <MadgwickAHRS.h> 

//implementation of arduino madgwick library - basically simplified MadgwickAHRS using object programming
//estimates rocket orientation from accelerometer and gyro data
//translates to 4D quaterion system

//define the inputs of the Madgwick filters
typedef struct {

    int16_t accel_raw[3]; 
    int16_t gyro_raw[3];

} Madgwick_data_t;

//for measugin time steps
unsigned long microsPerReading, microsPrevious;

void Madgwick_init(Madgwick filter); //init using declared filter object
void Madgwick_run(Madgwick *filter, Madgwick_data_t *Madgwick_inputs);
float convertRawGyro(int gRaw);
float convertRawAcceleration(int aRaw);
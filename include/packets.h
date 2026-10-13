#include "Arduino.h"

//telemetry packet
typedef struct{ 

    uint8_t pkt_type;

    uint32_t time; //time since boot

    // battery
    float batt_v;

    // Body frame sensors
    float accel_b[3]; // [m/s/s] in body frame. *proper acceleration
    float omega_b[3]; // [rad/s] in body frame
    float mag_b[3]; // [mgauss] in body frame

    //Calculated Values
    float alt_agl;
    float vel_z;

    //Pyro Values
    float pryo_status[2]; //contain zero and ones for fired status


} telemetry_packet_t;


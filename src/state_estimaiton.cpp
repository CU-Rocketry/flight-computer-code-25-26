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
float R_baro = 4.0f; //baro trust due to accuracy

//define ISA values
float R = 8.31432*10*10*10; //8.31432×103 J/(kmol*K)
float G = 9.80665f; //m/s^2'
float T0 = 273; //ref temp kelvin
float L = 6.5; //lapse rate K/km

//this step uses known physics equations to estimate state (X)
//then Q is defined - which is basically the noise influence on measurements, its how you expect sensor noise to effect measurements
//P is a guess of uncertainty in the measurement (technically covarience- the relationship between the trend of new variables)
//You guess an initial P value
//Then you update the P value using the noise matrix Q

//the "goal" of the kalman filter is to minimize the trace (sum of diagonal elements) of P with a good Kalman gain value K (see derivation)
//the diagonal elements are the "variance of estimation errors"
//basically if you minimize this "variance of estimation errors", you have a good estiamte

//in the end... I am not a controls engineer 

void kalman_predict(float accel_z, float dt){

    //Predict the altitude and velocity 
    kalman.X[0] = kalman.X[0] + kalman.X[1] * dt + 0.5f*accel_z*dt*dt; //predicted altitude y = y + v*dt + 0.5*a*t^2
    kalman.X[1] = kalman.X[1] + accel_z*dt; //predicted velocity v =  v + a*dt

    //predicted process noise covariance calculation 
    //matricies are as follows [00, 01; 10, 11]

    //Q is basically how confident you are in your prediction - introduces artificial noise to simulate sensor noise
    //A diagonal Q like [1, 0; 0, 1] means the two variables are independent of each other
    float Q00 = (dt * dt * dt * dt / 4.0f) * (sigma_acc * sigma_acc);
    float Q01 = (dt * dt * dt / 2.0f) * (sigma_acc * sigma_acc);
    float Q10 = Q01;
    float Q11 = (dt * dt) * (sigma_acc * sigma_acc);

    //initial p value guess - this is mainly just based on judgement
    float P00 = kalman.P[0][0];
    float P01 = kalman.P[0][1];
    float P10 = kalman.P[1][0];
    float P11 = kalman.P[1][1];

    //update p with predicted p
    kalman.P[0][0] = P00 + dt*P10 + (P01 + dt*P11)*dt + Q00;
    kalman.P[0][1] = P01 + dt*P11 + Q01;
    kalman.P[1][0] = P10 + dt*P11 + Q10;
    kalman.P[1][1] = P11 + Q11;

}

void kalman_update(float pressure){

    kalman.P_ground = 0.99f * kalman.P_ground + 0.01f * pressure; //update pressure with the current ground pressure

    //convert pressure to height using ISA model to get z_meas
    float exponent = ((R*L)/(G));
    float h_agl_pres = (T0/L) * (1.0f-powf(pressure/kalman.P_ground, exponent));
    float z_meas = -h_agl_pres; // NED coordinate system

    //the following steps calculate measurement prediction covarience (S)
    //H = [1, 0] due to derivatives
    //innovation residual: i = z - H*x (remember q is predicted from above)
    float i = z_meas - kalman.X[0];

    //measurement innovation (prediction) covariance 
    // S = H*P*H' + R
    //R here is the measurement noise covarience - the actual sensor noise
    float S = kalman.P[0][0] + R_baro;
    
    //Kalman gain K 
    ///K = PH'/S
    float K0 = kalman.P[0][0]/ S;
    float K1 = kalman.P[1][0] / S;

    //state update - THIS IS OUR NEW ALTITUDE AND VELOCITY
    kalman.X[0]= kalman.X[0] + K0*i; //new estimate of altitude
    kalman.X[1]= kalman.X[1] + K1*i; //new estimate of vertical velocity

    //update error covariance
    //P = P*(I-KH)
    //where I is an identity matrix 

    //just write out p values so its nicer in the equation
    float P00 = kalman.P[0][0];
    float P01 = kalman.P[0][1];
    float P10 = kalman.P[1][0];
    float P11 = kalman.P[1][1];

    //update P according to the equation
    kalman.P[0][0] = (1-K0)*P00;
    kalman.P[0][1] = (1-K0)*P01;
    kalman.P[1][0] = -K1*P00 + P10;
    kalman.P[1][1] = -K1*P10 + P11;

}
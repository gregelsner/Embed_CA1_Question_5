// Embed_CA_Question_5. Using the program in Lab 3: accelerometer and angle measurement. within the computeAngle function
//write logic to turn ON led 1 (green LED) when the board is lying flat on the table otherwise turn off LED. Lines of code added 54-58

#include "mbed.h"
#include "LSM6DSLSensor.h"
#include <cmath>
#define PI 3.141592654

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address
DigitalOut led1 (LED1); //Sets digital output build in led1

float computeAngle(int x, int y, int z){
    //Declared variables float used in angle calculation
    float res = 0; 
    float res_1 = 0;
    float sum_yz = 0;
    float atan_res = 0;
    float convert = 0;
   
    y= y*y; //Squares up the 'y' axis value
    z= z*z; //Squares up the 'z' axis value
    sum_yz = sqrt(y+z); //Squares up 'y & z'
    res_1 = float (x)/(sum_yz); //Obtains the angle by devidng 'x' over sum of 'y&z'
    atan_res = atan(res_1); //Returns the arctangent of res_1
    convert = (atan_res*180)/PI; //Coverts gradians to angle
    res = convert; //Final result in angle
    return res;
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {
        
        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, %3.6f\r\n", axes[0], axes[1], axes[2], res);
        
        if ( axes[0] <= 0 && axes[0] >=-12 && axes[1] <=0 && axes[1] >=-14 || axes[2]==2000 ){ //The'if'statement verify 3 axis are within the specified values (MC is flat). If so D/O LED1 is set to true 
        led1 =true; //Toggles led1 ON
        }
        else{
        led1 = false;
        }
        
        thread_sleep_for(500);//Increased scanning time for more accuracy and stable readings. 

    } 
}
  

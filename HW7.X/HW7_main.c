#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>

void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    i2c_master_setup();
    init_mpu6050();
    
    float xaccel;
    float yaccel;
    float zaccel;
    float temp;
    float xgyro;
    float ygyro;
    float zgyro;
	
	// char array for the raw data
    char m_in[100];
    // char array for sending
    char bus[200];
	// floats to store the data
	
	// read whoami
    uint8_t who = whoami();
    sprintf(bus,"who am I: %u \r\n", who);
    NU32DIP_WriteUART1(bus);
    
    //write to PWR_MGMT
    //write_byte_I2C1(IMU_ADDR,PWR_MGMT_1,0b10000000);//register 0x6B, chip 0x68, value 0b10000000

    //write to ACCEL_CONFIG (MAYBE DONT SELF TEST)
    //write_byte_I2C1(IMU_ADDR,ACCEL_CONFIG,0b11100000);//register 0x1C, chip 0x68, value 0b00000000
    
    //write to GYRO_CONFIG (MAYBE DONT SELF TEST)
    //write_byte_I2C1(IMU_ADDR,GYRO_CONFIG,0b11111000);//register 0x1B, chip 0x68, value 0b00000000
       
    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        // read IMU
        burst_read_I2C1(IMU_ADDR,0x3B, m_in, 14);//register start 0x3C, chip 0x68, value 0b00000000
		// convert data
        xaccel = conv_xXL(m_in);
        yaccel = conv_yXL(m_in);
        zaccel = conv_zXL(m_in);
        temp = conv_temp(m_in);
        xgyro = conv_xG(m_in);
        ygyro = conv_yG(m_in);
        zgyro = conv_zG(m_in);
        
        // print out the data
        //sprintf(bus,"x_a: %f \r\n y_a: %f \r\n z_a: %f \r\n temp: %f \r\n x_g: %f \r\n y_g: %f \r\n z_g: %f \r\n", xaccel, yaccel, zaccel, temp, xgyro, ygyro, zgyro);
        sprintf(bus,"%f\n", yaccel);
        
        
        NU32DIP_WriteUART1(bus);
        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
            
        }
    }
}

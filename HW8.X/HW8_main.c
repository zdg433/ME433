#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "ssd1606.h"
#include "mpu6050.h"
#include <stdio.h>




int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  i2c_master_setup();//start I2c communication
  ssd1306_setup(); //set up display
  init_mpu6050(); //set up accelerometer

  
  char message[50]; //char array to be displayed
  // char array for the raw data
  

  float zaccel; //zacceleration from accelerometer

  int i = 0;
  while(1){
    _CP0_SET_COUNT(0);
    char m_in[100];
    burst_read_I2C1(IMU_ADDR,0x3B, m_in, 14);//register start 0x3C, chip 0x68, value 0b00000000
    zaccel = conv_zXL(m_in);
    sprintf(message,"z_a: %f", zaccel);
    ssd1306_drawMessage(1,1, message);
    
    int frames = (24000000 / _CP0_GET_COUNT());
    sprintf(message,"fps: %d", frames);
    ssd1306_drawMessage(1,19, message);
    
    ssd1306_update();
      
    if (_CP0_GET_COUNT() > 48000000/200){
        if(i == 0){
          i = 1;
        }
        else{
          i = 0;
        }
        NU32DIP_GREEN = i;
        //ssd1306_drawPixel(1,1,i);
        //ssd1306_update();
    }   
  }
}

		

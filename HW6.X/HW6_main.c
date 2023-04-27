#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"




int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  i2c_master_setup();//start I2c communication
  unsigned char recv;
  int i = 0;
  
  i2c_master_start(); //S
  i2c_master_send(0b01000000);//OP+W write to device of address 000 
  i2c_master_send(0b00000000);//ADDR (IODIR)
  i2c_master_send(0b00000001);//DIN
  i2c_master_stop();//P
  
  
  i2c_master_start(); //S
  i2c_master_send(0b01000000);//OP+W write to device of address 000 
  i2c_master_send(0b00001010);//ADDR (OLAT)
  i2c_master_send(0b10000000);//DIN
  i2c_master_stop();//P
  
  
  //i2c_master_restart();//SR
  //i2c_master_send(0b01000000);//OP+W write to device of address 000
  
  while(1){
      if(i == 0){
          i = 1;
      }
      else{
          i = 0;
      }
      NU32DIP_GREEN = i;
      
      i2c_master_start(); //S
      i2c_master_send(0b01000000);//OP+W write to device of address 000 
      i2c_master_send(0b00001001);//ADDR (GPIO)
      i2c_master_restart();
      i2c_master_send(0b01000001);//OP+R read to device of address 000
      recv = i2c_master_recv(); //DOUT
      i2c_master_stop();//P
      
      i2c_master_start(); //S
      i2c_master_send(0b01000000);//OP+W write to device of address 000 
      i2c_master_send(0b00001010);//ADDR (OLAT)
      if(recv & 0b1){
        i2c_master_send(0b00000000);//DIN OFF
      }
      else{
        i2c_master_send(0b10000000);//DIN ON
      }
      i2c_master_stop();//P
      
      
    for(int h = 0; h < 48000;h++){
        
    }
  }
}

		

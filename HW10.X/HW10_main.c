#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"




int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  ws2812b_setup();
  float rainbow[] = {0,31,62,93,124,155,186,217,248};
  
  wsColor c[8];
  int i;
  while(1){
      for(i = 0; i<8; i++){
          c[i] = HSBtoRGB(rainbow[i],1,.75);
          rainbow[i] = rainbow[i] + 1;
          if(rainbow[i] > 360){
              rainbow[i] = 0;
          }
          
      }
      
      ws2812b_setColor(c,8);
      for(i = 0; i < 90000;i++){
          
      }
  }   
}




		

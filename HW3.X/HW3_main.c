#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

void gen_sin_wave(); // blink the LEDs function

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
	if (NU32DIP_USER == 0){
		gen_sin_wave();
	}
  }
}

// blink the LEDs
void gen_sin_wave(){
	int i;
    float val1;
    char message[100];

	for (i=0; i< 100; i++){
        _CP0_SET_COUNT(0);
	  	val1 = (100.0 * 0.5*sin(2*M_PI* (i/100.0) ) + (100.0/2));
        sprintf(message,"%f\n",val1);        
        NU32DIP_WriteUART1(message);

        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
        }
	}
    
    
}
		

#include "nu32dip.h" // constants, functions for startup and UART


//NOTE I did the math to make the duty cycle 1.5 and 2.5 ms but for some reason my specific servo had 0 degrees at .4 ms and 180 degrees at 2.4 ms

//For some reason, had to take out the power supply wire from VIN and put it back in 
//on the H-bridge to get the motor to start (would just hum if Inleft it in while resetting the code)

int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  //b6 is EN(High)
  TRISBbits.TRISB6 = 0;
  LATBbits.LATB6 = 1;
  //b8 is PH(Low)
  TRISBbits.TRISB8 = 0;
  LATBbits.LATB8 = 1;
  //b7 is OC1
  RPB7Rbits.RPB7R = 0b0101;   //use B7 as OC1
  
  
  
  T2CONbits.TCKPS = 4;     // N = 16
  PR2 = 59999;              // period = (PR2+1) * N * (1/48000000) = 50Hz
  TMR2 = 0;                // initial TMR2 count is 0
  OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
  OC1CONbits.OCTSEL = 0;   // Use timer2
  OC1RS = 7199;             // duty cycle = OC1RS/(PR2+1) = 25% //1429 for 0, 7199 for 180
  OC1R = 7199;              // initialize before turning OC1 on; afterward it is read-only
  T2CONbits.ON = 1;        // turn on Timer2
  OC1CONbits.ON = 1;       // turn on OC1
  
  
  
  //135 is OC1RS = 5755
  //45 is OC1RS = 2870
  
  int one_deg = (7199-1429)/180;
  
  //2 degree increments, I'm scared to increment close to the 50 Hz frequency 
  //so I'm doing roughly 10 Hz increment frequency
  
  while(1){
      int i;
      int OCV = 2870;
      for(i = 0; i < 45; i++){
          OC1RS = OCV + i*2*one_deg;
          for(int j = 0;j < 426666; j++){
              //wait 4 seconds divided by 45 
          }
      }
  }
  
  
  
}




		

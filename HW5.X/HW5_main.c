#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>
#include <stdio.h>

void initSPI();
unsigned char spi_io(unsigned char o);


int main(void) {
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI();
  int i = 0;
  int refA;
  int refB;
  while(1){//100x in 1 second so .01 second delays  
    if(i == 100){
        i = 0;
    }
    refA =  (int) (1023 * 0.5*sin(4*M_PI*i /100.0) + (1023/2));
    if(i < 50){
        refB =  (int) (1023 * (i)/50.0);
    }
    else{
        refB =  (int) (1023 * (50-(i-52)/50.0));
    }
    int sendA1 = ((refA >> 6) | 0b01110000);
    int sendA2 = ((refA << 2) & 0b11111111);
    int sendB1 = ((refB >> 6) | 0b11110000);
    int sendB2 = ((refB << 2) & 0b11111111);
    LATBbits.LATB6 = 0;
    unsigned char n = spi_io(sendA1);
    unsigned char o = spi_io(sendA2);
    LATBbits.LATB6 = 1;
    LATBbits.LATB6 = 0;
    unsigned char p = spi_io(sendB1);
    unsigned char q = spi_io(sendB2);
    LATBbits.LATB6 = 1;
    
    i++;
    
    for(int h = 0; h < 52000;h++){
        
    }
  }
}

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    // Turn of analog pins
    //...
    // Make an output pin for CS
    TRISBbits.TRISB6 = 0;
    LATBbits.LATB6 = 1;
    //...
    //...
    // Set SDO1 (B8)
    RPB8Rbits.RPB8R = 0b0011;
    //...
    // Set SDI1 (B11)
    SDI1Rbits.SDI1R = 0b0011;
    //...

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}
		

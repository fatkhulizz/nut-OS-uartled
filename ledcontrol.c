#define F_CPU 14745600UL
#include <compiler.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <dev/board.h>
#include <sys/timer.h>

uint32_t      baud = 9600;
FILE        *uart;
static char inbuf[50];

void InitUART1(void)
{
  DDRD |=0b00001000;   //cfg pin TXD1 as output
  DDRD &=0b11111011;   //cfg pin RXD1 as input

  //use pull-up res for pin TXD1 & RXD1
  PORTD |= 0b00001100; //use this if RXCIE1=1

  NutRegisterDevice(&DEV_UART, 0, 0);
  uart = fopen(DEV_UART_NAME, "r+");
  _ioctl(_fileno(uart), UART_SETSPEED, &baud);
}

//turn on/off led
void led_on(int ledPin, int duration){
  PORTB |= 0b1000 << ledPin; //hidupkan led sesuai nilai ledPin
  NutSleep(duration);
  PORTB &= ~(0b1000 << ledPin); //matikan led sesuai nilai ledPin
  NutSleep(duration);
}

int main(void){
  DDRB= DDRB | 0xF0;
  PORTB=0b00000000;
  
  InitUART1();
  while(1){
    fprintf(uart,"\r\n= Welcome to RemLab K2 =\r\n");
    // PORTB = PORTB & 0b00001111; //turn off LED
    
    fputs("Enter your command:", uart);
    fflush(uart);
    fgets(inbuf, sizeof(inbuf), uart);
    fprintf(uart, "%s\r\n", inbuf);
    
    char* cp = strchr(inbuf, '\n');   //get first occurrence/position of the character '\n'
    if (cp) *cp = 0;            //if found then remove	

    // parsing inbuf
    char *argv[16] = {NULL};
    int argc = 0;
    for (; argc < 16; argc++) {
      argv[argc] = strtok(argc == 0 ? inbuf : 0, " ");
      if (argv[argc] == NULL) break;
    }

    // 
    int pin, dur=1000, rec=1;
    sscanf(argv[0], "%d", &pin);
    if (argc > 0) sscanf(argv[1], "%d", &dur);
    if (argc>1) sscanf(argv[2], "%d", &rec);

    // sscanf(inbuf, "%d %d %d", &pin, &dur, &rec);
    int i=0;
    for (; i < rec; i++) led_on(pin, dur);
  }
  return 0;
}

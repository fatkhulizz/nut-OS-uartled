# nut-OS-uartled<a name="TOP"></a>



- - - - 
control LED on/off at atmega with UART input using ethernut

## atmega configuration ##
      - PORTD for UART
      - PINB.4 for LED 1
      - PINB.5 for LED 2
      - PINB.6 for LED 3
      - PINB.7 for LED 4
  
## Install ##
- install nut/OS, http://www.ethernut.de/en/download/index.html
- clone this repo to your `nutapp` folder
- open `nut-OS-uartled` folder on terminal/cmd
- compile using nut/OS
  ~~~
  make clean && make all
  ~~~
- upload the hex file
## Usage ##
input format on UART :
      `[pin]<space>[duration]<space>[recursion]`
- `pin` is for which led to turn on
- `duration` is for how long the led turn on and off in milisecond
- `recursion` is how many led will blink
### example ###
turn on `LED 3` with duration `1.5 second` `4 times`
~~~
3 1500 4
~~~

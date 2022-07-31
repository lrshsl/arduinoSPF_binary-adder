# arduinoSPF_binary-adder
Arduino code for a binary adder with sevensegment display

Code for a school project of [cmsuisse](https://github.com/cmsuisse) and me.
It controls two arduino boards: 
* The first one takes two decimal numbers as input (via Serial monitor)
  and writes them in binary representation on 8 analog pins.
* The built binary adder adds them together
* The result get read by the second arduino which converts it to hex and outputs
  on a sevensegment display.

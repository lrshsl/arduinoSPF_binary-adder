/* sevensegment.ino
 *  
 *  Code for the second of two arduinos.
 *  It reads the output value of a binary adder,
 *  converts it to decimal and writes the value
 *  to a sevensegment display
 *  
 *  Coded by lrshsl and cmsuisse (github.com)
 */



// Pins of sevensegment display
const uint8_t sevenSegPins[] {2, 3, 4, 5, 6, 7, 8};

// Input pins
const uint8_t analogInputPins[] {A2, A3, A4, A5};

// Lookup table for sevensegment display
const uint8_t graphics_buffer[18][7] = {
  {1,1,1,0,1,1,1},  // 0
  {0,0,1,0,0,1,0},  // 1
  {1,0,1,1,1,0,1},  // 2
  {1,0,1,1,0,1,1},  // 3
  {0,1,1,1,0,1,0},  // 4
  {1,1,0,1,0,1,1},  // 5
  {1,1,0,1,1,1,1},  // 6
  {1,0,1,0,0,1,0},  // 7
  {1,1,1,1,1,1,1},  // 8
  {1,1,1,1,0,1,1},  // 9
  
  {1,1,1,1,1,1,0},  // A  (10)
  {0,1,0,1,1,1,1},  // b  (11)
  {1,1,0,0,1,0,1},  // C  (12)
  {0,0,1,1,1,1,1},  // d  (13)
  {1,1,0,1,1,0,1},  // E  (14)
  {1,1,0,1,1,0,0},  // F  (15)
  
  {0,0,0,0,0,0,0},  // All LOW
  {1,1,1,1,1,1,1}   // All HIGH
};


// Entry point
void setup()
{
  // Start void loop
  Serial.begin(9600);  // IMPORTANT!!!!

  // Pin Setup
  for (uint8_t pin : sevenSegPins){
    pinMode(pin, OUTPUT);
    
    digitalWrite(pin, HIGH);  // Short comfirmation flashing
    delay(100);
    digitalWrite(pin, LOW);
  }

  Serial.println("Setup complete");
}


// Main loop
void loop()
{
  // Read from input pins
  uint8_t binaryReads[4];

  for (uint8_t i=0; i<4; i++) {
    binaryReads[i] = convertAnalogToDigital(
      analogRead(analogInputPins[i])
    );
    Serial.print(binaryReads[i]);
  }
  Serial.println();

  // Convert to hexadecimal
  uint8_t decimalInput = binaryToDecimal(binaryReads);

  // Write result to sevensegment display
  showNumber(decimalInput);

  delay(300);  // Just in case..
}


// showNumberOnSevensegment
void showNumberOnSevensegment(
  const uint8_t outputPins[], 
  uint8_t len, 
  uint8_t n
) {
  for (uint8_t i; i<len; i++)
    digitalWrite(outputPins[i], graphics_buffer[n][i]);
}


// showNumber
void showNumber(uint8_t n)
{
  showNumberOnSevensegment(sevenSegPins, 7, n);
}


// convertAnalogToDigital
uint8_t convertAnalogToDigital(int analogInput)
{
  return analogInput > 256;

  /* // Short for:
   * if (analogInput > 256)
   *   return 1;
   * return 0;
   */
}


// binaryToDecimal
uint8_t binaryToDecimal(uint8_t binaryInput[])
{
  uint8_t decimalOutput = 0;

  for (uint8_t i=0; i<4; i++)
    decimalOutput = (decimalOutput << 1) + binaryInput[i];

  return decimalOutput;
}

/* binary_adder.ino
 *  
 *  Code for the first of two arduinos.
 *  The code takes input from the user, converts it to its
 *  binary representation and writes that value to the 
 *  specified pins
 *  
 *  Coded by cmsuisse and lrshsl (github.com)
 */



// Pins of the first number
const uint8_t aPins[] {2, 3, 4, 5};

// Pins of the second number
const uint8_t bPins[] {7, 8, 9, 10};


// Entry point
void setup()
{
  Serial.begin(9600);     // Important!!!!!!

  // Pin Setup 
  for (uint8_t pin : aPins)
    pinMode(pin, OUTPUT);
  for (uint8_t pin : bPins)
    pinMode(pin, OUTPUT);

  // First carry must always be 0
  pinMode(6, OUTPUT);     // Important!!!!!!
  digitalWrite(6, LOW);

  Serial.println("Setup complete");
}


void loop() 
{
  /* First number */
  
  // Get input via serial monitor
  Serial.println("Geben Sie den ersten Summanden ein: ");
  while (!Serial.available()) { /* Wait for input */ }
  uint8_t val1 = Serial.parseInt();

  // Conversion to binary representation
  uint8_t* a = decimalToBinary(val1);

  // Write to Pins
  simBinaryInput(a, aPins);

  // 'Refresh' Serial (/kill and revive)
  Serial.end();
  Serial.begin(9600);



  /* Second number */

  // Get input
  Serial.println("Geben Sie den zweiten Summanden ein: ");
  while (Serial.available() == 0) { /* Wait for input */ }
  uint8_t val2 = Serial.parseInt();

  // Conversion to binary representation
  uint8_t* b = decimalToBinary(val2);

  // Write to Pins
  simBinaryInput(b, bPins);

  // 'Refresh' Serial (/ kill and revive)
  Serial.end();
  Serial.begin(9600);
}


// decimalToBinary
uint8_t* decimalToBinary(uint8_t n)
{
  // Convert decimal number to its binary representation

  static uint8_t output[4];
  for (int i=3; i>=0; i--) {  // NOT uint8!!
    uint8_t digit = n%2 == 0? 0: 1;
    output[i] = digit;
    n /= 2;
  }

  return output;
}


// simBinaryInput
void simBinaryInput(uint8_t nb[4], const uint8_t inputs[4])
{
  // Write binary number to pins

  for (uint8_t i=0; i<4; i++)
    digitalWrite(inputs[i], nb[i]);

}

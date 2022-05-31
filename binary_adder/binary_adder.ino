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
const int aPins[] {2, 3, 4, 5};

// Pins of the second number
const int bPins[] {7, 8, 9, 10};


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
  Serial.println("Bitte geben Sie den ersten Summanden ein: ");
  while (Serial.available() == 0) { /* Wait for input */ }
  uint8_t val1 = Serial.parseInt();

  // Conversion to binary representation
  int* a = decimalToBinary(val1);

  // Write to Pins
  simBinaryInput(a, aPins);

  // Refresh Serial
  Serial.end();
  Serial.begin(9600);



  /* Second number */

  // Get input
  Serial.println("Geben Sie den zweiten Summanden ein: ");
  while (Serial.available() == 0) { /* Wait for input */ }
  uint8_t val2 = Serial.parseInt();

  // Conversion to binary representation
  int* b = decimalToBinary(val2);

  // Write to Pins
  simBinaryInput(b, bPins);   // Write to pins

  // Refresh Serial
  Serial.end();
  Serial.begin(9600);
}


// decimalToBinary
int* decimalToBinary(int n)
{
  // Convert decimal number to its binary representation

  static int output[4];
  for (int i=3; i>=0; i--) {
    int digit = n%2 == 0? 0: 1;
    output[i] = digit;
    n /= 2;
  }

  return output;
}


// simBinaryInput
void simBinaryInput(int nb[4], const int inputs[4])
{
  // Write binary number to pins

  for (int i=0; i<4; i++)
    digitalWrite(inputs[i], nb[i]);

}

// Constants
const String message = "somebody once told me the world is gonna roll me. i aint the sharpest tool in the shed. she was looking kinda dumb with her finger and her thumb in the shape of an l on her forehead.6";
const int chainLength = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Truncate message to chain length max, or pad on spaces to reach length.
  // Send the message over RX
  // When TX comes back, verify it is an end char, if not, change the chainlength
}

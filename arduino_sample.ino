// Define the analog pin where the flex sensor is connected
const int flexSensorPin = A0;

void setup() {
  // Start the Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the value from the flex sensor
  int flexValue = analogRead(flexSensorPin);
  
  // Print the value to the Serial Monitor
  Serial.print("Flex Sensor Value: ");
  Serial.println(flexValue);
  
  // Wait for a moment before the next reading
  delay(500);
}

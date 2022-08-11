const int SENSOR_PIN = 7; // the Arduino's input pin that connects to the sensor's SIGNAL pin 

int lastState = LOW;      // the previous state from the input pin
int currentState;         // the current reading from the input pin

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  currentState = digitalRead(SENSOR_PIN);

  if(lastState == LOW && currentState == HIGH)
    Serial.println("The sensor is touched");


  lastState = currentState;
}

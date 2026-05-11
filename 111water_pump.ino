// 1. PIN DEFINITIONS
const int trigPin = 5;
const int echoPin = 6;
const int relayPin = 2;

// 2. VARIABLES
bool pumpActive = false;
float startDistance = 0;
const float stopDelta = 3.0; // cm to drain before stopping

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH); // Pump OFF

  Serial.println("--- SYSTEM ONLINE ---");
  Serial.println("Type ON to start pumping");
}

float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

void loop() {
  float distance = measureDistance();

  // SENSOR ERROR SAFETY
  if (distance < 0 || distance < 2) {
    Serial.println("SENSOR ERROR");
    digitalWrite(relayPin, HIGH);
    pumpActive = false;
    delay(500);
    return;
  }

  // SERIAL COMMAND
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toUpperCase();

    if (cmd == "ON" && !pumpActive) {
      startDistance = distance;
      pumpActive = true;
      digitalWrite(relayPin, LOW); // PUMP ON

      Serial.print("PUMP ON | Start distance: ");
      Serial.print(startDistance);
      Serial.println(" cm");
    }
  }

  // AUTO STOP LOGIC
  if (pumpActive) {
    if (distance >= startDistance + stopDelta) {
      digitalWrite(relayPin, HIGH); // PUMP OFF
      pumpActive = false;

      Serial.println("!!! 3 CM DRAINED — PUMP OFF !!!");
    }
  }

  // DEBUG OUTPUT
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Pump: ");
  Serial.println(pumpActive ? "ON" : "OFF");

  delay(500);
}

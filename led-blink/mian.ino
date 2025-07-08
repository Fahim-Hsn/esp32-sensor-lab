```cpp
void setup() {
  pinMode(2, OUTPUT); // GPIO 2 controls LED
}

void loop() {
  digitalWrite(2, HIGH); // Turn ON LED
  delay(1000);           // Wait 1 second
  digitalWrite(2, LOW);  // Turn OFF LED
  delay(1000);           // Wait 1 second
}```

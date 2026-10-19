// Smart Parking Radar Logic:
    // If distance < 10 cm: Critical proximity (continuous warning sound)
    // If distance between 10 cm and 30 cm: Proportional pulsing beep
    // If distance > 30 cm: Safe zone (silent)
    
    if (distanceCm < 10.0) {
      tone(BUZZER_PIN, 1500); // 1500 Hz high pitch tone
      delay(50);
      noTone(BUZZER_PIN);     // Stop the tone
      delay(50);
    } else if (distanceCm <= 30.0) {
      int beepDelay = map((int)distanceCm, 10, 30, 80, 400);
      tone(BUZZER_PIN, 1000); // 1000 Hz standard tone
      delay(40);
      noTone(BUZZER_PIN);
      delay(beepDelay);
    } else {
      noTone(BUZZER_PIN);     // Silence the buzzer
      delay(200);
    }

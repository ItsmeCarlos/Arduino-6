#define BUTTON_PIN 13
#define BUZZER_PIN 12
#define NUM_LEDS 10

int ledPins[NUM_LEDS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
bool buttonPressed = false;

void setup() {
    for (int i = 0; i < NUM_LEDS; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
        buttonPressed = true;
        runWheel();
    }
}

void runWheel() {
    int currentLed = 0;
    unsigned long delayTime = 50;
    unsigned long stopTime = millis() + random(3000, 5000);

    while (millis() < stopTime) {
        digitalWrite(ledPins[currentLed], HIGH);
        tone(BUZZER_PIN, 1000, 100);
        delay(delayTime);
        digitalWrite(ledPins[currentLed], LOW);

        currentLed = (currentLed + 1) % NUM_LEDS;

        if (millis() + delayTime < stopTime && delayTime < 500) {
            delayTime += 10;  
        }
    }

    int stopLed = random(NUM_LEDS);
    for (int i = 0; i < 5; i++) {
        digitalWrite(ledPins[stopLed], HIGH);
        tone(BUZZER_PIN, 1000, 100);
        delay(200);
        digitalWrite(ledPins[stopLed], LOW);
   		delay(200);
    }

    digitalWrite(ledPins[stopLed], HIGH);
    tone(BUZZER_PIN, 1000);
    delay(500);
    noTone(BUZZER_PIN);
    digitalWrite(ledPins[stopLed], LOW);

    buttonPressed = false;
}

#include <LiquidCrystal.h>

// --- Pin Definitions ---
// LCD Pins (Based on previous discussion)
const int lcd_RS = 12;
const int lcd_E = 11;
const int lcd_D4 = 5;
const int lcd_D5 = 4;
const int lcd_D6 = 3;
const int lcd_D7 = 2;

// LED Pin
const int ledPin = 9;

// Button Pins (Using internal pull-ups)
const int button1Pin = 7;
const int button2Pin = 8;

// Output Signal Pin (To Receiver Board)
const int outputSignalPin = 6;

// --- LCD Object ---
LiquidCrystal lcd(lcd_RS, lcd_E, lcd_D4, lcd_D5, lcd_D6, lcd_D7);

// --- Button State Variables ---
// bool button1Pressed = false; // Not strictly needed with new logic
// bool button2Pressed = false; // Not strictly needed with new logic
bool triggerSent = false; // Flag to send signal only once per press

void setup() {
  // Initialize Serial (Optional, for debugging)
  Serial.begin(9600);
  Serial.println("Sender Board Initializing...");

  // Initialize LCD
  lcd.begin(16, 2); // 16 columns, 2 rows
  lcd.print("System Ready");

  // Setup Pin Modes
  pinMode(ledPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP); // INPUT_PULLUP reads HIGH when open, LOW when pressed
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(outputSignalPin, OUTPUT);

  // Ensure signal starts LOW
  digitalWrite(outputSignalPin, LOW);
  digitalWrite(ledPin, LOW); // Start with LED off

  Serial.println("Sender Ready.");
}

void loop() {
  // Read current button states (LOW means pressed)
  bool currentButton1State = (digitalRead(button1Pin) == LOW);
  bool currentButton2State = (digitalRead(button2Pin) == LOW);

  // Check if EITHER button is currently pressed
  if (currentButton1State || currentButton2State) {
    // Check if this is a NEW press (triggerSent is false)
    if (!triggerSent) {
      Serial.println("Button Pressed - Sending HIGH Signal");

      digitalWrite(outputSignalPin, HIGH); // Send HIGH signal to receiver
      digitalWrite(ledPin, HIGH);         // Turn on LED
      triggerSent = true;                 // Mark signal as sent

      // Update LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Button Pressed!");
      lcd.setCursor(0, 1);
      lcd.print("Triggering Motor");
    }
    // If buttons are still held down but signal was already sent, do nothing new
  }
  // Check if BOTH buttons are released AND the signal was previously sent
  else if (!currentButton1State && !currentButton2State && triggerSent) {
     Serial.println("Buttons Released - Sending LOW Signal");

    digitalWrite(outputSignalPin, LOW); // Send LOW signal
    digitalWrite(ledPin, LOW);        // Turn off LED
    triggerSent = false;              // Reset the trigger flag

    // Update LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Ready");
  }

  // Small delay for stability / debounce
  delay(50);
}
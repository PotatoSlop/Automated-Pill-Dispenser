// --- Motor Configuration ---
// Define the motor driver pins CONNECTED TO THIS RECEIVER BOARD
const int AIN1 = 13;      // Control pin 1 on the motor driver
const int AIN2 = 12;      // Control pin 2 on the motor driver
const int PWMA = 11;      // Speed control pin (PWM) on the motor driver
// ** Ensure pin 11 is PWM capable on this board! **

// --- Communication Pin ---
const int triggerPin = 6; // Listens for HIGH signal from Sender Pin 7

// --- Motor Control Variables ---
// Set the desired motor speed (0-255).
// Matched to the constrain() limit in spinMotor function below.
const int MOTOR_SPEED_PULSE = 75; // Using 75 based on spinMotor below.

// *** CALIBRATION REQUIRED FOR ~360 DEGREE ROTATION ***
// This value (milliseconds) determines motor run time. Adjust it via trial and error!
// 1. Upload code with a guess (e.g., 3000).
// 2. Press Sender button, observe rotation.
// 3. If LESS than 360°, INCREASE this value.
// 4. If MORE than 360°, DECREASE this value.
// 5. Repeat steps 1-4 until rotation is close to 360°.
const unsigned long ROTATION_DURATION_MS = 3000; // STARTING GUESS (3 seconds) - *** ADJUST THIS VALUE ***
// *** ACCURATE CALIBRATION IS ESSENTIAL for timed control ***

// State variable to prevent multiple triggers from one pulse or during spin
bool motorIsSpinning = false;

void setup() {
  // Initialize serial communication (for debugging on receiver)
  Serial.begin(9600);
  Serial.println("Receiver Board Initialized");
  // Adding timestamp/location context for Boston, MA (uses compile time)
  Serial.println("Boston, MA - Current Time: " + String(__DATE__) + " " + String(__TIME__));

  // Initialize motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  // Initialize trigger pin as input
  pinMode(triggerPin, INPUT);
  // Note: External pull-down resistor recommended on Pin 6 for stability.

  // Ensure motor is stopped initially
  spinMotor(0);
  Serial.println("Waiting for HIGH signal on Pin 6 to spin motor...");
}

void loop() {
  // Read the state of the trigger pin
  int triggerState = digitalRead(triggerPin);

  // Check if the trigger pin is HIGH AND the motor is not already spinning
  if (triggerState == HIGH && !motorIsSpinning) {
    Serial.println("Trigger Signal Received (Pin 6 HIGH)");
    motorIsSpinning = true; // Set flag: motor action is now in progress

    // --- Motor Spin Sequence ---
    Serial.println("Starting motor spin...");
    Serial.print("Running for ");
    Serial.print(ROTATION_DURATION_MS);
    Serial.println(" ms");

    spinMotor(MOTOR_SPEED_PULSE); // Start motor at the defined speed

    // Keep the motor running for the calibrated duration
    delay(ROTATION_DURATION_MS); // <--- THIS IS THE CALIBRATED DELAY

    // Stop the motor
    spinMotor(0);
    Serial.println("Motor spin complete.");
    // --- End Motor Spin Sequence ---

    // Optional short delay AFTER stopping
    delay(100);

  } else if (triggerState == LOW) {
    // If the trigger pin is LOW, reset the spinning flag
    motorIsSpinning = false;
  }
}

/********************************************************************************/
// Function for driving the motor (Controls direction and speed)
void spinMotor(int motorSpeed) {
  // Constrain the actual speed.
  // NOTE: This limits speed to 75. If MOTOR_SPEED_PULSE is changed, change this too!
  int actualSpeed = constrain(abs(motorSpeed), 0, 75); // LIMIT IS 75!

  if (motorSpeed > 0) {        // Forward
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else if (motorSpeed < 0) { // Backward
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  } else {                     // Stop
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    actualSpeed = 0; // Ensure speed is 0 for analogWrite when stopping
  }

  // Set the motor speed using PWM
  analogWrite(PWMA, actualSpeed);
}
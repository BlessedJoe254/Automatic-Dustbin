#include <Servo.h> // Include the Servo library

// Define ultrasonic sensor pins
#define trigPin 9
#define echoPin 10

// Define servo motor pin
#define servoPin 6

// Create a servo object
Servo lidServo;

// Variables for ultrasonic sensor
long duration, distance;

// Variables for lid control
bool lidOpen = false; // Track if the lid is open
unsigned long lidOpenTime = 0; // Track when the lid was opened

void setup() {
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servo to the servo pin
  lidServo.attach(servoPin);

  // Close the lid initially
  closeLid();

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure distance using the ultrasonic sensor
  distance = getDistance();

  // Debugging: Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if a person is within 30 cm of the dustbin
  if (distance <= 30) {
    if (!lidOpen) {
      openLid(); // Open the lid if it's not already open
      lidOpenTime = millis(); // Record the time the lid was opened
    }
  } else {
    // If the lid is open and no one is nearby, close it after 3 seconds
    if (lidOpen && (millis() - lidOpenTime >= 3000)) {
      closeLid();
    }
  }

  // Small delay to avoid rapid sensor readings
  delay(100);
}

// Function to measure distance using the ultrasonic sensor
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

// Function to open the lid
void openLid() {
  lidServo.write(90); // Rotate servo to 90 degrees (open position)
  lidOpen = true;
  Serial.println("Lid opened");
}

// Function to close the lid
void closeLid() {
  lidServo.write(0); // Rotate servo to 0 degrees (closed position)
  lidOpen = false;
  Serial.println("Lid closed");
}


/*Wiring:
Ultrasonic Sensor:

Trig → Arduino Digital Pin 9.

Echo → Arduino Digital Pin 10.

VCC → 5V.

GND → GND.

Servo Motor:

Signal → Arduino Digital Pin 6.

VCC → 5V.

GND → GND.



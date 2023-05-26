#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 5
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

const int waterPin = 6;
const int relayPin = 12;
int Temp = 0;
// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD 1
#define REVERSE 0
// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1
// Pin Assignments //
//Default pins:
#define DIRA 2 // Direction control for motor A
#define PWMA 3 // PWM control (speed) for motor A
#define DIRB 4 // Direction control for motor B
#define PWMB 11 // PWM control (speed) for motor B


void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(waterPin, INPUT);
  setupArdumoto(); // Set all pins as outputs
  delay(10);
  Serial.println("Set a Temperature Between 90- and 150-degrees F");

  // Start up the library
  sensors.begin();
}
void loop(void){
 
 // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
 if (Serial.available() > 0) {
      // read the incoming byte:
      Temp = Serial.parseInt();
     // SetTemp = Temp;
      Serial.print("You set temperature to ");
      Serial.print(Temp);
      Serial.println(" F");
  }

  if (digitalRead(waterPin) != 0) {
    // Drive motor A (and only motor A) at various speeds, then stop.
    driveArdumoto(MOTOR_A, FORWARD, 255); // Set motor A to REVERSE at max

      if (sensors.getTempFByIndex(0) < Temp) {
        digitalWrite(relayPin, HIGH);
      }

      else {
      digitalWrite(relayPin, LOW);
      }

    sensors.requestTemperatures();
    Serial.print("Celsius temperature: ");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print(" - Fahrenheit temperature: ");
    Serial.print(sensors.getTempFByIndex(0));

    Serial.print(" F  Set temp is: ");
    Serial.println(Temp);
    delay(500);
    }

 }
void driveArdumoto(byte motor, byte dir, byte spd) {
  if (motor == MOTOR_A) {
  digitalWrite(DIRA, dir);
  analogWrite(PWMA, spd);
  }

  else if (motor == MOTOR_B) {
  digitalWrite(DIRB, dir);
  analogWrite(PWMB, spd);
 }
}

// setupArdumoto initialize all pins
void setupArdumoto() {
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
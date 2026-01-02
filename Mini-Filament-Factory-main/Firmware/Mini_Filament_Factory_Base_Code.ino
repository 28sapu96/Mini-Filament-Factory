#include <MAX6675.h>
#include <AccelStepper.h>
#include <PID_v1.h>

// --- PIN DEFINITIONS
#define THERMO_SO  4
#define THERMO_CS  5
#define THERMO_SCK 6
#define SSR_PIN    3
#define HALL_PIN   A0
#define PULL_STEP  7
#define PULL_DIR   11
#define EXT_STEP   8
#define EXT_DIR    10

// --- PID TEMPERATURE CONTROL
double targetTemp = 270.0;
double currentTemp, tempOutput;
double Kp_T = 50, Ki_T = 1.5, Kd_T = 20; // PID Constants
PID tempPID(&currentTemp, &tempOutput, &targetTemp, Kp_T, Ki_T, Kd_T, DIRECT);

// --- PID DIAMETER CONTROL (PULLER)
double targetDia = 1.75;
double currentDia, pullerSpeed; // pullerSpeed is the PID Output
double Kp_D = 150, Ki_D = 10, Kd_D = 5; // PID Constants
PID pullerPID(&currentDia, &pullerSpeed, &targetDia, Kp_D, Ki_D, Kd_D, DIRECT);

// --- HARDWARE
MAX6675 thermocouple(THERMO_SCK, THERMO_CS, THERMO_SO);
AccelStepper extruder(AccelStepper::DRIVER, EXT_STEP, EXT_DIR);
AccelStepper puller(AccelStepper::DRIVER, PULL_STEP, PULL_DIR);

unsigned long windowSize = 1000;
unsigned long windowStartTime;

void setup() {
  Serial.begin(115200);
  windowStartTime = millis();

  // PID 1 Config (Heater)
  tempPID.SetOutputLimits(0, windowSize);
  tempPID.SetMode(AUTOMATIC);

  // PID 2 Config (Puller)
  pullerPID.SetOutputLimits(100, 1000); 
  pullerPID.SetMode(AUTOMATIC);

  extruder.setMaxSpeed(2000);
  puller.setMaxSpeed(2000);
  pinMode(SSR_PIN, OUTPUT);
}

void loop() {
  // INPUT SENSING
  currentTemp = thermocouple.getCelsius();
  
  // Hall Effect Mapping 
  int rawHall = analogRead(HALL_PIN);
  // Calibration: Replace 450 and 550 with measured min max with objects of 1.5mm and 2mm dia respectively
  currentDia = map(rawHall, 450, 550, 150, 200) / 100.0;

  // PID CALCULATIONS
  tempPID.Compute();
  
  if (currentTemp >= 240.0) // Only run puller PID if plastic is molten
  {
    pullerPID.Compute();
  }

  //HEATER OUTPUT
  unsigned long now = millis();
  if (now - windowStartTime > windowSize) windowStartTime += windowSize;
  digitalWrite(SSR_PIN, tempOutput > (now - windowStartTime) ? HIGH : LOW);

  // STEPPER OUTPUT
  if (currentTemp >= 240.0) {
    extruder.setSpeed(250); // Master speed (Constant)
    puller.setSpeed(pullerSpeed); // Slave speed (Variable via PID)
    
    extruder.runSpeed();
    puller.runSpeed();
  } else {
    extruder.stop();
    puller.stop();
  }

  // 5. DEBUGGING
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 500) {
    Serial.print("T:"); Serial.print(currentTemp);
    Serial.print(" D:"); Serial.print(currentDia);
    Serial.print(" vPull:"); Serial.println(pullerSpeed);
    lastUpdate = millis();
  }
}
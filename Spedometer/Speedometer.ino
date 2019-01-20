#include <LiquidCrystal.h>

#define SENSOR 2
#define TIRE_RADIUS 0.33

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

volatile unsigned long magnetCount = 0;
unsigned long oldMagnetCount = 0;
unsigned long oldTime = millis();
unsigned long timer = millis();
double velocity; // m/s
double totalDistance; 
const double tireCircumference = 2 * PI * TIRE_RADIUS;


void setup() {
  pinMode(SENSOR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR), interruptServiceRoutine, RISING);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Dist: Vel: Time:");
  lcd.setCursor(12, 1);
  lcd.print("0:00");
}


void loop() {
 writeSpeed();
 writeDistance();
 writeTime();
}

void interruptServiceRoutine() {
  magnetCount++;
}

void writeSpeed() {
  double deltaTime = 2.0;
  unsigned short numSpins;
  double deltaDistance;
  double acceleration;
  double currVelocity;
  double convertedVelocity;
  short printVelocity;
  
  if( millis() >= oldTime + int(deltaTime * 1000) ) {
    numSpins = magnetCount - oldMagnetCount;

    oldMagnetCount = magnetCount;
    oldTime = millis();

    deltaDistance = numSpins * tireCircumference;
    currVelocity = deltaDistance / deltaTime;
    acceleration = (currVelocity - velocity) / deltaTime;
    velocity = velocity + acceleration * deltaTime;

    convertedVelocity = velocity * 60.0 * 60.0 / 1000.0; // km/h
    printVelocity = round(convertedVelocity);
    lcd.setCursor(6, 1);
    if( printVelocity >= 100 ) {
      lcd.print(printVelocity);
    }
    else if( printVelocity >= 10 ) {
      lcd.print(" ");
      lcd.print(printVelocity);
    }
    else if( printVelocity > 0 ) {
      lcd.print("  ");
      lcd.print(printVelocity);
    }
    else if( printVelocity <= 0 ) {
      lcd.print(" ");
      lcd.print("00");
    }
  }

}

void writeDistance() {
  if( millis() > timer + 1000 ) {
    double distance = (float(magnetCount) * tireCircumference) / 1000.0;
    String distanceString = String(distance);
    String printString;
    lcd.setCursor(0, 1);
    if( distance >= 10.0 ) {
      printString = distanceString.substring(0, 4);
      lcd.print(printString);
    }
    else if( distance >= 1.0 ) {
      lcd.print(" ");
      printString = distanceString.substring(0, 3);
      lcd.print(printString);
    }
    else if( distance >= 0.1 ) {
      lcd.print(" 0.");
      printString = distanceString.charAt(2);
      lcd.print(printString);
    }
    else {
      lcd.print("00.0");
    }
  }
}

void writeTime() {
  unsigned long hours;
  unsigned long mins;
  unsigned long secs;
  if( millis() > timer + 60000 ) {
    secs = millis() / 1000;
    mins = (secs / 60) % 60;
    hours = (secs / (60 * 60));

    lcd.setCursor(12, 1);
    lcd.print(hours);
    lcd.print(":");
    if( mins >= 10 ) {
      lcd.print(mins);
    }
    else {
      lcd.print("0");

      lcd.print(mins);
    }
    timer = millis();
  }
}


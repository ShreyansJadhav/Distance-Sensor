const int pingPin = 12; // defining all of the pins used in the project
const int echoPin = 11;
int rPin = 4;
int bPin = 3;
int aPin = 7;
int fPin = 13;

void setup() {

  Serial.begin(9600);  // initialize serial communication:

  pinMode(pingPin, OUTPUT); // setting the required pins to either OUTPUT or INPUT
  pinMode(echoPin, INPUT);
  pinMode(rPin,OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(aPin, OUTPUT);
  pinMode(fPin, OUTPUT);

  pinMode(A6, INPUT); // potentiometer pin set as in input
}

void loop() {
 
  long duration, inches, cm; // establish variables for duration of the ping, and the distance result in inches and centimeters:
  int sensorValue = analogRead(A6); // the sensor value is the potentiometer value between 0 and 1023
  int brightness = sensorValue/4; // diving it by 4 gives a value ~256 which is what LEDs accept as an analog brightness
  
  digitalWrite(pingPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH); // the ultrasonic sensor sends a ping/high frequency sound wave out 
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW); // the wave is sent for 10 milliseconds

  // a different pin is used to read the signal that has bounced back
  duration = pulseIn(echoPin, HIGH); // the microseconds is the duration that is read with this command

  // convert the time into a distance
  inches = microsecondsToInches(duration); // calls to the functions at the bottom
  cm = microsecondsToCentimeters(duration);

  if(inches <= 2){   // if the object is less than 2 inches from the ultrasonic sensor
    analogWrite(bPin, LOW); 
    analogWrite(rPin,brightness); // only this LED is turned on with the condition met
    analogWrite(aPin,LOW);
    analogWrite(fPin, LOW);
  }
  else if (2<inches && inches<=5){    // if the object is less than 5 inches and greater than 2 inches from the ultrasonic sensor
    analogWrite(bPin, brightness);    // only 2 LEDs turn on when the condition is met
    analogWrite(rPin,brightness);
    analogWrite(aPin, LOW);
    analogWrite(fPin, LOW);
  }
  else if (5<inches && inches <=8){    // if the object is less than 8 inches and greater than 5 inches from the ultrasonic sensor
    analogWrite(bPin, brightness);     // only 3 LEDs turn on when the condition is met
    analogWrite(rPin,brightness);
    analogWrite(aPin, brightness);
    analogWrite(fPin, LOW);
  }
  else{
    analogWrite(bPin, brightness);    // if all of the above conditions fail, this code runs
    analogWrite(rPin,brightness);     // all LEDs are turned on when neither of the conditions are met
    analogWrite(aPin,brightness);
    analogWrite(fPin, brightness);
  }


  Serial.print(inches);     // used to see all of the data in writing on the serial monitor
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

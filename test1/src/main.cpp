#include <Arduino.h>

#define RPWM_motor1  5
#define LPWM_motor1  6
#define RPWM_motor2  9
#define LPWM_motor2  10
#define Buzzer 4 //mendefinisikan pin 4 Arduino sebagai pin Output Buzzer
#define trigPin 3 //mendefinisikan pin 5 arduino sebagai trigger pin sensor ultrasonic
#define echoPin 11//mendefinisikan pin 6 arduino sebagai echoPin sensor ultrasonic
const int X_pin = 0;
const int Y_pin =  1;
int analogValueX;
int analogValueY;
long duration; // variabel durasi sensor ultrasonic
int distance = 0; // jarah dalam centimeter
void setup()
{
  pinMode (RPWM_motor1, OUTPUT);
  pinMode (LPWM_motor1, OUTPUT);
  pinMode (RPWM_motor2, OUTPUT);
  pinMode (LPWM_motor2, OUTPUT);
  pinMode(trigPin, OUTPUT); // setting triggerpin sebagai output
  pinMode(echoPin, INPUT); // setting echopin sebagai Input
  pinMode(Buzzer, OUTPUT); // setting Buzzer sebagai Output
  Serial.begin(9600);
}
void SensorMundur() {
  digitalWrite(trigPin, HIGH);// aktifkan sensor ultrasonic
  delayMicroseconds(10); // selama 10 microseconds
  digitalWrite(trigPin, LOW); // matikan sensor ultrasonic
  duration = pulseIn(echoPin, HIGH); // baca rentan waktu dari trigPin High sampai echoPin high
  distance = duration * 0.040 / 2; //konversi selang waktu ke CM
  if (distance <= 38) // Hanya menampilkan jarak jika jaraknya kurang dari 300 cm / 3 meter
  {
    Serial.println(distance); // kirim data jarak ke PC
    digitalWrite(Buzzer, HIGH);
    delay(distance);
    digitalWrite(Buzzer, LOW);
    delay(distance);
  }
}
void MotorJalan() {

  analogValueX = analogRead(X_pin);
  analogValueY = analogRead(Y_pin);
  // maju
  if (analogValueX >= 550 && analogValueX <= 1023)
  {
    digitalWrite(RPWM_motor1,  HIGH);
    digitalWrite (LPWM_motor1, LOW);
    digitalWrite(RPWM_motor2,  HIGH);
    digitalWrite (LPWM_motor2, LOW);
  }


  // kiri
  else if (analogValueY == 0 )
  {
    digitalWrite (RPWM_motor2, HIGH);
    digitalWrite (LPWM_motor2, LOW);
    digitalWrite (RPWM_motor1, LOW);
    digitalWrite (LPWM_motor1, LOW);
  }
  // kanan
  else if (analogValueY >= 1000 )
  {
    digitalWrite (RPWM_motor1, HIGH);
    digitalWrite (LPWM_motor1, LOW);
    digitalWrite (RPWM_motor2, LOW);
    digitalWrite (LPWM_motor2, LOW);
  }

  // mundur
  else if (analogValueX == 0 && analogValueY >= 0 && analogValueY <= 570)
  {
    digitalWrite (RPWM_motor1, LOW);
    digitalWrite (LPWM_motor1, HIGH);
    digitalWrite (RPWM_motor2, LOW);
    digitalWrite (LPWM_motor2, HIGH);
  }

  // stop
  else if ((analogValueX >= 480 && analogValueX <= 512) || (analogValueY >= 523 && analogValueY <= 526) )
  {
    digitalWrite(RPWM_motor1, LOW);
    digitalWrite(LPWM_motor1, LOW);
    digitalWrite(RPWM_motor2, LOW);
    digitalWrite(LPWM_motor2, LOW);
  }
}
void  loop()
{
  Serial.print("VALUE X: ");
  Serial.println(analogRead(X_pin));
  Serial.print("VALUE Y: ");
  Serial.println(analogRead(Y_pin));
  //delay(250);

  SensorMundur();
  MotorJalan();


}

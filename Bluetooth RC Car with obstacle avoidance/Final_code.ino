 // include parts

 #include <NewPing.h>
 #include <Servo.h>

 //servo intialisation 
 Servo myservo;  
int pos = 0; 

//ultrasonic pins
const int trigPin = 11;
const int echoPin = 3;
// defines variables ultrasonic
long duration;
int distance;


 //define the control pins of the motors
//motor A
int enableA = 10;
int IN1 = 9;
int IN2 = 8;

//motor B
int enableB = 5;
int IN3 = 7;
int IN4 = 6;

#define maximumSpeed 250

String readString;

void setup() {
//servo motor
myservo.attach(2);

//ultrasonic
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 

 
  //set all the motor control pins to output
 
  pinMode (enableA, OUTPUT);
  pinMode (enableB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
 //sweep
 sweep(); 

 



  //motor
  while(Serial.available()){
    //delay(50);
    char c = Serial.read();
    readString+=c;
  }

  if(readString.length() > 0) {
    Serial.println(readString);

    if(readString == "FORWARD"){
      moveForward();
    }
    
    if(readString == "BACK"){
      moveBack();
    }

    if(readString == "LEFT"){
      turnLeft();
    }

    if(readString == "RIGHT"){
      turnRight();
    }

    if(readString == "STOP"){
      stopMotors();
     {
      if(distance>=100 == "STOP")
      stopMotors();
    }}

    readString = "";
  }
}

void moveForward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // accelerate from zero to maximum speed
  for(int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++){
    analogWrite(enableA, motorSpeed);
    analogWrite(enableB, motorSpeed);
    }
}

void moveBack(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  for(int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++){
    analogWrite(enableA, motorSpeed);
    analogWrite(enableB, motorSpeed);
    }
}

void turnLeft(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  for(int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++){
    analogWrite(enableA, motorSpeed);
    analogWrite(enableB, motorSpeed);
  }
}

void turnRight(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  for(int motorSpeed = 0; motorSpeed < maximumSpeed; motorSpeed++){
    analogWrite(enableA, motorSpeed);
    analogWrite(enableB, motorSpeed);
  }
}

void stopMotors(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


//servo sweep loop 
void sweep()
{
  for (pos = 0; pos <= 180; pos += 20) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                        // waits 15ms for the servo to reach the position
     distance = ultrasonic();
    Serial.println(distance);
 

  }
  for (pos = 180; pos >= 0; pos -= 20) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
   distance = ultrasonic();
   Serial.println(distance); 
  
  }}
//ultrasonic 
int ultrasonic()
{

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
return distance;

}

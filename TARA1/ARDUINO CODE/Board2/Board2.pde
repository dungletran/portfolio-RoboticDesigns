#include <Servo.h> 
 
//front motor
Servo servoF;

int ForwardF = 1200;    // run forward
int StopF = 1450;    // stop movement range from 1400-1500
int BackwardF = 1900;    // run backward
int first_motor_move =40 ;

//ping pin number
const int pingPin = 7;
long duration, cm;

//finish step1,2
int finish12=0;

byte On1 = 5;
byte On2 = 10;
byte Finish=1;
byte rxVal = 0;

int i=0;
int first = 1;
void setup() 
{ 
  servoF.attach(11);
  Serial.begin(9600);
} 

void loop()
{
  if (first ==1){
    run();
    first++;
  }
  if(Serial.available()) {
    rxVal = Serial.read();
    if (rxVal == On1){ //1st activation of multi-speed motor 
      run();
      while (1){
        
        if(Serial.available()) {
          rxVal = Serial.read();
          if (rxVal == On2){ //1st activation of multi-speed motor 
            run();
            while (1){
            }
          }
        }
      }    
    }
  }
}

void run(){
  
   for(i = 1; i <= first_motor_move; i++){ // first_motor_move can be adjust                                  
      servoF.writeMicroseconds(ForwardF);
      delay(13);                       
   }
   
  //stop the motor
  for(i = 1; i <= 10; i++){                                  
    servoF.writeMicroseconds(StopF);
    delay(13);                       
  } 
  
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  delay (1000);
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  while ((cm <= 2) || (cm>=5)){
    for(i = 1; i <= 5; i++){                                  
        servoF.writeMicroseconds(ForwardF);
        delay(1);                       
    }
    
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
  
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
    cm = microsecondsToCentimeters(duration);
  }
  
  //off multi-speed motor
  for(i = 1; i <= 5; i++){                                  
    servoF.writeMicroseconds(StopF);
    delay(13);                       
  }
  
  //when finish, send the signal to board1
  for (i ==1; i<=10;i++){
    Serial.print(Finish); //send the new value of txVal
    delay(100); 
  }


}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

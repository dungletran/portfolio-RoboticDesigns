#include <Servo.h> 
 
// servo motor declaration
Servo servoL1;  
Servo servoL2;  
Servo servoR1;  
Servo servoR2;
Servo servoBack1;  
Servo servoBack2;

//set of variables for calibration
float doubleL1,doubleL2;
float doubleR1,doubleR2;
float doubleBack1,doubleBack2;
int L1,L2,Back1,Back2,R1,R2;

//board communication
byte On1 = 5;
byte On2 = 10;
byte Finish=1;
byte rxVal;

int i = 0; 

void setup() 
{ 
  //for all servo motors
  servoL1.attach(3);
  servoL2.attach(9); 
  servoR1.attach(11);
  servoR2.attach(5);   
  servoBack1.attach(6);
  servoBack2.attach(10);
  
  L1 = 1060;  //l   
  L2 = 1730;
  R1 = 1910;   
  R2 = 735;
  Back1 = 900;   
  Back2 = 2040;
  
  servoL1.writeMicroseconds(L1);
  servoL2.writeMicroseconds(L2); 
  servoR1.writeMicroseconds(R1);
  servoR2.writeMicroseconds(R2); 
  servoBack1.writeMicroseconds(Back1); 
  servoBack2.writeMicroseconds(Back2);

  
  //initialize serial transmission
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  start();
  run1();
  run2();
  while(1)
  {
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
  }

} 

void start()
{
  if (Serial.available())
  {
    rxVal = Serial.read();
  }
  while ( rxVal != Finish){
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
     if (Serial.available()){
       rxVal = Serial.read();
     }
  }
   
  L1 = 1060;  //l   
  L2 = 1730;
  R1 = 1910;   
  R2 = 735;
  Back1 = 900;   
  Back2 = 2040;
  
  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2);
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  } 
 
  for(i = 1; i <= 10; i++){                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    L2 -= 4;  
    R2 += 3;      
    delay(13);                       
  } 
 
  L1 = 1060;  //l   
  L2 = 1690;
  R1 = 1910;   
  R2 = 765;
  Back1 = 900;   
  Back2 = 2040;
  
  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2);
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  } 
  
 //proceed the standing up action
  doubleL1 = L1 = 1060 ;
  doubleL2 = L2 = 1690;
  doubleR1 = R1 =1910;
  doubleR2 = R2 =765;
  doubleBack1 = Back1=900 ;
  doubleBack2 = Back2 = 2040;
  
  for(i = 1; i <= 100; i++){                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    doubleL1 += 1.85;
    doubleL2 -= 1.7; 
    doubleR1 -= 1.9;
    doubleR2 += 2.00;
    doubleBack1 += 12;
    doubleBack2 -= 12;
    L1 = (int) doubleL1;
    L2 = (int) doubleL2; 
    R1 = (int) doubleR1;
    R2 = (int) doubleR2; 
    Back1 = (int) doubleBack1;
    Back2 = (int) doubleBack2;       
    delay(26);                       
  } 
  
  //Hold position   
  L1 = 1245;     
  L2 = 1520;
  R1 = 1720;   
  R2 = 965;
  Back1 = 2100;   
  Back2 = 840;
   
  for (i = 1; i < 300; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2);
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
  
}


void run1()
{
  // initial position for step1 of all motor
  L1 = 1235;     
  L2 = 1500;
  R1 = 1720;   
  R2 = 990;
  Back1 = 2100;   
  Back2 = 840;  
  
  //writing initial position for all motors
  servoL1.writeMicroseconds(L1); 
  servoL2.writeMicroseconds(L2);
  servoR1.writeMicroseconds(R1); 
  servoR2.writeMicroseconds(R2);
  servoBack1.writeMicroseconds(Back1); 
  servoBack2.writeMicroseconds(Back2);
  
// first movement,3 legs turns  
  doubleBack1 = Back1 = 2120 ;
  doubleBack2 = Back2 = 840 ;
  
  for(i = 1; i <= 25; i++)  
  {                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    L1 += 2;
    R1 -= 2; 
    doubleBack1 -= 300/25; 
    Back1 = (int) doubleBack1; 
    delay(26);                       
  } 
  
  for(i = 1; i <= 25; i++)  
  {                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    L1 += 3;
    L2 -= 2;
    R1 -= 4;
    R2 += 4;
    doubleBack1 -= 300/25;
    doubleBack2 += 24;
    Back1 = (int) doubleBack1;
    Back2 = (int) doubleBack2;    
    delay(26);                       
  } 
  
 //Holding after 1st turn
  doubleL1 = L1 =1360 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1620 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=1500 ;
  doubleBack2 = Back2 =1440;

  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
  
//Second turn:L1,R1 turn 90, then L2,R2 turn 90 then send signal to board2
  //L1,R1 turn 90
  doubleL1 = L1 =1360 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1620 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=1500 ;
  doubleBack2 = Back2 =1440;
  
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoR1.writeMicroseconds(R1);
    servoL2.writeMicroseconds(L2);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    doubleL1 += 8/5;
    doubleR1 -= 2;
    L1 = (int) doubleL1;   
    R1 = (int) doubleR1;   
    delay(13);                       
  }
  
  //Holding
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=1500 ;
  doubleBack2 = Back2 =1440;

  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }

  //send 1 signal to board2
  for (i=1;i<=3;i++){
    Serial.print(On1); //send the new value of txVal
    delay(100);
  }
  
  //after receive 1st signal from board2, backleg will turn
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=1500 ;
  doubleBack2 = Back2 =1440;

  //B1 
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2);
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    doubleBack1 -= 620/50.0;
    Back1 = (int) doubleBack1;    
    delay(13);                       
  }
  
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=880 ;
  doubleBack2 = Back2 =1440;

  //B2 
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2);
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    doubleBack2 += 12;
    Back2 = (int) doubleBack2;    
    delay(13);                       
  }
  
  
  //hold
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=880 ;
  doubleBack2 = Back2 =2040;
  
  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }

//waiting for the data
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=880 ;
  doubleBack2 = Back2 =2040;

  //hodling all 6 motors when waiting for board2
  
  Serial.available();
  rxVal = Serial.read();
  while ( rxVal != Finish){
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
     if (Serial.available()){
       rxVal = Serial.read();
     }
  }
  
  
  
  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
  
    //L2,R2 turn 90
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1400;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1090;
  doubleBack1 = Back1=880 ;
  doubleBack2 = Back2 =2040;
  
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2);
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    doubleL2 -= 2;  
    doubleR2 += 2.2;  
    L2 = (int) doubleL2; 
    R2 = (int) doubleR2;    
    delay(13);                       
  }  
  
  //Hold position and send the signal to board2 
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1300;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1200;
  doubleBack1 = Back1=880 ;
  doubleBack2 = Back2 =2040;
  
  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
  
//proceed the standing up action
  doubleL1 = L1 =1440 ;
  doubleL2 = L2 =1300;
  doubleR1 = R1 = 1520 ;
  doubleR2 = R2 = 1200;
  doubleBack1 = Back1=880 ;
  doubleBack2 = Back2 =2040;
  
  //25%
    for(i = 1; i <= 100; i++){                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    doubleBack1 += 12.2/5;
    Back1 = (int) doubleBack1;       
    delay(13);                       
  } 
  
  
  for(i = 1; i <= 100; i++){                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    //doubleL1 += 1.9;
    doubleL1 +=1.7;
    doubleL2 -= 1.9; 
    //doubleR1 -= 2.1;
    doubleR1 -=1.9;
    doubleR2 += 2;
    doubleBack1 += 12.2/5*4;
    doubleBack2 -= 12;
    L1 = (int) doubleL1;
    L2 = (int) doubleL2; 
    R1 = (int) doubleR1;
    R2 = (int) doubleR2; 
    Back1 = (int) doubleBack1;
    Back2 = (int) doubleBack2;       
    delay(26);                       
  } 
  
  //Hold position   
  //doubleL1 = L1 =1630;
  doubleL1 = L1 =1610;
  doubleL2 = L2 =1110;
  //doubleR1 = R1=1310 ;
  doubleR1 = R1=1330 ;
  doubleR2 = R2 =1400;
  doubleBack1 = Back1=2100 ;
  doubleBack2 = Back2 =840;
   
  for (i = 1; i < 300; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2);
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
}

void run2()
{
  // initial position for step1 of all motor

  doubleL1 =L1 =1625;
  doubleL2 =L2 =1100;
  doubleR1 =R1 =1300;
  doubleR2 =R2 =1410;
  doubleBack1 = Back1 = 2050;
  doubleBack2 = Back2 = 840; 
  
  //writing initial position for all motors
  servoL1.writeMicroseconds(L1); 
  servoL2.writeMicroseconds(L2);
  servoR1.writeMicroseconds(R1); 
  servoR2.writeMicroseconds(R2);
  servoBack1.writeMicroseconds(Back1); 
  servoBack2.writeMicroseconds(Back2);
  
// first movement,3 legs turns  
  doubleBack1 = Back1 = 2050;
  doubleBack2 = Back2 = 840;
  
  for(i = 1; i <= 25; i++)  
  {                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    doubleL1 += 2.2;
    R1 -= 2; 
    doubleBack1 -= 310/25; 
    L1 = (int) doubleL1;
    Back1 = (int) doubleBack1; 
    delay(26);                       
  } 
  
  for(i = 1; i <= 25; i++)  
  {                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    doubleL1 += 2.2;
    L2 -= 4;
    R1 -= 2;
    R2 += 4; 
    doubleBack1 -= 310/25;
    doubleBack2 += 24;
    L1 = (int) doubleL1;
    Back1 = (int) doubleBack1;
    Back2 = (int) doubleBack2;    
    delay(26);                       
  } 
  
 //Holding after 1st turn
  doubleL1 =L1 =1735;
  doubleL2 =L2 =1000;
  doubleR1 =R1 =1200;
  doubleR2 =R2 =1510;
  doubleBack1 = Back1 = 1430;
  doubleBack2 = Back2 = 1440;

  for (i = 1; i < 100; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
  
//Second turn:L1,R1 turn 90, then L2,R2 turn 90 then send signal to board2
  //L1,R1 turn 90 
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoR1.writeMicroseconds(R1);
    servoL2.writeMicroseconds(L2);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    doubleL1 += 1.8;
    R1 -= 2; 
    L1 = (int) doubleL1; 
    delay(13);                       
  }
  
  //Holding
  doubleL1 =L1 =1825;
  doubleL2 =L2 =1000;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1510;
  doubleBack1 = Back1 = 1430;
  doubleBack2 = Back2 = 1440;

  for (i = 1; i < 100; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
  
  
  //send 1 signal to board2
  for (i=1;i<=3;i++){
    Serial.print(On2); //send the new value of txVal
    delay(100);
  }
  
  //after receive 1st signal from board2, backleg will turn
  doubleL1 =L1 =1825;
  doubleL2 =L2 =1000;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1510;
  doubleBack1 = Back1 = 1430;
  doubleBack2 = Back2 = 1440;

  //B1 
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2);
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    doubleBack1 -= 620/50.0;
    Back1 = (int) doubleBack1;    
    delay(13);                       
  }
  
  doubleL1 =L1 =1825;
  doubleL2 =L2 =1000;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1510;
  doubleBack1 = Back1 = 810;
  doubleBack2 = Back2 = 1440;

  //B2 
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2);
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    doubleBack2 += 12;
    Back2 = (int) doubleBack2;    
    delay(13);                       
  }
  
  
  //hold
  doubleL1 =L1 =1825;
  doubleL2 =L2 =1000;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1510;
  doubleBack1 = Back1 = 810;
  doubleBack2 = Back2 = 2040;
  
  for (i = 1; i < 100; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }

//waiting for the data
  doubleL1 =L1 =1825;
  doubleL2 =L2 =1000;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1510;
  doubleBack1 = Back1 = 810;
  doubleBack2 = Back2 = 2040;

  //hodling all 6 motors when waiting for board2
  
  Serial.available();
  rxVal = Serial.read();
  while ( rxVal != Finish){
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
     if (Serial.available()){
       rxVal = Serial.read();
     }
  }
  
  //L2,R2 turn 90
  doubleL1 =L1 =1825;
  doubleL2 =L2 =1000;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1510;
  doubleBack1 = Back1 = 810;
  doubleBack2 = Back2 = 2040;
  
  for(i = 1; i <= 50; i++)  
  {                                      
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2);
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2); 
    L2 -= 2; 
    doubleR2 += 2.1;   
    R2 = (int) doubleR2;    
    delay(13);                       
  }  
  
  //Hold position and send the signal to board2 
  doubleL1 =L1 =1825;
  doubleL2 =L2 =900;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1615;
  doubleBack1 = Back1 = 810;
  doubleBack2 = Back2 = 2040;
  
  for (i = 1; i < 100; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2); 
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }

//proceed the standing up action
  doubleL1 =L1 =1825;
  doubleL2 =L2 =900;
  doubleR1 =R1 =1100;
  doubleR2 =R2 =1615;
  doubleBack1 = Back1 = 810;
  doubleBack2 = Back2 = 2040;
  
  for(i = 1; i <= 100; i++){                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    doubleBack1 += 11.4/5;
    Back1 = (int) doubleBack1;      
    delay(13);                 
  }
  
  for(i = 1; i <= 100; i++){                                  
    servoL1.writeMicroseconds(L1);
    servoL2.writeMicroseconds(L2); 
    servoR1.writeMicroseconds(R1);
    servoR2.writeMicroseconds(R2); 
    servoBack1.writeMicroseconds(Back1); 
    servoBack2.writeMicroseconds(Back2);
    doubleL1 += 1.8;
    L2 -= 2; 
    doubleR1 -= 1.9;
    R2 += 2;
    doubleBack1 += 11.4/5*4;
    Back2 -= 12;
    L1 = (int) doubleL1;
    R1 = (int) doubleR1;
    Back1 = (int) doubleBack1;      
    delay(26);                 
  } 
  
  //Hold position   
  doubleL1 = L1 = 2005;
  doubleL2 = L2 = 700;
  doubleR1 = R1 = 910;
  doubleR2 = R2 = 1815;
  doubleBack1 = Back1 = 2000;
  doubleBack2 = Back2 = 840;
   
  for (i = 1; i < 200; i++)
  {
     servoL1.writeMicroseconds(L1);
     servoL2.writeMicroseconds(L2); 
     servoR1.writeMicroseconds(R1);
     servoR2.writeMicroseconds(R2);
     servoBack1.writeMicroseconds(Back1); 
     servoBack2.writeMicroseconds(Back2);
     delay(13);
  }
}


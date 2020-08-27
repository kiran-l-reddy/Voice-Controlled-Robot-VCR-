#include <SoftwareSerial.h>

// Create a string to store the incomming text message
String readString;
String voice;

//Define the pins for ultrasonic Sensor
#define trigPin 2;
#define echoPin 3;

//Define pins for motor driver 
int rightf=5;
int rightb=4;
int leftf=3;
int leftb=2;


int distance;
int i=2;
int j=0;
int motorSpeed=125;
int turn=50;
int ledf=7;
int ledr=8;

//******************************************************************************************************************************************************************
//Initial Setup

void setup() 
{
   Serial.flush();
   pinMode(5,INPUT);   //Set pins as input or output pins
   pinMode(6,INPUT);
   pinMode(7,OUTPUT);
   pinMode(8,OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(9, OUTPUT);
   pinMode(10,OUTPUT);
   pinMode(11,OUTPUT);
   pinMode(12,OUTPUT); 
   Serial.begin(9600);  //Set baud rate at 9600
}


//******************************************************************************************************************************************************************
//Run forever

void loop()
{ 
   distance = ping();   //check for obstracle
   if(distance<15)      //If there is a obstracle present then turn left 
      leftm();          //you can turn right as well or stop the robot, based on your project requirements

   int button=digitalRead(5);    // buttons to select the mode of input
   int button1=digitalRead(6);
 
   //check mode select
   if(button==1)   
     i=1;
   else if(button1==1)
     i=0;

   //select mode
   if(i==0)
     control();
   else
     terminal();
}

//******************************************************************************************************************************************************************
//terminal mode or text mode

void terminal()
{
   String input="";
   while(Serial.available()) 
   {
     input+=(char)Serial.read();  //Read the incomming text 
     delay(5);
   }
   if(input=="n")                 //compare the received text with the predefined string and call the respective function
   {
     stp();
   }
   else if(input=="F")
   {
     frontm();
   }
   else if(input=="R")
   {
     backm();
   }
   else if(input.indexOf("TL")>-1)
   {
     leftm();
   }
   else if(input.indexOf("TR")>-1)
   {
     rightm();
   }
}

//******************************************************************************************************************************************************************
//voice mode

void control()
{
   // get the string
   while ( Serial.available() ) 
   { 
      delay( 3 );
      char c = Serial.read();           //Store the incomming message in a string  
      readString += c;
   }
   if ( readString.length() >0 )        //Check if any message is received or not
   {
      Serial.println( readString );
      voice= readString;
      readString="";
   }
   if(voice=="straight"||voice=="front"||voice=="forward")  //compare the received text with the predefined string and call the respective function
   {
      frontm();
   }
   else if(voice=="stop")
   {
      stp();
   }
   else if(voice=="backward"||voice=="back"||voice=="reverse")
   { 
      backm();
   }
   else if(voice=="turn right"||voice=="turn write"||voice=="write"||voice=="right")
   {
      rightm();
   }
   else if(voice=="turn left"||voice=="left")
   {
      leftm();
   }
}

//******************************************************************************************************************************************************************
//right

void rightm()
{   
    digitalWrite(rightf,LOW);
    digitalWrite(rightb,HIGH);
    digitalWrite(leftf,HIGH);
    digitalWrite(leftb,LOW);
    digitalWrite(ledr,HIGH);
    delay(1000);
    digitalWrite(ledr,LOW);
}


//left
void leftm()
{
    digitalWrite(rightf,HIGH);
    digitalWrite(rightb,LOW);
    digitalWrite(leftf,LOW);
    digitalWrite(leftb,HIGH);
    digitalWrite(ledf,HIGH);
    delay(1000);
    digitalWrite(ledf,LOW);
}


//front
void frontm()
{  
    digitalWrite(rightf,HIGH);
    digitalWrite(rightb,LOW);
    digitalWrite(leftf,HIGH);
    digitalWrite(leftb,LOW);
}


//back
void backm()
{  
    digitalWrite(rightf,LOW);
    digitalWrite(rightb,HIGH);
    digitalWrite(leftf,LOW);
    digitalWrite(leftb,HIGH);
}


//stop
void stp()
{  
    digitalWrite(rightf,LOW);
    digitalWrite(rightb,LOW);
    digitalWrite(leftf,LOW);
    digitalWrite(leftb,LOW);
}  

//******************************************************************************************************************************************************************
//function to check the distance

long ping()
{
   pinMode(2, OUTPUT);
   digitalWrite(2, LOW);
   delayMicroseconds(2);
   digitalWrite(2, HIGH);
   delayMicroseconds(5);
   digitalWrite(2, LOW);
   pinMode(3, INPUT);
   long duration = pulseIn(3, HIGH);  
   return duration / 29 / 2;
}

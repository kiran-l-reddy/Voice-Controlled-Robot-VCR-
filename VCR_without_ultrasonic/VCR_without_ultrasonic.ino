// Define pins for motor driver control 

int front=6;
int back=7;
int right=8;
int left=9;

int i;

// Define a string to hold the incomming text message

String readString;
String voice;


//************************************************************************************************************************************************************
//Initial Setup

void setup() 
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);    //Buad rate is set to 9600
}

//*************************************************************************************************************************************************************
// Runs forever

void loop()
{
  while ( Serial.available() ) //Check if there's any incomming text available 
  { 
     delay( 3 );
     char c = Serial.read();    //the incomming characters is stored in c
     readString += c;           //Staore the incomming message in readstring
  }

  if ( readString.length() >0 ) //Check the length to see if you have reveived any message
  {
    Serial.println( readString );
    voice= readString;           //If any message is received then copy the message to voice and empty the string
    readString="";               //This is to ensure that the next incomming message is not concatinated with the existing one
  }

//*************************************************************************************************************************************************************
//Compare the received message with predefined commands

  if(voice=="straight"||voice=="front"||voice=="forward") // you can compare with your own strings here
  {
    frontm();                                             //Call the respective functions
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
  else if(voice=="rotate left")
  {
    leftmr();
  }
    else if(voice=="rotate right"||voice=="rotate write")
  {
    rightmr();
  }
     else 
  {
    stp();
  }
}

//*************************************************************************************************************************************************************
//function definition

void rightm()
{
    digitalWrite(back,HIGH);
    digitalWrite(right,LOW);
    digitalWrite(front,LOW);
    digitalWrite(left,LOW);
    for(i=0;i<200;i++);        //This is to ensure that the robot turns right and starts moving forward
    digitalWrite(left,HIGH);
    digitalWrite(back,HIGH);
    digitalWrite(front,LOW);
    digitalWrite(right,LOW);
}

void leftm()
{
    digitalWrite(left,HIGH);
    digitalWrite(back,LOW);
    digitalWrite(front,LOW);
    digitalWrite(right,LOW);
    for(i=0;i<200;i++);
    digitalWrite(left,HIGH);
    digitalWrite(back,HIGH);
    digitalWrite(front,LOW);
    digitalWrite(right,LOW);
}

void frontm()
{
    digitalWrite(left,HIGH);
    digitalWrite(back,HIGH);
    digitalWrite(front,LOW);
    digitalWrite(right,LOW);
}

void backm()
{
    digitalWrite(right,HIGH);
    digitalWrite(front,HIGH);
    digitalWrite(back,LOW);
    digitalWrite(left,LOW);
}

void rightmr()
{
    digitalWrite(back,HIGH);
    digitalWrite(right,LOW);
    digitalWrite(front,LOW);
    digitalWrite(left,LOW);
}

void leftmr()
{
    digitalWrite(left,HIGH);
    digitalWrite(back,LOW);
    digitalWrite(front,LOW);
    digitalWrite(right,LOW);
}

void stp()
{
    digitalWrite(right,LOW);
    digitalWrite(front,LOW);
    digitalWrite(back,LOW);
    digitalWrite(left,LOW);
}  

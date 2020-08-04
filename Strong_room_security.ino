//include Keypad.h,LiquidCrystal.h,Servo.h libraries 
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo servo;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {11,10,9,8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0,A2,A3,A4}; //connect to the column pinouts of the keypad
// initialize the Keypad.h library 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// 16x2 LCD 
#define rs 7 
#define en 6 
#define d4 5  
#define d5 4  
#define d6 3 
#define d7 2 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//'key' password
String password = "5858";
//variable to verify the 'key' password
String mypassword;
//'master' password
String master="585D";
//variable to verify the 'master' password
String masterpass;

int redled = 13;//red led to indicate incorrect password
int greenled= 15;// green led to indicate correct password
int buzz = 12;// piezo buzzer to rise an alarm in case of three 
              // unsuccesful trails
int angle=0;// Servo motor angle initialized to zero degrees
int counter = 0; 
int attempts = 0; 
int max_attempts = 3;// maximum attempts to enter 'key' password is 3


 
void setup()
{
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  pinMode(redled, OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(redled, LOW);
  digitalWrite(buzz, LOW);
  //setup for the servo motor
  Serial.println("enter password");
  lcd.begin(16, 2);
  servo.attach(A5);
  servo.write(angle);
  lcd.print("Enter Password:");
}
  
void loop()
{
  keypadfunction();
}

 
void keypadfunction()
{
 char key = keypad.getKey();// get the key typed in the keypad
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);//cursor is incremented on eack key press
    lcd.print("*");// password is displayed with *
  }
  if (key == '1')
  {
 
    mypassword = mypassword + 1;   
  }
  
    if (key == '2')
  {
 
    mypassword = mypassword + 2;  
  }
  
  if (key == '3')
  {
 
    mypassword = mypassword + 3; 
  }
  
   if (key == '4')
  {
  
    mypassword = mypassword + 4;  
  }
  
  if (key == '5')
  {
  
    mypassword = mypassword + 5;
  }
  
   if (key == '6')
  {
   
    mypassword = mypassword + 6; 
  }
  
   if (key == '7')
  {
 
    mypassword = mypassword + 7; 
  }
 
   if (key == '8')
  {
 
    mypassword = mypassword + 8; 
  }
  
  if (key == '9')
  {
 
    mypassword = mypassword + 9;
  }
             
  if (key == '0')
  {
 
    mypassword = mypassword + 0; 
  }
  if(key=='A')
  {
    mypassword=mypassword+'A';
  }
  if(key=='B')
  {
    mypassword=mypassword+'B';
  }
  if(key=='C')
  {
    mypassword=mypassword+'C';
  }
  if(key=='D')
  {
    mypassword=mypassword+'D';
  }
  
  if (key == '#')//  '#' is pressed to confirm password
  {
    Serial.println(mypassword); 
 //if typed password is right   
   if ( password == mypassword )
   {
     digitalWrite(15,HIGH);
     lcd.clear(); 
     lcd.println("ACCESS");
     lcd.setCursor(0,1);
     lcd.println("GRANTED");
     delay(2000);
   // open the door      
   for(angle = 0; angle < 180; angle++)  
    {                                  
      servo.write(angle);               
      delay(15);                   
    } 
  delay(10000);//waits for 10 seconds
  digitalWrite(greenled,LOW);
  // now scan back from 180 to 0 degrees
  // close the door after 10 seconds
  for(angle = 180; angle > 0; angle--)    
   {                                
    servo.write(angle);           
    delay(15);       
   } 
    mypassword = ""; //mypassword variable cleared
    counter = 0;// counter variable cleared
    attempts=0;//number of attempts cleared
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.println("Enter Password:");
}
//if typed password is wrong
else
{
   Serial.println("wrong");
   digitalWrite(redled,HIGH);// red led blinks indicating wrong password
   delay(250);
   digitalWrite(redled,LOW);
   delay(250);
   attempts = attempts + 1; //attempts is incremented to control the max number of attempts
   Serial.println(attempts);
   mypassword = "";// mypassword variable cleared to re-enter the password
   counter = 0; //counter variable cleared
   lcd.clear(); 
   lcd.setCursor(0,0); 
   lcd.print("Wrong Password");
   delay(500);
   lcd.setCursor(0,1); 
   lcd.print("max attempts 3");
   delay(500);
   lcd.clear(); 
   lcd.print("Enter Password:");
   lcd.setCursor(0,1); 
} 
} 
// if wrong password is entered 3 times
if (attempts>=max_attempts)
  {
    tone(buzz,950);//buzzer ON until 'master' password is typed
    digitalWrite(redled,HIGH);
    
    lcd.setCursor(0,0);
    lcd.print("enter master key:");
    char key = keypad.getKey();
     
  if(key)
  {
    counter=counter+1;
    lcd.setCursor(counter,1);
    lcd.print("*");
  }
  if (key == '1')
  {
 
    masterpass = masterpass + 1;   
  }
  
    if (key == '2')
  {
 
    masterpass = masterpass + 2;  
  }
  
  if (key == '3')
  {
 
    masterpass = masterpass + 3; 
  }
  
   if (key == '4')
  {
  
    masterpass = masterpass + 4;  
  }
  
  if (key == '5')
  {
  
    masterpass = masterpass + 5;
  }
  
   if (key == '6')
  {
   
    masterpass = masterpass + 6; 
  }
  
   if (key == '7')
  {
 
    masterpass = masterpass + 7; 
  }
 
   if (key == '8')
  {
 
    masterpass = masterpass + 8; 
  }
  
  if (key == '9')
  {
 
    masterpass = masterpass + 9;
  }
             
  if (key == '0')
  {
 
    masterpass = masterpass + 0; 
  }
  if(key=='A')
  {
    masterpass=masterpass+'A';
  }
  if(key=='B')
  {
    masterpass=masterpass+'B';
  }
  if(key=='C')
  {
    masterpass=masterpass+'C';
  }
  if(key=='D')
  {
    masterpass=masterpass+'D';
  }  
  
  if (key == '#')// # indicates confirmation of entered password
  {
     
    
   if ( masterpass == master )
   {
    digitalWrite(greenled,HIGH);
    noTone(buzz);//stop the buzzer alarm
    digitalWrite(redled,LOW);
    lcd.clear(); 
    lcd.println("ACCESS");
    lcd.setCursor(0,1);
    lcd.println("GRANTED");
    delay(5000);
  //open door
  for(angle = 0; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  delay(10000);//wait for 10 seconds
  digitalWrite(greenled,LOW);
  // close door
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 
  masterpass = ""; // master password cleared
  counter = 0; 
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Enter password:");
  attempts=0;
}
}
}
}
  

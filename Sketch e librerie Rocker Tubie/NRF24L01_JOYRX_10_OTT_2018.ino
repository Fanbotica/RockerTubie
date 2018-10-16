/* YourDuinoStarter Example: nRF24L01 Radio remote control of servos by joystick
  - WHAT IT DOES
   Joystick on other Arduino communicates by nRF25L01 Radio to
   this Arduino with 2 pan-tilt servos
   SEE: The variable 'hasHardware'. You can test without servos and later set hasHardware = true;
        You NEED separate Servo power, not USB. YourDuino RoboRED has built in 2A power for servos
  - SEE the comments after "//" on each line below
  - CONNECTIONS:
   - nRF24L01 Radio Module: See http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 5V
   3 - CE to Arduino pin 48
   4 - CSN to Arduino pin 53
   5 - SCK to Arduino pin 52
   6 - MOSI to Arduino pin 51
   7 - MISO to Arduino pin 50
   8 - UNUSED

  - V2.12 02/08/2016
   - Uses the RF24 Library by TMRH20 and Maniacbug: https://github.com/TMRh20/RF24 (Download ZIP)
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
#include "printf.h" // Needed for "printDetails" Takes up some memory
#include "DBH1.h" // DBH-12V DC Motor Driver library
// NEED the SoftwareServo library installed
// http://playground.arduino.cc/uploads/ComponentLib/SoftwareServo.zip
#include <SoftwareServo.h>  // Regular Servo library creates timer conflict!
/*-----( Declare Constants and Pin Numbers )-----*/
#define  CE_PIN  48   // The pins to be used for CE and SN
#define  CSN_PIN 53

#define SERVO_IIC_ADDR  (0x41)
Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver(SERVO_IIC_ADDR);
//#define ServoXPIN 2   //Pin Numbers for servos and laser/LED
//#define ServoYPIN 3
#define ServoHPIN 44
#define ServoTPIN 45
#define ServoSPIN 7
#define ButtonAPIN 24
#define ButtonBPIN 25
#define redPin 4
#define greenPin 5
#define bluePin 6
#define redPin1 44
#define greenPin1 45
#define bluePin1 46
#define COMMON_ANODE //uncomment this line if using a Common Anode LED

long speedX, mapX;  //variabili di gestione movimenti motore X
long speedY, mapY;  //variabili di gestione movimenti motore Y
long speedA, speedB;
const int maxSpeed = 255; //massima velocità settabile per il motore
const int minSpeed = 0; //minima velocità settabile per il motore
 
const int dz = 30;  //DeadZone la lettura dei potenziometri non è mai affidabile al 100%, questo valore aiuta a determinare il punto da considerare come "Stai fermo" nei movimenti
long dzUp, dzDown;  //variabili di servizio per espletare il compito descritto sopra

DBH1 dbh;

//#define ServoMIN_X  30  // Don't go to very end of servo travel
//#define ServoMAX_X  150 // which may not be all the way from 0 to 180. 
//#define ServoMIN_Y  30  // Don't go to very end of servo travel
//#define ServoMAX_Y  150 // which may not be all the way from 0 to 180
//#define ServoMIN_H  30  // Don't go to very end of servo travel
//#define ServoMAX_H  150 // which may not be all the way from 0 to 180. 
//#define ServoMIN_T  30  // Don't go to very end of servo travel
//#define ServoMAX_T  150 // which may not be all the way from 0 to 180
//#define ServoMIN_S  30  // Don't go to very end of servo travel
//#define ServoMAX_S  150 // which may not be all the way from 0 to 180.

/*-----( Declare objects )-----*/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus (usually) pins 7 & 8 (Can be changed) */
RF24 radio(CE_PIN, CSN_PIN);

//SoftwareServo XServo;
//SoftwareServo YServo;  // create servo objects to control servos
SoftwareServo HServo;
SoftwareServo TServo;  // create servo objects to control servos
SoftwareServo SServo;

/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

// Allows testing of radios and code without servo hardware. Set 'true' when servos connected
//boolean hasHardware = false;  // Allows testing of radios and code without Joystick hardware.
boolean hasHardware = true;

int XJoyReceived; // Variable to store received Joystick values
//int XServoPosition;    // variable to store the servo position

int YJoyReceived;   // Variable to store received Joystick values
//int YServoPosition;      // variable to store the servo position

int HJoyReceived; // Variable to store received Joystick values
//int HServoPosition;    // variable to store the servo position

int TJoyReceived;   // Variable to store received Joystick values
//int TServoPosition;      // variable to store the servo position

int SJoyReceived; // Variable to store received Joystick values
//int SServoPosition;    // variable to store the servo position

int AJoyReceived;   // Variable to store received Joystick values
//int AButtonPosition;      // variable to store the button position

int BJoyReceived;   // Variable to store received Joystick values
//int BButtonPosition;      // variable to store the button position
/**
  Create a data structure for transmitting and receiving data
  This allows many variables to be easily sent and received in a single transmission
  See http://www.cplusplus.com/doc/tutorial/structures/
*/
struct dataStruct {
  unsigned long _micros;  // to save response times
  int Xposition;          // The Joystick position values
  int Yposition;
  int Hposition;          // The Joystick position values
  int Tposition;
  int Sposition;          // The Joystick position values
  int Abutton;
  int Bbutton;          // The Joystick push-down switch
} myData;                 // This can be accessed in the form:  myData.Xposition  etc.


void setup()   /****** SETUP: RUNS ONCE ******/
{
  //calcola range valori entro i quali considerare la posizione del joystick come "Stai fermo"
  dzDown = (maxSpeed / 2) - dz;
  dzUp = (maxSpeed / 2) + dz;
  Serial.begin(115200);   // MUST reset the Serial Monitor to 115200 (lower right of window )
  // NOTE: The "F" in the print statements means "unchangable data; save in Flash Memory to conserve SRAM"
  Serial.println(F("YourDuino.com Example: Receive joystick data by nRF24L01 radio from another Arduino"));
  Serial.println(F("and control servos if attached (Check 'hasHardware' variable"));
  printf_begin(); // Needed for "printDetails" Takes up some memory
  /*-----( Set up servos )-----*/
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);   
  if (hasHardware)
  {
    // XServo.attach(ServoXPIN);  // attaches the servo to the servo object
    // YServo.attach(ServoYPIN);
    HServo.attach(ServoHPIN);
    //TServo.attach(ServoTPIN);
    SServo.attach(ServoSPIN);
    pinMode(ButtonAPIN, OUTPUT);  // set button pin
    pinMode(ButtonBPIN, OUTPUT);

    dbh.init(8, 9, 10, 11, 22, 23, 0, 1);
    dbh.Braking();
  }

  radio.begin();          // Initialize the nRF24L01 Radio
  radio.setChannel(108);  // 2.508 Ghz - Above most Wifi Channels
  radio.setDataRate(RF24_250KBPS); // Fast enough.. Better range

  // Set the Power Amplifier Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // PALevelcan be one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);
  // radio.setPALevel(RF24_PA_HIGH);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);

  // Start the radio listening for data
  radio.startListening();
  setColor(255, 0, 0);// red  
  radio.printDetails(); //Uncomment to show LOTS of debugging information

}//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{

  if ( radio.available())
  {

    while (radio.available())   // While there is data ready to be retrieved from the receive pipe
    {
      radio.read( &myData, sizeof(myData) );             // Get the data
      //setColor(255, 128, 0);// yellow
    }

    radio.stopListening();                               // First, stop listening so we can transmit  
    radio.write( &myData, sizeof(myData) );              // Send the received data back.
    setColor(0, 0, 255);// blue
    radio.startListening();                              // Now, resume listening so we catch the next packets.
    //setColor(0, 255, 0);// green

//    Serial.print(F("Packet Received - Sent response "));  // Print the received packet data
//    Serial.println(myData._micros);
//    Serial.print(F(" X= "));
//    Serial.println(myData.Xposition);
//    Serial.print(F(" Y= "));
//    Serial.println(myData.Yposition);
//    Serial.print(F(" H= "));
//    Serial.println(myData.Hposition);
//    Serial.print(F(" T= "));
//    Serial.println(myData.Tposition);
//    Serial.print(F(" S= "));
//    Serial.println(myData.Sposition);
//    Serial.print(F(" A= "));
//    Serial.println(myData.Abutton);
//    Serial.print(F(" B= "));
//    Serial.println(myData.Bbutton);

  } // END radio available

  if (hasHardware)
  {
    /*-----( Calculate servo position values, send to the servos )-----*/
    SoftwareServo::refresh();//refreshes servo to keep them updating
    XJoyReceived  = myData.Xposition;  // Get the values received
    YJoyReceived  = myData.Yposition;
    HJoyReceived  = myData.Hposition;
    TJoyReceived  = myData.Tposition;
    SJoyReceived  = myData.Sposition;
    AJoyReceived  = myData.Abutton;
    BJoyReceived  = myData.Bbutton;
    
    
    // scale it to use it with the servo (value between MIN and MAX)
//    XServoPosition  = map(XJoyReceived, 0, 1023, ServoMIN_X , ServoMAX_X);
//    YServoPosition  = map(YJoyReceived, 0, 1023, ServoMIN_Y , ServoMAX_Y);
//    HServoPosition  = map(HJoyReceived, 0, 7, ServoMIN_H , ServoMAX_H);
//    TServoPosition  = map(TJoyReceived, 0, 255, ServoMIN_T , ServoMAX_T);
//    SServoPosition  = map(SJoyReceived, 0, 255, ServoMIN_S , ServoMAX_S);
//    AButtonPosition  = AJoyReceived;
//    BButtonPosition  = BJoyReceived;
    
    // tell servos to go to position
    //XServo.write(XJoyReceived);
    //YServo.write(YJoyReceived);
    dbh.EnableBoth();

    //mappa i valori letti in funzione della velocità minima e massima
    mapX = map(XJoyReceived, 0, 1023, minSpeed, maxSpeed);
    mapY = map(YJoyReceived, 0, 1023, minSpeed, maxSpeed);
    
    //esegui funzione di comando dei motori
    pilotaMotori(mapX, mapY);    

//    HServo.write(HJoyReceived);
//    TServo.write(TJoyReceived);
//    SServo.write(SJoyReceived);
//    switch (AJoyReceived) {
//      case 0:    // your hand is on the sensor
//        digitalWrite(ButtonAPIN, LOW);
//        break;
//      case 1:    // your hand is on the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        break;
//      case 2:    // your hand is close to the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        delay(250);
//        digitalWrite(ButtonAPIN, LOW);
//        delay(250);
//        digitalWrite(ButtonAPIN, HIGH);
//        delay(1000);
//        digitalWrite(ButtonAPIN, LOW);
//        delay(250);        
//        break;
//      case 4:    // your hand is a few inches from the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        break;
//      case 8:    // your hand is nowhere near the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        break;
//      case 16:    // your hand is on the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        break;
//      case 32:    // your hand is close to the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        break;
//      case 64:    // your hand is a few inches from the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        break;
//      case 128:    // your hand is nowhere near the sensor
//        digitalWrite(ButtonAPIN, HIGH);
//        break;        
//    }
//    delay(5);        // delay in between reads for stability
//
//    switch (BJoyReceived) {
//      case 1:    // your hand is on the sensor
//        digitalWrite(ButtonBPIN, HIGH);
//        break;
//      case 2:    // your hand is close to the sensor
//        digitalWrite(ButtonBPIN, LOW);
//        break;
//      case 4:    // your hand is a few inches from the sensor
//        digitalWrite(ButtonBPIN, HIGH);
//        break;
//      case 8:    // your hand is nowhere near the sensor
//        digitalWrite(ButtonBPIN, LOW);
//        break;        
//    }
//    delay(5);        // delay in between reads for stability  
      
        
  } // END hasHardware
  else
  {
    dbh.Braking();
   }
}//--(end main loop )---


void pilotaMotori(long mapX, long mapY) {
 
  if ((mapX <= dzDown) & (mapY <= dzDown)){
    //sinistra avanti con differenziale
    speedX = map(mapX,  maxSpeed, dzUp,  maxSpeed, minSpeed);
    speedY = map(mapY,  minSpeed, dzDown,  maxSpeed, minSpeed);    
    speedA = (speedX + speedY)/2;
    speedB = speedY/2;
    dbh.ForwardA(speedA);
    dbh.ForwardB(speedB);
    //muoviX = true;
    //direzioneX = SINISTRA;
    
  } else if ((mapX >= dzUp) & (mapY >= dzUp)){
    //destra indietro con differenziale
    speedX = map(mapX,  maxSpeed, dzUp,  maxSpeed, minSpeed);
    speedY = map(mapY,  maxSpeed, dzUp,  maxSpeed, minSpeed);    
    speedA = (speedX + speedY)/2;
    speedB = speedY/2;
    dbh.ReverseA(speedA);
    dbh.ReverseB(speedB);    
    //muoviX = true;
    //direzioneX = DESTRA;

  } else if ((mapX >= dzUp) & (mapY <= dzDown)){
    //destra avanti con differenziale

    speedX = map(mapX, dzDown, minSpeed,   minSpeed, maxSpeed);
    speedY = map(mapY, dzDown, minSpeed,   minSpeed, maxSpeed);
    speedA = speedY/2;
    speedB = (speedX + speedY)/2;
    dbh.ForwardA(speedA);
    dbh.ForwardB(speedB);    
    //muoviX = true;
    //direzioneX = DESTRA;

  } else if ((mapX <= dzDown) & (mapY >= dzUp)){
    //sinistra indietro con differenziale
    speedX = map(mapX,  minSpeed, dzDown,  maxSpeed, minSpeed);
    speedY = map(mapY,  maxSpeed, dzUp,  maxSpeed, minSpeed);
    speedA = speedY/2;
    speedB = (speedX + speedY)/2;
    dbh.ReverseA(speedA);
    dbh.ReverseB(speedB);    
    //muoviX = true;
    //direzioneX = DESTRA;

  } else if ((mapX >= dzDown & mapX <= dzUp & mapY <= dzDown)){
    //avanti
    speedY = map(mapY,  minSpeed, dzDown,  maxSpeed, minSpeed);
    speedA = speedY;
    speedB = speedY;
    dbh.Forward(speedA, speedB);
    //muoviX = true;
    //direzioneX = DESTRA;

  } else if ((mapX >= dzDown & mapX <= dzUp & mapY >= dzUp)){
    //indietro
    speedY = map(mapY,  maxSpeed, dzUp,  maxSpeed, minSpeed);
    speedA = speedY;
    speedB = speedY;
    dbh.Reverse(speedA, speedB);
    //muoviX = true;
    //direzioneX = DESTRA;

  } else if ((mapY >= dzDown & mapY <= dzUp & mapX <= dzDown)){
    //a sinistra stretto
    speedX = map(mapX,  minSpeed, dzDown,  maxSpeed, minSpeed);
    speedA = speedX;
    speedB = speedX;
    dbh.TurnLeft(speedA, speedB);
    //muoviX = true;
    //direzioneX = DESTRA;

  } else if ((mapY >= dzDown & mapY <= dzUp & mapX >= dzUp)){
    //a destra stretto
    speedX = map(mapX,  maxSpeed, dzUp,  maxSpeed, minSpeed);
    speedA = speedX;
    speedB = speedX;
    dbh.TurnRight(speedA, speedB);
    //muoviX = true;
    //direzioneX = DESTRA;
  
  } else {
    //x sta fermo
    speedX = 0;
    speedY = 0;
    dbh.Braking();
    //muoviX = false;
  }
 
//  if (enable) {
//    if (muoviX) {
//      motoreX.setSpeed(speedX);
//      motoreX.run(direzioneX);
//    } else {
//      motoreX.stop();
//    }
// 
//    if (muoviY) {
//      motoreY.setSpeed(speedY);
//      motoreY.run(direzioneY);
//    } else {
//      motoreY.stop();
//    }
//  } else {
//    motoreX.stop();
//    motoreY.stop();
//  }
}


/*-----( Declare User-written Functions )-----*/
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  analogWrite(redPin1, red);
  analogWrite(greenPin1, green);
  analogWrite(bluePin1, blue);
    
}

// NONE YET
//*********( THE END )***********

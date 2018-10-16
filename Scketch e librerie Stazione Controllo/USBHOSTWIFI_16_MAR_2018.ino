
/* Simplified Logitech Force 3D Pro Joystick Report Parser by Francesco Onorati www.fanbotica.com*/

#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

//#include "DigitalIO.h"
#include "le3dp_rptparser.h"
#include "RF24.h"  // Download and Install (See above)
#include "printf.h" // Needed for "printDetails" Takes up some memory
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN  48   // The pins to be used for CE and SN
#define CSN_PIN 53
#define redPin 4
#define greenPin 5
#define bluePin 6
#define COMMON_ANODE //uncomment this line if using a Common Anode LED

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);
InitPin                                    inpx;
InitPin                                    inpy;
InitPin                                    inph;
InitPin                                    inpt;
InitPin                                    inps;
InitPin                                    inpa;
InitPin                                    inpb;

//int servoX;

/*-----( Declare objects )-----*/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus (usually) pins 7 & 8 (Can be changed) */
RF24 radio(CE_PIN, CSN_PIN);

/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

unsigned long timeNow;  // Used to grab the current time, calculate delays
unsigned long started_waiting_at;
boolean timeout;       // Timeout? True or False

// Allows testing of radios and code without Joystick hardware. Set 'true' when joystick connected
//boolean hasHardware = false;
boolean hasHardware = true;

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


void setup()
{
//inpx.initx(6);
//inpy.inity(7);
//inph.inith(8);
//inpt.initt(5);
//inps.inits(4);
//inpa.inita(2);
//inpb.initb(3);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
    
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
      Serial.println("OSC did not start.");

  delay( 5 );

  if (!Hid.SetReportParser(0, &Joy))
      ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );
  // NOTE: The "F" in the print statements means "unchangable data; save in Flash Memory to conserve SRAM"
  Serial.println(F("Fanbotica.com Example: Send joystick data by nRF24L01 radio to Rocker Tubie"));
  printf_begin(); // Needed for "printDetails" Takes up some memory

  radio.begin();          // Initialize the nRF24L01 Radio
  radio.setChannel(108);  // Above most WiFi frequencies
  radio.setDataRate(RF24_250KBPS); // Fast enough.. Better range

  // Set the Power Amplifier Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // PALevelcan be one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);
  // radio.setPALevel(RF24_PA_HIGH);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  // Start the radio listening for data
  radio.startListening();
  //setColor(255, 0, 0);// red
  radio.printDetails(); //Uncomment to show LOTS of debugging information
}//--(end setup )---

void loop()
{
  radio.stopListening();                                    // First, stop listening so we can talk.
  //setColor(255, 0, 0);  // red
      if (hasHardware)  // Set in variables at top
  {
    /*********************( Read the Joystick positions )*************************/

    
    
    //myData.switchOn  = !digitalRead(JOYSTICK_SW);  // Invert the pulldown switch

    
//    Usb.Task();   
//    inpx.wrx();
//    inpy.wry();
//    inph.wrh();
//    inpt.wrt();
//    inps.wrs();
//    inpa.wra();
//    inpb.wrb();   

    Usb.Task();
    myData.Xposition = inpx.ValX();
    myData.Yposition = inpy.ValY();
    myData.Hposition = inph.ValH();
    myData.Tposition = inpt.ValT();
    myData.Sposition = inps.ValS();
    myData.Abutton = inpa.ValA();
    myData.Bbutton = inpb.ValB();       
  }
  else
  {
    myData.Xposition = 512;  // Send some known fake data
    myData.Yposition = 512;
    myData.Hposition = 90;
    myData.Tposition = 512;
    myData.Sposition = 90;
    myData.Abutton = 256;
    myData.Bbutton = 256;
  }

  myData._micros = micros();  // Send back for timing


//  Serial.print(F("Now sending  -  "));
    setColor(0, 0, 255);  // blue
  if (!radio.write( &myData, sizeof(myData) )) {            // Send data, checking for error ("!" means NOT)
    Serial.println(F("Transmit failed "));
    setColor(255, 0, 0);  // red    
  }

  radio.startListening();                                    // Now, continue listening
  //setColor(0, 255, 0);// green
  started_waiting_at = micros();               // timeout period, get the current microseconds
  timeout = false;                            //  variable to indicate if a response was received or not

  while ( ! radio.available() ) {                            // While nothing is received
    if (micros() - started_waiting_at > 200000 ) {           // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }
  }

  if ( timeout )
  { // Describe the results
//    Serial.println(F("Response timed out -  no Acknowledge."));
  setColor(255, 0, 0);  // red
  }
  else
  {
    // Grab the response, compare, and send to Serial Monitor
    radio.read( &myData, sizeof(myData) );
    timeNow = micros();
    //setColor(255, 0, 0);// red
   // Show it
//    Serial.print(F("Sent "));
//    Serial.print(timeNow);
//    Serial.print(F(", Got response "));
//    Serial.print(myData._micros);
//    Serial.print(F(", Round-trip delay "));
//    Serial.print(timeNow - myData._micros);
//    Serial.println(F(" microseconds "));

  }

  // Send again after delay. When working OK, change to something like 100
  delay(5);

}//--(end main loop )---

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
}
// NONE YET
//*********( THE END )***********


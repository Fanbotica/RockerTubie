#include "le3dp_rptparser.h"
//#include <Servo.h>
#define rad2grad 57.295779513
//Servo servox, servoy, servoh, servot, servos;
int srvxval = 512;
int srvyval = 512;
int srvhval = 10;
int srvtval = 512;
int srvsval = 512;
int actaval = 0;
int actbval = 0;
double sen   = 0;
float grado  = 0;

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
	joyEvents(evt)
{}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
		if( buf[i] != oldPad[i] ) {
			match = false;
			break;
		}
  }
  	// Calling Game Pad event handler
	if (!match && joyEvents) {
		joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
	}
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{

        uint16_t myX = evt->x;
        //int srvX = map(myX, 0, 1023, 0, 1023);
        //srvxval = srvX;
          srvxval = myX;
//        Serial.print("X: ");
//        Serial.println(srvxval);         

        uint16_t myY = evt->y;
        //int srvY = map(myY, 0, 1023, 0, 1023);
        //srvyval = srvY;
          srvyval = myY;
//        Serial.print("Y: ");
//        Serial.println(srvyval);         

        uint16_t myH = evt->hat;
        int srvH = map(myH, 0, 7, 10, 170);
        srvhval = srvH;
//        Serial.print("Hat: ");
//        Serial.println(srvhval);        
        
        uint16_t myT = evt->twist;
        //int srvT = map(myT, 0, 1023, 0, 1023);
        //srvtval = srvT;
          srvtval = myT;
//        Serial.print("Twist: ");
//        Serial.println(srvtval);         
//        sen = sin( (srvtval/rad2grad) );
//        grado = (( sen * 80 ) + 90 );
        
        
        uint16_t myS = evt->slider;
        //int srvS = map(myS, 0, 1023, 0, 1023);
        //srvsval = srvS;
          srvsval = myS;
//        Serial.print("Slider: ");
//        Serial.println(srvsval);        

        uint16_t myBA = evt->buttons_a;
        actaval = myBA;
//        Serial.print("Buttons A: ");
//        Serial.println(actaval);                

        uint16_t myBB = evt->buttons_b;
        actbval = myBB;
//        Serial.print("Buttons B: ");
//        Serial.println(actbval);

}

int InitPin::ValX()
{
return(srvxval);
}

int InitPin::ValY()
{
return(srvyval);
}

int InitPin::ValH()
{
return(srvhval);
}

int InitPin::ValT()
{
return(srvtval);
}

int InitPin::ValS()
{
return(srvsval);
}

int InitPin::ValA()
{
return(actaval);
}

int InitPin::ValB()
{
return(actbval);
}



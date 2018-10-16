#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <usbhid.h>


struct GamePadEventData
{
  union { //axes and hut switch
    uint32_t axes;
    struct {
      uint32_t x : 10;
      uint32_t y : 10;
      uint32_t hat : 4;
      uint32_t twist : 8;      
    };
  };
  uint8_t buttons_a;
  uint8_t slider;
  uint8_t buttons_b;
};

class JoystickEvents
{
public:
	virtual void OnGamePadChanged(const GamePadEventData *evt);
};

#define RPT_GAMEPAD_LEN	sizeof(GamePadEventData)/sizeof(uint8_t)


class InitPin
{
private:
//  byte pinGlobX;  // pin utilizzato per servo X
//  byte pinGlobY;  // pin utilizzato per servo Y
//  byte pinGlobH;  // pin utilizzato per servo H
//  byte pinGlobT;  // pin utilizzato per servo T
//  byte pinGlobS;  // pin utilizzato per servo S
//  byte pinGlobA;  // pin utilizzato per servo A
//  byte pinGlobB;  // pin utilizzato per servo B

public:
//  void initx (byte pinServX);
//  void inity (byte pinServY);  
//  void inith (byte pinServH);  
//  void initt (byte pinServT);  
//  void inits (byte pinServS);
//  void inita (byte pinActuA);
//  void initb (byte pinActuB);    
//  void wrx(void);
//  void wry(void);
//  void wrh(void);
//  void wrt(void);
//  void wrs(void);
//  void wra(void);
//  void wrb(void);

  int ValX();
  int ValY();
  int ValH();
  int ValT();
  int ValS();
  int ValA();
  int ValB();             
};


class JoystickReportParser : public HIDReportParser
{
	JoystickEvents		*joyEvents;

  uint8_t oldPad[RPT_GAMEPAD_LEN];
  
public:
	JoystickReportParser(JoystickEvents *evt);

	virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);

};

#endif // __HIDJOYSTICKRPTPARSER_H__

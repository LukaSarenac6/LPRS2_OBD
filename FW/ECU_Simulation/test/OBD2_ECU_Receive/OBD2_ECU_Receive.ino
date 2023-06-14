
//#include <SPI.h>
#include "mcp2515_can.h"
mcp2515_can CAN(10);                                    // Set CS to pin 10

int32_t canId = 0x000;

unsigned char len = 0;
unsigned char buf[8];
char str[20];

String BuildMessage="";
int MSGIdentifier=0;


void setup() {
  Serial.begin(115200);
  digitalWrite(1, 1);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}

void loop()
{

    if(CAN_MSGAVAIL == CAN.checkReceive())  
    {
      
      CAN.readMsgBuf(&len, buf);

      for(int i = 0; i<len; i++)
      {  
        BuildMessage = BuildMessage + buf[i] + ",";
      }
      Serial.println(BuildMessage);
      
    }
}
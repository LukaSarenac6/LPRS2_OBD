#include <mcp_can.h>
#include <SPI.h>
#include "mcp2515_can.h"

//request messages
unsigned char CoolantTemp[8] = {2,1,5,0,0,0,0,0};
unsigned char EngineSpeed[8] = {2,1,12,0,0,0,0,0};
unsigned char VehicleSpeed[8] = {2,1,13,0,0,0,0,0};
unsigned char IATSensor[8] = {2,1,15,0,0,0,0,0};//Intake Air Temp
unsigned char MAFSensor[8] = {2,1,16,0,0,0,0,0};//Mass Air Flow
unsigned char AmbientAirTemp[8] = {2,1,70,0,0,0,0,0};
unsigned char CAT1Temp[8] = {2,1,60,0,0,0,0,0};
unsigned char CAT2Temp[8] = {2,1,61,0,0,0,0,0};
unsigned char CAT3Temp[8] = {2,1,62,0,0,0,0,0};
unsigned char CAT4Temp[8] = {2,1,63,0,0,0,0,0};

mcp2515_can CAN(10);                                      // Set CS to pin 10


int32_t canId = 0x000;

unsigned char len = 0;
unsigned char buf[8];
char str[20];

String BuildMessage="";
int MSGIdentifier=0;


void setup() {
  Serial.begin(115200);

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

    sendPid(CoolantTemp);
   // sendPid(EngineSpeed);
   // sendPid(VehicleSpeed);
    
    delay(2000);

}

void sendPid(unsigned char* temp) {
    SERIAL_PORT_MONITOR.print("SEND PID: 0x");
    SERIAL_PORT_MONITOR.println(0x7DF, HEX);
    CAN.sendMsgBuf(0x00, CAN_STDID, 8, temp);
    //CAN.sendMessage()
}

void checkResponse(unsigned char message[]){
  int intMessage = (int)message[2];
  switch(intMessage){
    case 0x05://CoolantTemp
      int CoolantTemp = strtol((char *)&message[3], NULL, 16);

      CoolantTemp = -40 + 1 * CoolantTemp;
      Serial.print("Coolant Temperature: ");
      Serial.print(CoolantTemp);
      break;
    case 0x0c://EngineSpeed
      int decimalValue = strtol((char *)&message[3], NULL, 16) * 256 + strtol((char *)&message[4], NULL, 16); 
      float EngineSpeed = decimalValue / 4;

      Serial.print("Engine Speed: ");
      Serial.print(EngineSpeed);
      break;
    case 0x0d://VehicleSpeed
      int VehicleSpeed = strtol((char *)&message[3], NULL, 16);
      
      Serial.print("Vehicle Speed: ");
      Serial.print(VehicleSpeed);
      break;
    case 0x0f://IATSensor
      break;
    case 0x10://MAFSensor
      break;
    case 0x46://AmbeintAirTemp
      break;
    case 0x3c://CAT1
      break;
    case 0x3d://CAT2
      break;
    case 0x3e://CAT3
      break;
    case 0x3f://CAT4
      break;
  }
}

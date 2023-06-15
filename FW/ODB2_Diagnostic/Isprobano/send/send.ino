#include <mcp2515_can.h>

MCP2515 mcp2515(10);  // CS pin connected to digital pin 10

void setup() {
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
}

void loop() {
  can_message_t message;
  message.id = 0x123;
  message.len = 8;
  message.data[0] = 0x11;
  message.data[1] = 0x22;
  message.data[2] = 0x33;
  message.data[3] = 0x44;
  message.data[4] = 0x55;
  message.data[5] = 0x66;
  message.data[6] = 0x77;
  message.data[7] = 0x88;

  mcp2515.sendMessage(&message);
  delay(1000);
}
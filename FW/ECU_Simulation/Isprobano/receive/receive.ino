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

  if (mcp2515.readMessage(&message) == MCP2515::ERROR_OK) {
    // Process received message
    Serial.print("Received message: ID = 0x");
    Serial.print(message.id, HEX);
    Serial.print(", Length = ");
    Serial.print(message.len);
    Serial.print(", Data = ");
    for (int i = 0; i < message.len; i++) {
      Serial.print(message.data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  delay(100);
}
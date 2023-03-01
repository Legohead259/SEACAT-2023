// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
#include <SPI.h>
#include <LoRa.h>

char servoPos;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // Start LoRa at 951 MHz
  LoRa.setPins(11, 10, 12);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received LoRa packet '");

    // read packet
    while (LoRa.available()) {
      servoPos = LoRa.read();
      Serial.print(servoPos, HEX);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

    // send packet: id is 11 bits, packet can contain up to 8 bytes of data
    Serial.print("Sending CAN packet ... ");

    CAN.beginPacket(0x12);
    CAN.write(servoPos);
    CAN.endPacket();

    Serial.println("done");
  }
}


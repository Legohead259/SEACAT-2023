#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>

Servo portRudder;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(9, OUTPUT);
  portRudder.attach(9);

  Serial.println("LoRa Receiver");

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
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      char servoPos = LoRa.read();
      Serial.print(servoPos, HEX);
      portRudder.write(servoPos);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

  delay(100);
}

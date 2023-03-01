#include <SPI.h>
#include <LoRa.h>

#define POT_IN A5

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(POT_IN, INPUT);

  Serial.println("LoRa Sender");

  LoRa.setPins(8, 4, 7);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // Read in the potentiometer value
  int rawValue = analogRead(POT_IN); 
  long adjValue = map(rawValue, 0, 1023, 0, 180);

  Serial.print("Sending packet: ");
  Serial.println((char) adjValue);

  // send packet
  LoRa.beginPacket();
  // LoRa.print("hello ");
  LoRa.print((uint8_t) adjValue);
  LoRa.endPacket();

  delay(100);
}

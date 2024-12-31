#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(9600);
  
  if (!radio.begin()) {
    Serial.println("NRF24L01 is not working");
    while (true); 
  }
  
  Serial.println("Scanning...");
  Serial.println("Channel | Data");
}

void loop() {
  const int numChannels = 126; 
  uint8_t values[numChannels]; 

  radio.startListening();
  for (int i = 0; i < numChannels; i++) {
    radio.setChannel(i);
    delay(2);
    values[i] = radio.testCarrier() || radio.testRPD();
  }
  radio.stopListening();

  for (int i = 0; i < numChannels; i++) {
    Serial.print("  ");
    Serial.print(i);
    Serial.print("   |   ");
    Serial.println(values[i] ? "Taken" : "Free");
  }
  
  Serial.println("-------------------------------");
  delay(5000);
}

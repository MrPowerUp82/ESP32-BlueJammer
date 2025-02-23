#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RF24.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

RF24 radio(7, 8); // CE, CSN

// Define start and end channels
const int startChannel = 10; // Start of the range
const int endChannel = 30;   // End of the range

int bluetooth_channels[] = {32, 34, 46, 48, 50, 52, 0, 1, 2, 4, 6, 8, 22, 24, 26, 28, 30, 74, 76, 78, 80};
int ble_channels[] = {2, 26, 80};


void setup() {
  Serial.begin(57600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH); // Maximum power level
  radio.setDataRate(RF24_2MBPS);  // Fastest data rate
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void configureRadio(RF24 &radio, int channel, SPIClass *spi) {
  if (radio.begin(spi)) {
      radio.setAutoAck(false);
      radio.stopListening();
      radio.setPALevel(RF24_PA_MAX, true);
      radio.startConstCarrier(RF24_PA_HIGH, channel);
  }
}

void jamBLE() {
  int randomIndex = random(0, sizeof(ble_channels) / sizeof(ble_channels[0]));
  radio.setChannel(ble_channels[randomIndex]);
}

void jammer() {
  char text[32]; // Array to hold random noise data
  for (int i = startChannel; i <= endChannel; i++) { // Iterate over specified range
    for (int j = 0; j < sizeof(text); j++) {
      text[j] = random(32, 127); // Generate random ASCII characters
    }
    radio.setChannel(i);
    radio.write(&text, sizeof(text));
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Jamming Channel: " + String(i));

    // Simulate Signal Strength
    int signalStrength = random(0, 101); // Example signal strength value
    display.setCursor(0, 10);
    display.println("Signal Strength: " + String(signalStrength) + "%");

    display.display();
    delay(20); // Reduced delay for faster hopping
  }
}

void loop() {
  jammer();
}



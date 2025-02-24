
// NRF24 Connection
// SCK=14, MISO=12, MOSI=13, CS=25, CE=26


#include "RF24.h"
#include "esp_bt.h"
#include "esp_wifi.h"

SPIClass *hp = nullptr;

RF24 radio(26, 25, 16000000);

byte i = 45;

unsigned int flag = 0;


void setup(void) {
  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_disconnect();
  Serial.begin(9600);
  initHP();
}
void initHP() {
  hp = new SPIClass(HSPI);
  hp->begin();
  if (radio.begin(hp)) {
    delay(200);
    Serial.println("BLE Jammer is Started !!!");
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPayloadSize(5);   ////SET VALUE ON RF24.CPP
    radio.setAddressWidth(3);  ////SET VALUE ON RF24.CPP
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.printPrettyDetails();
    radio.startConstCarrier(RF24_PA_MAX, i);
  } else {
    Serial.println("BLE Jammer couldn't be started !!!");
  }
}
void two() {

  ///CHANNEL WITH 2 SPACING HOPPING
  if (flag == 0) {
    i += 3;
  } else {
    i -= 3;
  }

  if ((i > 79) && (flag == 0)) {
    flag = 1;
  } else if ((i < 2) && (flag == 1)) {
    flag = 0;
  }

  radio.setChannel(i);
  //Serial.println(i);
}

void one() {
  ////SWEEP CHANNEL
  for (int i = 0; i < 79; i++) {
    radio.setChannel(i);
  }
}

/*YOU CAN DO RANDOM CHANNEL 

radio.setChannel(random(79));
*/




void loop(void) {

  if (random(0, 2) == 0)
    two();

  else {
    one();
  }
}
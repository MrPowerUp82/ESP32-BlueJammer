#include "RF24.h"
#include <SPI.h>
#include "esp_bt.h"
#include "esp_wifi.h"

constexpr int SPI_SPEED = 16000000;

SPIClass *spiVSPI = nullptr;
SPIClass *spiHSPI = nullptr;
RF24 radioVSPI(15, 5, SPI_SPEED);
RF24 radioHSPI(22, 21, SPI_SPEED);

int bluetooth_channels[] = {32, 34, 46, 48, 50, 52, 0, 1, 2, 4, 6, 8, 22, 24, 26, 28, 30, 74, 76, 78, 80};
int ble_channels[] = {2, 26, 80};

void configureRadio(RF24 &radio, int channel, SPIClass *spi);
void executeMode();
void jamBLE();
void jamBluetooth();
void jamAll();

void setup()
{
    Serial.begin(115200);

    esp_bt_controller_deinit();
    esp_wifi_stop();
    esp_wifi_deinit();
    esp_wifi_disconnect();

    spiVSPI = new SPIClass(VSPI);
    spiVSPI->begin();
    configureRadio(radioVSPI, ble_channels[0], spiVSPI);

    spiHSPI = new SPIClass(HSPI);
    spiHSPI->begin();
    configureRadio(radioHSPI, bluetooth_channels[0], spiHSPI);
}

void configureRadio(RF24 &radio, int channel, SPIClass *spi)
{
    if (radio.begin(spi))
    {
        radio.setAutoAck(false);
        radio.stopListening();
        radio.setRetries(0, 0);
        radio.setPALevel(RF24_PA_MAX, true);
        radio.setDataRate(RF24_2MBPS);
        radio.setCRCLength(RF24_CRC_DISABLED);
        radio.startConstCarrier(RF24_PA_HIGH, channel);
    }
}

void loop()
{
    executeMode();
}

void executeMode()
{
    jamAll();
}

void jamBLE()
{
    int randomIndex = random(0, sizeof(ble_channels) / sizeof(ble_channels[0]));
    int channel = ble_channels[randomIndex];
    radioVSPI.setChannel(channel);
    radioHSPI.setChannel(channel);
}

void jamBluetooth()
{
    int randomIndex = random(0, sizeof(bluetooth_channels) / sizeof(bluetooth_channels[0]));
    int channel = bluetooth_channels[randomIndex];
    radioVSPI.setChannel(channel);
    radioHSPI.setChannel(channel);
}

void jamAll()
{
    if (random(0, 2))
    {
        jamBluetooth();
    }
    else
    {
        jamBLE();
    }
    // delayMicroseconds(20);
    delay(2);
}
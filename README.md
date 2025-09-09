# ESP32-BlueJammer
## ESP32 BLE/Bluetooth Jamming Tool

### Descrição
BlueJammer é uma ferramenta de interferência de sinal BLE/Bluetooth baseada no ESP32. Ela permite realizar testes de segurança em dispositivos Bluetooth, simulando ataques de negação de serviço (DoS) e outras formas de interferência de sinal. Esta ferramenta é destinada a pesquisadores de segurança e deve ser usada de forma ética e legal.

### PinOut

#### HSPI
| 1st nRF24L01 module Pin | HSPI Pin (ESP32) | 10uf capacitor |
|---------------|------------------|--------------------|
| VCC           | 3.3V             | (+) capacitor |
| GND           | GND              | (-) capacitor |
| CE            | GPIO 16          |
| CSN           | GPIO 15          |
| SCK           | GPIO 14          |
| MOSI          | GPIO 13          |
| MISO          | GPIO 12          |
| IRQ           |                  |

#### VSPI 
| 2nd nRF24L01 module Pin | VSPI Pin (ESP32) | 10uf capacitor |
|---------------|------------------|--------------------|
| VCC           | 3.3V             | (+) capacitor |
| GND           | GND              | (-) capacitor |
| CE            | GPIO 22          |
| CSN           | GPIO 21          |
| SCK           | GPIO 18          |
| MOSI          | GPIO 23          |
| MISO          | GPIO 19          |
| IRQ           |                  |

#### My Connection

| nRF24L01 | ESP32 Dev Kit |
|----------|---------------|
| VCC      | 3.3V          |
| GND      | GND           |
| CE       | GPIO 26       |
| CSN      | GPIO 25       |
| SCK      | GPIO 14       |
| MOSI     | GPIO 13       |
| MISO     | GPIO 12       |

### Inspirado em
 - [NRF24L01 Jammer Wokwi](https://wokwi.com/projects/411928608367368193)
 - [RF-Clown Hackster.io](https://www.hackster.io/CiferTech/rf-clown-your-portable-ble-bluetooth-jamming-tool-7f74e4)
 - [Project Hub Arduino](https://projecthub.arduino.cc/CiferTech/how-to-make-wifi-jammer-but-with-nrf24l01-2c6ea1)
 - [BLE Jammer using ESP32 and NRF24](https://github.com/WOD-MN/bt_jam)
 - [ESP32-BlueJammer - by @emensta](https://github.com/EmenstaNougat/ESP32-BlueJammer)

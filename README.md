# LoRa APRS iGate

![PlatformIO CI](https://github.com/lora-aprs/LoRa_APRS_iGate/workflows/PlatformIO%20CI/badge.svg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0b7452d5b3b747b88c736e253dda51e6)](https://app.codacy.com/gh/lora-aprs/LoRa_APRS_iGate?utm_source=github.com&utm_medium=referral&utm_content=lora-aprs/LoRa_APRS_iGate&utm_campaign=Badge_Grade_Dashboard)

The LoRa APRS iGate will work with very cheep hardware which you can buy from amazon, ebay or aliexpress.
Try it out and be part of the APRS network.

**There is a german [quick start](https://www.lora-aprs.info/docs/LoRa_APRS_iGate/quick-start-guide/) page! Take a look ;)**

![TTGO LoRa32](pics/iGate.png)

## Supported boards

You can use one of the Lora32 boards without changings :

*   Heltec WiFi LoRa 32 V1 (433MHz SX1278)
*   Heltec WiFi LoRa 32 V2 (433MHz SX1278)
*   TTGO LoRa32 V1 (433MHz SX1278)
*   TTGO LoRa32 V2 (433MHz SX1278)
*   TTGO LoRa32 V2.1 (433MHz SX1278)
*   TTGO T-Beam V0.7 (433MHz SX1278)
*   TTGO T-Beam V1 (433MHz SX1278)
*   Tracker D from [OE1ACM and OE1CGC](https://www.lora-aprs.at/)
*   and sure many more...

Here are some amazon-de links for some example boards:
*   [LoRa32 V1](https://www.amazon.de/dp/B07VPHYYJD)
*   [LoRa32 V1](https://www.amazon.de/dp/B07QRG89ZV)
*   [LoRa32 V2](https://www.amazon.de/dp/B07VL97VNH)
*   [LoRa32 V2.1](https://www.amazon.de/dp/B07RXSKPBX)
*   [T-Beam V1.0](https://www.amazon.de/dp/B07RT9FKPL)

This boards cost around 20 Euros, they are very cheap and perfect for an LoRa iGate.
Keep in minde: you need a 433MHz version!

## Compiling

### How to compile

The best success is to use PlatformIO. 

*   Go to [PlatformIO](https://platformio.org/) download and install the IDE. 
*   If installed open the IDE, go to the left side and klick on 'extensions' then search for 'PatformIO' and install.
*   When installed click 'the ant head' on the left and choose import the project on the right.
*   Just open the folder and you can compile the Firmware.

### Dependencies

*   [LoRa](https://github.com/sandeepmistry/arduino-LoRa) by Sandeep Mistry
*   [APRS-IS-Lib](https://github.com/peterus/APRS-IS-Lib) by Peter Buchegger
*   [APRS-Decoder-Lib](https://github.com/peterus/APRS-Decoder-Lib) by Peter Buchegger
*   [LoRa-APRS-Lib](https://github.com/peterus/LoRa-APRS-Lib) by Peter Buchegger
*   [ArduinoJson](https://github.com/bblanchon/ArduinoJson) by Benoit Blanchon
*   [AXP202X_Library](https://github.com/lewisxhe/AXP202X_Library) by Lewis He
*   [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) by Adafruit (with all dependecies)
*   [NTPClient](https://github.com/arduino-libraries/NTPClient) by Fabrice Weinberg

But you don't need to download all this libs, PlatformIO will take care for you ;)

## Configuration

*   You can find all nessesary settings to change for your configuration in **data/is-cfg.json**.
*   To upload it to your board you have to do this via **Upload File System image** in PlatformIO!
*   To find the 'Upload File System image' click the PlatformIO symbol (the little alien) on the left side, choos your configuration, click on 'Platform' and search for 'Upload File System image'.

## LoRa APRS iGates on aprs.fi

Feel free to add a link to your iGate here:

*   [OE5BPA-10](https://aprs.fi/info/a/OE5BPA-10)

## Future plans

*   [x] show time until next beaconing
*   [ ] show login issues from IS server
*   [ ] add better OLED library to support multiple different OLEDs
*   [x] add support to turn OLED on, off and dimming
*   [ ] add support for temperature chips (BMExxx)
*   [ ] add FTP server support to upload configuration
*   [ ] add web server for configuration and other things
*   [ ] add statistics for received packages
*   [ ] show received packages on a map
*   [ ] etc.

## LoRa Tracker

Look at my other project: a [LoRa Tracker](https://github.com/peterus/LoRa_APRS_Tracker)

## Hints

### Here are some peculiarities of the different boards

*   Wemos® TTGO T-Beam V1

When adding a 0,96" OLED display direct to the board you have to be careful becouse thre are two different pinout versions. 
For direct mount you need this Pinout -> 'VCC - GND - SCL - SDA'
For example (https://www.amazon.de/dp/B07RXSKPBX) 
The other display works too but you have to change VCC and GND.
A direct mount is not possible to the board is not possible without damage the display!

feel free to add hints!
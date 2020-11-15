# LoRa APRS iGate

![PlatformIO CI](https://github.com/lora-aprs/LoRa_APRS_iGate/workflows/PlatformIO%20CI/badge.svg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0b7452d5b3b747b88c736e253dda51e6)](https://app.codacy.com/gh/lora-aprs/LoRa_APRS_iGate?utm_source=github.com&utm_medium=referral&utm_content=lora-aprs/LoRa_APRS_iGate&utm_campaign=Badge_Grade_Dashboard)

The LoRa APRS iGate will work with very cheep hardware which you can buy from amazon, ebay or aliexpress.
Try it out and be part of the APRS network.

**There is a german [quick start](https://www.lora-aprs.info/docs/LoRa_APRS_iGate/quick-start-guide/) page! Take a look ;)**

![TTGO LoRa32](pics/iGate.png)

## Supported boards

You can use one of the Lora32 boards without changings :

* Heltec WiFi LoRa 32 V1 (433MHz SX1278)
* Heltec WiFi LoRa 32 V2 (433MHz SX1278)
* TTGO LoRa32 V1 (433MHz SX1278)
* TTGO LoRa32 V2 (433MHz SX1278)
* TTGO LoRa32 V2.1 (433MHz SX1278)
* TTGO T-Beam V0.7 (433MHz SX1278)
* TTGO T-Beam V1 (433MHz SX1278)
* Tracker D from [OE1ACM and OE1CGC](https://www.lora-aprs.at/)
* and sure many more...

Here are some amazon-de links for some example boards:
* [LoRa32 V1](https://www.amazon.de/dp/B07VPHYYJD)
* [LoRa32 V1](https://www.amazon.de/dp/B07QRG89ZV)
* [LoRa32 V2](https://www.amazon.de/dp/B07VL97VNH)
* [LoRa32 V2.1](https://www.amazon.de/dp/B07RXSKPBX)
* [T-Beam V1.0](https://www.amazon.de/dp/B07RT9FKPL)

This boards cost around 20 Euros, they are very cheap and perfect for an LoRa iGate.
Keep in minde: you need a 433MHz version!

## Compiling

### How to compile

The best success is to use PlatformIO (and it is the only platform where I can support you). 

* Go to [PlatformIO](https://platformio.org/) download and install the IDE. 
* If installed open the IDE, go to the left side and klick on 'extensions' then search for 'PatformIO' and install.
* When installed click 'the ant head' on the left and choose import the project on the right.
* Just open the folder and you can compile the Firmware.

## Configuration

* You can find all nessesary settings to change for your configuration in **data/is-cfg.json**.
* To upload it to your board you have to do this via **Upload File System image** in PlatformIO!
* To find the 'Upload File System image' click the PlatformIO symbol (the little alien) on the left side, choos your configuration, click on 'Platform' and search for 'Upload File System image'.

## Future plans

* [x] show time until next beaconing
* [ ] show login issues from IS server
* [ ] add better OLED library to support multiple different OLEDs
* [x] add support to turn OLED on, off and dimming
* [ ] add support for temperature chips (BMExxx)
* [x] add FTP server support to upload configuration
* [ ] add web server for configuration and other things
* [ ] add statistics for received packages
* [ ] show received packages on a map
* [ ] etc.

## LoRa Tracker

Look at my other project: a [LoRa Tracker](https://github.com/peterus/LoRa_APRS_Tracker)

## Hints

### Here are some peculiarities of the different boards

*   TTGO T-Beam V1

When adding a 0,96" OLED display direct to the board you have to be careful, there are two different pinout
versions on the market. 
For direct mount you need a display with this Pinout -> [VCC - GND - SCL - SDA](pics/display-right.jpg).
A direct mount of the [other display](pics/display-wrong.jpg) is not possible without damage the display!
The 'wrong' display works too but you have to change VCC and GND by wire !

feel free to add hints!

## Blog posts and Youtube videos from other Hams

* [OE1ROT](https://www.aronaut.at/2020/11/lora-aprs-gateway-mit-esp32-boards/)
* [DL7AG](http://online.dl7ag.de/lora-aprs-dl7ag-10/)
* [Manuel Lausmann - Tracker](https://www.youtube.com/watch?v=clIlTEFbWLk)
* [Manuel Lausmann - iGate](https://www.youtube.com/watch?v=C7hfVe32pXs)

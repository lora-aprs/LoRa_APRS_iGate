# LoRa APRS iGate

The LoRa APRS iGate will work with very cheep hardware which you can buy from amazon, ebay or aliexpress.
Try it out and be part of the APRS network.

## Supported boards

You can use one of the Lora32 boards:

* Heltec WiFi LoRa 32 V1 (433MHz SX1278)
* Heltec WiFi LoRa 32 V2 (433MHz SX1278) https://heltec.org/project/wifi-lora-32/
* TTGO LoRa32 V1 (433MHz SX1278)
* TTGO LoRa32 V2 (433MHz SX1278)
* many more...

Here are some amazon-de links for some example boards:
* [Link](https://www.amazon.de/gp/product/B07VPHYYJD/)
* [Link](https://www.amazon.de/gp/product/B078LXL5ZK/)
* [Link](https://www.amazon.de/gp/product/B07QRG89ZV/).

This boards cost around 20 Euros, they are very cheap but perfect for an LoRa iGate.
Keep in minde: you need a 433MHz version!

## what you need to compile

### Additional boards manager URL (Arduino IDE only)

```https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

### Dependencies

* [NTPClient](https://github.com/arduino-libraries/NTPClient) by Fabrice Weinberg
* [LoRa](https://github.com/sandeepmistry/arduino-LoRa) by Sandeep Mistry
* [APRS-IS-Lib](https://github.com/peterus/APRS-IS-Lib) by Peter Buchegger
* [APRS-Decoder-Lib](https://github.com/peterus/APRS-Decoder-Lib) by Peter Buchegger
* [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) by Adafruit (with all dependecies)

## Configuration

Change your configuration in settings.h

## LoRa APRS iGates on aprs.fi

Feel free to add a link to your iGate here:

* [OE5BPA-10](https://aprs.fi/info/a/OE5BPA-10)

## Future plans

The complete configuration should move to [IotWebConf](https://github.com/prampec/IotWebConf).

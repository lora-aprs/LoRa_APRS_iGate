#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define USB_VID 0x303a
#define USB_PID 0x1001

#define EXTERNAL_NUM_INTERRUPTS 46
#define NUM_DIGITAL_PINS        48
#define NUM_ANALOG_INPUTS       20

#define analogInputToDigitalPin(p) (((p) < 20) ? (analogChannelToDigitalPin(p)) : -1)
#define digitalPinToInterrupt(p)   (((p) < 48) ? (p) : -1)
#define digitalPinHasPWM(p)        (p < 46)

#define TX 43
#define RX 44

// The default Wire will be mapped to PMU and RTC
#define SDA 42
#define SCL 41

// Wire1 will be mapped to display and QMC6310 sensor
#define OLED_SDA 17
#define OLED_SCL 18

// Default SPI will be mapped to Radio
#define SS   10
#define MOSI 11
#define MISO 13
#define SCK  12

#define LORA_CS   10
#define LORA_MOSI 11
#define LORA_MISO 13
#define LORA_SCK  12
#define DIO0      -1
#define RST_LoRa  5
#define BUSY_LoRa 4

#define LORA_IRQ 1
#define LORA_RST 5

// Another SPI bus shares SD card and QMI8653 inertial measurement sensor
#define SPI_MOSI (35)
#define SPI_SCK  (36)
#define SPI_MISO (37)
#define SPI_CS   (47)
#define IMU_CS   (34)

#define SDCARD_CS SPI_CS
#define IMU_INT   (33)
// #define PMU_IRQ                  (40)
#define RTC_INT (14)

#endif /* Pins_Arduino_h */

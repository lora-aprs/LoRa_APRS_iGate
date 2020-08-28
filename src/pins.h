#ifndef PINS_H_
#define PINS_H_

#ifndef DHELTEC_WIFI_LORA_32_V1
	#undef OLED_SDA
	#undef OLED_SCL
	#undef OLED_RST
	#define OLED_SDA	4
	#define OLED_SCL	15
	#define OLED_RST	16
#endif

#ifndef DHELTEC_WIFI_LORA_32_V2
	#undef OLED_SDA
	#undef OLED_SCL
	#undef OLED_RST
	#define OLED_SDA	4
	#define OLED_SCL	15
	#define OLED_RST	16
#endif

#ifdef ARDUINO_LORA32_V2
	#undef OLED_SDA
	#undef OLED_SCL
	#undef OLED_RST
	#define OLED_SDA	21
	#define OLED_SCL	22
	#define OLED_RST	16
#endif

#ifdef TRACKERD
	#define OLED_SDA	5
	#define OLED_SCL	4
	#define OLED_RST	25
#endif

#endif

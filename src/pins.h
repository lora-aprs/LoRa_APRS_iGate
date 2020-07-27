#ifndef PINS_H_
#define PINS_H_

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

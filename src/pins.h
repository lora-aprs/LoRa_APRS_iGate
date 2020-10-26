#ifndef PINS_H_
#define PINS_H_

#undef OLED_SDA
#undef OLED_SCL
#undef OLED_RST

#if defined(HELTEC_WIFI_LORA_32_V1) || defined(HELTEC_WIFI_LORA_32_V2) || defined(TTGO_LORA32_V1)
	#define OLED_SDA	4
	#define OLED_SCL	15
	#define OLED_RST	16
#endif

#if defined(TTGO_LORA32_V2) || defined(TTGO_T_Beam_V0_7) || defined(TTGO_T_Beam_V1_0)
	#define OLED_SDA	21
	#define OLED_SCL	22
	#define OLED_RST	16
#endif

#ifdef TRACKERD
	#define OLED_SDA	5
	#define OLED_SCL	4
	#define OLED_RST	25
#endif



#undef KEY_BUILTIN
#if defined(TTGO_T_Beam_V0_7)
	#define KEY_BUILTIN 39
#endif

#if defined(TTGO_T_Beam_V1_0)
	#define KEY_BUILTIN 38
#endif

#ifndef KEY_BUILTIN
	#define KEY_BUILTIN 0
#endif

#endif

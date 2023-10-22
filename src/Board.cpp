#include "Board.h"

String getBoardName() {
#if defined(HELTEC_V1)
  return "Heltec V1";
#elif defined(HELTEC_V2_0)
  return "Heltec V2";
#elif defined(HELTEC_V3)
  return "Heltec V3";
#elif defined(T_INTERNET_POE)
  return "T-Internet PoE";
#elif defined(TBEAM_V10)
  return "T-Beam V1.0 and V1.1";
#elif defined(TBEAM_V12_AXP2101)
  return "T-Beam V1.2 AXP2101";
#elif defined(TBEAM_S3_CORE)
  return "T-Beam S3 Core";
#elif defined(TLORA_V1)
  return "T-LoRa32 V1";
#elif defined(TLORA_V2)
  return "T-LoRa32 V2";
#else
#error "Board not defined!"
#endif
  return "";
}

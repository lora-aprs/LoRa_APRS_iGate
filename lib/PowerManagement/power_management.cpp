
#include "power_management.h"

PowerManagement::PowerManagement() {
}

bool PowerManagement::begin(TwoWire &port) {
  bool result = axp.begin(port, AXP192_SLAVE_ADDRESS);
  if (!result) {
    axp.setDCDC1Voltage(3300);
  }
  return result;
}

void PowerManagement::activateLoRa() {
  axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
}

// cppcheck-suppress unusedFunction
void PowerManagement::deactivateLoRa() {
  axp.setPowerOutPut(AXP192_LDO2, AXP202_OFF);
}

// cppcheck-suppress unusedFunction
void PowerManagement::activateGPS() {
  axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
}

void PowerManagement::deactivateGPS() {
  axp.setPowerOutPut(AXP192_LDO3, AXP202_OFF);
}

void PowerManagement::activateOLED() {
  axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
}

// cppcheck-suppress unusedFunction
void PowerManagement::deactivateOLED() {
  axp.setPowerOutPut(AXP192_DCDC1, AXP202_OFF);
}

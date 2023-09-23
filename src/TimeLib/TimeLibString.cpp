/* DateStrings.cpp
 * Definitions for date strings for use with the Time library
 *
 * Updated for Arduino 1.5.7 18 July 2014
 *
 * No memory is consumed in the sketch if your code does not call any of the string methods
 * You can change the text of the strings, make sure the short strings are each exactly 3 characters
 * the long strings can be any length up to the constant dt_MAX_STRING_LEN defined in TimeLib.h
 *
 */

#include "TimeLib.h"
#include <Arduino.h>

const String monthNames[] = {"Error", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

const String monthStr(uint8_t month) {
  return monthNames[month];
}

const String monthShortNames[] = {"Err", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

const String monthShortStr(uint8_t month) {
  return monthShortNames[month];
}

const String dayNames[] = {"Err", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const String dayStr(uint8_t day) {
  return dayNames[day];
}

const String dayShortNames[] = {"Err", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

const String dayShortStr(uint8_t day) {
  return dayShortNames[day];
}

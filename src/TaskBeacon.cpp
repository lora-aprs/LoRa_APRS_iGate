#include <logger.h>

#include "TimeLib/TimeLib.h"
#include <OneButton.h>

#include "Task.h"
#include "TaskBeacon.h"
#include "project_configuration.h"

BeaconTask::BeaconTask(TaskQueue<std::shared_ptr<APRSMessage>> &toModem, TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs) : Task(TASK_BEACON, TaskBeacon), _toModem(toModem), _toAprsIs(toAprsIs), _ss(1), _useGps(false) {
}

BeaconTask::~BeaconTask() {
}

OneButton BeaconTask::_userButton;
bool      BeaconTask::_send_update;
uint      BeaconTask::_instances;

void BeaconTask::pushButton() {
  _send_update = true;
}

bool BeaconTask::setup(System &system) {
#ifdef KEY_BUILTIN
  if (_instances++ == 0 && KEY_BUILTIN != 0) {
    _userButton = OneButton(KEY_BUILTIN, true, true);
    _userButton.attachClick(pushButton);
    _send_update = false;
  }
#endif

  _useGps = system.getUserConfig()->beacon.use_gps;

  if (_useGps) {
#if defined(GPS_RX_PIN) && defined(GPS_TX_PIN)
    _ss.begin(9600, SERIAL_8N1, GPS_TX_PIN, GPS_RX_PIN);
#else
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "NO GPS found.");
    _useGps = false;
#endif
  }
  // setup beacon
  _beacon_timer.setTimeout(system.getUserConfig()->beacon.timeout * 60 * 1000);

  _beaconMsg = std::shared_ptr<APRSMessage>(new APRSMessage());
  _beaconMsg->setSource(system.getUserConfig()->callsign);
  _beaconMsg->setDestination("APLG01");

  return true;
}

bool BeaconTask::loop(System &system) {
  if (_useGps) {
    while (_ss.available() > 0) {
      char c = _ss.read();
      _gps.encode(c);
    }
  }

  _userButton.tick();

  // check for beacon
  if (_beacon_timer.check() || _send_update) {
    if (sendBeacon(system)) {
      _send_update = false;
      _beacon_timer.start();
    }
  }

  uint32_t diff = _beacon_timer.getTriggerTimeInSec();
  _stateInfo    = "beacon " + String(uint32_t(diff / 600)) + String(uint32_t(diff / 60) % 10) + ":" + String(uint32_t(diff / 10) % 6) + String(uint32_t(diff % 10));

  return true;
}

String create_lat_aprs(double lat) {
  char str[20];
  char n_s = 'N';
  if (lat < 0) {
    n_s = 'S';
  }
  lat = std::abs(lat);
  sprintf(str, "%02d%05.2f%c", (int)lat, (lat - (double)((int)lat)) * 60.0, n_s);
  String lat_str(str);
  return lat_str;
}

String create_long_aprs(double lng) {
  char str[20];
  char e_w = 'E';
  if (lng < 0) {
    e_w = 'W';
  }
  lng = std::abs(lng);
  sprintf(str, "%03d%05.2f%c", (int)lng, (lng - (double)((int)lng)) * 60.0, e_w);
  String lng_str(str);
  return lng_str;
}

bool BeaconTask::sendBeacon(System &system) {
  double lat = system.getUserConfig()->beacon.positionLatitude;
  double lng = system.getUserConfig()->beacon.positionLongitude;

  if (_useGps) {
    if (_gps.location.isUpdated()) {
      lat = _gps.location.lat();
      lng = _gps.location.lng();
    } else {
      return false;
    }
  }
  _beaconMsg->getBody()->setData(String("=") + create_lat_aprs(lat) + "L" + create_long_aprs(lng) + "&" + system.getUserConfig()->beacon.message);

  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "[%s] %s", timeString().c_str(), _beaconMsg->encode().c_str());

  if (system.getUserConfig()->aprs_is.active) {
    _toAprsIs.addElement(_beaconMsg);
  }

  if (system.getUserConfig()->beacon.send_on_hf) {
    _toModem.addElement(_beaconMsg);
  }

  system.getDisplay().addFrame(std::shared_ptr<DisplayFrame>(new TextFrame("BEACON", _beaconMsg->toString())));

  return true;
}

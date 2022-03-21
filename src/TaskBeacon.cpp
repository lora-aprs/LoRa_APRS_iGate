#include <logger.h>

#include <TimeLib.h>

#include "Task.h"
#include "TaskBeacon.h"
#include "project_configuration.h"

BeaconTask::BeaconTask(TaskQueue<std::shared_ptr<APRSMessage>> &toModem, TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs) : Task(TASK_BEACON, TaskBeacon), _toModem(toModem), _toAprsIs(toAprsIs), ss(1), gpsok(false) {
}

BeaconTask::~BeaconTask() {
}

bool BeaconTask::setup(System &system) {
  gpsok = system.getUserConfig()->beacon.gps;

  // Setup GPS
  if (gpsok) {
    if (system.getBoardConfig()->GpsRx != 0) {
      ss.begin(9600, SERIAL_8N1, system.getBoardConfig()->GpsTx, system.getBoardConfig()->GpsRx);
    } else {
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "NO GPS found.");
      gpsok = false;
    }
  }
  // setup beacon
  _beacon_timer.setTimeout(system.getUserConfig()->beacon.timeout * 60 * 1000);

  _beaconMsg = std::shared_ptr<APRSMessage>(new APRSMessage());
  _beaconMsg->setSource(system.getUserConfig()->callsign);
  _beaconMsg->setDestination("APLG01");

  return true;
}

bool BeaconTask::loop(System &system) {

  if (gpsok) {
    while (ss.available() > 0) {
      char c = ss.read();
      gps.encode(c);
    }
  }

  // check for beacon
    if (setBeacon(system)) {
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

bool BeaconTask::setBeacon(System &system) {

  double lat, lng;

  if (gpsok) {
    if (gps.location.isUpdated()) {
      lat = gps.location.lat();
      lng = gps.location.lng();
    } else {
      return false;
    }
  } else {
    lat = system.getUserConfig()->beacon.positionLatitude;
    lng = system.getUserConfig()->beacon.positionLongitude;
  }
  _beaconMsg->getBody()->setData(String("=") + create_lat_aprs(lat) + "L" + create_long_aprs(lng) + "&" + system.getUserConfig()->beacon.message);

  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "[%s]%s", timeString().c_str(), _beaconMsg->encode().c_str());

  if (system.getUserConfig()->aprs_is.active)
    _toAprsIs.addElement(_beaconMsg);

  if (system.getUserConfig()->digi.beacon) {
    _toModem.addElement(_beaconMsg);
  }

  system.getDisplay().addFrame(std::shared_ptr<DisplayFrame>(new TextFrame("BEACON", _beaconMsg->toString())));

  return true;
}

#include <logger.h>

#include "Task.h"
#include "TaskRouter.h"
#include "project_configuration.h"

String create_lat_aprs(double lat);
String create_long_aprs(double lng);

RouterTask::RouterTask(TaskQueue<std::shared_ptr<APRSMessage>> &fromModem, TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs) : Task(TASK_ROUTER, TaskRouter), _fromModem(fromModem), _toAprsIs(toAprsIs) {
}

RouterTask::~RouterTask() {
}

bool RouterTask::setup(System &system) {
  // setup beacon
  _beacon_timer.setTimeout(system.getUserConfig()->beacon.timeout * 60 * 1000);
  _beaconMsg = std::shared_ptr<APRSMessage>(new APRSMessage());
  _beaconMsg->setSource(system.getUserConfig()->callsign);
  _beaconMsg->setDestination("APLG01");
  String lat = create_lat_aprs(system.getUserConfig()->beacon.positionLatitude);
  String lng = create_long_aprs(system.getUserConfig()->beacon.positionLongitude);
  _beaconMsg->getBody()->setData(String("=") + lat + "L" + lng + "&" + system.getUserConfig()->beacon.message);

  return true;
}

bool RouterTask::loop(System &system) {
  // do routing
  if (!_fromModem.empty()) {
    _toAprsIs.addElement(_fromModem.getElement());
  }

  // check for beacon
  if (_beacon_timer.check()) {
    logPrintD("[" + timeString() + "] ");
    logPrintlnD(_beaconMsg->encode());
    _toAprsIs.addElement(_beaconMsg);
    system.getDisplay().addFrame(std::shared_ptr<DisplayFrame>(new TextFrame("BEACON", _beaconMsg->toString())));
    _beacon_timer.start();
  }
  time_t diff = _beacon_timer.getTriggerTimeInSec();
  _stateInfo  = "beacon " + String(diff / 60) + ":" + String(diff % 60);
  return true;
}

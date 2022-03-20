#ifndef TASK_BEACON_H_
#define TASK_BEACON_H_

#include <TinyGPS++.h>

#include <APRSMessage.h>
#include <TaskMQTT.h>
#include <TaskManager.h>

class BeaconTask : public Task {
public:
  BeaconTask(TaskQueue<std::shared_ptr<APRSMessage>> &toModem, TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs);
  virtual ~BeaconTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;
  void         setBeacon(System &system);

private:
  TaskQueue<std::shared_ptr<APRSMessage>> &_toModem;
  TaskQueue<std::shared_ptr<APRSMessage>> &_toAprsIs;

  std::shared_ptr<APRSMessage> _beaconMsg;
  Timer                        _beacon_timer;

  HardwareSerial ss;
  TinyGPSPlus    gps;
  bool           gpsok;
};

#endif

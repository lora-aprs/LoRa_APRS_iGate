#include <logger.h>

#include <TimeLib.h>

#include "Task.h"
#include "TaskRouter.h"
#include "project_configuration.h"

RouterTask::RouterTask(TaskQueue<std::shared_ptr<APRSMessage>> &fromModem, TaskQueue<std::shared_ptr<APRSMessage>> &toModem, TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs, TaskQueue<std::shared_ptr<APRSMessage>> &toMQTT) : Task(TASK_ROUTER, TaskRouter), _fromModem(fromModem), _toModem(toModem), _toAprsIs(toAprsIs), _toMQTT(toMQTT) {
}

RouterTask::~RouterTask() {
}

bool RouterTask::setup(System &system) {
  return true;
}

bool RouterTask::loop(System &system) {
  if (!_fromModem.empty()) {
    std::shared_ptr<APRSMessage> modemMsg = _fromModem.getElement();

    if (system.getUserConfig()->mqtt.active) {
      _toMQTT.addElement(modemMsg);
    }

    if (system.getUserConfig()->aprs_is.active && modemMsg->getSource() != system.getUserConfig()->callsign) {
      std::shared_ptr<APRSMessage> aprsIsMsg = std::make_shared<APRSMessage>(*modemMsg);
      String                       path      = aprsIsMsg->getPath();

      if (!(path.indexOf("RFONLY") != -1 || path.indexOf("NOGATE") != -1 || path.indexOf("TCPIP") != -1)) {
        if (!path.isEmpty()) {
          path += ",";
        }

        aprsIsMsg->setPath(path + "qAO," + system.getUserConfig()->callsign);

        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "APRS-IS: %s", aprsIsMsg->toString().c_str());
        _toAprsIs.addElement(aprsIsMsg);
      } else {
        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "APRS-IS: no forward => RFonly");
      }
    } else {
      if (!system.getUserConfig()->aprs_is.active) {
        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "APRS-IS: disabled");
      }

      if (modemMsg->getSource() == system.getUserConfig()->callsign) {
        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "APRS-IS: no forward => own packet received");
      }
    }

    if (system.getUserConfig()->digi.active && modemMsg->getSource() != system.getUserConfig()->callsign) {
      std::shared_ptr<APRSMessage> digiMsg = std::make_shared<APRSMessage>(*modemMsg);
      String                       path    = digiMsg->getPath();

      // simple loop check
      if (path.indexOf("WIDE1-1") >= 0 && path.indexOf(system.getUserConfig()->callsign) == -1) {
        // fixme
        digiMsg->setPath(system.getUserConfig()->callsign + "*");

        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "DIGI: %s", digiMsg->toString().c_str());

        _toModem.addElement(digiMsg);
      }
    }
  }

  _stateInfo = "Router done ";

  return true;
}

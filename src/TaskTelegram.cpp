#include <logger.h>

#include "Task.h"
#include "TaskTelegram.h"
#include "project_configuration.h"
#include <System.h>
#include <TimeLib.h>

TelegramTask::TelegramTask(TaskQueue<std::shared_ptr<TelegramMessage>> &toTelegram) : Task(TASK_Telegram, TaskTelegram), _toTelegram(toTelegram) {
}

TelegramTask::~TelegramTask() {
}

bool TelegramTask::setup(System &system) {
  _chatid   = system.getUserConfig()->telegram.chatid;
  _bottoken = system.getUserConfig()->telegram.bottoken;
  _client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  _telegram = new UniversalTelegramBot(_bottoken, _client);
  logPrintI("BotToken: ");
  logPrintI(_bottoken);
  logPrintI(" Chat-ID: ");
  logPrintlnI(_chatid);
  logPrintlnI("TelegramTask: setup done...");
  return true;
}

bool TelegramTask::loop(System &system) {
  if (!system.isWifiEthConnected()) {
    return false;
  }
  // logPrintlnD("Telegram: check messages");
  if (millis() > _lastTimeTelegramRan + _telegramRequestDelay) {

    if (!_toTelegram.empty()) {
      std::shared_ptr<TelegramMessage> msg = _toTelegram.getElement();
      logPrintI("New Telegram Messages in Queue: ");
      logPrintlnI(msg->toString());
      _telegram->sendMessage(_chatid, msg->toString(), "");
    }

    int numNewMessages = _telegram->getUpdates(_telegram->last_message_received + 1);
    while (numNewMessages) {
      logPrintI("New Telegram Messages: ");
      logPrintlnI(String(numNewMessages));

      for (int i = 0; i < numNewMessages; i++) {
        String chatid = String(_telegram->messages[i].chat_id);
        if (chatid != _chatid) {
          _telegram->sendMessage(chatid, "Unauthorized user", "");
          continue;
        }

        String cmd  = _telegram->messages[i].text;
        String from = _telegram->messages[i].from_name;
        cmd.toLowerCase();
        logPrintlnI(from + ": " + cmd);
        String text = "";
        if (cmd == "/start") {
          text = "Welcome, " + from + ".\n";
          text += "Use following commands to get current readings.\n\n";
          text += "/monon - aprs msg monitoring on\n";
          text += "/monoff - aprs msg monitoring off\n";
          text += "/bat - battery voltage\n";
          text += "/last - last heard Telegram Paket\n";
          text += "/millis - arduino millis()\n";
          text += "/time - time and date\n";
          text += "/config - current configuration\n";
        } else if (cmd == "/monon") {
          text = timeString(now()) + " (UTC), ";
          text += "Monitoring: ON";
          system.setCopyToTelegram();
        } else if (cmd == "/monoff") {
          text = timeString(now()) + " (UTC), ";
          text += "Monitoring: OFF ";
          system.unsetCopyToTelegram();
        } else if (cmd == "/bat") {
          text = timeString(now()) + " (UTC), ";
          text += "Battery Voltage: ";
          text += String(system.getVoltage()) + " V";
        } else if (cmd == "/last") {
          text = "Last APRS message: ";
          text += "not implemented!";
        } else if (cmd == "/millis") {
          text = "millis: ";
          text += String(millis());
        } else if (cmd == "/time") {
          text = timeString(now()) + " (UTC), ";
          text += "  " + String(day()) + "." + String(month()) + "." + String(year());
        } else if (cmd == "/config") {
          text = "Current config: ";
          text += "not implemented!";
        } else {
          text = "unknwon command, try /start for help!";
        };
        _telegram->sendMessage(_chatid, text, "");
      }
      numNewMessages = _telegram->getUpdates(_telegram->last_message_received + 1);
    }
    _lastTimeTelegramRan = millis();
  }
  _stateInfo = "Telegram: active";
  _state     = Okay;
  return true;
}

#include <logger.h>

#include "Task.h"
#include "TaskTelegram.h"
#include "project_configuration.h"

TelegramTask::TelegramTask() : Task(TASK_Telegram, TaskTelegram) {
}

TelegramTask::~TelegramTask() {
}

bool TelegramTask::setup(System &system) {
  _chatid = system.getUserConfig()->telegram.chatid;
  _bottoken = system.getUserConfig()->telegram.bottoken;
  _telegram = UniversalTelegramBot(_bottoken, _client);
  return true;
}

bool TelegramTask::loop(System &system) {
  if (!system.isWifiEthConnected()) {
    return false;
  }
  if (millis() > _lastTimeTelegramRan + _telegramRequestDelay) {
    int numNewMessages = _telegram.getUpdates(_telegram.last_message_received + 1);
    while (numNewMessages) {
      logPrintI("New Telegram Messages: ");
      logPrintlnI(String(numNewMessages));

      for (int i=0; i<numNewMessages; i++) {
        String chatid = String(_telegram.messages[i].chat_id);
        if (chatid != _chatid) {
          _telegram.sendMessage(chatid, "Unauthorized user", "");
          continue;
        }

        String text = _telegram.messages[i].text;
        String from = _telegram.messages[i].from_name;
        logPrintlnI(from + " " + text);

        if (text == "/start") {
          String welcome = "Welcome, " + from + ".\n";
          welcome += "Use following commands to get current readings.\n\n";
          welcome += "/bat - akku voltage\n";
          welcome += "/last - last heard APRS Paket\n";
          welcome += "/time - ntp time and date\n";
          welcome += "/config - current configuration\n";
          _telegram.sendMessage(_chatid, welcome, ""); 
        }
      }
      numNewMessages = _telegram.getUpdates(_telegram.last_message_received +1);
    }
    _lastTimeTelegramRan = millis();
  }
  _stateInfo = "Telegram: active";
  _state = Okay;
  return true;
}


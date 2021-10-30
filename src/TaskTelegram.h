#ifndef TASK_Telegram_H_
#define TASK_Telegram_H_

#include <TaskManager.h>
#include <UniversalTelegramBot.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

class TelegramTask : public Task {

private:
  UniversalTelegramBot  *_telegram;
  String                _chatid;
  String                _bottoken;
  int                   _telegramRequestDelay = 1000;
  unsigned long         _lastTimeTelegramRan;
  WiFiClientSecure      _client;

public:
  TelegramTask();
  virtual ~TelegramTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

};

#endif

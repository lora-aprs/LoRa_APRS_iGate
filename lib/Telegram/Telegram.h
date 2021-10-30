#ifndef Telegram_H_
#define Telegram_H_

#include <Ardunio.h>
#include <UniversalTelegramBot.h>

class Telegram : public UniversalTelegramBot
 {

private:
  UniversalTelegramBot  _telegram;
  String                _chatid;
  String                _bottoken;
  int                   _telegramRequestDelay = 1000;
  unsigned long         _lastTimeTelegramRan;
  WiFiClient            _client;

public:
  Telegram();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

};

#endif

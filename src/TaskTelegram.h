#ifndef TASK_Telegram_H_
#define TASK_Telegram_H_

#include <TaskManager.h>
#include <UniversalTelegramBot.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>



class TelegramMessage {
public:
	TelegramMessage();
  virtual ~TelegramMessage();

  UniversalTelegramBot * getBOT();
  void setBOT(UniversalTelegramBot *bot);
  unsigned long getTime() const;
  void setTime(const unsigned long & other_time);
  String getMessage() const;
  void setMessage(const String & other_message);
  void setMessage(const String & other_message, const unsigned long & other_time);
  void setMessage(UniversalTelegramBot *bot, const String & other_message);
  void setMessage(UniversalTelegramBot *bot, const String & other_message, const unsigned long & other_time);
  private:
  typedef struct {
        UniversalTelegramBot  *bot;
        unsigned long         time;
        String                message;
  } data;
  data _body;
};

#endif

class TelegramTask : public Task {

private:
  UniversalTelegramBot  *_telegram;
  String                _chatid;
  String                _bottoken;
  int                   _telegramRequestDelay = 1000;
  unsigned long         _lastTimeTelegramRan;
  WiFiClientSecure      _client;

public:
  TelegramTask(TaskQueue<std::shared_ptr<TelegramMessage>> &toTelegram);
  virtual ~TelegramTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

  TaskQueue<std::shared_ptr<TelegramMessage>> &_toTelegram;
};


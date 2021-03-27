#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Arduino.h>
#include <BoardFinder.h>
#include <SSD1306.h>
#include <TimeLib.h>
#include <Timer.h>
#include <Wire.h>
#include <list>
#include <map>
#include <memory>

class Timer;
class StatusFrame;

class DisplayFrame {
public:
  DisplayFrame() {
  }
  virtual ~DisplayFrame() {
  }
  virtual void drawStatusPage(Bitmap &bitmap) = 0;
};

class Display {
public:
  Display();
  ~Display();

  void setup(std::shared_ptr<BoardConfig> boardConfig);
  // setup functions
  void showSpashScreen(String firmwareTitle, String version);
  void setStatusFrame(std::shared_ptr<StatusFrame> frame);
  void showStatusScreen(String header, String text);

  void turn180();
  void activateDisplaySaveMode();
  void setDisplaySaveTimeout(uint32_t timeout);

  // functions for update loop
  void update();
  void addFrame(std::shared_ptr<DisplayFrame> frame);

private:
  std::shared_ptr<OLEDDisplay> _disp;

  Timer                        _displayFrameRate;
  std::shared_ptr<StatusFrame> _statusFrame;

  std::list<std::shared_ptr<DisplayFrame>> _frames;
  Timer                                    _frameTimeout;

  bool  _displaySaveMode;
  Timer _displaySaveModeTimer;
};

class TextFrame : public DisplayFrame {
public:
  TextFrame(String header, String text) : _header(header), _text(text) {
  }
  virtual ~TextFrame() {
  }
  void drawStatusPage(Bitmap &bitmap) override;

private:
  String _header;
  String _text;
};

#endif

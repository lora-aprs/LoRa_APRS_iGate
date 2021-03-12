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
  static Display &instance() {
    static Display _instance;
    return _instance;
  }

  ~Display() {
  }

  void setup(std::shared_ptr<BoardConfig> boardConfig);
  void turn180();
  void update();

  void addFrame(std::shared_ptr<DisplayFrame> frame);

  void setStatusFrame(std::shared_ptr<StatusFrame> frame);

  void showSpashScreen(String firmwareTitle, String version);

private:
  std::shared_ptr<OLEDDisplay> _disp;

  std::list<std::shared_ptr<DisplayFrame>> _frames;
  std::shared_ptr<StatusFrame>             _statusFrame;
  Timer                                    _frameTimeout;

  Timer _displayTimeout;
  bool  _displayOff;

  Display();
  Display(const Display &);
  Display &operator=(const Display &);

  void activateDisplay();
  void deactivateDisplay();
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

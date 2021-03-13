#include "Display.h"
#include <TaskManager.h>
#include <logger.h>

Display::Display() : _disp(0), _statusFrame(0), _displayOff(false), _displaySaveMode(false) {
}

void Display::setup(std::shared_ptr<BoardConfig> boardConfig) {
  if (boardConfig->OledReset != 0) {
    pinMode(boardConfig->OledReset, OUTPUT);
    digitalWrite(boardConfig->OledReset, HIGH);
    delay(1);
    digitalWrite(boardConfig->OledReset, LOW);
    delay(10);
    digitalWrite(boardConfig->OledReset, HIGH);
  }
  Wire.begin(boardConfig->OledSda, boardConfig->OledScl);
  _disp = std::shared_ptr<OLEDDisplay>(new SSD1306(&Wire, boardConfig->OledAddr));

  Bitmap bitmap(_disp->getWidth(), _disp->getHeight());
  _disp->display(&bitmap);
  _displayTimeout.setTimeout(10);
  _frameTimeout.setTimeout(15);
}

void Display::turn180() {
  _disp->flipScreenVertically();
}

void Display::activateDisplaySaveMode() {
  _displaySaveMode = true;
}

void Display::setDisplayTimeout(time_t timeout) {
  _displayTimeout.setTimeout(timeout);
}

void Display::update() {
  if (_frameTimeout.check()) {
    if (_statusFrame->isPrio()) {
      Bitmap bitmap(_disp.get());
      _statusFrame->drawStatusPage(bitmap);
      activateDisplay();
      _disp->display(&bitmap);
      return;
    }

    if (_frames.size() > 0) {
      std::shared_ptr<DisplayFrame> frame = *_frames.begin();
      Bitmap                        bitmap(_disp.get());
      frame->drawStatusPage(bitmap);
      activateDisplay();
      _disp->display(&bitmap);
      _frames.pop_front();
      _frameTimeout.start();
      return;
    }

    if (!_displayOff && !_displayTimeout.isActive()) {
      Bitmap bitmap(_disp.get());
      _statusFrame->drawStatusPage(bitmap);
      activateDisplay();
      _disp->display(&bitmap);
      if (_displaySaveMode) {
        _displayTimeout.start();
      }
    }
    if (_displayTimeout.check()) {
      deactivateDisplay();
      _displayTimeout.reset();
    }
  }
}

void Display::addFrame(std::shared_ptr<DisplayFrame> frame) {
  _frames.push_back(frame);
}

void Display::setStatusFrame(std::shared_ptr<StatusFrame> frame) {
  _statusFrame = frame;
}

void Display::showSpashScreen(String firmwareTitle, String version) {
  Bitmap bitmap(_disp.get());
  bitmap.drawString(0, 10, firmwareTitle);
  bitmap.drawString(0, 20, version);
  bitmap.drawString(0, 35, "by Peter Buchegger");
  bitmap.drawString(30, 45, "OE5BPA");
  _disp->display(&bitmap);
}

void Display::activateDisplay() {
  if (_displayOff) {
    _disp->displayOn();
    _displayOff = false;
  }
}

void Display::deactivateDisplay() {
  _disp->displayOff();
  _displayOff = true;
}

void TextFrame::drawStatusPage(Bitmap &bitmap) {
  bitmap.drawString(0, 0, _header);
  bitmap.drawStringLF(0, 10, _text);
}

#include "Display.h"
#include "System/TaskManager.h"
#include <logger.h>

Display::Display() : _disp(0), _statusFrame(0), _displaySaveMode(false) {
}

Display::~Display() {
}

void Display::setup() {
#ifdef RESET_OLED
  pinMode(RESET_OLED, OUTPUT);
  digitalWrite(RESET_OLED, HIGH);
  delay(1);
  digitalWrite(RESET_OLED, LOW);
  delay(10);
  digitalWrite(RESET_OLED, HIGH);
#endif
#if defined(OLED_SDA) && defined(OLED_SCL)
  Wire.begin(OLED_SDA, OLED_SCL);
#else
  Wire.begin(SDA, SCL);
#endif
  _disp = new SSD1306(&Wire, 0x3C);

  Bitmap bitmap(_disp->getWidth(), _disp->getHeight());
  _disp->display(&bitmap);

  _displayFrameRate.setTimeout(500);
  _displayFrameRate.start();

  _frameTimeout.setTimeout(15 * 1000);
  _displaySaveModeTimer.setTimeout(10 * 1000);
}

void Display::turn180() {
  _disp->flipScreenVertically();
}

void Display::activateDisplaySaveMode() {
  _displaySaveMode = true;
}

void Display::setDisplaySaveTimeout(uint32_t timeout) {
  _displaySaveModeTimer.setTimeout(timeout * 1000);
}

void Display::activateDistplay() {
  _disp->displayOn();
}

void Display::update() {
  if (_displayFrameRate.check()) {

    if (_frames.size() > 0) {
      std::shared_ptr<DisplayFrame> frame = *_frames.begin();
      Bitmap                        bitmap(_disp);
      frame->drawStatusPage(bitmap);
      _disp->display(&bitmap);

      if (!_frameTimeout.isActive()) {
        _frameTimeout.start();
        _displaySaveModeTimer.reset();
      } else if (_frameTimeout.check()) {
        _frames.pop_front();
        _frameTimeout.reset();
      }
    } else {
      if (_disp->isDisplayOn()) {
        Bitmap bitmap(_disp);
        _statusFrame->drawStatusPage(bitmap);
        _disp->display(&bitmap);

        if (_displaySaveMode) {
          if (_displaySaveModeTimer.isActive() && _displaySaveModeTimer.check()) {
            _disp->displayOff();
            _displaySaveModeTimer.reset();
          } else if (!_displaySaveModeTimer.isActive()) {
            _displaySaveModeTimer.start();
          }
        }
      }
    }

    _displayFrameRate.start();
  }
}

void Display::addFrame(std::shared_ptr<DisplayFrame> frame) {
  _frames.push_back(frame);
}

void Display::setStatusFrame(std::shared_ptr<StatusFrame> frame) {
  _statusFrame = frame;
}

void Display::showSpashScreen(String firmwareTitle, String version, String boardname) {
  Bitmap bitmap(_disp);
  bitmap.drawString(0, 10, firmwareTitle);
  bitmap.drawString(0, 20, version);
  bitmap.drawString(0, 35, "by Peter Buchegger");
  bitmap.drawString(30, 45, "OE5BPA");
  bitmap.drawString(0, 55, "for board");
  bitmap.drawString(0, 65, boardname);
  _disp->display(&bitmap);
}

void Display::showStatusScreen(String header, String text) {
  Bitmap bitmap(_disp);
  bitmap.drawString(0, 0, header);
  bitmap.drawStringLF(0, 10, text);
  _disp->display(&bitmap);
}

void TextFrame::drawStatusPage(Bitmap &bitmap) {
  bitmap.drawString(0, 0, _header);
  bitmap.drawStringLF(0, 10, _text);
}

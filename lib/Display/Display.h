#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <array>
#include <memory>
#include <map>
#include <Arduino.h>
#include <Wire.h>
#include <SSD1306.h>
#include <OLEDDisplayUi.h>
#include <BoardFinder.h>

class Display
{
public:
	static Display & instance()
	{
		static Display _instance;
		return _instance;
	}

	~Display() {}

	void setup(std::shared_ptr<BoardConfig> boardConfig);

	void setTaskStatus(const String & task, const String & status);

	void update();

private:
	std::shared_ptr<OLEDDisplay> _disp;
	std::shared_ptr<OLEDDisplayUi> _ui;

	static void drawStatusPage(OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y);

	std::map<String, String> _taskStatus;

	Display();
	Display(const Display &);
	Display & operator = (const Display &);
};

#endif

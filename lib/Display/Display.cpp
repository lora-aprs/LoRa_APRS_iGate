#include <logger.h>
#include "Display.h"

Display::Display()
{
}

void Display::setup(std::shared_ptr<BoardConfig> boardConfig)
{
	_disp = std::shared_ptr<OLEDDisplay>(new SSD1306Wire(boardConfig->OledAddr, boardConfig->OledSda, boardConfig->OledScl));
	_ui = std::shared_ptr<OLEDDisplayUi>(new OLEDDisplayUi(_disp.get()));

	static std::array<FrameCallback, 2> frames;
	frames[0] = drawStatusPage;
	frames[1] = drawStatusPage;
	_ui->setFrames(frames.data(), frames.size());

	_ui->setTargetFPS(15);
	_ui->setFrameAnimation(SLIDE_LEFT);
	_ui->init();
	_disp->flipScreenVertically();
}

void Display::setTaskStatus(const String & task, const String & status)
{
	_taskStatus.insert(std::pair<String, String>(task, status));
}

void Display::update()
{
	_ui->update();
}

void Display::drawStatusPage(OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y)
{
	//logPrintlnD("blib");
	display->setTextAlignment(TEXT_ALIGN_LEFT);
	display->setFont(ArialMT_Plain_10);
	display->drawString(0 + x, 10 + y, "Arial 10");

	display->setFont(ArialMT_Plain_16);
	display->drawString(0 + x, 20 + y, "Arial 16");

	display->setFont(ArialMT_Plain_24);
	display->drawString(0 + x, 34 + y, "Arial 24");
}

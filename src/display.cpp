
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "BoardFinder.h"
#include "display.h"
#include "logger.h"

Adafruit_SSD1306 * display = 0;
TwoWire * wire = 0;

// cppcheck-suppress unusedFunction
void setup_display(std::shared_ptr<BoardConfig> boardConfig)
{
	if(display == 0)
	{
		wire = new TwoWire(0);
		wire->begin(boardConfig->OledSda, boardConfig->OledScl);
		if(boardConfig->OledReset > 0)
		{
			display = new Adafruit_SSD1306(128, 64, wire, boardConfig->OledReset);
			logPrintlnI("with reset");
		}
		else
		{
			display = new Adafruit_SSD1306(128, 64, wire);
			logPrintlnI("with NO reset");
		}
	}
	if(!display->begin(SSD1306_SWITCHCAPVCC, boardConfig->OledAddr, false, false))
	{
		logPrintlnE("SSD1306 allocation failed");
		while (1);
	}
	logPrintlnI("Display init done!");
}

/*void turn_off_display()
{
	display->ssd1306_command(SSD1306_DISPLAYOFF);
}*/

/*void show_display(String header, int wait)
{
	display->clearDisplay();
	display->setTextColor(WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println(header);
	display->display();
	delay(wait);
}*/

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, int wait)
{
	display->clearDisplay();
	display->setTextColor(WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println(header);
	display->setTextSize(1);
	display->setCursor(0,16);
	display->println(line1);
	display->display();
	delay(wait);
}

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, String line2, int wait)
{
	display->clearDisplay();
	display->setTextColor(WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println(header);
	display->setTextSize(1);
	display->setCursor(0,16);
	display->println(line1);
	display->setCursor(0,26);
	display->println(line2);
	display->display();
	delay(wait);
}

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, String line2, String line3, int wait)
{
	display->clearDisplay();
	display->setTextColor(WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println(header);
	display->setTextSize(1);
	display->setCursor(0,16);
	display->println(line1);
	display->setCursor(0,26);
	display->println(line2);
	display->setCursor(0,36);
	display->println(line3);
	display->display();
	delay(wait);
}

/*void show_display(String header, String line1, String line2, String line3, String line4, int wait)
{
	display->clearDisplay();
	display->setTextColor(WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println(header);
	display->setTextSize(1);
	display->setCursor(0,16);
	display->println(line1);
	display->setCursor(0,26);
	display->println(line2);
	display->setCursor(0,36);
	display->println(line3);
	display->setCursor(0,46);
	display->println(line4);
	display->display();
	delay(wait);
}*/

/*void show_display(String header, String line1, String line2, String line3, String line4, String line5, int wait)
{
	display->clearDisplay();
	display->setTextColor(WHITE);
	display->setTextSize(2);
	display->setCursor(0,0);
	display->println(header);
	display->setTextSize(1);
	display->setCursor(0,16);
	display->println(line1);
	display->setCursor(0,26);
	display->println(line2);
	display->setCursor(0,36);
	display->println(line3);
	display->setCursor(0,46);
	display->println(line4);
	display->setCursor(0,56);
	display->println(line5);
	display->display();
	delay(wait);
}*/

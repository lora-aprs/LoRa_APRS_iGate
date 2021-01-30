/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 * Copyright (c) 2019 by Helmut Tschemernjak - www.radioshuttle.de
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 *
 */

#include "OLEDDisplay.h"

OLEDDisplay::OLEDDisplay(OLEDDISPLAY_GEOMETRY g)
	: _geometry(g)
{
}

OLEDDisplay::~OLEDDisplay()
{
}

void OLEDDisplay::displayOn()
{
	sendCommand(DISPLAYON);
}

void OLEDDisplay::displayOff()
{
	sendCommand(DISPLAYOFF);
}

void OLEDDisplay::invertDisplay()
{
	sendCommand(INVERTDISPLAY);
}

void OLEDDisplay::normalDisplay()
{
	sendCommand(NORMALDISPLAY);
}

void OLEDDisplay::setContrast(uint8_t contrast, uint8_t precharge, uint8_t comdetect)
{
	sendCommand(SETPRECHARGE);	//0xD9
	sendCommand(precharge);		//0xF1 default, to lower the contrast, put 1-1F
	sendCommand(SETCONTRAST);
	sendCommand(contrast);		// 0-255
	sendCommand(SETVCOMDETECT);	//0xDB, (additionally needed to lower the contrast)
	sendCommand(comdetect);		//0x40 default, to lower the contrast, put 0
	sendCommand(DISPLAYALLON_RESUME);
	sendCommand(NORMALDISPLAY);
	sendCommand(DISPLAYON);
}

void OLEDDisplay::setBrightness(uint8_t brightness)
{
	uint8_t contrast = brightness;
	if (brightness < 128)
	{
		// Magic values to get a smooth/ step-free transition
		contrast = brightness * 1.171;
	}
	else
	{
		contrast = brightness * 1.171 - 43;
	}

	uint8_t precharge = 241;
	if (brightness == 0)
	{
		precharge = 0;
	}
	uint8_t comdetect = brightness / 8;
	setContrast(contrast, precharge, comdetect);
}

void OLEDDisplay::resetOrientation()
{
	sendCommand(SEGREMAP);
	sendCommand(COMSCANINC);
}

void OLEDDisplay::flipScreenVertically()
{
	sendCommand(SEGREMAP | 0x01);
	sendCommand(COMSCANDEC);
}

void OLEDDisplay::mirrorScreen()
{
	sendCommand(SEGREMAP);
	sendCommand(COMSCANDEC);
}

void OLEDDisplay::clear()
{
}

uint OLEDDisplay::getWidth()
{
	switch(_geometry)
	{
	case GEOMETRY_128_64:
	case GEOMETRY_128_32:
		return 128;
	case GEOMETRY_64_48:
	case GEOMETRY_64_32:
		return 64;
	}
	return 0;
}

uint OLEDDisplay::getHeight()
{
	switch(_geometry)
	{
	case GEOMETRY_128_64:
		return 64;
	case GEOMETRY_64_48:
		return 48;
	case GEOMETRY_128_32:
	case GEOMETRY_64_32:
		return 32;
	}
	return 0;
}

void OLEDDisplay::sendInitCommands()
{
	sendCommand(DISPLAYOFF);
	sendCommand(SETDISPLAYCLOCKDIV);
	sendCommand(0xF0); // Increase speed of the display max ~96Hz
	sendCommand(SETMULTIPLEX);
	sendCommand(this->getHeight() - 1);
	sendCommand(SETDISPLAYOFFSET);
	sendCommand(0x00);
	if(_geometry == GEOMETRY_64_32)
	{
		sendCommand(0x00);
	}
	else
	{
		sendCommand(SETSTARTLINE);
	}
	sendCommand(CHARGEPUMP);
	sendCommand(0x14);
	sendCommand(MEMORYMODE);
	sendCommand(0x00);
	sendCommand(SEGREMAP);
	sendCommand(COMSCANINC);
	sendCommand(SETCOMPINS);

	if (_geometry == GEOMETRY_128_64 || _geometry == GEOMETRY_64_48 || _geometry == GEOMETRY_64_32)
	{
		sendCommand(0x12);
	}
	else if (_geometry == GEOMETRY_128_32)
	{
		sendCommand(0x02);
	}

	sendCommand(SETCONTRAST);

	if (_geometry == GEOMETRY_128_64 || _geometry == GEOMETRY_64_48 || _geometry == GEOMETRY_64_32)
	{
		sendCommand(0xCF);
	}
	else if (_geometry == GEOMETRY_128_32)
	{
		sendCommand(0x8F);
	}

	sendCommand(SETPRECHARGE);
	sendCommand(0xF1);
	sendCommand(SETVCOMDETECT); //0xDB, (additionally needed to lower the contrast)
	sendCommand(0x40);	        //0x40 default, to lower the contrast, put 0
	sendCommand(DISPLAYALLON_RESUME);
	sendCommand(NORMALDISPLAY);
	sendCommand(0x2e);            // stop scroll
	sendCommand(DISPLAYON);
}

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

#ifndef OLEDDISPLAY_h
#define OLEDDISPLAY_h

#include <Arduino.h>
#include "Bitmap.h"
//#include "OLEDDisplayFonts.h"

// Display commands
#define CHARGEPUMP 0x8D
#define COLUMNADDR 0x21
#define COMSCANDEC 0xC8
#define COMSCANINC 0xC0
#define DISPLAYALLON 0xA5
#define DISPLAYALLON_RESUME 0xA4
#define DISPLAYOFF 0xAE
#define DISPLAYON 0xAF
#define EXTERNALVCC 0x1
#define INVERTDISPLAY 0xA7
#define MEMORYMODE 0x20
#define NORMALDISPLAY 0xA6
#define PAGEADDR 0x22
#define SEGREMAP 0xA0
#define SETCOMPINS 0xDA
#define SETCONTRAST 0x81
#define SETDISPLAYCLOCKDIV 0xD5
#define SETDISPLAYOFFSET 0xD3
#define SETHIGHCOLUMN 0x10
#define SETLOWCOLUMN 0x00
#define SETMULTIPLEX 0xA8
#define SETPRECHARGE 0xD9
#define SETSEGMENTREMAP 0xA1
#define SETSTARTLINE 0x40
#define SETVCOMDETECT 0xDB
#define SWITCHCAPVCC 0x2

enum OLEDDISPLAY_GEOMETRY
{
	GEOMETRY_128_64   = 0,
	GEOMETRY_128_32   = 1,
	GEOMETRY_64_48    = 2,
	GEOMETRY_64_32    = 3
};

class OLEDDisplay
{
public:
	OLEDDisplay(OLEDDISPLAY_GEOMETRY g = GEOMETRY_128_64);
	virtual ~OLEDDisplay();

	// Turn the display on
	void displayOn();

	// Turn the display offs
	void displayOff();

	// Inverted display mode
	void invertDisplay();

	// Normal display mode
	void normalDisplay();

	// Set display contrast
	// really low brightness & contrast: contrast = 10, precharge = 5, comdetect = 0
	// normal brightness & contrast:  contrast = 100
	void setContrast(uint8_t contrast, uint8_t precharge = 241, uint8_t comdetect = 64);

	// Convenience method to access
	void setBrightness(uint8_t brightness);

	// Reset display rotation or mirroring
	void resetOrientation();

	// Turn the display upside down
	void flipScreenVertically();

	// Mirror the display (to be used in a mirror or as a projector)
	void mirrorScreen();

	// Write the buffer to the display memory
	virtual void display(Bitmap * bitmap) = 0;

	// Clear the local pixel buffer
	void clear();

	// Get screen geometry
	uint getWidth();
	uint getHeight();

protected:
	// Send all the init commands
	void sendInitCommands();

private:
	OLEDDISPLAY_GEOMETRY _geometry;

	// Send a command to the display (low level function)
	virtual void sendCommand(uint8_t com) = 0;
};

#endif

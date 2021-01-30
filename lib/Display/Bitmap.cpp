#include "Bitmap.h"
#include "OLEDDisplay.h"
#include "FontConfig.h"
//#include "OLEDDisplayFonts.h"

// cppcheck-suppress unusedFunction
Bitmap::Bitmap(uint width, uint height)
	: _width(width), _height(height), _buffer(0)
{
	allocateBuffer();
}

// cppcheck-suppress unusedFunction
Bitmap::Bitmap(OLEDDisplay * display)
	: _width(display->getWidth()), _height(display->getHeight()), _buffer(0)
{
	allocateBuffer();
}

// cppcheck-suppress unusedFunction
Bitmap::~Bitmap()
{
	if(_buffer != 0)
	{
		delete _buffer;
	}
}

// cppcheck-suppress unusedFunction
uint Bitmap::getWidth() const
{
	return _width;
}

// cppcheck-suppress unusedFunction
uint Bitmap::getHeight() const
{
	return _height;
}

// cppcheck-suppress unusedFunction
void Bitmap::setPixel(int x, int y)
{
	if(x >= 0 && x < _width && y >= 0 && y < _height)
	{
		_buffer[x + (y / 8) * _width] |= (1 << (y % 8));
	}
}

// cppcheck-suppress unusedFunction
void Bitmap::clearPixel(int x, int y)
{
	if(x >= 0 && x < _width && y >= 0 && y < _height)
	{
		_buffer[x + (y / 8) * _width] &= ~(1 << (y % 8));
	}
}

// cppcheck-suppress unusedFunction
bool Bitmap::getPixel(int x, int y) const
{
	if(x >= 0 && x < _width && y >= 0 && y < _height)
	{
		return _buffer[x + (y / 8) * _width] & (1 << (y % 8));
	}
	return false;
}

// cppcheck-suppress unusedFunction
void Bitmap::clear()
{
	memset(_buffer, 0, _width * _height / 8);
}

// cppcheck-suppress unusedFunction
void Bitmap::drawLine(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;

	while(true)
	{
		setPixel(x0, y0);
		if(x0 == x1 && y0 == y1)
			break;

		int e2 = err;
		if(e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if(e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

// cppcheck-suppress unusedFunction
void Bitmap::drawHorizontalLine(int x, int y, int length)
{
	if(y < 0 || y >= _height)
	{
		return;
	}

	for(int i = 0; i < length; i++)
	{
		setPixel(x + i, y);
	}
}

// cppcheck-suppress unusedFunction
void Bitmap::drawVerticalLine(int x, int y, int length)
{
	if (x < 0 || x >= _width)
	{
		return;
	}

	for(int i = 0; i < length; i++)
	{
		setPixel(x, y + i);
	}
}

// cppcheck-suppress unusedFunction
void Bitmap::drawRect(int x, int y, int width, int height)
{
	drawHorizontalLine(x, y, width);
	drawVerticalLine(x, y, height);
	drawVerticalLine(x + width - 1, y, height);
	drawHorizontalLine(x, y + height - 1, width);
}

// cppcheck-suppress unusedFunction
void Bitmap::fillRect(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		drawVerticalLine(x + i, y, height);
	}
}

// cppcheck-suppress unusedFunction
void Bitmap::drawCircle(int x0, int y0, int radius)
{
	int x = 0;
	int y = radius;
	int dp = 1 - radius;

	do
	{
		if (dp < 0)
		{
			dp = dp + (x++) * 2 + 3;
		}
		else
		{
			dp = dp + (x++) * 2 - (y--) * 2 + 5;
		}

		setPixel(x0 + x, y0 + y);     //For the 8 octants
		setPixel(x0 - x, y0 + y);
		setPixel(x0 + x, y0 - y);
		setPixel(x0 - x, y0 - y);
		setPixel(x0 + y, y0 + x);
		setPixel(x0 - y, y0 + x);
		setPixel(x0 + y, y0 - x);
		setPixel(x0 - y, y0 - x);
	}
	while (x < y);

	setPixel(x0 + radius, y0);
	setPixel(x0, y0 + radius);
	setPixel(x0 - radius, y0);
	setPixel(x0, y0 - radius);
}

// cppcheck-suppress unusedFunction
void Bitmap::fillCircle(int x0, int y0, int radius)
{
	int x = 0;
	int y = radius;
	int dp = 1 - radius;

	do
	{
		if (dp < 0)
		{
			dp = dp + (x++) * 2 + 3;
		}
		else
		{
 			dp = dp + (x++) * 2 - (y--) * 2 + 5;
		}

		drawHorizontalLine(x0 - x, y0 - y, 2 * x);
		drawHorizontalLine(x0 - x, y0 + y, 2 * x);
		drawHorizontalLine(x0 - y, y0 - x, 2 * y);
		drawHorizontalLine(x0 - y, y0 + x, 2 * y);
	}
	while (x < y);
	
	drawHorizontalLine(x0 - radius, y0, 2 * radius);
}

// cppcheck-suppress unusedFunction
void Bitmap::drawCircleQuads(int x0, int y0, int radius, int quads)
{
	int x = 0;
	int y = radius;
	int dp = 1 - radius;

	while (x < y)
	{
		if (dp < 0)
		{
			dp = dp + (x++) * 2 + 3;
		}
		else
		{
			dp = dp + (x++) * 2 - (y--) * 2 + 5;
		}

		if (quads & 0x1)
		{
			setPixel(x0 + x, y0 - y);
			setPixel(x0 + y, y0 - x);
		}
		if (quads & 0x2)
		{
			setPixel(x0 - y, y0 - x);
			setPixel(x0 - x, y0 - y);
		}
		if (quads & 0x4)
		{
			setPixel(x0 - y, y0 + x);
			setPixel(x0 - x, y0 + y);
		}
		if (quads & 0x8)
		{
			setPixel(x0 + x, y0 + y);
			setPixel(x0 + y, y0 + x);
		}
	}
	if (quads & 0x1 && quads & 0x8)
	{
		setPixel(x0 + radius, y0);
	}
	if (quads & 0x4 && quads & 0x8)
	{
		setPixel(x0, y0 + radius);
	}
	if (quads & 0x2 && quads & 0x4)
	{
		setPixel(x0 - radius, y0);
	}
	if (quads & 0x1 && quads & 0x2)
	{
		setPixel(x0, y0 - radius);
	}
}

// cppcheck-suppress unusedFunction
void Bitmap::drawProgressBar(int x, int y, int width, int height, int progress)
{
	int radius = height / 2;
	int xRadius = x + radius;
	int yRadius = y + radius;
	int doubleRadius = 2 * radius;
	int innerRadius = radius - 2;

	drawCircleQuads(xRadius, yRadius, radius, 0b00000110);
	drawHorizontalLine(xRadius, y, width - doubleRadius + 1);
	drawHorizontalLine(xRadius, y + height, width - doubleRadius + 1);
	drawCircleQuads(x + width - radius, yRadius, radius, 0b00001001);

	uint16_t maxProgressWidth = (width - doubleRadius + 1) * progress / 100;

	fillCircle(xRadius, yRadius, innerRadius);
	fillRect(xRadius + 1, y + 2, maxProgressWidth, height - 3);
	fillCircle(xRadius + maxProgressWidth, yRadius, innerRadius);
}

// cppcheck-suppress unusedFunction
int Bitmap::drawChar(int x, int y, char c)
{
	fontDesc_t const * font = getSystemFont();

	if(c == ' ')
	{
		return x + font->widthInPixel * 4 / 10;
	}

	unsigned char cu = (unsigned char)c;
	if(cu < font->firstChar || cu > font->lastChar)
	{
		cu = '?';
	}

	int firstPixelBitPos = 0;
	for(int i = 0; i < (cu - font->firstChar); i++)
	{
		firstPixelBitPos = firstPixelBitPos + font->pData[i];
	}
	firstPixelBitPos = firstPixelBitPos * font->heightInPixel;

	unsigned char const * pDataStart = &(font->pData[font->lastChar - font->firstChar + 1]);
	const int top = y;
	const int widthInPixel = font->pData[cu - font->firstChar];
	for(int i = 0; i < widthInPixel * font->heightInPixel; i++ )
	{
		int bytePos = firstPixelBitPos / 8;
		int bitPos  = firstPixelBitPos % 8;

		if(pDataStart[bytePos] & ( 1 << bitPos))
		{
			setPixel(x, y);
		}
		else
		{
			clearPixel(x, y);
		}

		firstPixelBitPos++;
		y++;
		if(y == top + font->heightInPixel)
		{
			y = top;
			x++;
		}
	}

	return x + FONT_CHAR_SPACING;
}

// cppcheck-suppress unusedFunction
int Bitmap::drawString(int x, int y, String text)
{
	int next_x = x;
	for(int i = 0; i < text.length(); i++)
	{
		next_x = drawChar(next_x, y, text[i]);
	}
	return next_x;
}

// cppcheck-suppress unusedFunction
void Bitmap::drawStringf(int x, int y, char * buffer, String format, ... )
{
	va_list myargs;
	va_start(myargs, format);
	vsprintf(buffer, format.c_str(), myargs);
	va_end(myargs);
	drawString(x, y, buffer);
}

// cppcheck-suppress unusedFunction
int Bitmap::drawStringLF(int x, int y, String text)
{
	fontDesc_t const * font = getSystemFont();
	int next_x = x;
	for(int i = 0; i < text.length(); i++)
	{
		if(next_x + font->widthInPixel > _width)
		{
			next_x = 0;
			y += font->heightInPixel;
		}
		next_x = drawChar(next_x, y, text[i]);
	}
	return next_x;
}

// cppcheck-suppress unusedFunction
void Bitmap::drawStringLFf(int x, int y, char * buffer, String format, ... )
{
	va_list myargs;
	va_start(myargs, format);
	vsprintf(buffer, format.c_str(), myargs);
	va_end(myargs);
	drawStringLF(x, y, buffer);
}

/*void Bitmap::drawBitmap(int x, int y, const Bitmap & bitmap)
{
	if(_width < x + bitmap.getWidth() || _height < y + bitmap.getHeight())
	{
		return;
	}

	for(int _x = 0; _x < bitmap.getWidth(); _x++)
	{
		for(int _y = 0; _y < bitmap.getHeight(); _y++)
		{
			if(bitmap.getPixel(_x, _y))
			{
				// _buffer[x + (y / 8) * _width] |= (1 << (y % 8));
				// return _buffer[x + (y / 8) * _width] & (1 << (y % 8));
				Serial.print(_x);
				Serial.print(" ");
				Serial.println(_y);
				setPixel(x + _x, y + _y);
			}
			else
			{
				clearPixel(x + _x, y + _y);
			}
		}
	}
}*/

// cppcheck-suppress unusedFunction
void Bitmap::allocateBuffer()
{
	_buffer = new uint8_t[_width * _height / 8];
	clear();
}

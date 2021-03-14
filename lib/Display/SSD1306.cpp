#include "SSD1306.h"

SSD1306::SSD1306(TwoWire * wire, uint8_t address, OLEDDISPLAY_GEOMETRY g)
	: OLEDDisplay(g), _wire(wire), _address(address)
{
	sendInitCommands();
}

SSD1306::~SSD1306()
{
}

void SSD1306::display(Bitmap * bitmap)
{
	sendCommand(PAGEADDR);
	sendCommand(0x0);
	sendCommand(0xFF);

	sendCommand(COLUMNADDR);
	sendCommand(0x0);
	sendCommand(getWidth() - 1);

	for (int i = 0; i < getWidth() * getHeight() / 8; )
	{
		Wire.beginTransmission(_address);
		Wire.write(0x40);
		for (uint8_t x = 0; x < 16; x++)
		{
			Wire.write(bitmap->_buffer[i]);
			i++;
		}
		Wire.endTransmission();
	}
}

void SSD1306::sendCommand(uint8_t command)
{
	_wire->beginTransmission(_address);
	_wire->write(0x80);
	_wire->write(command);
	_wire->endTransmission();
}

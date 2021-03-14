#ifndef FONT_DESC_H
#define FONT_DESC_H

#include <inttypes.h>

struct fontDesc_t
{
	uint16_t	totalSize;
	uint8_t		widthInPixel;
	uint8_t		heightInPixel;
	uint8_t		bitsPerPixel;
	uint8_t		firstChar;
	uint8_t		lastChar;

	unsigned char const * const pData;
};

#endif

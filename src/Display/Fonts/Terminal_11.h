/*
    created with FontEditor written by H. Reddmann
    HaReddmann at t-online dot de

    File Name           : Terminal_11.h
    Date                : 29.06.2016
    Font size in bytes  : 0x129C, 4764
    Font width          : 11
    Font height         : 18
    Font first char     : 0x01
    Font last char      : 0xFE
    Font bits per pixel : 1
    Font is compressed  : false

    The font data are defined as

    struct _FONT_ {
     // common shared fields
       uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
       uint8_t    font_Width_in_Pixel_for_fixed_drawing;
       uint8_t    font_Height_in_Pixel_for_all_Characters;
       uint8_t    font_Bits_per_Pixels;
                    // if MSB are set then font is a compressed font
       uint8_t    font_First_Char;
       uint8_t    font_Last_Char;
       uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
                    // for each character the separate width in pixels,
                    // characters < 128 have an implicit virtual right empty row
                    // characters with font_Char_Widths[] == 0 are undefined

     // if compressed font then additional fields
       uint8_t    font_Byte_Padding;
                    // each Char in the table are aligned in size to this value
       uint8_t    font_RLE_Table[3];
                    // Run Length Encoding Table for compression
       uint8_t    font_Char_Size_in_Bytes[font_Last_Char - font_First_Char +1];
                    // for each char the size in (bytes / font_Byte_Padding) are stored,
                    // this get us the table to seek to the right beginning of each char
                    // in the font_data[].

     // for compressed and uncompressed fonts
       uint8_t    font_data[];
                    // bit field of all characters
    }
*/

#include "FontDesc.h"

#ifndef Terminal_11_FONT_H
#define Terminal_11_FONT_H

#define Terminal_11_WIDTH  11
#define Terminal_11_HEIGHT 18

/*
From FontDesc.h
struct fontDesc_t {
  unsigned int   totalSize;
  unsigned char  widthInPixel;
  unsigned char  heightInPixel;
  unsigned char  bitsPerPixel;
  unsigned char  firstChar;
  unsigned char  lastChar;

  unsigned char* pData;
};
*/

static unsigned char const Terminal_11_Bytes[] = {
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x0A, 0x06, 0x0A, 0x09, 0x08, 0x06, 0x08, 0x07, 0x08, 0x08, 0x06, 0x06, 0x08, 0x08, 0x08, 0x06, 0x06, 0x06, 0x08, 0x08, 0x07, 0x08, 0x08, 0x00, 0x00, 0x04, 0x06, 0x08, 0x08, 0x08, 0x08, 0x02, 0x04, 0x04, 0x08, 0x08, 0x02, 0x08, 0x02, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x02, 0x02, 0x07, 0x08, 0x07, 0x08, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x08, 0x04, 0x08, 0x0A, 0x02, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x05, 0x08, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x05, 0x02, 0x05, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x09,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x09, 0x09, 0x07, 0x09, 0x09, 0x08, 0x09, 0x0A, 0x06, 0x06, 0x09, 0x09, 0x09, 0x09, 0x07, 0x07, 0x07, 0x07, 0x09, 0x09, 0x06, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x08, 0x09, 0x09, 0x09, 0x09, 0x06, 0x08, 0x08, 0x08, 0x06, 0x0A, 0x0A, 0x0A, 0x06, 0x08, 0x0A, 0x09, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x07, 0x08, 0x08, 0x08, 0x09,
    0x09, 0x09, 0x09, 0x07, 0x08, 0x08, 0x06, 0x04, 0x06, 0x07, 0x07, 0xF0, 0x3F, 0x20, 0x00, 0x41, 0x48, 0x08, 0x01, 0x22, 0x04, 0x88, 0x10, 0x12, 0x82, 0x00, 0x04, 0xFC, 0x0F, 0xF0, 0x3F, 0xE0, 0xFF, 0xC1, 0xB7, 0x0F, 0xFF, 0x3D, 0xFC, 0xF7, 0xF0, 0xED, 0x83, 0xFF, 0x07, 0xFC, 0x0F, 0xF8, 0x01, 0xF0, 0x3F, 0xC0, 0xFF, 0x03, 0xFE, 0x3F, 0xF8, 0xFF, 0xF0, 0xFF, 0xC0, 0xFF, 0x00, 0x7E, 0x00, 0x00, 0x03, 0x00, 0x3F, 0x00, 0xFF, 0x03, 0xFF, 0x3F, 0xFC, 0xFF, 0xC0, 0xFF, 0x00, 0xFC, 0x00,
    0xC0, 0x00, 0x00, 0x03, 0x00, 0x1E, 0x82, 0x7B, 0x0E, 0xDF, 0x3E, 0x7C, 0xFB, 0xE0, 0x9E, 0x03, 0x78, 0x08, 0xC0, 0x00, 0x80, 0x07, 0x00, 0x3F, 0x02, 0x7F, 0x0E, 0xFF, 0x3F, 0xFC, 0xFF, 0xC0, 0x9F, 0x03, 0xFC, 0x08, 0xE0, 0x01, 0x00, 0x03, 0x00, 0x1E, 0x00, 0x78, 0x00, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0x7F, 0xF8, 0xFF, 0xE1, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0x00, 0x60, 0x06, 0x80, 0x10, 0x00, 0x42, 0x00, 0x98, 0x01,
    0xC0, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0xCF, 0xFC, 0xBF, 0xF7, 0xFF, 0xDE, 0xFF, 0x33, 0xFF, 0x1F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xC0, 0x01, 0x80, 0x0F, 0x00, 0x63, 0x00, 0x04, 0x01, 0x18, 0x04, 0xF2, 0x18, 0x68, 0x3E, 0xE0, 0x70, 0x80, 0x0F, 0x00, 0x1C, 0x00, 0xF8, 0x08, 0x30, 0x26, 0x40, 0xF0, 0x07, 0xC1, 0x1F, 0x8C, 0x09, 0xE0, 0x23, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0xF0, 0xF0, 0xFF, 0x01, 0x0F, 0x00, 0x3C, 0x00, 0x80, 0x07, 0x00, 0x80, 0x03, 0x00, 0x0F,
    0xF8, 0x1F, 0x60, 0x02, 0xC0, 0x0C, 0x00, 0x99, 0x03, 0x36, 0x0F, 0xFC, 0x1F, 0x00, 0x92, 0x00, 0xB0, 0x01, 0x40, 0x04, 0xC0, 0x71, 0x00, 0x44, 0x00, 0xB0, 0x01, 0x20, 0x09, 0xE0, 0x0F, 0x80, 0x3F, 0x00, 0x7C, 0x00, 0xF0, 0x01, 0x80, 0x03, 0x00, 0x0E, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x38, 0x00, 0xE0, 0x00, 0xC0, 0x07, 0x00, 0x1F, 0x00, 0xFE, 0x00, 0xF8, 0x03, 0x30, 0x30, 0x60, 0x80, 0xC1, 0xFF, 0x0F, 0xFF, 0x3F, 0x18, 0x60, 0xC0, 0xC0, 0xC0, 0xFF, 0x0C,
    0xFF, 0x33, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x0C, 0xFF, 0x33, 0xF8, 0x01, 0xF0, 0x0F, 0xC0, 0xFF, 0x0F, 0xFF, 0x3F, 0x04, 0x00, 0x10, 0x00, 0xC0, 0xFF, 0x0F, 0xFF, 0x3F, 0x18, 0x60, 0xF0, 0x86, 0x43, 0x3F, 0x08, 0x99, 0x21, 0xC4, 0x8C, 0x10, 0x7E, 0xC2, 0xB1, 0x0F, 0x06, 0x1C, 0x00, 0xF0, 0x00, 0xC0, 0x03, 0x00, 0x0F, 0x00, 0x3C, 0x00, 0xF0, 0x00, 0xC0, 0x03, 0x00, 0x0F, 0x00, 0x3C, 0x30, 0x30, 0xE0, 0xC0, 0xC1, 0xFF, 0x0F, 0xFF, 0x3F, 0x38, 0x70, 0xC0, 0xC0, 0x00, 0x03, 0x00,
    0x0E, 0x00, 0xFC, 0xFF, 0xF0, 0xFF, 0x83, 0x03, 0x00, 0x0C, 0x00, 0x00, 0x30, 0x00, 0xC0, 0xC1, 0xFF, 0x0F, 0xFF, 0x3F, 0x00, 0x70, 0x00, 0xC0, 0x00, 0x30, 0x00, 0xC0, 0x00, 0x00, 0x03, 0x00, 0x0C, 0x00, 0xFC, 0x00, 0xF0, 0x03, 0x80, 0x07, 0x00, 0x0C, 0x00, 0x60, 0x00, 0xC0, 0x03, 0x80, 0x1F, 0x00, 0x7E, 0x00, 0x60, 0x00, 0x80, 0x01, 0x00, 0x06, 0x00, 0x18, 0x00, 0x80, 0x03, 0x00, 0x0E, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x18, 0x00, 0xF0, 0x00,
    0xE0, 0x07, 0x00, 0x06, 0x00, 0x18, 0x00, 0xF8, 0x01, 0xC0, 0x03, 0x00, 0x06, 0x00, 0x30, 0x00, 0xF0, 0x00, 0xF0, 0x03, 0xF0, 0x0F, 0xC0, 0x3F, 0x00, 0xFC, 0x00, 0xC0, 0x03, 0x00, 0x0C, 0xE0, 0x03, 0xC0, 0xFF, 0x0C, 0xFF, 0x33, 0xF8, 0x00, 0x70, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xC0, 0x01, 0x00, 0x20, 0x01, 0xF8, 0x7F, 0xE0, 0xFF, 0x01, 0x48, 0x00, 0x20, 0x01, 0xF8, 0x7F, 0xE0, 0xFF, 0x01, 0x48, 0x00, 0x38, 0x06, 0xF0, 0x38, 0x40, 0x86, 0xC0, 0xFF, 0x0F,
    0xFF, 0x3F, 0x10, 0x26, 0xC0, 0xF1, 0x00, 0xC6, 0x01, 0x1E, 0x30, 0xCC, 0x70, 0xE0, 0x71, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x78, 0x70, 0x30, 0x43, 0x80, 0x07, 0x1E, 0x1F, 0xCC, 0xC6, 0x10, 0x0E, 0x42, 0x38, 0x08, 0xB3, 0x31, 0x78, 0x7C, 0x00, 0xB0, 0x01, 0x60, 0x0C, 0x0B, 0x00, 0x1C, 0x00, 0x80, 0x7F, 0xC0, 0xFF, 0x8F, 0x07, 0x78, 0x02, 0x00, 0x09, 0x00, 0xE4, 0x01, 0x1E, 0xFF, 0x3F, 0xE0, 0x1F, 0x00, 0x08, 0x00, 0xA8, 0x00, 0xE0, 0x03, 0x00, 0x07, 0x00, 0x1C, 0x00, 0xF8, 0x00,
    0xA0, 0x02, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x80, 0x0F, 0x00, 0x3E, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0B, 0x00, 0x1C, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x00, 0x30, 0x00, 0xC0, 0x00, 0x00, 0x03, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x0C, 0x00, 0xC0, 0xFF, 0x80, 0xFF, 0x07, 0x03, 0x36, 0x04, 0x86, 0x10, 0x06, 0xC2, 0x06, 0x0C,
    0xFE, 0x1F, 0xF0, 0x3F, 0x40, 0x00, 0x02, 0x01, 0x08, 0x06, 0x20, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0xC0, 0x80, 0x83, 0x03, 0x0F, 0x03, 0x26, 0x04, 0x8C, 0x10, 0x18, 0xC2, 0x30, 0x08, 0x7E, 0x20, 0xF0, 0x80, 0xC0, 0xC0, 0x80, 0x03, 0x07, 0x43, 0x30, 0x04, 0x81, 0x10, 0x04, 0xC2, 0x10, 0x0C, 0xFE, 0x1F, 0xF0, 0x3E, 0x00, 0xF0, 0x00, 0xF8, 0x03, 0xFC, 0x08, 0x7C, 0x20, 0x30, 0xF8, 0x03, 0xE0, 0x0F, 0x00, 0x08, 0x00, 0x20, 0xF0, 0xC3, 0xC0, 0x0F, 0x07,
    0x21, 0x30, 0x84, 0x80, 0x10, 0x02, 0x42, 0x18, 0x0C, 0xC1, 0x1F, 0x04, 0x3E, 0x00, 0xFE, 0x00, 0xFE, 0x07, 0x5C, 0x30, 0x18, 0x81, 0x30, 0x04, 0x42, 0x30, 0x0C, 0x81, 0x1F, 0x04, 0x3C, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0xF0, 0x10, 0xF8, 0x43, 0xFC, 0x00, 0x7F, 0x00, 0x3C, 0x00, 0xC0, 0xF1, 0x80, 0xEF, 0x07, 0xE3, 0x30, 0x04, 0x81, 0x10, 0x04, 0xC2, 0x38, 0x0C, 0xBE, 0x1F, 0x70, 0x3C, 0xC0, 0x03, 0x82, 0x1F, 0x08, 0xC3, 0x20, 0x04, 0xC2, 0x10, 0x88, 0xC1, 0xA0, 0x03,
    0xFE, 0x07, 0xF0, 0x07, 0x00, 0x06, 0x03, 0x18, 0x0C, 0x60, 0xB0, 0x80, 0xC1, 0x01, 0x08, 0x00, 0x70, 0x00, 0x60, 0x03, 0xC0, 0x18, 0x80, 0xC1, 0x00, 0x03, 0x06, 0x04, 0x10, 0x80, 0x04, 0x00, 0x12, 0x00, 0x48, 0x00, 0x20, 0x01, 0x80, 0x04, 0x00, 0x12, 0x00, 0x48, 0x00, 0x20, 0x01, 0x10, 0x40, 0xC0, 0x80, 0x01, 0x06, 0x03, 0x30, 0x06, 0x80, 0x0D, 0x00, 0x1C, 0x00, 0x20, 0x00, 0x06, 0x00, 0x1C, 0x00, 0x30, 0x00, 0x40, 0xC0, 0x0C, 0xC1, 0x33, 0xCC, 0x03, 0xF0, 0x03, 0x80, 0x07, 0x00,
    0xFC, 0x0F, 0xF8, 0x7F, 0x30, 0x00, 0x43, 0x78, 0x08, 0xF1, 0x23, 0x44, 0x88, 0x30, 0x11, 0x82, 0xFF, 0x0C, 0xFC, 0x13, 0xF0, 0xFF, 0xE0, 0xFF, 0xC3, 0x40, 0x00, 0x01, 0x01, 0x04, 0x04, 0x30, 0x10, 0x80, 0xFF, 0x0F, 0xFC, 0x3F, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x10, 0x08, 0x41, 0x20, 0x04, 0x81, 0x30, 0x0E, 0x83, 0xEF, 0x07, 0x1C, 0x0F, 0xF0, 0x3F, 0xE0, 0xFF, 0xC1, 0x00, 0x0C, 0x01, 0x20, 0x04, 0x80, 0x30, 0x00, 0x83, 0x03, 0x07, 0x0C, 0x0C, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x00, 0x08,
    0x01, 0x20, 0x04, 0x80, 0x70, 0x80, 0x83, 0xFF, 0x07, 0xF8, 0x07, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x10, 0x08, 0x41, 0x20, 0x04, 0x81, 0x10, 0x04, 0x42, 0x10, 0x08, 0x01, 0x20, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x20, 0x00, 0x81, 0x00, 0x04, 0x02, 0x10, 0x08, 0x40, 0x20, 0x00, 0x01, 0x00, 0xF0, 0x3F, 0xE0, 0xFF, 0xC1, 0x00, 0x0C, 0x01, 0x20, 0x04, 0x82, 0x30, 0x08, 0x83, 0xE3, 0x07, 0x8C, 0x0F, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0xC0, 0xFF, 0x0F,
    0xFF, 0x3F, 0x04, 0x80, 0x10, 0x00, 0x42, 0x00, 0x08, 0xFF, 0x3F, 0xFC, 0xFF, 0x10, 0x00, 0x42, 0x00, 0x08, 0x01, 0x20, 0x00, 0x30, 0x00, 0xC0, 0x01, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0xC3, 0xFF, 0x07, 0xFF, 0x0F, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x30, 0x00, 0xE0, 0x01, 0xE0, 0x1C, 0xC0, 0xE1, 0xC0, 0x03, 0x0F, 0x03, 0x30, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x1E, 0x00,
    0xC0, 0x03, 0x00, 0x0F, 0x80, 0x07, 0xC0, 0xFF, 0x0F, 0xFF, 0x3F, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x07, 0x00, 0x70, 0x00, 0x00, 0x07, 0x00, 0x70, 0xC0, 0xFF, 0x0F, 0xFF, 0x3F, 0xF0, 0x3F, 0xE0, 0xFF, 0xC1, 0x00, 0x0C, 0x01, 0x20, 0x04, 0x80, 0x30, 0x00, 0x83, 0xFF, 0x07, 0xFC, 0x0F, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x20, 0x00, 0x81, 0x00, 0x04, 0x02, 0x30, 0x0C, 0x80, 0x1F, 0x00, 0x3C, 0x00, 0xF0, 0x3F, 0xE0, 0xFF, 0xC1, 0x00, 0x0C, 0x01, 0x20, 0x04, 0x80, 0x31, 0x00, 0x8F, 0xFF, 0x27,
    0xFC, 0x0F, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x20, 0x00, 0x81, 0x00, 0x04, 0x06, 0x30, 0xFC, 0x81, 0x9F, 0x0F, 0x3C, 0x20, 0xF0, 0x30, 0xE0, 0xC7, 0xC1, 0x18, 0x0C, 0xE1, 0x20, 0x04, 0x87, 0x30, 0x18, 0x83, 0xE3, 0x07, 0x0C, 0x0F, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0xFF, 0x3F, 0xFC, 0xFF, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0xFC, 0x3F, 0xF0, 0xFF, 0x01, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0xC3, 0xFF, 0x07, 0xFF, 0x0F, 0xFC, 0x00, 0xF0, 0x1F, 0x00, 0xF0, 0x03,
    0x00, 0x3C, 0x00, 0xF0, 0x00, 0xFC, 0xC0, 0x7F, 0x00, 0x3F, 0x00, 0xFC, 0x07, 0xF0, 0xFF, 0x03, 0x80, 0x0F, 0xC0, 0x01, 0x00, 0x07, 0x00, 0xE0, 0xC3, 0xFF, 0x0F, 0xFF, 0x01, 0x3C, 0xF0, 0xF0, 0xF3, 0x03, 0xFC, 0x00, 0xC0, 0x00, 0x00, 0x03, 0x00, 0x3F, 0xC0, 0xCF, 0x0F, 0x0F, 0x3C, 0xFC, 0x00, 0xF0, 0x0F, 0x00, 0x70, 0x00, 0x80, 0x3F, 0x00, 0xFE, 0x00, 0x1C, 0xC0, 0x3F, 0x00, 0x3F, 0x00, 0x04, 0xE0, 0x10, 0xE0, 0x43, 0xE0, 0x09, 0xC1, 0x21, 0x84, 0x81, 0x90, 0x03, 0xC2, 0x07, 0x08,
    0x07, 0x20, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x00, 0x08, 0x01, 0x20, 0x0C, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x30, 0x04, 0x80, 0x10, 0x00, 0xC2, 0xFF, 0x0F, 0xFF, 0x3F, 0x10, 0x00, 0x40, 0x00, 0x80, 0x01, 0x00, 0x03, 0x00, 0x0C, 0x00, 0x60, 0x00, 0x80, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0xC8, 0x01, 0x00,
    0x0B, 0x00, 0x00, 0x78, 0x00, 0xF4, 0x03, 0x48, 0x08, 0x20, 0x21, 0x80, 0x84, 0x00, 0x12, 0x01, 0xF8, 0x0F, 0xC0, 0x3F, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x10, 0x04, 0x20, 0x20, 0x80, 0x80, 0x00, 0x06, 0x03, 0xF0, 0x07, 0x80, 0x0F, 0x00, 0x3E, 0x00, 0xFC, 0x01, 0x18, 0x0C, 0x20, 0x20, 0x80, 0x80, 0x00, 0x02, 0x02, 0x18, 0x0C, 0x40, 0x10, 0x00, 0x3E, 0x00, 0xFC, 0x01, 0x18, 0x0C, 0x20, 0x20, 0x80, 0x80, 0x00, 0x04, 0xC1, 0xFF, 0x0F, 0xFF, 0x3F, 0x00, 0x3E, 0x00, 0xFC, 0x01, 0x98, 0x0C,
    0x20, 0x22, 0x80, 0x88, 0x00, 0x26, 0x02, 0xF0, 0x0C, 0x80, 0x13, 0x80, 0x00, 0x00, 0x02, 0x80, 0xFF, 0x0F, 0xFF, 0x3F, 0x84, 0x00, 0x10, 0x02, 0xC0, 0x08, 0x00, 0x02, 0x00, 0x00, 0x1E, 0x01, 0xFC, 0x04, 0x18, 0x36, 0x20, 0x90, 0x80, 0x40, 0x02, 0x84, 0x0C, 0xF8, 0x1F, 0xE0, 0x3F, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x10, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x06, 0x00, 0xF0, 0x0F, 0x80, 0x3F, 0x80, 0x80, 0x00, 0x02, 0xC2, 0xF8, 0x0F, 0xE3, 0x3F, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x10,
    0x20, 0xC0, 0x80, 0x00, 0x32, 0xFE, 0xCF, 0xF8, 0x1F, 0xFF, 0x3F, 0xFC, 0xFF, 0x00, 0x60, 0x00, 0xC0, 0x01, 0x80, 0x0D, 0x00, 0x63, 0x00, 0x06, 0x03, 0x08, 0x08, 0x01, 0x20, 0x04, 0x80, 0xF0, 0xFF, 0xC3, 0xFF, 0x0F, 0x00, 0x20, 0x00, 0x80, 0x00, 0xFE, 0x03, 0xF8, 0x0F, 0x60, 0x00, 0x00, 0x7F, 0x00, 0xFC, 0x01, 0x18, 0x00, 0xE0, 0x3F, 0x00, 0xFF, 0x00, 0xFE, 0x03, 0xF8, 0x0F, 0x40, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x18, 0x00, 0xC0, 0x3F, 0x00, 0xFE, 0x00, 0xF8, 0x00, 0xF0, 0x07,
    0x60, 0x30, 0x80, 0x80, 0x00, 0x02, 0x02, 0x18, 0x0C, 0xC0, 0x1F, 0x00, 0x3E, 0x00, 0xFE, 0x0F, 0xF8, 0x3F, 0x40, 0x10, 0x80, 0x80, 0x00, 0x02, 0x02, 0x18, 0x0C, 0xC0, 0x1F, 0x00, 0x3E, 0x00, 0xF8, 0x00, 0xF0, 0x07, 0x20, 0x20, 0x80, 0x80, 0x00, 0x02, 0x02, 0x10, 0x04, 0xE0, 0xFF, 0x80, 0xFF, 0x03, 0xFE, 0x03, 0xF8, 0x0F, 0xC0, 0x00, 0x00, 0x01, 0x00, 0x06, 0x00, 0x18, 0x00, 0x60, 0x00, 0x00, 0x01, 0x00, 0x0C, 0x01, 0x78, 0x0C, 0x20, 0x21, 0x80, 0x8C, 0x00, 0x62, 0x02, 0x08, 0x09,
    0x60, 0x3C, 0x00, 0x61, 0x00, 0x02, 0x00, 0x08, 0x00, 0xFE, 0x1F, 0xF8, 0xFF, 0x00, 0x02, 0x02, 0x08, 0x08, 0xE0, 0x1F, 0x80, 0xFF, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x40, 0x00, 0xFE, 0x03, 0xF8, 0x0F, 0xE0, 0x03, 0x80, 0x1F, 0x00, 0xC0, 0x01, 0x00, 0x0C, 0x00, 0x30, 0x00, 0x70, 0x00, 0x7E, 0x00, 0xF8, 0x00, 0xE0, 0x07, 0x80, 0xFF, 0x00, 0x80, 0x03, 0xF0, 0x01, 0xC0, 0x07, 0x00, 0xE0, 0x00, 0xFE, 0x03, 0xF8, 0x01, 0x60, 0x30, 0x80, 0xF7, 0x00, 0xD8, 0x00, 0xC0, 0x01,
    0x00, 0x07, 0x00, 0x36, 0x00, 0xDE, 0x03, 0x18, 0x0C, 0xE0, 0x83, 0x80, 0x3F, 0x02, 0xC0, 0x0D, 0x00, 0x1C, 0x00, 0x30, 0x00, 0x70, 0x00, 0xFE, 0x00, 0xF8, 0x00, 0x20, 0x30, 0x80, 0xE0, 0x00, 0xC2, 0x02, 0x88, 0x09, 0x20, 0x23, 0x80, 0x86, 0x00, 0x0E, 0x02, 0x18, 0x08, 0x80, 0x00, 0xF8, 0xFF, 0xF0, 0xF7, 0x47, 0x00, 0x10, 0x01, 0x40, 0xFC, 0xFF, 0xF3, 0xFF, 0x4F, 0x00, 0x10, 0x01, 0x40, 0xFC, 0xFD, 0xE1, 0xFF, 0x03, 0x20, 0x00, 0x02, 0x00, 0x08, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00,
    0x02, 0x00, 0x08, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0xE0, 0x3F, 0xE0, 0xFF, 0xC0, 0x01, 0xC3, 0x01, 0x0C, 0x07, 0x30, 0x70, 0xC0, 0x80, 0xFF, 0x03, 0xF8, 0x0F, 0x00, 0x00, 0xF0, 0x3F, 0xE0, 0xFF, 0xC1, 0x00, 0x0C, 0x01, 0xA0, 0x04, 0x80, 0x33, 0x00, 0x87, 0x03, 0x07, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0xFE, 0xC1, 0xF8, 0x0F, 0x03, 0x20, 0x00, 0x80, 0x00, 0x00, 0xC2, 0x00, 0x04, 0xE3, 0x3F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0xE0, 0x03, 0xC0, 0x1F, 0x80, 0xC9, 0x00, 0x22, 0x82, 0x88, 0x08,
    0x63, 0x22, 0x04, 0xCF, 0x10, 0x38, 0x01, 0x00, 0x00, 0x00, 0x1E, 0x00, 0xFD, 0x40, 0x12, 0x82, 0x49, 0x08, 0x23, 0x21, 0x8C, 0x44, 0x60, 0xFE, 0x03, 0xF1, 0x0F, 0x00, 0x00, 0x00, 0x78, 0x30, 0xF4, 0xC3, 0x48, 0x08, 0x20, 0x21, 0x80, 0x84, 0x30, 0x12, 0xC1, 0xF8, 0x0F, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0xE0, 0x01, 0xD0, 0x0F, 0x21, 0x21, 0x84, 0x84, 0x30, 0x12, 0x82, 0x48, 0x04, 0xE0, 0x3F, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x80, 0x07, 0x40, 0x3F, 0x88, 0x84, 0x70, 0x12, 0x42, 0x49, 0x08,
    0x27, 0x11, 0x88, 0xFF, 0x00, 0xFC, 0x03, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x7F, 0x00, 0x06, 0x03, 0x08, 0x28, 0x20, 0xE0, 0x80, 0x80, 0x01, 0x06, 0x03, 0x10, 0x04, 0x00, 0x00, 0x00, 0x3E, 0x00, 0xFC, 0x01, 0x99, 0x0C, 0x26, 0x22, 0x8C, 0x88, 0x60, 0x26, 0x02, 0xF1, 0x0C, 0x80, 0x13, 0x00, 0x00, 0x00, 0xF8, 0xC0, 0xF0, 0x07, 0x63, 0x32, 0x80, 0x88, 0x00, 0x22, 0xC2, 0x98, 0x08, 0xC3, 0x33, 0x00, 0x4E, 0x00, 0x00, 0x00, 0xE0, 0x03, 0xC0, 0x1F, 0x84, 0xC9, 0x10, 0x22, 0xC2, 0x88, 0x08,
    0x62, 0x22, 0x00, 0xCF, 0x00, 0x38, 0x01, 0x00, 0x00, 0x00, 0x00, 0x8C, 0x80, 0x30, 0x02, 0x02, 0xF8, 0x0F, 0xE0, 0x3F, 0x0C, 0x80, 0x30, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x90, 0x80, 0x60, 0x02, 0xC2, 0xF8, 0x0F, 0xE3, 0x3F, 0x18, 0x80, 0x40, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x84, 0x80, 0x10, 0x02, 0xC2, 0xF8, 0x0F, 0xE2, 0x3F, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x00, 0xC0, 0x3F, 0x8C, 0xFF, 0x30, 0x23, 0x00, 0x84, 0x00, 0x10, 0x02, 0xCC, 0x08, 0x30, 0xFE, 0x03, 0xF0, 0x0F,
    0x00, 0x00, 0x00, 0xFF, 0x00, 0xFE, 0x03, 0x8C, 0x00, 0x13, 0x02, 0x52, 0x08, 0x30, 0x23, 0x00, 0xF8, 0x0F, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0xFF, 0x03, 0xFC, 0x0F, 0x10, 0x21, 0x40, 0x84, 0x20, 0x11, 0xC2, 0x44, 0x08, 0x11, 0x21, 0x44, 0x80, 0x00, 0x00, 0x00, 0x90, 0x07, 0x20, 0x3F, 0x80, 0x84, 0x00, 0xFC, 0x03, 0xF8, 0x07, 0x20, 0x22, 0x80, 0x8F, 0x00, 0x3C, 0x01, 0x00, 0x00, 0xF8, 0x3F, 0xF0, 0xFF, 0xE0, 0x10, 0xC0, 0xFF, 0x0F, 0xFF, 0x3F, 0x04, 0x82, 0x10, 0x08, 0x42, 0x00, 0x08,
    0x00, 0x00, 0x00, 0x3E, 0x00, 0xFC, 0x01, 0x19, 0x0C, 0x26, 0x20, 0x8C, 0x80, 0x60, 0x06, 0x03, 0xF1, 0x07, 0x80, 0x0F, 0x00, 0x00, 0x00, 0xF8, 0xC0, 0xF0, 0x07, 0x63, 0x30, 0x80, 0x80, 0x00, 0x02, 0xC2, 0x18, 0x0C, 0xC3, 0x1F, 0x00, 0x3E, 0x00, 0x00, 0x00, 0xE0, 0x03, 0xC1, 0x1F, 0x84, 0xC1, 0x30, 0x02, 0x82, 0x08, 0x08, 0x60, 0x30, 0x00, 0x7F, 0x00, 0xF8, 0x00, 0x00, 0x00, 0xE0, 0x1F, 0x80, 0xFF, 0x40, 0x00, 0x82, 0x01, 0x08, 0x03, 0x20, 0x18, 0x40, 0x40, 0xFE, 0x03, 0xF8, 0x0F,
    0x00, 0x00, 0x80, 0x7F, 0x10, 0xFE, 0x43, 0x00, 0x08, 0x03, 0x20, 0x08, 0x80, 0x00, 0x00, 0x01, 0xF8, 0x0F, 0xE0, 0x3F, 0x00, 0x00, 0x00, 0x3E, 0xC8, 0xF8, 0x23, 0x03, 0xCC, 0x00, 0xE0, 0x01, 0x80, 0xC3, 0x00, 0x07, 0xE3, 0x0F, 0x80, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x03, 0xE3, 0x1F, 0xCC, 0xC0, 0x00, 0x01, 0x02, 0x04, 0x08, 0x33, 0x30, 0x8C, 0x7F, 0x00, 0xFC, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0xCC, 0x7F, 0x30, 0x00, 0x03, 0x00, 0x08, 0x00, 0x20, 0x0C, 0xC0, 0x30, 0xFF, 0x01, 0xFC, 0x03,
    0x00, 0x00, 0x00, 0xBE, 0x01, 0xFC, 0x07, 0x18, 0x0E, 0x20, 0x2F, 0x80, 0x9E, 0x00, 0x0E, 0x03, 0xFC, 0x07, 0xB0, 0x0F, 0x00, 0x00, 0xC0, 0x09, 0x83, 0xFF, 0x0F, 0xE3, 0x2F, 0x04, 0x82, 0x10, 0x08, 0x42, 0x20, 0x08, 0x03, 0x30, 0x08, 0x40, 0x00, 0x00, 0x00, 0xFF, 0x1B, 0xFE, 0x7F, 0x0C, 0xF8, 0x10, 0x7E, 0x42, 0x7E, 0x08, 0x1F, 0x30, 0xFE, 0x7F, 0xD8, 0xFF, 0x00, 0x00, 0x00, 0x18, 0x06, 0xE0, 0x1C, 0x00, 0x3F, 0x00, 0x78, 0x00, 0xE0, 0x01, 0xC0, 0x0F, 0x80, 0x73, 0x00, 0x86, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x08, 0x10, 0x20, 0xFE, 0xFF, 0xFC, 0xFF, 0x11, 0x04, 0x40, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0xD0, 0x0F, 0x20, 0x21, 0x80, 0x84, 0x20, 0x12, 0xC2, 0x48, 0x04, 0xE1, 0x3F, 0x04, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x80, 0x80, 0x20, 0xFE, 0xC3, 0xF8, 0x0F, 0x01, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x03, 0xC0, 0x1F, 0x80, 0xC1, 0x00, 0x02, 0x82, 0x08, 0x08, 0x63, 0x30, 0x04, 0x7F, 0x10, 0xF8, 0x00, 0x00, 0x00,
    0xE0, 0x1F, 0x80, 0xFF, 0x00, 0x00, 0x82, 0x00, 0x08, 0x03, 0x20, 0x04, 0x40, 0x10, 0xFE, 0x03, 0xF8, 0x0F, 0x00, 0x00, 0x80, 0xFF, 0x00, 0xFE, 0x83, 0x10, 0x00, 0x21, 0x00, 0x8C, 0x00, 0x20, 0x06, 0x40, 0xF0, 0x0F, 0x80, 0x3F, 0x00, 0x00, 0x00, 0xFF, 0x03, 0xFC, 0x0F, 0x62, 0x00, 0x04, 0x03, 0x30, 0x18, 0x80, 0xC0, 0x00, 0xF1, 0x3F, 0xC0, 0xFF, 0x00, 0x00, 0x00, 0x4E, 0x00, 0x38, 0x01, 0x14, 0x05, 0x50, 0x14, 0x40, 0x51, 0x00, 0x45, 0x01, 0xFC, 0x05, 0xE0, 0x17, 0x00, 0x00, 0x00,
    0x1C, 0x01, 0xF8, 0x04, 0x30, 0x16, 0x40, 0x50, 0x00, 0x41, 0x01, 0x8C, 0x05, 0xE0, 0x13, 0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0xF0, 0x03, 0xF0, 0x0C, 0xF3, 0x20, 0xCC, 0x80, 0x00, 0x00, 0x03, 0x00, 0x0E, 0x00, 0x18, 0xF0, 0x3F, 0xE0, 0xFF, 0xC1, 0x00, 0x0C, 0xF1, 0x23, 0x44, 0x82, 0x10, 0x36, 0xC2, 0x00, 0x0C, 0xFE, 0x1F, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x0E, 0x00, 0x38, 0x00, 0x00, 0x40, 0x08, 0x98,
    0x3F, 0x18, 0x80, 0x18, 0x00, 0x18, 0x00, 0x98, 0x18, 0x18, 0x51, 0x18, 0x24, 0x19, 0x60, 0x04, 0x00, 0x00, 0x21, 0x60, 0xFE, 0x60, 0x00, 0x62, 0x00, 0x60, 0x00, 0x60, 0x18, 0x60, 0x58, 0x60, 0x90, 0x67, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x07, 0xF3, 0x3F, 0xCC, 0xFF, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x3C, 0x00, 0x98, 0x01, 0x30, 0x0C, 0x00, 0x06, 0x00, 0x3C, 0x00, 0x98, 0x01, 0x30, 0x0C, 0x00, 0x00, 0x00, 0xC3, 0x00, 0x98, 0x01, 0xC0, 0x03,
    0x00, 0x06, 0x00, 0xC3, 0x00, 0x98, 0x01, 0xC0, 0x03, 0x00, 0x06, 0x08, 0x11, 0x02, 0x00, 0x20, 0x44, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20, 0x44, 0x08, 0x00, 0x80, 0x10, 0x21, 0xAA, 0xAA, 0x02, 0x00, 0x00, 0x00, 0x40, 0x55, 0x55, 0x00, 0x00, 0xA8, 0xAA, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x55, 0x55, 0xA5, 0xAA, 0x6A, 0x55, 0x55, 0xAA, 0xAA, 0x56, 0x55, 0xA5, 0xAA, 0x6A, 0x55, 0x55, 0xAA, 0xAA, 0x56, 0x55, 0xA5, 0xAA, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0x03, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0xF0, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFE, 0x83, 0x8C, 0x00, 0x13, 0x02, 0x44, 0x08, 0x10, 0x23, 0x00, 0xF8, 0x0F, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0xFC, 0x03, 0xF8, 0x0F, 0x32, 0x02, 0x4C, 0x08, 0x18, 0x21, 0xC0, 0x8C, 0x00, 0xE2, 0x3F, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0xE0, 0x3F, 0xC4, 0x08, 0x10, 0x21, 0xC0, 0x84, 0x00, 0x32, 0x02, 0x80, 0xFF, 0x00, 0xFC, 0x03, 0xFF, 0x03,
    0xFE, 0x1F, 0x0C, 0xC0, 0x10, 0x1E, 0x42, 0x84, 0x08, 0x21, 0x21, 0x0C, 0xC0, 0xE0, 0xFF, 0x01, 0xFF, 0x03, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0xC0, 0xBF, 0xFF, 0x00, 0x00, 0xFC, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x3F, 0x00, 0x00, 0xFF, 0xFF, 0x03, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0x00, 0xFA, 0x0F, 0x08, 0x00, 0xE0, 0xFF, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0xFF, 0x02, 0x00, 0x08, 0xF0, 0x3F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0xFF, 0x01, 0x04, 0x04, 0xFC, 0x7F, 0x40, 0x40, 0x00, 0xC7, 0x01, 0x18, 0x03, 0x00, 0x00, 0x30, 0x00, 0xC0, 0x47, 0x01, 0x7C, 0x05, 0x80, 0xFF, 0x00, 0xFE, 0x03, 0x5F, 0x01, 0x1F, 0x05, 0x0C, 0x00, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00,
    0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0xF0, 0x1F, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0xFF, 0x03, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x3F, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00,
    0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0xF0, 0xFF, 0x3F, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0xF4, 0x83, 0x48, 0x08, 0x21, 0x21, 0x8C, 0x84, 0x20, 0x12, 0x41, 0xF8, 0x0F, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0xFC, 0x03, 0xF8, 0x0F, 0x32, 0x02, 0x44, 0x08, 0x30, 0x21, 0x80, 0x8C, 0x00, 0xE1, 0x3F, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x0F, 0x00, 0x20, 0xC0,
    0xBF, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x80, 0x00, 0x00, 0xFA, 0x0F, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0xFC, 0x0B, 0x00, 0x20, 0xC0, 0xBF, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0xFF, 0x80, 0x00, 0x00, 0xFA, 0x0F, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x0F, 0x00, 0xC0, 0xBF, 0xFF, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0xA0, 0x00, 0x80, 0x02, 0xFC, 0xFB, 0x0F, 0x00, 0xC0, 0xBF, 0xFF, 0x80, 0x02, 0x00, 0x0A, 0x00, 0x28, 0x00, 0x00, 0x00, 0xD8, 0x37, 0xC0, 0x7F, 0x80, 0x01, 0x03, 0x02, 0x08, 0x08, 0x20, 0x60, 0xC0, 0x00, 0xFF, 0x01,
    0xF6, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x07, 0x3C, 0x3F, 0xB0, 0xCD, 0xC0, 0x1C, 0x03, 0xE3, 0x0F, 0x0C, 0x1F, 0x00, 0x02, 0xF0, 0xFF, 0xC3, 0xFF, 0x0F, 0x81, 0x20, 0x04, 0x80, 0x10, 0x00, 0xC2, 0x01, 0x0E, 0xFE, 0x1F, 0xE0, 0x1F, 0x00, 0x00, 0x00, 0xFC, 0x0F, 0xF0, 0x3F, 0x48, 0x84, 0x30, 0x11, 0x62, 0x44, 0x08, 0x13, 0x21, 0x48, 0x84, 0x00, 0x01, 0x02, 0x00, 0x00, 0xF0, 0x3F, 0xC0, 0xFF, 0x30, 0x11, 0xC2, 0x44, 0x08, 0x10, 0x21, 0x4C, 0x84, 0x30, 0x11, 0x02, 0x04, 0x08,
    0x00, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x43, 0x44, 0x08, 0x11, 0x21, 0x4C, 0x84, 0x20, 0x11, 0x02, 0x44, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0xF8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x01, 0x82, 0xFC, 0x0F, 0xF3, 0x3F, 0x44, 0x80, 0x10, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x20, 0x01, 0xC2, 0xFC, 0x8F, 0xF1, 0x3F, 0x4C, 0x80, 0x20, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x30, 0x01, 0xC2, 0xFC, 0x0F,
    0xF0, 0x3F, 0x4C, 0x80, 0x30, 0x01, 0x02, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x0F, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFE, 0x03, 0xF8, 0x0F, 0xE0, 0x3F, 0x80, 0xFF, 0x00, 0xFE, 0x03, 0xF8, 0x0F, 0xE0, 0x3F,
    0x80, 0xFF, 0x00, 0xFE, 0x03, 0xF8, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xDF, 0x3F, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x40, 0x04, 0x08, 0x11, 0x20, 0xCC, 0xFF, 0x20, 0xFF, 0x03, 0x04, 0x08, 0x10, 0x20, 0xFF, 0x01, 0xFC, 0x07, 0xF0, 0x1F, 0xC0, 0x7F, 0x00, 0xFF, 0x01, 0xFC, 0x07, 0xF0, 0x1F, 0xC0, 0x7F, 0x00, 0xFF, 0x01, 0xFC, 0x07, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0x80, 0x7F, 0x00, 0x03, 0x83, 0x04, 0x08, 0x13, 0x20, 0xC4, 0xC0, 0x10, 0xFE, 0x01, 0xF0, 0x03,
    0x00, 0x00, 0xF8, 0xFF, 0xF3, 0xFF, 0x4F, 0x10, 0x08, 0x41, 0x20, 0x8C, 0x83, 0xE0, 0xFB, 0x03, 0xC7, 0x07, 0x00, 0x00, 0x00, 0x3F, 0x00, 0xFE, 0x81, 0x0C, 0x0C, 0x13, 0x20, 0x46, 0x80, 0x30, 0x03, 0x83, 0xF8, 0x07, 0xC0, 0x0F, 0x00, 0x00, 0x00, 0xFC, 0x40, 0xF8, 0x07, 0x31, 0x30, 0x4C, 0x80, 0x20, 0x01, 0x02, 0x0C, 0x0C, 0xE0, 0x1F, 0x00, 0x3F, 0x00, 0x00, 0x00, 0xE0, 0x03, 0xC2, 0x1F, 0x84, 0xC1, 0x30, 0x02, 0x82, 0x08, 0x08, 0x61, 0x30, 0x00, 0x7F, 0x00, 0xF8, 0x00, 0x00, 0x00,
    0xC0, 0x0F, 0x88, 0x7F, 0x10, 0x03, 0xC3, 0x04, 0x08, 0x12, 0x20, 0xC4, 0xC0, 0x00, 0xFE, 0x01, 0xF0, 0x03, 0x00, 0x00, 0x80, 0xFF, 0x03, 0xFE, 0x0F, 0x00, 0x0C, 0x00, 0x30, 0x00, 0xC0, 0x00, 0x80, 0x01, 0xF8, 0x0F, 0xE0, 0x3F, 0x00, 0x00, 0x80, 0x00, 0x01, 0xFE, 0x07, 0xF8, 0x1F, 0x20, 0x49, 0x00, 0x24, 0x00, 0xF0, 0x00, 0x80, 0x01, 0x00, 0x00, 0x40, 0x00, 0x02, 0xFF, 0x0F, 0xFC, 0x3F, 0x90, 0x90, 0x00, 0x42, 0x00, 0xF8, 0x01, 0xC0, 0x03, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFC, 0x07,
    0x00, 0x30, 0x08, 0x80, 0x30, 0x00, 0x42, 0x00, 0x0C, 0xF1, 0x1F, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0xFC, 0x03, 0xF0, 0x1F, 0x08, 0xC0, 0x30, 0x00, 0x62, 0x00, 0x08, 0x03, 0x30, 0xC8, 0x7F, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0xC4, 0x7F, 0x10, 0x00, 0xC3, 0x00, 0x08, 0x02, 0x20, 0x00, 0xC0, 0x00, 0xFF, 0x01, 0xFC, 0x03, 0x00, 0x00, 0x80, 0x0F, 0x02, 0xFE, 0x08, 0x00, 0x33, 0x02, 0x78, 0x0C, 0xE0, 0x10, 0xC0, 0x41, 0xF8, 0x03, 0xE0, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x7C, 0x00,
    0x80, 0x03, 0x08, 0xFC, 0x30, 0xF0, 0x43, 0xE0, 0x00, 0xF1, 0x01, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x30, 0x00, 0x40, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x40, 0x08, 0xC0, 0x27, 0x00, 0x9F, 0x00, 0x10, 0x02,
    0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x20, 0x01, 0x80, 0x04, 0x00, 0x12, 0x00, 0x48, 0x00, 0x20, 0x01, 0x00, 0x00, 0x08, 0x02, 0xA6, 0x08, 0x86, 0x1D, 0x06, 0x00, 0x06, 0x00, 0x86, 0x01, 0x86, 0x05, 0x06, 0x79, 0x06, 0x40, 0x00, 0x00, 0x80, 0x1F, 0x00, 0xFF, 0x00, 0xFC, 0xFF, 0xF0, 0xFF, 0x43, 0x00, 0x00, 0x01, 0x00, 0xFC, 0xFF, 0xF0, 0xFF, 0x03, 0x00, 0x00, 0x06, 0x18, 0xBC, 0xE1, 0xD0, 0x0F, 0x42, 0x66, 0x08, 0x31, 0x23, 0x84, 0x9F, 0x70, 0xEC, 0x83, 0x01, 0x07,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00, 0xB0, 0x06, 0xC0, 0x1A, 0x00, 0x08, 0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x0C, 0x00, 0x30, 0x00, 0x00, 0x00, 0x18, 0x00, 0xF0, 0x00, 0x60, 0x06, 0x80, 0x10, 0x00, 0x66, 0x00, 0xF0, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00, 0x25, 0x00, 0xFC, 0x00, 0xA0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0xB0, 0x03, 0x40, 0x0B, 0x00, 0x27, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0xFC, 0x00, 0xF0, 0x03, 0xC0, 0x0F, 0x00};

static struct fontDesc_t const Terminal_11_Desc = {
    sizeof(Terminal_11_Bytes) + 7,     // total Size
    11,                                // width in pixel
    18,                                // height in pixel
    1,                                 // bits per pixel
    0x01,                              // Code of first char
    0xFE,                              // Code of last char
    (unsigned char *)Terminal_11_Bytes // Data
};

#endif

#ifndef FONT_CONFIG_H_
#define FONT_CONFIG_H_

// make sure, the font is uncommented in fontConfig.c
//
// you do not need to worry about having too many fonts
// activated in fontConfig.c
// all fonts not referenced will be discarded by the linker
//

// Note: since all of the fonts have been generated from TTF fonts
// we cannot guarantee a consistent character height. We get what we
// get when requesting a font height of 12 or 20. Some converted
// fonts are visually larger then others.
// You are invited to fix this by try and error in the conversion process.
// The idea is that 12 denotes the intended character height
// including "subscripts" (as in g, y, ...)
// Same for 20.
// Right now, 12 is some sort of small font, 20 is some sort of large font
// if this is not useful to you, then by all means convert your own fonts.
//
// Been there, done that. It is a pain in the ass. Good luck! (Seriously)

// These fonts are good text fonts
// #define FONT    Blue_12_Desc                // elegant
// #define FONT    Courier_12_Desc             // der Klassiker, der immer geht
// #define FONT    FixedSys_11_Desc            // good allround font
// #define FONT    Gabriola_12_Desc            // schön, aber nicht besonders nützlich
// #define FONT    Gabriola_20_Desc
// #define FONT    HoloLens_12_Desc            // kleine Schrift, gut zu lesen, elegant
// #define FONT    HoloLens_20_Desc
// #define FONT    Neuropol_12_Desc            // modern, breite Buchstaben
// #define FONT    Roboto_12_Desc              // almost like Terminal, little bit more elegant
// #define FONT    Open_12_Desc                // kleine Schrift, gut lesbar, klassisch
// #define FONT    Tahoma_10_Desc              // gute allround Schrift, was fuers Grobe
#define FONT Terminal_8_Desc // if you need lots of space, still readable
// #define FONT    Terminal_11_Desc            // good allround font
//  #define FONT    Times_12_Desc               // dazu braucht man nichts sagen, wirkt altbacken
//  #define FONT    Trebuchet_12_Desc           // gute Schrift, wenn es etwas bold sein darf
//  #define FONT    Verdana_12_Desc             // ausgewogen, gut lesbar, bolder als Trebuchet

// These fonts are fancy fonts
// #define FONT    Amadeus_12_Desc
// #define FONT    Burnstown_12_Desc           // rustikale Bretterschrift
// #define FONT    Cowboys_10_Desc             // ratatatata Bonanzaaaaa
// #define FONT    Mickey_12_Desc              // Nomen est omen in den Grossbuchstaben
// #define FONT    Script_12_Desc              // Schreibschrift
// #define FONT    Seaside_12_Desc             // Art D'eco
// #define FONT    Waker_12_Desc               // was fuer zb Halloween

#define FONT_CHAR_SPACING 2

#include "Fonts/FontDesc.h"

fontDesc_t const *getSystemFont();

#endif

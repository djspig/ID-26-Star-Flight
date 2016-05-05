#ifndef GLOBAL_H
#define GLOBAL_H

#include "Arglib.h"
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_HELP              2
#define STATE_MENU_PLAY              3
#define STATE_MENU_INFO              4
#define STATE_MENU_SOUNDFX           5

//define game states (on main menu)
#define STATE_GAME_PLAYING           6
#define STATE_GAME_PAUSE             7
#define STATE_GAME_OVER              8

#define LEVEL_ONE       1
#define LEVEL_TWO       2

Arduboy arduboy;
Sprites sprites(arduboy);
SimpleButtons buttons (arduboy);

unsigned char gameState;
boolean soundYesNo;
int menuSelection;
byte counter = 0;
byte life;
byte level;
boolean atEndOfLevel;
unsigned long scorePlayer;
byte levelProgress;

#endif

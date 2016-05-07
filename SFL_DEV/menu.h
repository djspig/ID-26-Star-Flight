#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"


byte slideCount01 = 0;
byte slideCount02 = 0;

void drawTitleScreen()
{
  arduboy.drawBitmap(0, 16, titleScreenSFL, 128, 48, WHITE);
  arduboy.drawBitmap(2, 8, gameTitleSFL, 124, 24, WHITE);
}

void setSlidersToZero()
{
  slideCount02 = 0;
  slideCount01 = 0;
}

void makeItSlide()
{
  slideCount01++;
  if (slideCount01 > 6)
  {
    slideCount02++;
    slideCount01 = 6;
  }

  if (slideCount02 > 3)
  {
    slideCount02 = 3;
  }
}

void stateMenuIntro()
{
  arduboy.drawBitmap(0, 8, TEAMarg, 128, 48, WHITE);
  counter++;
  if (counter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  // show the splash art
  drawTitleScreen();

  for (byte i = 0; i < 4; i++)
  {
    {
      if (((2 + i) - menuSelection) != 0)
      {
        sprites.drawSelfMasked(9 + (28 * i), -9 + slideCount01, menuText, i);
      }
      if (((2 + i) - menuSelection) == 0) sprites.drawSelfMasked(9 + (28 * i), -9 + slideCount01 + slideCount02  , menuText, i);
    }
  }

  if (buttons.justPressed(RIGHT_BUTTON) && (menuSelection < 5))
  {
    menuSelection++;
    slideCount02 = 0;
  }
  if (buttons.justPressed(LEFT_BUTTON) && (menuSelection > 2))
  {
    menuSelection--;
    slideCount02 = 0;
  }
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    setSlidersToZero();
    gameState = menuSelection;
  }
  if (arduboy.everyXFrames(6)) makeItSlide();
}

void stateMenuHelp()
{
  arduboy.drawBitmap(32, 0, qrcode, 64, 64, WHITE);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuInfo()
{
  arduboy.drawBitmap(2, 8, gameTitleSFL, 124, 24, WHITE);
  arduboy.drawBitmap(16, 32, info_bitmap, 96, 24, WHITE);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  drawTitleScreen();

  sprites.drawSelfMasked(36, -6 + slideCount01, menuText, 4);
  sprites.drawSelfMasked(57, -9 + slideCount01 + (slideCount02 *(1-soundYesNo)), menuText, 5);
  sprites.drawSelfMasked(78, -9 + slideCount01 + (slideCount02 *(soundYesNo)) , menuText, 6);


  if (buttons.justPressed(LEFT_BUTTON))
  {

    soundYesNo = false;
    slideCount02 = 0;
  }
    if (buttons.justPressed(RIGHT_BUTTON))
  {
    soundYesNo = true;
    slideCount02 = 0;
  }
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    setSlidersToZero();
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
  if (soundYesNo == true)
  {
    arduboy.audio.on();
  }
  else
  {
    arduboy.audio.off();
  }
  if (arduboy.everyXFrames(6)) makeItSlide();
}

void stateMenuPlay()
{
  gameState = STATE_GAME_PREPARE_LEVEL;
}


#endif

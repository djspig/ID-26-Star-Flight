#ifndef MENU_H
#define MENU_H

#include "globals.h"
#include "player.h"
#include "stage.h"

void stateMenuIntro()
{
  arduboy.drawBitmap(0, 8, TEAMarg, 128, 48, WHITE);
  counter++;
  if (counter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  // show the splash art
  arduboy.drawBitmap(0, 16, titleScreenSFL, 128, 48, WHITE);
  arduboy.drawBitmap(2, 8, gameTitleSFL, 124, 24, WHITE);
  if (buttons.justPressed(RIGHT_BUTTON) && (menuSelection < 5)) menuSelection++;
  if (buttons.justPressed(LEFT_BUTTON) && (menuSelection > 2)) menuSelection--;
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = menuSelection;
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
  drawStarField();
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  arduboy.drawBitmap(0, 16, titleScreenSFL, 128, 48, WHITE);
  arduboy.drawBitmap(2, 8, gameTitleSFL, 124, 24, WHITE);
  if (buttons.justPressed(RIGHT_BUTTON)) soundYesNo = true;
  if (buttons.justPressed(LEFT_BUTTON)) soundYesNo = false;
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
}

void stateMenuPlay()
{
  playerShip.reset();
  currentBullet = 0;
  life = 3;
  bombs = 3;
  scorePlayer = 0;
  level = LEVEL_ONE;
  atEndOfLevel = false;
  levelProgress = 0;
  currentWeapon = WEAPON_CANON;
  gameState = STATE_GAME_PLAYING;
}


#endif

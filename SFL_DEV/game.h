#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"


boolean checkGameOver()
{
  return false;
}


void stateGamePrepareLevel()
{
  level = 1;
  scorePlayer = 0;
  spaceShip.life = 3;
  gameState = STATE_GAME_NEXT_LEVEL;
};

void stateGameNextLevel()
{
  spaceShip.set();
  currentWave = 0;
  previousWave = 255;
  //calculateLevelSize();
  gameState = STATE_GAME_PLAYING;
};

void stateGamePlaying()
{
  checkInputs();
  checkIfShipIsImune();
  drawSpaceShip();
  //if (checkGameOver())gameState = STATE_GAME_OVER;
}
void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_GAME_PLAYING;
}
void stateGameOver()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

#endif

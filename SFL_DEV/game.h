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
  level = 0;
  scorePlayer = 0;
  spaceShip.life = 3;
  setEnemies();
  gameState = STATE_GAME_NEXT_LEVEL;
};

void stateGameNextLevel()
{
  spaceShip.set();
  currentWave = 0;
  previousWave = 255;
  level++;
  gameState = STATE_GAME_PLAYING;
};

void stateGamePlaying()
{
  checkInputs();
  checkIfShipIsImune();
  checkEnemies();
  if (arduboy.everyXFrames(2))Levels[level-1][currentWave]();
  if (checkEndLevel()) gameState = STATE_GAME_NEXT_LEVEL;
  drawEnemies();
  drawSpaceShip();
  if (checkGameOver())gameState = STATE_GAME_OVER;
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

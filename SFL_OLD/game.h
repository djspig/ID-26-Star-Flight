#ifndef GAME_H
#define GAME_H

#include "stage.h"

void updateStage()
{
  updateMap();
  drawStarField();
  drawBullets();
  drawBomb();
  drawEnemyShips();
  drawBoss();
  drawPlayerShip();
  drawScreenInfo();
  checkIfShipIsImune();
  scorePlayer++;
}

boolean checkGameOver()
{
  return false;
}

void stateGamePlaying()
{
  checkInputs();
  updateStage();
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

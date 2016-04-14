/*
 Star Flight: http://www.team-arg.org/SFL-manual.html

 Arduboy version 0.3:  http://www.team-arg.org/SFL-downloads.html

 MADE by TEAM a.r.g. : http://www.team-arg.org/About.html

 2015 - creator name (name of helpers)

 Game License: MIT : https://opensource.org/licenses/MIT
*/

#include "Arglib.h"
#include "globals.h"
#include "menu.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "stage.h"
#include "boss.h"

//determine the game
#define GAME_ID 26

typedef void (*FunctionPointer) ();
FunctionPointer mainGameLoop[] =
{
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;
  arduboy.initRandomSeed();
  gameState = STATE_MENU_INTRO;
  gameState = STATE_MENU_MAIN;
  menuSelection = STATE_MENU_PLAY;
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.clearDisplay();
  mainGameLoop[gameState]();
  arduboy.display();
};


/*

void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  switch (gameState)
  {
    case STATE_MENU_MAIN:
      break;
    case STATE_MENU_HELP: // QR code
      break;
    case STATE_MENU_INFO: // infoscreen
      break;
    case STATE_MENU_SOUNDFX: // soundconfig screen

      break;
    case STATE_MENU_PLAY:
      arduboy.clearDisplay();

      break;
    case STATE_GAME_PLAYING:

      break;
    case STATE_GAME_OVER:
      arduboy.clearDisplay();
      //arduboy.drawSprite(0, 0, gameOverSFL, 128, 64, 0, WHITE);
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.clearDisplay();
        gameState = STATE_MENU_MAIN;
      }
      break;
    case STATE_GAME_PAUSE:
      if (buttons.justPressed(B_BUTTON))
      {
        //afterPause();
        gameState = STATE_GAME_PLAYING;
      }
      break;
  }
  arduboy.display();
}

*/

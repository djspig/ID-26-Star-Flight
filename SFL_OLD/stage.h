#ifndef STAGE_H
#define STAGE_H

#include "Arglib.h"
#include "globals.h"
#include "enemies.h"
#include "boss.h"


byte groupOfThree;

byte stillStar[11][2] = {{84, 9}, {67, 14}, {109, 19}, {27, 24}, {9, 29}, {96, 34}, {31, 39}, {45, 44}, {82, 49}, {19, 54}, {57, 59}};
byte movingStar[11][2] = {{16, 5}, {125, 10}, {62, 15}, {79, 20}, {115, 25}, {104, 30}, {16, 35}, {117, 40}, {65, 45}, {98, 50}, {23, 55}};
byte fastMovingStar[11][2] = {{84, 7}, {67, 12}, {109, 17}, {27, 22}, {9, 27}, {96, 32}, {31, 37}, {45, 42}, {82, 47}, {19, 52}, {57, 57}};
boolean makeProgress = false;

const byte PROGMEM levelOne[] =
{
  /*
  0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x09, 0x00, 0x0A, 0x00, 0x0B, 0x00, 0x0C, 0x00,
  0x00, 0x00, 0x0D, 0x00, 0x0E, 0x00, 0x0F, 0x00, 0x11, 0x00,
  */
  /*
  0x00,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x11,
  */
  0x00, 0xFF,
};

void drawStarField()
{
  for (byte i = 0; i < 11; i++)
  {
    if (arduboy.everyXFrames(1))
    {
      fastMovingStar[i][0]--;
      if (fastMovingStar[i][0] < 1) fastMovingStar[i][0] = 127;
      arduboy.drawPixel(fastMovingStar[i][0], fastMovingStar[i][1], WHITE);
    }
    if (arduboy.everyXFrames(2))
    {
      movingStar[i][0]--;
      if (movingStar[i][0] < 1) movingStar[i][0] = 127;
      arduboy.drawPixel(movingStar[i][0], movingStar[i][1], WHITE);
    }
    if (arduboy.everyXFrames(3))
    {
      stillStar[i][0]--;
      if (stillStar[i][0] < 1) stillStar[i][0] = 127;
      arduboy.drawPixel(stillStar[i][0], stillStar[i][1], WHITE);
    }

  }
}

void drawScreenInfo()
{
  // life
  for (byte i = 0; i < life; i++) arduboy.drawSprite(8 + i * 6, 0, lifes_bitmaps, 5, 8, 0, WHITE);

  // score
  char buf[10];
  //scorePlayer = arduboy.cpuLoad();
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 10 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    arduboy.drawSprite(44 + (4 * i), 0, numbers_bitmaps, 3, 8, 0, WHITE);
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    arduboy.drawSprite(44 + (pad * 4) + (4 * i), 0, numbers_bitmaps, 3, 8, digit , WHITE);
  }

  //bombs
  if (bombs > 0) for (byte i = 0; i < bombs; i++) arduboy.drawSprite(115 - i * 6, 0, bombs_bitmaps, 5, 8, 0, WHITE);

  //charge
  arduboy.drawLine(8, 63, 8 + bombCharge, 63, WHITE);
}

void threeEnemies(byte enemyType, byte y)
{
  while (groupOfThree < 3)
  {
    currentEnemy++;
    if (currentEnemy > 7) currentEnemy = 0;
    enemies[currentEnemy].setEnemyType(enemyType);
    enemies[currentEnemy].y = y;
    enemies[currentEnemy].x = 128 + (20 * groupOfThree);
    enemies[currentEnemy].frontFrame += (groupOfThree);
    enemies[currentEnemy].backFrame += (groupOfThree);
    enemies[currentEnemy].isActive = true;
    groupOfThree++;
  }
  groupOfThree = 0;
}

void bossActivate(byte enemyType)
{
  endBoss.setEnemyType(enemyType);
  endBoss.isActive = true;
  //endBoss.partThreeFrame += 4;
}

void updateMap()
{
  if (arduboy.everyXFrames(120) && !atEndOfLevel)
  {
    levelProgress++;
    makeProgress = true;
  }
  switch (level)
  {
    case LEVEL_ONE:
      switch (pgm_read_byte(&levelOne[levelProgress]))
      {
        case 0x00:
          //groupOfThree = 0;
          break;
        case 0x01:
          if (makeProgress)threeEnemies(ENEMY_ONE,  8);
          break;
        case 0x02:
          if (makeProgress)threeEnemies(ENEMY_TWO,  40);
          break;
        case 0x03:
          if (makeProgress)threeEnemies(ENEMY_THREE,  32);
          break;
        case 0x04:
          if (makeProgress)threeEnemies(ENEMY_FOUR,  16);
          break;
        case 0x05:
          if (makeProgress)threeEnemies(ENEMY_FIVE,  8);
          break;
        case 0x06:
          if (makeProgress)threeEnemies(ENEMY_SIX,  40);
          break;
        case 0x07:
          if (makeProgress)threeEnemies(ENEMY_SEVEN,  32);
          break;
        case 0x08:
          if (makeProgress)threeEnemies(ENEMY_EIGHT,  16);
          break;
        case 0x09:
          if (makeProgress)threeEnemies(ENEMY_NINE,  8);
          break;
        case 0x0A:
          if (makeProgress)threeEnemies(ENEMY_TEN,  40);
          break;
        case 0x0B:
          if (makeProgress)threeEnemies(ENEMY_ELEVEN,  32);
          break;
        case 0x0C:
          if (makeProgress)threeEnemies(ENEMY_TWELVE,  16);
          break;
        case 0x0D:
          if (makeProgress)threeEnemies(ENEMY_THIRTEEN,  8);
          break;
        case 0x0E:
          if (makeProgress)threeEnemies(ENEMY_FOURTEEN,  40);
          break;
        case 0x0F:
          if (makeProgress)threeEnemies(ENEMY_FIFTEEN, 32);
          break;
        case 0x11:
          if (makeProgress)threeEnemies(ENEMY_SIXTEEN,  16);
          break;
        case 0xFF:
          atEndOfLevel = true;
          if (makeProgress) bossActivate(BOSS_SIX);
          break;
      }
      break;
    case LEVEL_TWO:
      break;
  }
  makeProgress = false;
}


#endif

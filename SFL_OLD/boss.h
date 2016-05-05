#ifndef BOSS_H
#define BOSS_H

#include "Arglib.h"
#include "globals.h"

#define BOSS_ONE           0
#define BOSS_TWO           1
#define BOSS_THREE         2
#define BOSS_FOUR          3
#define BOSS_FIVE          4
#define BOSS_SIX           5


struct Boss
{
  public:
    int x = 88;
    int y = 8;
    byte type;
    byte partOneFrame;
    byte firstPartOneFrame;
    int partOneX = 0;
    int partOneY;
    byte partTwoFrame;
    byte firstPartTwoFrame;
    int partTwoX = 0;
    int partTwoY;
    byte partThreeFrame;
    byte firstPartThreeFrame;
    int partThreeX = 0;
    int partThreeY;
    boolean isActive = false;
    boolean crashing = false;
    byte enemySpeed;
    byte HP;

    void Update()
    {
      
    }

    void setEnemyType(byte bossType)
    {
      switch (bossType)
      {
        case BOSS_ONE:
          type = 0;
          firstPartOneFrame = 32;
          partOneFrame = firstPartOneFrame;
          partOneX = -8;
          partOneY = 16;
          enemySpeed = 1;
          HP = 1;
          break;
        case BOSS_TWO:
          type = 1;
          firstPartThreeFrame = 48;
          partThreeFrame = firstPartThreeFrame;
          partThreeX = -8;
          partThreeY = 16;
          enemySpeed = 1;
          HP = 2;
          break;
        case BOSS_THREE:
          type = 2;
          firstPartOneFrame = 16;
          partOneFrame = firstPartOneFrame;
          partOneX = -8;
          partOneY = -4;
          firstPartTwoFrame = 16;
          partTwoFrame = firstPartTwoFrame;
          partTwoX = -8;
          partTwoY = 36;
          enemySpeed = 1;
          HP = 2;
          break;
        case BOSS_FOUR:
          type = 3;
          firstPartOneFrame = 40;
          partOneFrame = firstPartOneFrame;
          partOneX = 9;
          partOneY = 2;
          firstPartTwoFrame = 40;
          partTwoFrame = firstPartTwoFrame;
          partTwoX = 9;
          partTwoY = 30;
          enemySpeed = 1;
          HP = 1;
          break;
        case BOSS_FIVE:
          type = 4;
          firstPartOneFrame = 48;
          partOneFrame = firstPartOneFrame;
          partOneX = 3;
          partOneY = 16;
          firstPartTwoFrame = 48;
          partTwoFrame = firstPartTwoFrame;
          partTwoX = 11;
          partTwoY = 16;
          firstPartThreeFrame = 48;
          partThreeFrame = firstPartThreeFrame;
          partThreeX = 19;
          partThreeY = 16;
          enemySpeed = 1;
          HP = 1;
          break;
        case BOSS_SIX:
          type = 5;
          firstPartOneFrame = 48;
          partOneFrame = firstPartOneFrame;
          partOneX = 8;
          partOneY = -3;
          firstPartTwoFrame = 48;
          partTwoFrame = firstPartTwoFrame;
          partTwoX = 8;
          partTwoY = 35;
          firstPartThreeFrame = 32;
          partThreeFrame = firstPartThreeFrame;
          partThreeX = -8;
          partThreeY = 16;
          enemySpeed = 1;
          HP = 1;
          break;
      }
    }
};

Boss endBoss;

void drawBoss()
{
  if (arduboy.everyXFrames(1))
  {
    if (endBoss.isActive)
    {
      if (arduboy.everyXFrames(4))
      {
        endBoss.partOneFrame++;
        endBoss.partTwoFrame++;
        endBoss.partThreeFrame++;
      }
      if (endBoss.partOneFrame > (7 + endBoss.firstPartOneFrame)) endBoss.partOneFrame = endBoss.firstPartOneFrame;
      if (endBoss.partTwoFrame > (7 + endBoss.firstPartTwoFrame)) endBoss.partTwoFrame = endBoss.firstPartTwoFrame;
      if (endBoss.partThreeFrame > (7 + endBoss.firstPartThreeFrame)) endBoss.partThreeFrame = endBoss.firstPartThreeFrame;
      if (!endBoss.crashing) arduboy.drawSprite(endBoss.x, endBoss.y, boss_bitmaps, 32, 48, endBoss.type, WHITE);
      if (endBoss.partOneX != 0) arduboy.drawSprite(endBoss.x+endBoss.partOneX, endBoss.y+endBoss.partOneY, enemy_bitmaps, 8, 16, endBoss.partOneFrame, WHITE);
      if (endBoss.partTwoX != 0) arduboy.drawSprite(endBoss.x+endBoss.partTwoX, endBoss.y+endBoss.partTwoY, enemy_bitmaps, 8, 16, endBoss.partTwoFrame, WHITE);
      if (endBoss.partThreeX != 0) arduboy.drawSprite(endBoss.x+endBoss.partThreeX, endBoss.y+endBoss.partThreeY, enemy_bitmaps, 8, 16, endBoss.partThreeFrame, WHITE);
    }
  }
}


#endif

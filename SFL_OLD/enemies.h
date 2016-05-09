#ifndef ENEMIES_H
#define ENEMIES_H

#include "Arglib.h"
#include "globals.h"

#define ENEMY_ONE           0
#define ENEMY_TWO           1
#define ENEMY_THREE         2
#define ENEMY_FOUR          3
#define ENEMY_FIVE          4
#define ENEMY_SIX           5
#define ENEMY_SEVEN         6
#define ENEMY_EIGHT         7
#define ENEMY_NINE          8
#define ENEMY_TEN           9
#define ENEMY_ELEVEN        10
#define ENEMY_TWELVE        11
#define ENEMY_THIRTEEN      12
#define ENEMY_FOURTEEN      13
#define ENEMY_FIFTEEN       14
#define ENEMY_SIXTEEN       15


byte currentEnemy;

struct Enemy
{
  public:
    int x = 136;
    int y = 24;
    byte frontFrame;
    byte firstFrontFrame;
    byte backFrame;
    byte firstBackFrame;
    boolean isActive = false;
    boolean crashing = false;
    byte enemySpeed;
    byte HP;

    void Update()
    {
      if (isActive)
      {
        if (x < -16)
        {
          isActive = false;
          x = 136;
        }
        x -= enemySpeed;
      }
    }

    void setEnemyType(byte enemyType)
    {
      switch (enemyType)
      {
        case ENEMY_ONE:
          firstFrontFrame = 0;
          frontFrame = firstFrontFrame;
          firstBackFrame = 8;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_TWO:
          firstFrontFrame = 0;
          frontFrame = firstFrontFrame;
          firstBackFrame = 24;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 2;
          break;
        case ENEMY_THREE:
          firstFrontFrame = 0;
          frontFrame = firstFrontFrame;
          firstBackFrame = 40;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_FOUR:
          firstFrontFrame = 0;
          frontFrame = firstFrontFrame;
          firstBackFrame = 56;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
          
        case ENEMY_FIVE:
          firstFrontFrame = 16;
          frontFrame = firstFrontFrame;
          firstBackFrame = 8;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_SIX:
          firstFrontFrame = 16;
          frontFrame = firstFrontFrame;
          firstBackFrame = 24;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_SEVEN:
          firstFrontFrame = 16;
          frontFrame = firstFrontFrame;
          firstBackFrame = 40;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;      
        case ENEMY_EIGHT:
          firstFrontFrame = 16;
          frontFrame = firstFrontFrame;
          firstBackFrame = 56;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
          
        case ENEMY_NINE:
          firstFrontFrame = 32;
          frontFrame = firstFrontFrame;
          firstBackFrame = 8;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_TEN:
          firstFrontFrame = 32;
          frontFrame = firstFrontFrame;
          firstBackFrame = 24;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_ELEVEN:
          firstFrontFrame = 32;
          frontFrame = firstFrontFrame;
          firstBackFrame = 40;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_TWELVE:
          firstFrontFrame = 32;
          frontFrame = firstFrontFrame;
          firstBackFrame = 56;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
          
        case ENEMY_THIRTEEN:
          firstFrontFrame = 48;
          frontFrame = firstFrontFrame;
          firstBackFrame = 8;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_FOURTEEN:
          firstFrontFrame = 48;
          frontFrame = firstFrontFrame;
          firstBackFrame = 24;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_FIFTEEN:
          firstFrontFrame = 48;
          frontFrame = firstFrontFrame;
          firstBackFrame = 40;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
        case ENEMY_SIXTEEN:
          firstFrontFrame = 48;
          frontFrame = firstFrontFrame;
          firstBackFrame = 56;
          backFrame = firstBackFrame;
          enemySpeed = 1;
          HP = 1;
          break;
      }
    }
};

Enemy enemies[8];

void drawEnemyShips()
{
  if (arduboy.everyXFrames(1))
  {
    for (byte i = 0; i < 8; i++)
    {
      if (enemies[i].isActive)
      {
        if (arduboy.everyXFrames(4))
        {
          enemies[i].frontFrame++;
          enemies[i].backFrame++;
        }
        if (enemies[i].frontFrame > (7 + enemies[i].firstFrontFrame)) enemies[i].frontFrame = enemies[i].firstFrontFrame;
        if (enemies[i].backFrame > (7 + enemies[i].firstBackFrame))enemies[i].backFrame = enemies[i].firstBackFrame;
        enemies[i].Update();
        if (!enemies[i].crashing)
        {
          arduboy.drawSprite(enemies[i].x, enemies[i].y, enemy_bitmaps, 8, 16, enemies[i].frontFrame, WHITE);
          arduboy.drawSprite(enemies[i].x+8, enemies[i].y, enemy_bitmaps, 8, 16, enemies[i].backFrame, WHITE);
        }
        if (enemies[i].crashing)
        {
          arduboy.drawSprite(enemies[i].x, enemies[i].y, shipMask_bitmaps, 8, 16, enemies[i].frontFrame, BLACK);
          arduboy.drawSprite(enemies[i].x, enemies[i].y, ship_bitmaps, 8, 16, enemies[i].frontFrame, WHITE);
        }
      }
    }
  }
}
#endif

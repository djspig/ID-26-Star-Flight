#ifndef PLAYER_H
#define PLAYER_H

#define WEAPON_CANON             0
#define WEAPON_WAVE              1
#define WEAPON_ROCKETS           2

#include <Arduino.h>
#include "globals.h"

struct Players
{
  public:
    int x;
    int y;
    byte weaponType = WEAPON_CANON;
    boolean isActive = true;
    boolean isImune = false;
    boolean crashing = false;
    byte imuneTimer;
    byte life;
    int frame;
    

    void set()
    {
      x = 8;
      y = 24;
      frame = 2;
      isImune = true;
      isActive = true;
      imuneTimer = 60;
      crashing = false;
    }
};

Players spaceShip;


void drawSpaceShip()
{
  //if (spaceShip.isActive)
  sprites.drawPlusMask(spaceShip.x, spaceShip.y, spaceShip_plus_mask, spaceShip.frame);
}

void checkIfShipIsImune()
{
  if (spaceShip.isImune)
  {
    if (arduboy.everyXFrames(3)) spaceShip.isActive = !spaceShip.isActive;
    spaceShip.imuneTimer--;
    if (spaceShip.imuneTimer < 1)
    {
      spaceShip.isImune = false;
      spaceShip.isActive = true;
    }
  }
}



#endif

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
    byte frame;
    

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



#endif

#ifndef PLAYER_H
#define PLAYER_H

#define WEAPON_BULLET            0
#define WEAPON_ROCKETS           1
#define WEAPON_WAVE              2

#define MAX_WEAPON_TYPES         3
#define MAX_AMOUNT_BULLETS       6

#define DAMAGE_BULLET            1
#define DAMAGE_ROCKETS           2
#define DAMAGE_WAVE              4

#define FUSE_BULLET              25
#define FUSE_ROCKETS             50
#define FUSE_WAVE                50

#define SPEEDY_BULLET            3
#define SPEEDY_ROCKETS           1
#define SPEEDY_WAVE              2

#include <Arduino.h>
#include "globals.h"

byte currentBullet;

const unsigned char PROGMEM bulletDamage[] = {
  DAMAGE_BULLET, DAMAGE_ROCKETS, DAMAGE_WAVE,
  FUSE_BULLET, FUSE_ROCKETS, FUSE_WAVE,
  SPEEDY_BULLET, SPEEDY_ROCKETS, SPEEDY_WAVE,
};

struct Players
{
  public:
    int x;
    int y;
    byte weaponType = WEAPON_BULLET;
    boolean isActive = true;
    boolean isImune = false;
    boolean crashing = false;
    byte imuneTimer;
    byte life;
    int frame;
    byte bombs;
    byte currentBullet;


    void set()
    {
      x = 8;
      y = 24;
      frame = 2;
      isImune = true;
      isActive = true;
      imuneTimer = 60;
      crashing = false;
      currentBullet = 0;
    }
};

struct PlayerShot
{
  public:
    byte x;
    byte y;
    byte damage;
    boolean isVisible = false;
    byte type;
    byte frame;
    int speedY;
    byte fuse;

    void set(byte weaponType)
    {
      type = weaponType;
      damage = pgm_read_word (&bulletDamage[weaponType]);
      fuse = pgm_read_word (&bulletDamage[weaponType + MAX_WEAPON_TYPES]);
      speedY = pgm_read_word (&bulletDamage[weaponType + (2 * MAX_WEAPON_TYPES)]);
    }
};

Players spaceShip;
PlayerShot bullets[MAX_AMOUNT_BULLETS];

void schoot()
{
  bullets[spaceShip.currentBullet].set(
}





void drawSpaceShip()
{
  if (spaceShip.isActive) sprites.drawPlusMask(spaceShip.x, spaceShip.y, spaceShip_plus_mask, spaceShip.frame);
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

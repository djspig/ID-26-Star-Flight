#ifndef PLAYER_H
#define PLAYER_H

#define WEAPON_CANON             0
#define WEAPON_WAVE              1
#define WEAPON_ROCKETS           2

#include "Arglib.h"

byte currentBullet;
byte currentWeapon;
byte testWeapon = 0;
int bombs;
byte bombCharge = 1;

struct SpaceShip
{
  public:
    int x, y;
    int frame;
    boolean isImune = false;
    boolean showShip = true;
    boolean crashing = false;
    byte imuneTimer;
    byte width = 16;
    byte height = 16;


    void reset()
    {
      x = 8;
      y = 24;
      frame = 2;
      isImune = true;
      showShip = true;
      imuneTimer = 60;
      crashing = false;
    }
};

struct Bomb
{
  public:
    byte x, y;
    int offsetY;
    byte fuse = 35;
    byte maxFuse = 35;
    byte damage = 20;
    byte bombFrame = 0;
    boolean isActive = false;
    boolean bombExplode = false;

    void Update()
    {
      if (isActive)
      {
        fuse--;
        if ((fuse == 0) || (x > 120))
        {
          isActive = false;
          fuse = maxFuse;
          bombExplode = true;
        }
        x += 2;
      }
    }
};


struct Bullet
{
  public:
    byte x;
    int y;
    int offsetY;
    byte width;
    byte height;
    byte fuse;
    byte damage;
    byte frame;
    byte bulletSpeed;
    byte type;
    boolean isActive = false;

    void Update()
    {
      if (isActive)
      {
        fuse--;
        if ((fuse == 0) || (x > 126) || (damage < 1))
        {
          isActive = false;
        }
        x += bulletSpeed;
      }
    }

    void setWeaponType(byte weaponType)
    {
      switch (weaponType)
      {
        case WEAPON_CANON:
          type = 0;
          offsetY = -4;
          width = 8;
          height = 16;
          fuse = 25;
          frame = 4;
          bulletSpeed = 3;
          damage = 1;
          break;
        case WEAPON_WAVE:
          type = 1;
          offsetY = -2;
          width = 16;
          height = 8;
          fuse = 50;
          frame = 7;
          bulletSpeed = 2;
          damage = 2;
          break;
        case WEAPON_ROCKETS:
          type = 2;
          offsetY = 0;
          width = 16;
          height = 8;
          fuse = 50;
          frame = 0;
          bulletSpeed = 1;
          damage = 4;
          break;
      }
    }
};

Bullet playerShot[6];
Bomb playerBomb;
SpaceShip playerShip;

void shoot()
{
  currentBullet++;
  if (currentBullet > 5) currentBullet = 0;
  playerShot[currentBullet].setWeaponType(currentWeapon);
  playerShot[currentBullet].isActive = true;
  playerShot[currentBullet].x = playerShip.x + 12;
  playerShot[currentBullet].y = playerShip.y + 6 + playerShot[currentBullet].offsetY;
}

void checkInputs()
{
  if (buttons.pressed(RIGHT_BUTTON) && !playerShip.crashing)
  {
    if (playerShip.x < 112) playerShip.x++;
  }
  if (buttons.pressed(LEFT_BUTTON) && !playerShip.crashing)
  {
    if (playerShip.x > 0) playerShip.x--;
  }
  if (buttons.pressed(UP_BUTTON) && !playerShip.crashing)
  {
    if (playerShip.y > -6) playerShip.y--;
    if (arduboy.everyXFrames(9)) playerShip.frame--;
    if (playerShip.frame < 0)playerShip.frame = 0;
  }
  if (buttons.pressed(DOWN_BUTTON) && !playerShip.crashing)
  {
    if (playerShip.y < 55) playerShip.y++;
    if (arduboy.everyXFrames(9)) playerShip.frame++;
    if (playerShip.frame  > 4)playerShip.frame = 4;
  }
  if (buttons.justPressed(B_BUTTON) && !playerShip.crashing)
  {
    shoot();
    if (arduboy.everyXFrames(1) && (bombCharge > 1))bombCharge--;
  }

  if (buttons.pressed(B_BUTTON) && !playerShip.crashing && (bombCharge < 120) && !playerBomb.isActive && (bombs > 0))
  {
    if (arduboy.everyXFrames(1))bombCharge++;
  }
  if (buttons.notPressed(B_BUTTON) && (bombCharge > 1))
  {
    if (arduboy.everyXFrames(1))bombCharge--;
  }

  if (bombCharge > 119)
  {
    bombCharge = 1;
    playerBomb.isActive = true;
    bombs--;
    if (bombs < 0) bombs = 0;
  }
  if (buttons.justPressed(A_BUTTON) && !playerShip.crashing)
  {
    testWeapon++;
    if (testWeapon > 2) testWeapon = 0;
    currentWeapon = testWeapon;
    //gameState = STATE_GAME_PAUSE;
  }
  if (buttons.notPressed(UP_BUTTON) && buttons.notPressed(DOWN_BUTTON) && !playerShip.crashing)
  {
    if (arduboy.everyXFrames(12))
    {
      if (playerShip.frame > 2)
        playerShip.frame--;
      if (playerShip.frame < 2)
        playerShip.frame++;
    }
  }
  if (playerShip.crashing) playerShip.frame++;
}

void drawPlayerShip()
{
  if (playerShip.showShip)
  {
    arduboy.drawSprite(playerShip.x, playerShip.y, shipMask_bitmaps, playerShip.width, playerShip.height, playerShip.frame, BLACK);
    arduboy.drawSprite(playerShip.x, playerShip.y, ship_bitmaps, playerShip.width, playerShip.height, playerShip.frame, WHITE);
  }
  if (playerShip.crashing)
  {
    arduboy.drawSprite(playerShip.x, playerShip.y, shipMask_bitmaps, playerShip.width, playerShip.height, playerShip.frame, BLACK);
    arduboy.drawSprite(playerShip.x, playerShip.y, ship_bitmaps, playerShip.width, playerShip.height, playerShip.frame, WHITE);
  }

}

void drawBullets()
{
  if (arduboy.everyXFrames(1))
  {
    for (byte i = 0; i < 6; i++)
    {
      if (playerShot[i].isActive)
      {
        switch (playerShot[i].type)
        {
          case WEAPON_CANON:
            if (playerShip.frame == 2) playerShot[i].frame = 4;
            if ((playerShip.frame == 3) || (playerShip.frame == 1)) playerShot[i].frame = 5;
            if ((playerShip.frame == 4) || (playerShip.frame == 0)) playerShot[i].frame = 6;
            break;
          case WEAPON_WAVE:
            playerShot[i].frame++;
            if (playerShot[i].frame > 13) playerShot[i].frame = 7;
            break;
          case WEAPON_ROCKETS:
            if (playerShot[i].fuse == 40) playerShot[i].bulletSpeed += 2;
            if (playerShot[i].fuse == 35) playerShot[i].bulletSpeed += 2;
            if (playerShot[i].fuse == 30) playerShot[i].bulletSpeed++;
            playerShot[i].frame++;
            if (playerShot[i].frame > 3) playerShot[i].frame = 0;
            break;

        }
        playerShot[i].Update();
        arduboy.drawSprite(playerShot[i].x, playerShot[i].y, bullet_bitmaps, playerShot[i].width, playerShot[i].height, playerShot[i].frame, WHITE);
      }
    }
  }
}

void drawBomb()
{
  if (!playerBomb.isActive)
  {
    playerBomb.x = playerShip.x + 12;
    playerBomb.y = playerShip.y + 4;
  }
  if (arduboy.everyXFrames(3))
  {
    playerBomb.bombFrame++;
    if (playerBomb.bombFrame > 5) playerBomb.bombFrame = 0;
    playerBomb.Update();
  }
  if (playerBomb.isActive)arduboy.drawSprite(playerBomb.x, playerBomb.y, bomb_bitmaps, 8, 8, playerBomb.bombFrame, WHITE);
  if (playerBomb.bombExplode)
  {
    arduboy.fillScreen(WHITE);
    playerBomb.bombExplode = false;
  }
}


void checkIfShipIsImune()
{
  if (playerShip.isImune)
  {
    if (arduboy.everyXFrames(3)) playerShip.showShip = !playerShip.showShip;
    playerShip.imuneTimer--;
    if (playerShip.imuneTimer < 1)
    {
      playerShip.isImune = false;
      playerShip.showShip = true;
    }
  }
}



#endif

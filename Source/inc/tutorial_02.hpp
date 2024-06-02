/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#pragma once

#include <tyra>


using Tyra::Pad;

namespace Tyra {

class Tutorial02 : public Game {
 public:
  Tutorial02(Engine* engine);
  ~Tutorial02();

  void init();
  void loop();

 private:
  void loadTexture();
  void loadSprite();
  
  void loadTexture2();
  void loadSprite2();

  void loadBgTexture();
  void loadBgSprite();

  void loadBulletSprite();
  void loadBulletTexture();
  void resetBullet();

  bool checkCollisionBoxBox(Vec2 playerPos,Vec2 playerSize,Vec2 bulletPos,Vec2 bulletSize);

  int bulletX,bulletY;
  Vec2 bulletSpeed;
  bool bulletShooted;

  int player1Dir;
  int cubeX;
  int cubeY;

  int cube2X;
  int cube2Y;
  int player2Dir;

  const int PlayerSpeed = 3;

  int whoWin = 0;

  Pad* pad;

  Engine* engine;

  Sprite sprite;
  Sprite sprite2;

  Sprite bg;

  Sprite bullet;

  Sprite hud1;
  Sprite hud2;

  Sprite bar1;
  Sprite bar2;

  Sprite win1;
  Sprite win2;

  int whoShooted;
  int player1Health,player2Heath;

  //hud
  void loadHud1Sprite();
  void loadHud1Texture();

  void loadHud2Sprite();
  void loadHud2Texture();

  void loadHealthBar1Sprite();
  void loadHealthBar1Texture();

  void loadHealthBar2Sprite();
  void loadHealthBar2Texture();

  void loadWin1Sprite();
  void loadWin1Texture();

  void loadWin2Sprite();
  void loadWin2Texture();
  //(0 = down) (1 = up) (2 = left) (3 = right)
};

}  // namespace Tyra

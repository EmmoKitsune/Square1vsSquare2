/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include <tyra>
#include "tutorial_02.hpp"

namespace Tyra {

Tutorial02::Tutorial02(Engine* t_engine) : engine(t_engine) {
  pad = &engine->pad;
}

Tutorial02::~Tutorial02() {
  engine->renderer.getTextureRepository().freeBySprite(sprite);
}

void Tutorial02::init() {
  engine->renderer.setClearScreenColor(Color(32.0F, 32.0F, 32.0F));
  cubeX = 0;
  cubeY = 100;

  cube2X = 300;
  cube2Y = 100;

  bulletShooted = false;
  whoShooted = 0;

  player1Health = 5;
  player2Heath = 5;

  /** Sprite contains rectangle information. */
  loadSprite();
  loadSprite2();

  loadBgSprite();
  loadBulletSprite();

  loadHud1Sprite();
  loadHud2Sprite();
  loadHealthBar1Sprite();
  loadHealthBar2Sprite();

  loadWin1Sprite();
  loadWin2Sprite();

  /** Texture contains png image. */
  loadTexture();
  loadBgTexture();

  loadTexture2();

  loadBulletTexture();

  loadHud1Texture();
  loadHud2Texture();

  loadHealthBar1Texture();
  loadHealthBar2Texture();
  
  loadWin1Texture();
  loadWin2Texture();
}

void Tutorial02::loop() {
  auto& renderer = engine->renderer;

  sprite2.position=Vec2(cubeX,cubeY);
  sprite.position =Vec2(cube2X,cube2Y);
  bullet.position =Vec2(bullet.position.x += bulletSpeed.x,bullet.position.y += bulletSpeed.y);
  bulletX = bullet.position.x;
  bulletY = bullet.position.y;

  if(pad->getLeftJoyPad().h <= 100 && cubeX > 0){
    cubeX -= PlayerSpeed;
    player1Dir = 3;
  }

  if(pad->getLeftJoyPad().h >= 200 && cubeX < engine->renderer.core.getSettings().getWidth() - 32.0f){
    cubeX += PlayerSpeed;
    player1Dir = 2;
  }

  if(pad->getLeftJoyPad().v <= 100 && cubeY > 0){
    cubeY -= PlayerSpeed;
    player1Dir = 1;
  }

  if(pad->getLeftJoyPad().v >= 200 && cubeY < engine->renderer.core.getSettings().getHeight() - 32.0f){
    cubeY += PlayerSpeed;
    player1Dir = 0;
  }

  //Player 2 movement

  if(pad->getRightJoyPad().h <= 100 && cube2X > 0){
    cube2X -= PlayerSpeed;
    player2Dir = 3;
  }

  if(pad->getRightJoyPad().h >= 200 && cube2X < engine->renderer.core.getSettings().getWidth() - 32.0f){
    cube2X += PlayerSpeed;
    player2Dir = 2;
  }

  if(pad->getRightJoyPad().v <= 100 && cube2Y > 0){
    cube2Y -= PlayerSpeed;
    player2Dir = 1;
  }

  if(pad->getRightJoyPad().v >= 200 && cube2Y < engine->renderer.core.getSettings().getHeight() - 32.0f){
    cube2Y += PlayerSpeed;
    player2Dir = 0;
  }

  //Shoot
  if(bulletX < 0){
    resetBullet();
  }
  if(bulletY < 0){
    resetBullet();
  }
  if(bulletX > engine->renderer.core.getSettings().getWidth()){
    resetBullet();
  }
  if(bulletY > engine->renderer.core.getSettings().getHeight()){
    resetBullet();
  }

  //Collisions...
  switch (whoShooted)
  {
    case 1:
      if(checkCollisionBoxBox(Vec2(bulletX,bulletY),bullet.size,Vec2(cube2X,cube2Y),sprite2.size)){
        resetBullet();
        player2Heath -= 1;
        bar2.size.x -= 22.4f;
      }
      break;
    case 2:
      if(checkCollisionBoxBox(Vec2(bulletX,bulletY),bullet.size,Vec2(cubeX,cubeY),sprite.size)){
        resetBullet();
        player1Health -= 1;
        bar1.size.x -= 22.4f;
      }
      break;

    default:
      break;
  }

  if(player1Health <= 0){
    whoWin = 2;
    player1Health = 0;
  }
  if(player2Heath <= 0){
    whoWin = 1;
    player2Heath = 0;
  }

  if(pad->getPressed().L2){
    if(!bulletShooted){
      switch (player1Dir)
      {
      case 0:
          whoShooted = 1;
          bulletSpeed = Vec2(0,2.5f);
          bulletShooted = true;
          bullet.position.x = cubeX;
          bullet.position.y = cubeY;
          break;
      case 1:
          whoShooted = 1;
          bulletSpeed = Vec2(0,-2.5f);
          bulletShooted = true;
          bullet.position.x = cubeX;
          bullet.position.y = cubeY;
          break;
      case 2:
        whoShooted = 1;
        bulletSpeed = Vec2(2.5f,0);
        bulletShooted = true;
        bullet.position.x = cubeX;
        bullet.position.y = cubeY;
        break;
      case 3:
        whoShooted = 1;
        bulletSpeed = Vec2(-2.5f,0);
        bulletShooted = true;
        bullet.position.x = cubeX;
        bullet.position.y = cubeY;
        break;
      
      default:
        break;
      }
    }
  }
  if(pad->getPressed().R2){
    if(!bulletShooted){
      switch (player2Dir)
      {
      case 0:
          whoShooted = 2;
          bulletSpeed = Vec2(0,2.5f);
          bulletShooted = true;
          bullet.position.x = cube2X;
          bullet.position.y = cube2Y;
          break;
      case 1:
          whoShooted = 2;
          bulletSpeed = Vec2(0,-2.5f);
          bulletShooted = true;
          bullet.position.x = cube2X;
          bullet.position.y = cube2Y;
          break;
      case 2:
        whoShooted = 2;
        bulletSpeed = Vec2(2.5f,0);
        bulletShooted = true;
        bullet.position.x = cube2X;
        bullet.position.y = cube2Y;
        break;
      case 3:
        whoShooted = 2;
        bulletSpeed = Vec2(-2.5f,0);
        bulletShooted = true;
        bullet.position.x = cube2X;
        bullet.position.y = cube2Y;
        break;
      
      default:
        break;
      }
    }
  }

  /** Begin frame will clear our screen. */
  renderer.beginFrame();

  /** Render sprite. */
  renderer.renderer2D.render(bg);
  renderer.renderer2D.render(sprite);
  renderer.renderer2D.render(sprite2);
  renderer.renderer2D.render(bullet);
  renderer.renderer2D.render(hud1);
  renderer.renderer2D.render(hud2);
  renderer.renderer2D.render(bar1);
  renderer.renderer2D.render(bar2);
  
  switch (whoWin)
  {
  case 1:
    renderer.renderer2D.render(win1);
    break;
  
  case 2:
    renderer.renderer2D.render(win2);
    break;
  default:
    break;
  }
  /** End frame will perform vsync. */
  renderer.endFrame();
}

void Tutorial02::loadSprite() {
  sprite.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  sprite.size = Vec2(32.0F, 32.0F);

  /** Set it in screen center */
  sprite.position =
      Vec2(200 - sprite.size.x / 2.0F,
           200 - sprite.size.y / 2.0F);

  TYRA_LOG("Sprite created!");
}

void Tutorial02::loadSprite2() {
  sprite2.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  sprite2.size = Vec2(32.0F, 32.0F);

  /** Set it in screen center */
  sprite2.position =
      Vec2(100 - sprite2.size.x / 2.0F,
           100 - sprite2.size.y / 2.0F);

  TYRA_LOG("Sprite created!");
}

void Tutorial02::loadTexture() {

  auto& renderer = engine->renderer;

  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("CubeBLACK.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(sprite.id);
  TYRA_LOG("black cube loaded");
  TYRA_LOG(sprite.id);
}

void Tutorial02::loadTexture2(){

  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("CubeWhite.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(sprite2.id);

  TYRA_LOG("white cube loaded");
  TYRA_LOG(sprite2.id);
}

void Tutorial02::loadBgTexture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("background.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(bg.id);

  TYRA_LOG("bg loaded");
  TYRA_LOG(bg.id);
}

void Tutorial02::loadBgSprite(){
  const auto& screenSettings = engine->renderer.core.getSettings();
  bg.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  bg.size = Vec2(screenSettings.getWidth(), screenSettings.getHeight());

  /** Set it in screen center */
  bg.position =
      Vec2(0,0);

  TYRA_LOG("Sprite created!");
}

void Tutorial02::loadBulletSprite(){
  bullet.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  bullet.size = Vec2(32.0F, 32.0F);

  /** Set it in screen center */
  bullet.position =
      Vec2(1000 - bullet.size.x / 2.0F,
           1000 - bullet.size.y / 2.0F);
  TYRA_LOG("Sprite created!");
}

void Tutorial02::loadBulletTexture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("Bullet.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(bullet.id);
  TYRA_LOG("bullet loaded");
  TYRA_LOG(bullet.id);
}

void Tutorial02::loadHud1Texture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("hud1.png");
  auto* texture = textureRepository.add(filepath);

  texture->addLink(hud1.id);

  TYRA_LOG("hud1 loaded");
  TYRA_LOG(hud1.id);
}

void Tutorial02::loadHud1Sprite(){
  hud1.mode = SpriteMode::MODE_STRETCH;

  const auto& screenSettings = engine->renderer.core.getSettings();

  /** Let's scale it down */
  hud1.size = Vec2(screenSettings.getWidth()/2.3f - 1.0f,screenSettings.getHeight()/2.3f - 1.0f);

  /** Set it in screen center */
  hud1.position =
      Vec2(screenSettings.getWidth()/1.7f,0);
  TYRA_LOG("Sprite created!");
}

void Tutorial02::loadHud2Sprite(){
  const auto& screenSettings = engine->renderer.core.getSettings();
  hud2.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  hud2.size = Vec2(screenSettings.getWidth()/2.3f - 1.0f,screenSettings.getHeight()/2.3f - 1.0f);

  /** Set it in screen center */
  hud2.position = Vec2(0,0);
  TYRA_LOG("Sprite created!");
}

void Tutorial02::loadHud2Texture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("hud2.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(hud2.id);

  TYRA_LOG("hud2 loaded");
  TYRA_LOG(hud2.id);
}

void Tutorial02::loadHealthBar1Sprite(){
  bar1.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  bar1.size = Vec2(112,16);

  /** Set it in screen center */
  bar1.position = Vec2(75,32);
  TYRA_LOG("Sprite created!"); 
}

void Tutorial02::loadHealthBar1Texture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("Health.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(bar1.id);

  TYRA_LOG("bar1 loaded");
  TYRA_LOG(bar1.id); 
}

void Tutorial02::loadHealthBar2Sprite(){
  const auto& screenSettings = engine->renderer.core.getSettings();
  bar2.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  bar2.size = Vec2(112,16);

  /** Set it in screen center */
  bar2.position = Vec2(screenSettings.getWidth() - 176,32);
  TYRA_LOG("Sprite created!");  
}

void Tutorial02::loadHealthBar2Texture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("Health.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(bar2.id);

  TYRA_LOG("bar2 loaded");
  TYRA_LOG(bar2.id); 
}

void Tutorial02::loadWin1Sprite(){
  const auto& screenSettings = engine->renderer.core.getSettings();
  win1.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  win1.size = Vec2(128,128);

  /** Set it in screen center */
  win1.position = Vec2(200,100);
  TYRA_LOG("Sprite created!");    
}

void Tutorial02::loadWin2Sprite(){
  const auto& screenSettings = engine->renderer.core.getSettings();
  win2.mode = SpriteMode::MODE_STRETCH;

  /** Let's scale it down */
  win2.size = Vec2(128,128);

  /** Set it in screen center */
  win2.position = Vec2(200,100);
  TYRA_LOG("Sprite created!");    
}

void Tutorial02::loadWin1Texture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("1wins.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(win1.id);

  TYRA_LOG("win1 loaded");
  TYRA_LOG(win1.id); 
}

void Tutorial02::loadWin2Texture(){
  auto& renderer = engine->renderer;
  auto& textureRepository = renderer.getTextureRepository();

  auto filepath = FileUtils::fromCwd("2wins.png");

  auto* texture = textureRepository.add(filepath);

  texture->addLink(win2.id);

  TYRA_LOG("win2 loaded");
  TYRA_LOG(win2.id); 
}

void Tutorial02::resetBullet(){
  bulletShooted = false;
  bullet.position = Vec2(1000,1000);
  bulletSpeed = Vec2(0,0);
  whoShooted = 0;
}

bool Tutorial02::checkCollisionBoxBox(Vec2 playerPos,Vec2 playerSize,Vec2 bulletPos,Vec2 bulletSize){
  if((playerPos.x + playerSize.x) > bulletPos.x && (playerPos.x - playerSize.x) < bulletPos.x
    && (playerPos.y + playerSize.y) > bulletPos.y && (playerPos.y - playerSize.y) < bulletPos.y){
      return true;
    }else{
      return false;
    }
}

}  // namespace Tyra

#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Hole.h"
#include "Wall.h"


class Ball
{
private:
 Sprite ball;
public:
 Vector2f position;
 Vector2f velocity;
 bool moving;
 Col color;
 bool visible;
 Ball(Vector2f const& Pos, Item & I, Col c);
 void update();
 void draw(RenderWindow & w);
 void onShoot(float & p, float r);
 void handleBallInHole(Hole const& h);
 void collideWith(Ball & B);
 void collideWith2(Wall & w);
};

class Snooker: public Ball
{
public:
  Snooker();
  bool correct_hit();
  void if_wrong_hit(bool);
};

class Eight_Ball: public Ball
{
public:
  Eight_Ball();

private:
  bool last_ball();
};

class plain_ball: public Ball
{
public:
  plain_ball();

private:
  int player;
};

class spot_ball: public Ball
{
public:
  spot_ball();

private:
  int player;
};

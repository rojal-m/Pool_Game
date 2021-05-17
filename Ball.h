#pragma once
#include <SFML/Graphics.hpp>


class Ball
{
  public:
    Ball(Texture& t);
    void update();
    void draw(RenderWindow& w);
    void onShoot(float&p,float r);

private:
    Sprite ball;
    Vector2f ball_position;
    Vector2f velocity;
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

class Stick
{
public:
  float power;
  Stick(Texture& t,Ball & b);

  void update(Event::MouseMoveEvent & v);
  void draw(RenderWindow& w);
  void updateRotation(Event::MouseMoveEvent & v);
  void increasePower();
  void shoot();

private:
  Sprite stick;
  Vecror2f ball_position;
  float rotation;
  Ball& Wball;
};

class Hole
{
public:
  Hole(Texture& t, Ball & b);
  bool is_in(Ball& b);
  void if_in(bool x);

private:
  Vector2i position;
};

class Wall
{
public:
  Wall(Texture & t);
  bool is_hit();
  void if_hit(bool y);

private:
  double length;
  Vector2i position;
};

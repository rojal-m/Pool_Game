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
bool is_in(Ball& b);
void if_in(bool x);

private:
  Vector2i position;

};

class Wall
{
public:
  bool is_hit();
  void if_hit(bool y);


private:
  double length;
  Vector2i position;

};

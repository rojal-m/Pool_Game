#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <string>
#include "constants.h"
#include "Hole.h"
#include "Wall.h"

class Ball
{
protected:
  sf::Sprite ball{};
  sf::Sound collide{};
  sf::Sound hole{};
  sf::Sound side{};

public:
  sf::Vector2f position;
  Id id;
  Col color;
  float mass;
  sf::Vector2f velocity;
  bool moving;
  bool visible;
  bool ballInHand{false};


  Ball(float, float, Id, Col, float);
  virtual ~Ball () = default;
  void update();
  void draw(sf::RenderWindow &);
  bool handleBallInHole(Hole const&);
  bool collideWith(Ball &);
  bool collideWith(Wall &);
  void load_data();
  virtual void onShoot(float, float);
};

template<typename T>
float dot(sf::Vector2<T> const& Left, sf::Vector2<T> const& Right)
{
  return Left.x * Right.x + Left.y * Right.y;
}

template<typename T>
float length(sf::Vector2<T> const& v)
{
  return sqrt(powf(v.x,2)+powf(v.y,2));
}

template<typename T>
float distFrom(sf::Vector2<T> const& Left, sf::Vector2<T> const& Right)
{
  return length(Left - Right);
}

class W_Ball : public Ball
{
public:
  W_Ball(float, float, Id);
  void onShoot(float, float) override;
};

class B_Ball : public Ball
{
public:
  B_Ball(float, float, Id);
};

class Stripes : public Ball
{
public:
  Stripes(float, float, Id);
};

class Solids : public Ball
{
public:
  Solids(float, float, Id);
};

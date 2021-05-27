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
  sf::Vector2f position{};
  Id id;
  Col color;
  sf::Vector2f velocity;
  bool moving;
  bool visible;
  bool ballInHand{false};


  Ball(Id i, Col c);
  void update();
  void draw(sf::RenderWindow &);
  bool handleBallInHole(Hole const&);
  void onShoot(float, float);
  bool collideWith(Ball &);
  bool collideWith(Wall &);
  void load_data(std::string const &);


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
};

class W_Ball : public Ball
{
public:
  W_Ball(std::string const &, Id);
};

class B_Ball : public Ball
{
public:
  B_Ball(std::string const &, Id);
};

class Stripes : public Ball
{
public:
  Stripes(std::string const &, Id);
};

class Solids : public Ball
{
public:
  Solids(std::string const &, Id);
};

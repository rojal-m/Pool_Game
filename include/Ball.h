#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "constants.h"
#include "Item.h"
#include "Hole.h"
#include "Wall.h"

class Ball
{
private:
  sf::Sprite ball;
  sf::Sound collide;
  sf::Sound hole;
  sf::Sound side;

public:
  sf::Vector2f position;
  sf::Vector2f velocity;
  bool moving;
  Col color;
  bool visible;
  bool ballInHand{false};

  Ball(sf::Vector2f const&, Item &, Col );
  void update();
  void draw(sf::RenderWindow &);
  bool handleBallInHole(Hole const&);
  bool collideWith(Ball &);
  bool collideWith(Wall &);
private:
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

#ifndef HOLE_H
#define HOLE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Hole
{
public:
  float radius;
  std::vector<sf::Vector2f> position;

  Hole();
};

#endif

//#ifndef COLLISION_H
//#define COLLISION_H
#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>

class Collision{
public:
  void if_hit(bool);
  bool is_hit();

public:
  double friction{};
  double mass{};
  double length{};
  double power{};

};

#endif

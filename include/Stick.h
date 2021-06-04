#ifndef STICK_H
#define STICK_H

#include <SFML/Graphics.hpp>
#include "Ball.h"

class Stick
{
private:
  sf::Sprite stick{};
  sf::Sound strike{};
  sf::Vector2f position{};
  float max_power{};
  float power_interval{};
  float direction_interval{};
  float power;
  float rotation;
  W_Ball * Wball{};

public:
  bool shot;
  bool visible;

  Stick();
  ~Stick() = default;
  Stick(const Stick&) = default;
  Stick& operator=(Stick&) = default;
  void update(sf::Vector2f &);
  void draw(sf::RenderWindow &);
  void updateRotation(sf::Vector2f &);
  void increasePower();
  void decreasePower();
  bool hasPower();
  void shoot();
  void reposition();
  void referBall(W_Ball*);
  void load_data(std::string const &);
};

#endif

#include <SFML/Graphics.hpp>
#include "Ball.h"
class Stick
{
private:
  sf::Sprite stick;
  sf::Vector2f position;
  float rotation;
  Ball & Wball;
  sf::Sound strike;

public:
  bool shot;
  float power;
  bool visible{true};

  Stick(Item const&,Ball &);
  void update();
  void draw(sf::RenderWindow &);
  void updateRotation(sf::Vector2f &);
  void increasePower();
  void decreasePower();
  void shoot();
  void reposition();
};

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

  Stick(Item const&,Ball &);
  void update();
  void draw(sf::RenderWindow &);
  void updateRotation(sf::RenderWindow &);
  void increasePower();
  void decreasePower();
  void shoot();
  void reposition(sf::Vector2f const&);
};

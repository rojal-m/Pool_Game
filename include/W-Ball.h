#include "Ball.h"
#include <SFML/Graphics.hpp>


class W_Ball: public Ball
{
private:
  sf::Sprite sprite;

public:
  W_Ball(sf::Sprite);
  void onShoot(float &, float);
};

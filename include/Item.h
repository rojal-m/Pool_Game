#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "constants.h"

class Item
{
public:
  sf::Texture Background;
  sf::Texture Stick;
  sf::Texture W_B;
  sf::Texture B_B;
  sf::Texture B1;
  sf::Texture B2;
  sf::Texture GameOver;

  Item();
  sf::Texture loadTexture(std::string const& s);
  sf::Texture const& getBallTextureByColor(Col C) const;
};

#endif

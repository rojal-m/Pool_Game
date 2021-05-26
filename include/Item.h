#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "constants.h"

class Item
{
public:
  sf::Texture Menu_Bg;
  sf::Texture Game_Bg;
  sf::Texture Stick;
  sf::Texture W_B;
  sf::Texture B_B;
  sf::Texture B1;
  sf::Texture B2;
  sf::Texture B3;
  sf::Texture B4;
  sf::Texture B5;
  sf::Texture B6;
  sf::Texture B7;
  sf::Texture B9;
  sf::Texture B10;
  sf::Texture B11;
  sf::Texture B12;
  sf::Texture B13;
  sf::Texture B14;
  sf::Texture B15;
  sf::Texture Controls;
  sf::Texture Play_Btn;
  sf::Texture Play_Btn2;
  sf::Texture GameOver;
  sf::Texture ball_8;

  int case_solids{0};
  int case_stripes{0};

  sf::SoundBuffer collideBuffer;
  sf::SoundBuffer holeBuffer;
  sf::SoundBuffer strikeBuffer;
  sf::SoundBuffer sideBuffer;

  sf::Font font;

  Item();
  sf::Texture loadTexture(std::string const&);
  sf::SoundBuffer loadSoundBuffer (std::string const&);
  sf::Font loadFont(std::string const&);
  sf::Texture const& getBallTexture(Col, Id);
};

#endif

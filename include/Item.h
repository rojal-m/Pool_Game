#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "constants.h"

using namespace sf;

class Item
{
public:
  Texture Menu_bg;
  Texture Game_bg;
  Texture Stick;

  Texture W_B;
  Texture B_B;
  Texture B1;
  Texture B2;
  Texture B3;
  Texture B4;
  Texture B5;
  Texture B6;
  Texture B7;
  Texture B9;
  Texture B10;
  Texture B11;
  Texture B12;
  Texture B13;
  Texture B14;
  Texture B15;
  Texture Controls;
  Texture Play_Btn;
  Texture Play_Btn2;
  Texture GameOver;
  Texture ball_8;

  SoundBuffer collideBuffer;
  SoundBuffer holeBuffer;
  SoundBuffer strikeBuffer;
  SoundBuffer sideBuffer;

  Item();
  Texture loadTexture(std::string const& s);
  SoundBuffer loadSoundBuffer (std::string const& a);
  Texture const& getBallTextureByColor(Col C) const;
};

#endif

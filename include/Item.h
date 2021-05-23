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
  Texture Background;
  Texture Stick;
  Texture W_B;
  Texture B_B;
  Texture B1;
  Texture B2;
  Texture GameOver;

  SoundBuffer collideBuffer;
  SoundBuffer holeBuffer;
  SoundBuffer strikeBuffer;
  SoundBuffer sideBuffer;

  Item();
  Texture loadTexture(std::string const& s);
  SoundBuffer loadSoundBuffer (std::string const& a);
  Texture const& getBallTextureByColor(Col C);
};

#endif

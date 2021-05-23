#include "Item.h"

using namespace std;
using namespace sf;

Item::Item()
  :Background{loadTexture("background.png")},
   Stick{loadTexture("stick.png")},
   W_B{loadTexture("ball.png")},
   B_B{loadTexture("black_ball.png")},
   B1{loadTexture("red_ball.png")},
   B2{loadTexture("yellow_ball.png")},
   GameOver{loadTexture("Game_Over.png")},
   collideBuffer{loadSoundBuffer ("Collide.wav")},
   holeBuffer{loadSoundBuffer("Hole.wav")},
   strikeBuffer{loadSoundBuffer("Strike.wav")},
   sideBuffer{loadSoundBuffer("Side.wav")} {}


Texture Item::loadTexture(std::string const& s)
{
  Texture T;
  if(!T.loadFromFile ("item/image/"+s))
    throw std::invalid_argument{"File not found"};
  return T;
}

SoundBuffer Item::loadSoundBuffer(std::string const& a)
{
  SoundBuffer S;
  if(!S.loadFromFile ("item/Music/"+a))
  throw std::invalid_argument{"File not found"};
  return S;
}

Texture const& Item::getBallTextureByColor(Col C)
{
  switch(C)
  {
  case Col::RED:
    return B1;
  case Col::YELLOW:
    return B2;
  case Col::BLACK:
    return B_B;
  case Col::WHITE:
    return W_B;
  }
  throw std::invalid_argument{"Wrong Ball Color"};
}

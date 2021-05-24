#include "Item.h"

using namespace std;
using namespace sf;

Item::Item()
  :Menu_bg{loadTexture("Menu-01.png")},
  Game_bg{loadTexture("background-01.png")},
  Stick{loadTexture("stick.png")},
  W_B{loadTexture("White.png")},
  B_B{loadTexture("8.png")},
  B1{loadTexture("1.png")},
  B2{loadTexture("2.png")},
  B3{loadTexture("3.png")},
  B4{loadTexture("4.png")},
  B5{loadTexture("5.png")},
  B6{loadTexture("6.png")},
  B7{loadTexture("7.png")},
  B9{loadTexture("9.png")},
  B10{loadTexture("10.png")},
  B11{loadTexture("11.png")},
  B12{loadTexture("12.png")},
  B13{loadTexture("13.png")},
  B14{loadTexture("14.png")},
  B15{loadTexture("15.png")},
  Controls{loadTexture("Controls-01.png")},
  Play_Btn{loadTexture("Play_Btn1.png")},
  Play_Btn2{loadTexture("Play_Btn2.png")},
  GameOver{loadTexture("Game_Over.png")},
  ball_8{loadTexture("8ball.png")},

  collideBuffer{loadSoundBuffer ("Collide.wav")},
  holeBuffer{loadSoundBuffer("Hole.wav")},
  strikeBuffer{loadSoundBuffer("Strike.wav")},
  sideBuffer{loadSoundBuffer("Side.wav")} {}

Texture Item::loadTexture(std::string const& s)
{
  Texture T;
  if(!T.loadFromFile ("item/image/"+s))
    throw std::invalid_argument{"File not found"};

  T.setSmooth(true);
  return T;
}

SoundBuffer Item::loadSoundBuffer(std::string const& a)
{
  SoundBuffer S;
  if(!S.loadFromFile ("item/Music/"+a))
  throw std::invalid_argument{"File not found"};

  return S;
}

Texture const& Item::getBallTextureByColor(Col C) const
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

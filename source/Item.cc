#include "Item.h"

using namespace std;
using namespace sf;

Item::Item()
  :Menu_Bg{loadTexture("Menu-01.png")},
   Game_Bg{loadTexture("background-01.png")},
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
   sideBuffer{loadSoundBuffer("Side.wav")},

   font{loadFont("BebasNeue-Regular.ttf")}{}


Texture Item::loadTexture(std::string const& s)
{
  Texture T;
  if(!T.loadFromFile ("item/image/"+s))
    throw std::invalid_argument{"File not found"};

  T.setSmooth(true);
  return T;
}

SoundBuffer Item::loadSoundBuffer(std::string const& s)
{
  SoundBuffer S;
  if(!S.loadFromFile ("item/Music/"+s))
    throw std::invalid_argument{"File not found"};

  return S;
}

Font Item::loadFont(std::string const& s)
{
  Font F;
  if(!F.loadFromFile ("item/font/"+s))
    throw std::invalid_argument{"File not found"};

  return F;
}
Texture const& Item::getBallTexture(Col C, Id I)
{
  switch(C)
  {
  case Col::SOLIDS:
    switch(I)
    {
    case Id::B1:
      return B1;
    case Id::B2:
      return B2;
    case Id::B3:
      return B3;
    case Id::B4:
      return B4;
    case Id::B5:
      return B5;
    case Id::B6:
      return B6;
    case Id::B7:
      return B7;
    default:
      break;
    }
  case Col::STRIPES:
    switch(I)
    {
      case Id::B9:
        return B9;
      case Id::B10:
        return B10;
      case Id::B11:
        return B11;
      case Id::B12:
        return B12;
      case Id::B13:
        return B13;
      case Id::B14:
        return B14;
      case Id::B15:
        return B15;
      default:
        break;
    }
  case Col::BLACK:
    return B_B;

  case Col::WHITE:
    return W_B;
  }
  throw std::invalid_argument{"Wrong Ball Color"};
}

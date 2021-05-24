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
Texture const& Item::getBallTextureByColor(Col C)
{
  switch(C)
  {
  case Col::SOLIDS:
    switch(case_solids++)
    {
    case 0:
      //case_solids++;
      return B7;
    case 1:
      //case_solids++;
      return B1;
    case 2:
      //case_solids++;
      return B3;
    case 3:
      //case_solids++;
      return B6;
    case 4:
      //case_solids++;
      return B5;
    case 5:
      //case_solids++;
      return B4;
    case 6:
      //case_solids++;
      return B2;
    }
  case Col::STRIPES:
    switch(case_stripes++)
    {
    case 0:
      //case_stripes++;
      return B9;
    case 1:
      //case_stripes++;
      return B12;
    case 2:
      //case_stripes++;
      return B15;
    case 3:
      //case_stripes++;
      return B14;
    case 4:
      //case_stripes++;
      return B10;
    case 5:
      //case_stripes++;
      return B13;
    case 6:
      //case_stripes++;
      return B11;
    }
  case Col::BLACK:
    return B_B;
  case Col::WHITE:
    return W_B;
  }
  throw std::invalid_argument{"Wrong Ball Color"};
}

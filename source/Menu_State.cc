#include <string>
#include <stdexcept>
#include <iostream>
#include "Menu_State.h"
#include "SourceManager.h"

using namespace sf;

Menu_State :: Menu_State ()
  :play { false }
{
  bg.setTexture(SourceManager<Texture>::load("item/image/8ball.png"));
  bg.setScale(0.45f,0.45f);
  bg.setPosition(1000.f,100.f);
  bg1.setTexture(SourceManager<Texture>::load("item/image/Menu-01.png"));

  instruct.setTexture(SourceManager<Texture>::load("item/image/Controls-01.png"));
  instruct.setPosition(1000.f,400.f);

  btn1.setTexture(SourceManager<Texture>::load("item/image/Play_Btn1.png"));
  btn1.setOrigin(btn1.getLocalBounds().width/2, btn1.getLocalBounds().height/2);
  btn1.setPosition(450.f,420.f);
  btn2.setTexture(SourceManager<Texture>::load("item/image/Play_Btn2.png"));
  btn2.setOrigin(btn2.getLocalBounds().width/2, btn2.getLocalBounds().height/2);
  btn2.setPosition(450.f,675.f);

}

void Menu_State::handle_event(sf::Event & event)
{
  if (btn1_hov() )
  {
    if ( event.type == Event::MouseButtonPressed)
     {
      auto b{event.mouseButton};
      if ( b.button == Mouse::Button::Left)
        {
         	play = true;
          btnClick = 1;
        }
    }
  }

  if (btn2_hov())
  {
      if ( event.type == Event::MouseButtonPressed)
      {
        auto b{event.mouseButton};
        if ( b.button == Mouse::Button::Left)
        {
          play = true;
          btnClick = 2;
        }
    }
  }
}

void Menu_State :: update()
{

}

void Menu_State::render (RenderWindow & target)
{
  m = Mouse::getPosition(target);

  target.draw(bg1);
  target.draw(bg);
  target.draw(instruct);
  target.draw(btn1);
  target.draw(btn2);
}


int Menu_State :: get_next_state()
{
  if (play)
  {
    play = false;
    if (btnClick == 1)
    {
      return GAME_STATE;
    }
    else if (btnClick == 2 )
    {
        return 2;
    }
    else
    {
      return MENU_STATE;
    }
  }
  else
  {
    return MENU_STATE;
  }
}


bool Menu_State::btn1_hov()
{
  FloatRect r(m.x,m.y,1,1);
  if(r.intersects(btn1.getGlobalBounds()))
  {
    btn1.setScale(1.2f,1.2f);
    return true;
  }
  btn1.setScale(1.f,1.f);
  return false;
}

bool Menu_State::btn2_hov()
{
  FloatRect r(m.x,m.y,1,1);
  if(r.intersects(btn2.getGlobalBounds()))
  {
    btn2.setScale(1.2f,1.2f);
    return true;
  }
  btn2.setScale(1.f,1.f);
  return false;

}

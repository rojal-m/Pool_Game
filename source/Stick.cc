#include <iostream>
#include <string>
#include <stdexcept>
#include <math.h>
#include "Stick.h"

using namespace sf;
using namespace std;

Stick::Stick(Item const& I ,Ball & w)
  :stick{I.Stick}, position{}, rotation {0}, Wball{w}, strike{I.strikeBuffer}, shot{false}, power{0}
{
  stick.setOrigin(970,11);
  position = Vector2f{413.0,413.0};
}

void Stick::update()
{
  if(shot)
  {
    position = Vector2f{-1000,-1000};
    return;
  }
}

void Stick::draw(RenderWindow& w)
{
  //std::cout<<rotation;
  stick.setRotation(rotation);
  stick.setPosition(position);
  w.draw(stick);
}

void Stick::updateRotation(RenderWindow & w)
{
  auto mp{sf::Mouse::getPosition(w)};
  float opposite = mp.y - position.y;
  float adjescent = mp.x - position.x;
  if(opposite < 0 && adjescent < 0)
    rotation = 180+(180*atan(opposite/adjescent))/pi;
  if(opposite > 0 && adjescent < 0)
    rotation = 180+(180*atan(opposite/adjescent))/pi;
  if(opposite < 0 && adjescent > 0)
    rotation = 360+(180*atan(opposite/adjescent))/pi;
  if(opposite > 0 && adjescent > 0)
    rotation = (180*atan(opposite/adjescent))/pi;

  //std::cout<<rotation<<"\n";
}

void Stick::increasePower()
{
  if(power > MAX_POWER)
    return;
  power += 100;
  Vector2f v = stick.getOrigin();
  stick.setOrigin(v.x+5,v.y);
}

void Stick::decreasePower()
{
  if(power <= 0){
    power = 0;
    return;
  }
  power -= 100;
  Vector2f v = stick.getOrigin();
  stick.setOrigin(v.x-5,v.y);
}

void Stick::shoot()
{
  Wball.onShoot(power,rotation);
  power = 0;
  stick.setOrigin(950,11);
  shot = true;
  strike.play();
}

void Stick::reposition(Vector2f const& pos)
{
  position = pos;
  stick.setOrigin(970,11);
  shot = false;
}

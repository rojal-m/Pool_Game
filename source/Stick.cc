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
  position = Wball.position;
}

void Stick::update()
{
  if (!visible)
    return;
  if(shot)
  {
    position = Vector2f{-1000,-1000};
    return;
  }
}

void Stick::draw(RenderWindow& w)
{
  if (!visible)
    return;
  //std::cout<<rotation;
  stick.setRotation(rotation);
  stick.setPosition(position);
  w.draw(stick);
}

void Stick::updateRotation(Vector2f & v)
{
  if (!visible)
    return;
  float opposite = v.y - position.y;
  float adjescent = v.x - position.x;
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
  if (!visible)
    return;
  if(power > MAX_POWER)
    return;
  power += 100;
  Vector2f v = stick.getOrigin();
  stick.setOrigin(v.x+5,v.y);
}

void Stick::decreasePower()
{
  if (!visible)
    return;
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
  if (!visible)
    return;
  Wball.onShoot(power,rotation);
  power = 0;
  stick.setOrigin(950,11);
  shot = true;
  strike.play();
}

void Stick::reposition()
{
  if (!visible)
    return;
  position = Wball.position;
  stick.setOrigin(970,11);
  shot = false;
}

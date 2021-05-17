#include <iostream>
#include <string>
#include <stdexcept>
#include "Ball.h"
#include <math.h>

using namespace sf;

Ball::Ball(Texture& t)
  :ball{t}, position{}, velocity{0,0}
{
  auto a = ball.getGlobalBounds();
  ball.setOrigin(a.width/2,a.height/2);
  position = Vector2f{413.0,413.0};
}

void Ball::update()
{
  position.x += velocity.x/delta;
  position.y += velocity.y/delta;
  velocity.x =  velocity.x*0.98;
  velocity.y =  velocity.y*0.98;
}

void Ball::draw(RenderWindow& w)
{
  ball.setPosition(position);
  w.draw(ball);
}

void Ball::onShoot(float&p,float r)
{
  velocity.x = p * cos((r*pi)/180);
  velocity.y = p * sin((r*pi)/180);

}

Stick::Stick(Texture& t,Ball & b)
  :stick{t}, ball_position{}, rotation {0}, Wball{b}, power{0}
{
  stick.setOrigin(970,11);
  position = Vector2f{413.0,413.0};
}

void Stick::update(Event::MouseMoveEvent & v)
{
  updateRotation(v);
}

void Stick::draw(RenderWindow& w)
{
  stick.setRotation(rotation);
  stick.setPosition(position);
  w.draw(stick);
}

void Stick::updateRotation(Event::MouseMoveEvent & v)
{
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
}

void Stick::increasePower()
{
  power += 100;
  Vector2f v = stick.getOrigin();
  stick.setOrigin(v.x+5,v.y);
}

void Stick::shoot()
{
  Wball.onShoot(power,rotation);
  power = 0;
  stick.setOrigin(950,11);
}

Hole::Hole()
:ball_position{};

bool Hole::is_in(Ball& b)
{
  if (b== 1)
{
  return true;
}
else
{
  return false;
}
}

void Hole::if_in(bool x, int p)
{
  if (x==true)
  {
    points++;
  }
}

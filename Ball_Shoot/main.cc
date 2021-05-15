#include <SFML/Graphics.hpp> // includes most things in SFML
#include <iostream>
#include <math.h>

using namespace sf;

int const width  { 1500 };
int const height { 825 };
float const pi{3.14159265359};
float const delta = 250;


class Item
{
};
class Game
{
};
class GameWorld
{
};
class Ball
{
private:
  Sprite ball;
  Vector2f position;
  Vector2f velocity;
public:
  Ball(Texture& t)
    :ball{t}, position{}, velocity{0,0}
  {
    auto a = ball.getGlobalBounds();
    ball.setOrigin(a.width/2,a.height/2);
    position = Vector2f{413.0,413.0}; 
  }
  void update()
  {
    //std::cout<<velocity.x<<" "<<velocity.y<<"\n";
    position.x += velocity.x/delta;
    position.y += velocity.y/delta;
    //std::cout<<velocity.x<<" "<<(velocity.x /delta)<<" "<<velocity.y<<"\n";
    velocity.x =  velocity.x*0.98;
    velocity.y =  velocity.y*0.98;
    
  }
  void draw(RenderWindow& w)
  {
    ball.setPosition(position);
    w.draw(ball);
  }
  void onShoot(float&p,float r)
  {
    velocity.x = p * cos((r*pi)/180);
    velocity.y = p * sin((r*pi)/180);
    //std::cout<<velocity.x<<" "<<velocity.y<<"\n";
    
    
  }
};
//-------------------------------------------
class Stick
{
private:
  Sprite stick;
  Vector2f position;
  float rotation;
  Ball& Wball;
public:
  float power;
  Stick(Texture& t,Ball & b)
    :stick{t}, position{}, rotation {0}, Wball{b}, power{0}
  {
    stick.setOrigin(970,11);
    position = Vector2f{413.0,413.0};
  }
  void update(Event::MouseMoveEvent & v)
  {
    updateRotation(v);
  }
  void draw(RenderWindow& w)
  {
    //std::cout<<rotation;
    stick.setRotation(rotation);
    stick.setPosition(position);
    w.draw(stick);
  }
  void updateRotation(Event::MouseMoveEvent & v)
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

     //std::cout<<rotation<<"\n";
  }
  void increasePower()
  {
    power += 100;
    Vector2f v = stick.getOrigin(); 
    stick.setOrigin(v.x+5,v.y);
  }
  void shoot()
  {
    Wball.onShoot(power,rotation);
    power = 0;
    stick.setOrigin(950,11);
  }
};


int main ()
{
  RenderWindow window{VideoMode{width, height},"Pool"};
  Texture t1,t2,t3;
    if (!t1.loadFromFile ("image/background.png"))
        return 1;
    if (!t2.loadFromFile ("image/stick.png"))
        return 1;
    if (!t3.loadFromFile ("image/ball.png"))
        return 1;
    
    // skapa sprite
    Sprite bg{t1};
    Ball ball{t3};
    Stick stick{t2,ball};
    
    
  while ( window.isOpen () )
  {
    Event event;
    while ( window.pollEvent(event) )
    {
      if ( event.type == Event::Closed )
      {
	window.close ();
      }
      else if ( event.type == Event::MouseButtonPressed )
      {
      }
      else if ( event.type == Event::MouseMoved )
      {
	auto mouse{event.mouseMove};
	stick.update(mouse);
	
	
      }
    }
    
      if ( event.type == Event::MouseButtonPressed )
      {
	stick.increasePower();
      }
      else if(stick.power >0)
      {stick.shoot();}
    window.clear();
    ball.update();
    
    window.draw(bg);
    stick.draw(window);
    ball.draw(window);
    window.display();
  }
}

#include <SFML/Graphics.hpp> // includes most things in SFML
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace sf;

int const width  { 1500 };
int const height { 825 };
float const pi{3.14159265359};
float const delta = 177;
float const BALL_DIAMETER = 38;

template<typename T>
auto dot(Vector2<T> const& Left, Vector2<T> const& Right)
{
  return Left.x * Right.x + Left.y * Right.y;
}

float length(Vector2f const& v)
{
  return sqrt(powf(v.x,2)+powf(v.y,2));
}

enum Col
    {
      RED = 1,
      YELLOW = 2,
      BLACK = 3,
      WHITE = 4
    };

class Item
{
  public:
  Texture Background;
  Texture Stick;
  Texture W_B;
  Texture B_B;
  Texture B1;
  Texture B2;
  
  Texture loadTexture(std::string const& s)
  {
    Texture T;
    if(!T.loadFromFile ("image/"+s))
      throw std::invalid_argument{"File not found"};
    //Texture::bind(&T);
    return T;
  }
  
  Item()
    :Background{loadTexture("background.png")},
     Stick{loadTexture("stick.png")},
     W_B{loadTexture("ball.png")},
     B_B{loadTexture("black_ball.png")},
     B1{loadTexture("red_ball.png")},
     B2{loadTexture("yellow_ball.png")} {}
  
  Texture const& getBallTextureByColor(Col C)
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
};
class Game
{
};
class GameWorld
{
};
//-------------------------------------------------------------------------------------
class Ball
{
private:
  Sprite ball;
public:
  Vector2f position;
  Vector2f velocity;
  bool moving;
  Ball(Vector2f const& Pos, Texture const& t)
    :ball{t}, position{Pos}, velocity{0,0}, moving{false}
  {
    auto a = ball.getGlobalBounds();
    ball.setOrigin(a.width/2,a.height/2);
  }
  void update()
  {
    //std::cout<<velocity.x<<" "<<velocity.y<<"\n";
    position.x += velocity.x/delta;
    position.y += velocity.y/delta;

    
    
    //std::cout<<velocity.x<<" "<<(velocity.x /delta)<<" "<<velocity.y<<"\n";
    velocity =  velocity*0.984f;

    if(length(velocity) < 5)
    {
      velocity.x = 0;
      velocity.y = 0;
      moving = false;
    }
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
    moving = true;
  }
  void collideWith(Ball & B)
  {
    //find normal vector
    const auto n{position - B.position};
    
    //find distance 
    const auto dist{length(n)};
    if(dist > BALL_DIAMETER)
      return;
    const auto mtd{n*((BALL_DIAMETER-dist)/dist)};
    position = position + mtd*(0.5f);
    B.position = B.position - mtd*(0.5f);
    
    //find unit normal vector
    const auto un{n*(1/length(n))};
    //find unit tangent vector
    const auto ut{Vector2f{-un.y,un.x}};
    //Project velocity onto the unit normal and unit tangent vectors.
    const auto v1n{dot(un,velocity)};
    const auto v1t{dot(ut,velocity)};
    const auto v2n{dot(un,B.velocity)};
    const auto v2t{dot(ut,B.velocity)};

    
    const auto v1nTag{un*v2n};
    const auto v1tTag{ut*v1t};
    const auto v2nTag{un*v1n};
    const auto v2tTag{ut*v2t};

    velocity = v1nTag + v1tTag;
    B.velocity = v2nTag + v2tTag;

    moving = true;
    B.moving = true;
  }
};
//---------------------------------------------------------------------------------------
class Stick
{
private:
  Sprite stick;
  Vector2f position;
  float rotation;
  Ball& Wball;
  
public:
  bool shot;
  float power;
  Stick(Texture& t,Ball & b)
    :stick{t}, position{}, rotation {0}, Wball{b}, shot{false}, power{0}
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
    shot = true;
  }
  void reposition(Vector2f const& pos)
  {
    position = pos;
    stick.setOrigin(970,11);
    shot = false;
  }
  
};

bool ballsMoving(std::vector<Ball> & b)
{
  bool ballsMoving{false};
  for(auto it{b.begin()};it != b.end(); ++it){
    if(it->moving)
    {
      ballsMoving = true;
      break;
    }
  }
  return ballsMoving;
}

void handleCollisions(std::vector<Ball> & b)
{
  for(auto i{b.begin()};i != b.end(); ++i){
    for(auto j{i+1};j != b.end(); ++j){
      auto & firstBall = *i;
      auto & secondBall = *j;
      firstBall.collideWith(secondBall);
    }
  }
}

//--------------------------------------------------------------------------------------
int main ()
{
  Item I;
  RenderWindow window{VideoMode{width, height},"Pool"}; 
  Texture t1,t2;
    if (!t1.loadFromFile ("image/background.png"))
        return 1;
    if (!t2.loadFromFile ("image/stick.png"))
        return 1;

    
  
    // skapa sprite
    Sprite bg{I.Background};
    std::vector<Ball> Balls{
      Ball{Vector2f{1022,413},I.getBallTextureByColor(Col::YELLOW)},
      Ball{Vector2f{1056,393},I.getBallTextureByColor(Col::YELLOW)},
      Ball{Vector2f{1056,433},I.getBallTextureByColor(Col::RED)},
      Ball{Vector2f{1090,374},I.getBallTextureByColor(Col::RED)},
      Ball{Vector2f{1090,413},I.getBallTextureByColor(Col::BLACK)},
      Ball{Vector2f{1090,452},I.getBallTextureByColor(Col::YELLOW)},
      Ball{Vector2f{1126,354},I.getBallTextureByColor(Col::YELLOW)},
      Ball{Vector2f{1126,393},I.getBallTextureByColor(Col::RED)},
      Ball{Vector2f{1126,433},I.getBallTextureByColor(Col::YELLOW)},
      Ball{Vector2f{1126,472},I.getBallTextureByColor(Col::RED)},
      Ball{Vector2f{1162,335},I.getBallTextureByColor(Col::RED)},
      Ball{Vector2f{1162,374},I.getBallTextureByColor(Col::RED)},
      Ball{Vector2f{1162,413},I.getBallTextureByColor(Col::YELLOW)},
      Ball{Vector2f{1162,452},I.getBallTextureByColor(Col::RED)},
      Ball{Vector2f{1162,491},I.getBallTextureByColor(Col::YELLOW)},
      Ball{Vector2f{413,413},I.getBallTextureByColor(Col::WHITE)},
	};
    Ball& W_ball{ Balls.at(Balls.size() -1)};
    Stick stick{I.Stick,W_ball};
    
    
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

    handleCollisions(Balls);
    
    std::for_each(Balls.begin(),Balls.end(),[](Ball & B){
	B.update();
      });
    if (!ballsMoving(Balls) && stick.shot)
    {
      stick.reposition(W_ball.position);
    }
    window.draw(bg);
    stick.draw(window);
    std::for_each(Balls.begin(),Balls.end(),[&window](Ball & B){
	B.draw(window);
      });
    window.display();
  }
}


#include <SFML/Graphics.hpp> // includes most things in SFML
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
using namespace sf;

int const width  { 1500 };
int const height { 825 };
float const pi{3.14159265359};
float const delta = 100;
float const BALL_DIAMETER = 36;
float const MAX_POWER = 3000;
float const FRICTION {0.985};
double const fps { 60.0 };

template<typename T>
float dot(Vector2<T> const& Left, Vector2<T> const& Right)
{
  return Left.x * Right.x + Left.y * Right.y;
}

float length(Vector2f const& v)
{
  return sqrt(powf(v.x,2)+powf(v.y,2));
}

template<typename T>
float distFrom(Vector2<T> const& Left, Vector2<T> const& Right)
{
  return length(Left - Right);
}

enum Col
{
  RED = 1,
  YELLOW = 2,
  BLACK = 3,
  WHITE = 4
};

std::vector<std::pair<Vector2f,Col>> const ConstantBalls
{
  {Vector2f{413,413},Col::WHITE},
  {Vector2f{1022,413},Col::YELLOW},
  {Vector2f{1056,393},Col::YELLOW},
  {Vector2f{1056,433},Col::RED},
  {Vector2f{1090,374},Col::RED},
  {Vector2f{1090,413},Col::BLACK},
  {Vector2f{1090,452},Col::YELLOW},
  {Vector2f{1126,354},Col::YELLOW},
  {Vector2f{1126,393},Col::RED},
  {Vector2f{1126,433},Col::YELLOW},
  {Vector2f{1126,472},Col::RED},
  {Vector2f{1162,335},Col::RED},
  {Vector2f{1162,374},Col::RED},
  {Vector2f{1162,413},Col::YELLOW},
  {Vector2f{1162,452},Col::RED},
  {Vector2f{1162,491},Col::YELLOW},
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

  sf::SoundBuffer collideBuffer;
  sf::SoundBuffer holeBuffer;
  sf::SoundBuffer strikeBuffer;
  sf::SoundBuffer sideBuffer;

  Texture loadTexture(std::string const& s)
  {
    Texture T;
    if(!T.loadFromFile ("image/"+s))
      throw std::invalid_argument{"File not found"};
    //Texture::bind(&T);
    return T;
  }

  SoundBuffer loadSoundBuffer(std::string const& a)
  {
    SoundBuffer S;
    if(!S.loadFromFile ("Music/"+a))
      throw std::invalid_argument{"File not found"};
    return S;
  }

  Item()
    :Background{loadTexture("background.png")},
     Stick{loadTexture("stick.png")},
     W_B{loadTexture("ball.png")},
     B_B{loadTexture("black_ball.png")},
     B1{loadTexture("red_ball.png")},
     B2{loadTexture("yellow_ball.png")},
     collideBuffer{loadSoundBuffer ("Collide.wav")},
     holeBuffer{loadSoundBuffer("Hole.wav")},
     strikeBuffer{loadSoundBuffer("Strike.wav")},
     sideBuffer{loadSoundBuffer("Side.wav")} {}

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

class Wall
{
public:
  float topY;
  float rightX;
  float bottomY;
  float leftX;
  Wall()
    : topY{57},rightX{1443},bottomY{768},leftX{57}
  {}
};
class Hole
{
public:
  float radius{46};
  std::vector<Vector2f> position{
    Vector2f{750,32},
      Vector2f{750,794},
	Vector2f{62,62},
	  Vector2f{1435,62},
	    Vector2f{62,762},
	      Vector2f{1435,762}};
};
//-------------------------------------------------------------------------------------

class Stick
{
private:
  Sprite stick;
  Vector2f position;
  float rotation;


public:
  bool shot;
  float power;
  Stick(Texture& t)
    :stick{t}, position{}, rotation {0}, shot{false}, power{0}
  {
    stick.setOrigin(970,11);
    position = Vector2f{413.0,413.0};
  }
  void update(Event & event,RenderWindow & w, Ball & Wball)
  {
    if(shot)
    {
      position = Vector2f{-1000,-1000};
      return;
    }

    if (event.type == Event::MouseButtonPressed)
      increasePower();
    else if(event.type == Event::MouseButtonReleased && power >0)
      shoot(Wball);

    updateRotation(w);
  }
  void draw(RenderWindow& w)
  {
    //std::cout<<rotation;
    stick.setRotation(rotation);
    stick.setPosition(position);
    w.draw(stick);
  }
  void updateRotation(RenderWindow & w)
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
  void increasePower()
  {
    if(power > MAX_POWER)
      return;
    power += 120;
    Vector2f v = stick.getOrigin();
    stick.setOrigin(v.x+5,v.y);
  }
  void shoot(Ball & Wball)
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

void handleCollisions(std::vector<Ball> & b, Wall & W, Hole & h)
{
  for(auto i{b.begin()};i != b.end(); ++i){
    i->handleBallInHole(h);
    i->collideWith(W);
    for(auto j{i+1};j != b.end(); ++j){
      /*auto & firstBall = *i;
	auto & secondBall = *j;
	firstBall.collideWith(secondBall);*/
      i->collideWith(*j);
    }
  }
}
void delay (sf::Clock & clock)
{
  sleep (milliseconds (1000.0 / fps) - clock.getElapsedTime ());
  clock.restart ();
}
//--------------------------------------------------------------------------------------
int main ()
{
  Clock clock{};
  Item I;
  RenderWindow window{VideoMode{width, height},"Pool"};
  Texture t1,t2;
  if (!t1.loadFromFile ("image/background.png"))
    return 1;
  if (!t2.loadFromFile ("image/stick.png"))
    return 1;

  // skapa sprite
  Sprite bg{I.Background};
  std::vector<Ball> Balls;
  std::transform(ConstantBalls.begin(),ConstantBalls.end(),std::back_inserter(Balls),
		 [&I](auto const& a){
		   return Ball{a.first,I,a.second};
		 });
  Ball& W_ball{ *std::find_if(Balls.begin(),Balls.end(),[](auto const& b){
	return b.color == Col::WHITE;
      })};
  //Balls.at(Balls.size() -1)};
  Stick stick{I.Stick};
  Wall wall;
  Hole hole;

  while ( window.isOpen () )
  {
    Event event;
    while ( window.pollEvent(event) )
    {
      if ( event.type == Event::Closed )
      {
	window.close ();
      }
    }

    window.clear();

    handleCollisions(Balls,wall,hole);

    stick.update(event,window,W_ball);
    std::for_each(Balls.begin(),Balls.end(),[](Ball & B){
	B.update();
      });
    if (!ballsMoving(Balls) && stick.shot)
    {
      stick.reposition(W_ball.position);
    }
    window.draw(bg);

    std::for_each(Balls.begin(),Balls.end(),[&window](Ball & B){
	B.draw(window);
      });
    stick.draw(window);
    window.display();
    delay(clock);
  }
}

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
double const fps { 120.0 };

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

//-------------------------------------------------------------------------------------
class Ball
{
private:
  Sprite ball;
  Sound collide;
  Sound hole;
  Sound side;

public:
  Vector2f position;
  Vector2f velocity;
  bool moving;
  Col color;
  bool visible;


  Ball(Vector2f const& Pos, Item & I, Col c)
    :ball{I.getBallTextureByColor(c)}, collide{I.collideBuffer}, hole{I.holeBuffer}, side{I.sideBuffer}, position{Pos}, velocity{0,0}, moving{false}, color{c}, visible{true}
  {
    auto a = ball.getGlobalBounds();
    ball.setOrigin(a.width/2,a.height/2);
  }
  void update()
  {
    if(!visible)
      return;
    //std::cout<<velocity.x<<" "<<velocity.y<<"\n";
    position += velocity/delta;



    //std::cout<<velocity.x<<" "<<(velocity.x /delta)<<" "<<velocity.y<<"\n";
    velocity =  velocity*FRICTION;

    if(length(velocity) < 10)
    {
      velocity.x = 0;
      velocity.y = 0;
      moving = false;
    }
  }
  void draw(RenderWindow& w)
  {
    if(!visible)
      return;
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
  void handleBallInHole(Hole const& h)
  {
    if(!visible)
    return;
    bool inHole{};
    Vector2f pos{position};
    std::for_each(h.position.begin(),h.position.end(),[&inHole,&h,&pos](auto const& p)
    {
	inHole += distFrom(pos,p) <= h.radius;
    });

    if(!inHole)
	{
    return;
  }
    visible = false;
    moving = false;

    hole.play();

  }
  void collideWith(Ball & B)
  {
    if(!visible || !B.visible)
      {
        return;
      }


    //find normal vector
    const auto n{position - B.position};


    //find distance
    const auto dist{length(n)};
    if(dist > BALL_DIAMETER)

    {
      return;

   }



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


    collide.setPlayingOffset(seconds(1.f));
    collide.play();
  }

  void collideWith(Wall & w)
  {
    if(!visible || !moving)
      return;
    bool collided = false;
    if(position.y <= w.topY+(BALL_DIAMETER/2))
    {
      position.y = w.topY+(BALL_DIAMETER/2);
      velocity = Vector2f{velocity.x,-velocity.y};
      collided = true;
    }
    if(position.x >= w.rightX-(BALL_DIAMETER/2))
    {
      position.x = w.rightX-(BALL_DIAMETER/2);
      velocity = Vector2f{-velocity.x,velocity.y};
      collided = true;
    }
    if(position.y >= w.bottomY-(BALL_DIAMETER/2))
    {
      position.y = w.bottomY-(BALL_DIAMETER/2);
      velocity = Vector2f{velocity.x,-velocity.y};
      collided = true;
    }
    if(position.x <= w.leftX+(BALL_DIAMETER/2))
    {
      position.x = w.leftX+(BALL_DIAMETER/2);
      velocity = Vector2f{-velocity.x,velocity.y};
      collided = true;
    }

    if(collided)
    {
      side.play();
      velocity *= FRICTION;
    }
  }


};
//---------------------------------------------------------------------------------------
class Stick
{
private:
  Sprite stick;
  Vector2f position;
  float rotation;
  Sound strike;

public:
  bool shot;
  float power;
  Stick(Texture & t, Item & I)
    :stick{t}, position{}, rotation {0}, strike{I.strikeBuffer}, shot{false}, power{0}
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

    strike.setVolume(100.f);
    strike.play();
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
    Stick stick{I.Stick, I};
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

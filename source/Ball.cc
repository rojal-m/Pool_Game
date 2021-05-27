#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <utility>
#include "Ball.h"
#include "SourceManager.h"


using namespace sf;
using namespace std;

Ball::Ball(Id i, Col c)
  :id{i}, color{c}, velocity{0,0}, moving{false}, visible{true}
{}

void Ball::update()
{
  if(!visible)
    return;

  position += velocity/delta;
  velocity =  velocity*FRICTION;

  if(length(velocity) < 10)
  {
    velocity.x = 0;
    velocity.y = 0;
    moving = false;
  }
}

void Ball::draw(RenderWindow& w)
{
  if(!visible)
    return;
  ball.setPosition(position);
  w.draw(ball);
}



void Ball::onShoot(float p,float r)
{
  velocity.x = p * cos((r*pi)/180);
  velocity.y = p * sin((r*pi)/180);
  moving = true;
}

bool Ball::collideWith(Ball & B)
{
  if(!visible || !B.visible )
    return false;
  //find normal vector
  const auto n{position - B.position};

  //find distance
  const auto dist{length(n)};
  if(dist > BALL_DIAMETER)
    return false;

  if(ballInHand)
    return true;

  collide.play();


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
  return true;
}

bool Ball::collideWith(Wall & w)
{
  if(!visible || !moving || ballInHand)
    return false;
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
    return true;
  }
  else
  {return false;}
}

bool Ball::handleBallInHole(Hole const& h)
{
  if(!visible || ballInHand)
    return false;
  bool inHole{};
  Vector2f pos{position};
  std::for_each(h.position.begin(),h.position.end(),[&inHole,&h,&pos, this](auto const& p)
    {
      inHole += distFrom(pos,p) <= h.radius;
    });

  if(!inHole)
  {
    return false;
  }
  if(ballInHand)
  {
    return true;
  }
  visible = false;
  moving = false;

  hole.play();
  return true;
}

void Ball::load_data(std::string const & file_name)
{
  ifstream file("item/ExternalSource/"+file_name);
  string trash{};
  getline(file,trash);
  int x;
  string textureFileName;
  while(file >> x >> position.x >>  position.y >> textureFileName)
  {
    if( x == id)
    {
      break;
    }
  }

  ball.setTexture(SourceManager<Texture>::load("item/image/"+textureFileName));
  auto a = ball.getGlobalBounds();
  ball.setOrigin(a.width/2,a.height/2);
  collide.setBuffer(SourceManager<SoundBuffer>::load("item/Music/Collide.wav"));
  hole.setBuffer(SourceManager<SoundBuffer>::load("item/Music/Hole.wav"));
  side.setBuffer(SourceManager<SoundBuffer>::load("item/Music/Side.wav"));

  file.close();
}


W_Ball::W_Ball(std::string const & s, Id i)
: Ball{i, Col::WHITE}
{
  load_data(s);
}

B_Ball::B_Ball(std::string const & s, Id i)
: Ball{i, Col::BLACK}
{
  load_data(s);
}

Stripes::Stripes(std::string const & s, Id i)
:Ball{i, Col::STRIPES}
{
  load_data(s);
}

Solids::Solids(std::string const & s, Id i)
:Ball{i, Col::SOLIDS}
{
  load_data(s);
}

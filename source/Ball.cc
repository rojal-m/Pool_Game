
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

Ball::Ball(float x, float y, Id i, Col c, float m)
  :position{x,y}, id{i}, color{c}, mass{m}, velocity{0,0}, moving{false}, visible{true}
{}

void Ball::update()
{
  if(!visible)
    return;

  position += velocity/delta;
  velocity =  velocity*FRICTION;

  if(length(velocity) < 15)
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
  const auto v1t{dot(ut,velocity)};
  const auto v1n{dot(un,velocity)};
  const auto v2n{dot(un,B.velocity)};
  const auto v2t{dot(ut,B.velocity)};


  const auto v1nT{(v1n*(mass-B.mass)+v2n*(2*B.mass))/(mass+B.mass)};
  const auto v1tT{v1t};
  const auto v2nT{(v2n*(B.mass-mass)+v1n*(2*mass))/(mass+B.mass)};
  const auto v2tT{v2t};

  const auto v1nTag{un*v1nT};
  const auto v1tTag{ut*v1tT};
  const auto v2nTag{un*v2nT};
  const auto v2tTag{ut*v2tT};

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

void Ball::load_data()
{
  ifstream file("item/ExternalSource/ball_sprite.txt");
  string trash{};
  getline(file,trash);
  int x;
  string textureFileName;
  while(file >> x >> textureFileName)
  {
    if( x == id)
    {
      break;
    }
  }
  Texture& T{SourceManager<Texture>::load("item/image/"+textureFileName)};
  T.setSmooth(true);
  ball.setTexture(T);
  auto a = ball.getGlobalBounds();
  ball.setOrigin(a.width/2,a.height/2);
  collide.setBuffer(SourceManager<SoundBuffer>::load("item/Music/Collide.wav"));
  hole.setBuffer(SourceManager<SoundBuffer>::load("item/Music/Hole.wav"));
  side.setBuffer(SourceManager<SoundBuffer>::load("item/Music/Side.wav"));
  file.close();
}

void Ball::onShoot([[maybe_unused]]float p,[[maybe_unused]]float r)
{}

W_Ball::W_Ball(float x, float y, Id i)
: Ball{x, y, i, Col::WHITE, 0.2f}
{
  load_data();
}

void W_Ball::onShoot(float p,float r)
{
  velocity.x = p * cos((r*pi)/180);
  velocity.y = p * sin((r*pi)/180);
  moving = true;
}

B_Ball::B_Ball(float x, float y, Id i)
: Ball{x, y, i, Col::BLACK, 3.f}
{
  load_data();
}


Stripes::Stripes(float x, float y, Id i)
:Ball{x, y, i, Col::STRIPES, 0.16f}
{
  load_data();
}


Solids::Solids(float x, float y, Id i)
:Ball{x, y, i, Col::SOLIDS, 0.16f}
{
  load_data();
}

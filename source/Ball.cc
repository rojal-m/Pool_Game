#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <utility>
#include "Ball.h"

using namespace sf;
using namespace std;

Ball::Ball(Vector2f const& Pos, Item const & I, Col c)
  :ball{I.getBallTextureByColor(c)}, position{Pos}, velocity{0,0}, moving{false}, color{c}, visible{true}
{
  auto a = ball.getGlobalBounds();
  ball.setOrigin(a.width/2,a.height/2);
}

void Ball::update()
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

void Ball::draw(RenderWindow& w)
{
  if(!visible)
    return;
  ball.setPosition(position);
  w.draw(ball);
}

void Ball::onShoot(float&p,float r)
{
  velocity.x = p * cos((r*pi)/180);
  velocity.y = p * sin((r*pi)/180);
  moving = true;
}

void Ball::handleBallInHole(Hole const& h)
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


void Ball::collideWith(Ball & B)
{
  if(!visible || !B.visible)
    return;
  //find normal vector
  const auto n{position - B.position};

  //find distance
  const auto dist{length(n)};
  if(dist > BALL_DIAMETER)
    return;

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

}

void Ball::collideWith(Wall & w)
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

    side.play();
  velocity *= FRICTION;


}
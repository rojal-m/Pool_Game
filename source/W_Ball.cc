#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <utility>
#include "W_Ball"



W_Ball::W_Ball()
:
{
  
}




void Ball::onShoot(float&p,float r)
{
  velocity.x = p * cos((r*pi)/180);
  velocity.y = p * sin((r*pi)/180);
  moving = true;
}

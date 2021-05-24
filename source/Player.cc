#include "Player.h"
#include "Stick.h"

using namespace std;
using namespace sf;

Player::Player(Col B, string N)
:assignBalls{B}, playerName{N}
{}

bool Player::takeTurn()
{
return true;
}

void Player::shootBall()
{

}

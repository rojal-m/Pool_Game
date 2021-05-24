#include "Player.h"
#include "Stick.h"

using namespace std;
using namespace sf;

Player::Player(string const& N,Font & F,bool B)
  :turn{B}, name{N,F,30}
{
  name.setPosition(100,840);
}

void Player::update()
{

}

void Player::render(RenderWindow & window)
{
  if (!turn)
    return;

  window.draw(name);
}

void takeTurn(Player & P1, Player & P2)
{
  P1.turn = !P1.turn;
  P2.turn = !P2.turn;
}

#include "Player.h"
#include "Stick.h"

using namespace std;
using namespace sf;

Player::Player(string const& N,Font & F,bool B)
  :turn{B}, name{N,F,30} ,font{F} , tur{"turn",F,30}
{
  name.setPosition(100,840);
  tur.setPosition(200,840);
}

void Player::update()
{

}

void Player::render(RenderWindow & window)
{
  if (!turn)
    return;
  if (assignBalls == Col::STRIPES)
  {
    sf::Text Ball {"Hit Stripes", font,30};
    Ball.setPosition(500,840);
    window.draw(Ball);
  }
  if (assignBalls == Col::SOLIDS)
  {
    sf::Text Ball {"Hit Solids", font,30};
    Ball.setPosition(500,840);
    window.draw(Ball);
  }
  window.draw(tur);
  window.draw(name);
}

void takeTurn(Player & P1, Player & P2)
{
  P1.turn = !P1.turn;
  P2.turn = !P2.turn;
}

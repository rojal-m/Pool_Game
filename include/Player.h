#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Ball.h"

class Player
{
public:
  Player(std::string const&, sf::Font &, bool);
  ~Player() = default;
  Player(const Player&) = default;
  Player& operator=(Player&) = default;
  void update();
  void render(sf::RenderWindow &);
  Col assignBalls{};
  bool assigned{false};
  bool turn;


private:
  sf::Text name;

  //Ball* currBall;
};

void takeTurn(Player &, Player &);

#endif

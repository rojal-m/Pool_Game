#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Ball.h"
#include "SourceManager.h"

class Player
{
public:
  Player(std::string const&, bool);
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
  sf::Font & font{SourceManager<sf::Font>::load("item/font/BebasNeue-Regular.ttf")};
  sf::Text tur;
  //Ball* currBall;
};

void takeTurn(Player &, Player &);

#endif

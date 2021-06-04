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
  void update();
  void render(sf::RenderWindow &);
  Col assignBalls{};
  bool assigned{false};
  bool turn;


private:
  sf::Font & font;
  sf::Text name;
  sf::Text tur;
};

void takeTurn(Player &, Player &);

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Ball.h"

class Player
{
public:
<<<<<<< HEAD

  Player(Col, std::string);
  void update();
  void render(sf::RenderWindow &);

  Player(Col, std::string&);

  bool takeTurn();
  void shootBall();

  int playerID{};
  bool turn{};
=======
  Player(std::string const&, sf::Font &, bool);
  ~Player() = default;
  Player(const Player&) = default;
  Player& operator=(Player&) = default;
  void update();
  void render(sf::RenderWindow &);
  Col assignBalls{};
  bool assigned{false};
  bool turn;

>>>>>>> 9c4190a51374d41eb474ab00413f30ec7b2e7ec9

private:
  sf::Text name;

  //Ball* currBall;
};

void takeTurn(Player &, Player &);

#endif

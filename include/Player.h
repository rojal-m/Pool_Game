#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.hpp>

class Player
{
public:

  Player(Col, std::string);
  void update();
  void render(sf::RenderWindow &);

  Player(Col, std::string&);

  bool takeTurn();
  void shootBall();

  int playerID{};
  bool turn{};

private:
  Col assignBalls;
  std::string playerName;
  //Ball* currBall;
};


#endif

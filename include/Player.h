#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SFML/Graphics.hpp>

class Player
{
public:
<<<<<<< HEAD
  Player(Col, std::string);
  void update();
  void render(sf::RenderWindow &);
=======
  Player(Col, std::string&);

>>>>>>> 66a9e1f90c76acf17c98e75b51c8009ab3e3d046
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

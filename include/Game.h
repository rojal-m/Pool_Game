#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>
#include "State.h"
#include "Item.h"

class Game
{
public:
<<<<<<< HEAD
  Game (std::string const &, unsigned, unsigned, Item  &);
=======
  Game (std::string const &, unsigned, unsigned, Item &);
>>>>>>> 9c4190a51374d41eb474ab00413f30ec7b2e7ec9
  void start ();
private:
  sf::RenderWindow window;
  std::map<int, std::unique_ptr<State>> states{};
  int current_state;
  bool running;
  void handle_events();
  void delay (sf::Clock & clock) const;
};

#endif

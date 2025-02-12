#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>
#include "State.h"
#include "constants.h"


class Game
{
public:
  Game (std::string const &, unsigned, unsigned);
  void start ();
private:
  sf::RenderWindow window;
  std::map<int, std::unique_ptr<State>> states{};
  int current_state;
  bool running;
  void handle_events();
  void delay (sf::Clock & clock) const;
  void handle_state();
};

#endif

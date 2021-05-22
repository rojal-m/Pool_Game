#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Game
{
public:

Game(std::string const & titel, unsigned width, unsigned screen_height);
void start();

private:

  std::map<int, std::unique_ptr<State>> States;
  int current_state;
  sf::RenderWindow window;
  bool running;

  enum ball_position {};
  enum ball_name{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  void hnandle_events();
  void delay(sf::Clock & c) const;
};

#endif;

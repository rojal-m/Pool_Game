#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

int const MENU_STATE{0};
int const GAME_STATE{1};
int const GAME_STATE_2{2};

class State
{
public:
  virtual ~State () = default;
  virtual void handle_event (sf::Event &) = 0;
  virtual void update () = 0;
  virtual void render(sf::RenderWindow &) = 0;
  virtual int get_next_state() = 0;
};

#endif

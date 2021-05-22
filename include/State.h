#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

int const Manu_State{0};
int const Game_State{1};

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


#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Item.h"

class Menu_State: public State
{
public:
  Menu_State(Item const &);
  virtual void handle_event (sf::Event & override;
  virtual void update () override;
  virtual void render (sf::RenderWindow &) override;
  virtual int get_next_state() override;
private:
  Item const & _I;
  sf::Text text{};
  sf::Font font{};
  bool play;
};

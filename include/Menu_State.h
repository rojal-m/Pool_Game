#pragma once

#include "State.h"
#include "Item.h"

#define MAX_NUMBER_OF_ITEMS 3

class Menu_State: public State
{
public:
  Menu_State(Item const &);
  virtual void handle_event (sf::Event &) override;
  virtual void update () override;
  virtual void render (sf::RenderWindow &) override;
  virtual int get_next_state() override;

  void MoveUp();
  void MoveDown();

private:
  sf::Sprite bg;
  sf::Sprite bg1;
  int selectedItemIndex;
  sf::Text menu[MAX_NUMBER_OF_ITEMS];
  Item const & _I;
  sf::Text text{};
  sf::Font font{};
  bool play;
};

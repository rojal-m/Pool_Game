
#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"


class Menu_State: public State
{
public:
  Menu_State();
  virtual bool vs_bot();
  virtual bool vs_player();
  virtual void handle_event(sf::Event e) override;
  virtual void update() override;
  virtual void render(sf::RenderTarget & t) override;
  virtual int get_next_state() override;


private:
  sf::Text text;
  sf::Font font{};
  bool play;
  Player player_1;
  Player player_2;

};

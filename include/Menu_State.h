#pragma once

#include "State.h"

class Menu_State: public State
{
  private:
  sf::Sprite bg{};
  sf::Sprite bg1{};
  sf::Sprite instruct{};
  sf::Sprite btn1{};
  sf::Sprite btn2{};
  sf::Vector2i m{};
  bool play;
  int btnClick {0};

public:
  Menu_State();
  virtual void handle_event (sf::Event &) override;
  virtual void update () override;
  virtual void render (sf::RenderWindow &) override;
  virtual int get_next_state() override;

  bool btn1_hov();
  bool btn2_hov();
};

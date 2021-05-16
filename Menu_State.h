#pragma once

#include <SFML/Graphics.hpp>
//#include "State.h"


class Menu_State //: public State
{
public:
  Menu_State();
  bool vs_bot();
  bool vs_player();
  void handle_event(sf::Event e) ;
  void update() ;
  void render(sf::RenderWindow & target) ;
  int get_next_state() ;


private:
  sf::Text text;
  sf::Font font{};
  bool play;
  //Player player_1;
  //Player player_2;

};

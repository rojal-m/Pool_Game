/*
#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <string>

int const Manu_State{0};
int const Game_State{1};

class State
{
public:

  virtual ~State () = default;

  virtual void Get_Next_State () = 0;
  virtual void Handle_Event(sf::Event e) = 0;
  virtual void update() = 0;
  virtual void render(sf::RenderTarget & t) = 0;
//0 då de ska köras i de andra klasserna som ärver. Pure functions används bara för de som ska ärva den

};

#endif
*/

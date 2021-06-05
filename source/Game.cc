#include "constants.h"
#include "Game.h"
#include "State.h"
#include "Menu_State.h"
#include "Game_State.h"
#include "Game_State_2.h"

using namespace sf;

Game :: Game (std::string const & title,
              unsigned            width,
              unsigned            height)
  : window { VideoMode { width, height },
    title, Style::Titlebar | Style::Close },
    current_state{ MENU_STATE },
    running { true }
{
    states.insert(std::pair<int,  std::unique_ptr<State>>({MENU_STATE, std::make_unique<Menu_State>()}));
}


void Game :: start ()
{
  Clock clock { };
  while ( running )
  {
    handle_events();
    states.at(current_state) -> update();
    window.clear ();
    states.at(current_state) -> render(window);
    window.display ();
    current_state = states.at(current_state) -> get_next_state();
    if (current_state != MENU_STATE)
    {
      handle_state();
    }
    else
    {
      states.erase(GAME_STATE);
      states.erase(GAME_STATE_2);
    }
    delay (clock);
  }
}


void Game :: handle_events ()
{
  Event event;
  while ( window.pollEvent(event) )
  {
    if ( event.type == Event::Closed )
      running = false;
    states.at(current_state) -> handle_event (event);
  }
}

void Game :: delay (sf::Clock & clock) const
{
  sleep (milliseconds (1000.0 / fps) - clock.getElapsedTime ());
  clock.restart ();
}

void Game :: handle_state()
{
  if (current_state == GAME_STATE && states.size() == 1)
  {
    states.insert(std::pair<int,  std::unique_ptr<State>>({GAME_STATE, std::make_unique<Game_State>()}));
  }
  if (current_state == GAME_STATE_2 && states.size() == 1)
  {
    states.insert(std::pair<int,  std::unique_ptr<State>>({GAME_STATE_2,  std::make_unique<Game_State_2>()}));
  }
}

//#include <Game.h>
//#include "State.h"
#include "Menu_State.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main ()

{
    //Game g { "8 Ball Pool", screen_width, screen_height };
    RenderWindow window{VideoMode{screen_width, screen_height},"Pool" };
    Menu_State menu;

    while ( window.isOpen () )
    {
      Event event;
      while ( window.pollEvent(event) )
      {
        if ( event.type == Event::Closed )
        {
  	window.close ();
        }
        menu.handle_event(event);
      }
    menu.render(window);
    }
}

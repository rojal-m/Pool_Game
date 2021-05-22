#include <string>
#include <stdexcept>
#include "Menu_State.h"

using namespace sf;

Menu_State::Menu_State()
:play{false} //player_1(), player_2()
{
  std::string file = "BebasNeue-Regular.ttf";
  if ( !font.loadFromFile (file) )
        throw std::invalid_argument ("Unable to load font");
    text = sf::Text{ "Press <Enter> to start", font, 16 };
    //text = sf::Text{"Press "}
}

void Menu_State::handle_event(sf::Event event)
{

    if ( event.type == Event::KeyPressed )
    {
        if ( event.key.code == Keyboard::Key::Return )
            play = true;
    }
}

void Menu_State :: render (RenderTarget & target)
{
    auto bounds { text.getGlobalBounds () };
    auto size   { target.getSize () };

    text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 2);

    target.draw (text);
}

int Menu_State :: get_next_state()
{
    if (play)
    {
        play = false;
        return 0;//GAME_STATE; //returnar en konstant från state.h
    }
    else
    {
        return 0; //MENU_STATE;
    }
}

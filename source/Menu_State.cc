#include <string>
#include <stdexcept>
#include "Menu_State.h"

using namespace sf;

Menu_State :: Menu_State (Item const & I)
  :bg{I.ball_8}, bg1{I.Background}, selectedItemIndex{0}, _I{I}, play { false }
{
  std::string file = "item/font/BebasNeue-Regular.ttf";
  if ( !font.loadFromFile (file) )
        throw std::invalid_argument ("Unable to load font");
    text = sf::Text{ "Press <Enter> to start", font, 16 };

    bg.setPosition(sf::Vector2f{550.f,420.f});

    menu[0].setFont(font);
    menu[0].setColor(sf::Color::White);
    menu[0].setString("One ball");
    menu[0].setOrigin(menu[0].getGlobalBounds().width/2, menu[0].getGlobalBounds().height/2);
    menu[0].setPosition(sf::Vector2f(screen_width/2, screen_height/(MAX_NUMBER_OF_ITEMS +1)*1));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Eight Ball");
    menu[1].setOrigin(menu[1].getGlobalBounds().width/2, menu[1].getGlobalBounds().height/2);
    menu[1].setPosition(sf::Vector2f(screen_width/2, screen_height/(MAX_NUMBER_OF_ITEMS +1)*2));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::Red);
    menu[2].setString("Exit");
    menu[2].setOrigin(menu[2].getGlobalBounds().width/2, menu[2].getGlobalBounds().height/2);
    menu[2].setPosition(sf::Vector2f(screen_width/2, screen_height/(MAX_NUMBER_OF_ITEMS +1)*3));
}

void Menu_State::handle_event(sf::Event & event)
{

    if ( event.type == Event::KeyPressed )
    {
        if ( event.key.code == Keyboard::Key::Return )
            play = true;
        if ( event.key.code == Keyboard::Key::W)
            MoveUp();
        if ( event.key.code == Keyboard::Key::S)
          MoveDown();
    }
}

void Menu_State :: update()
{}

void Menu_State :: render (RenderWindow & target)
{
    auto bounds { text.getGlobalBounds () };
    auto size   { target.getSize () };

    text.setPosition ((size.x - bounds.width) / 2,
                      (size.y - bounds.height) / 2);

    target.draw (text);

    target.draw(bg1);
    target.draw(bg);
    for(int i=0; i<MAX_NUMBER_OF_ITEMS; i++)
    {
      target.draw(menu[i]);
    }
}

int Menu_State :: get_next_state()
{
    if (play)
    {
        play = false;
        return GAME_STATE; //returnar en konstant från state.h
    }
    else
    {
        return MENU_STATE;
    }
}

void Menu_State::MoveUp()
{
  if(selectedItemIndex -1 >= 0)
  {
    menu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex--;
    menu[selectedItemIndex].setColor(sf::Color::Black);
  }
}


void Menu_State::MoveDown()
{
  if(selectedItemIndex +1 < MAX_NUMBER_OF_ITEMS)
  {
    menu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex++;
    menu[selectedItemIndex].setColor(sf::Color::Black);
  }
}

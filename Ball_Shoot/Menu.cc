#include "Menu.h"


Menu::Menu(float width, float hight)
{
  if(!font.loadFromFile("BebasNeue-Regular.ttf"))
  {
    throw std::invalid_argument ("Unable to load font");
  }
  menu[0].setFont(font);
  menu[0].setColor(sf::Color::White);
  menu[0].setString("One ball");
  menu[0].setPosition(sf::Vector2f(width/2, hight/(MAX_NUMBER_OF_ITEMS +1)*1));

  menu[1].setFont(font);
  menu[1].setColor(sf::Color::White);
  menu[1].setString("Eight Ball");
  menu[1].setPosition(sf::Vector2f(width/2, hight/(MAX_NUMBER_OF_ITEMS +1)*2));

  menu[2].setFont(font);
  menu[2].setColor(sf::Color::Red);
  menu[2].setString("Exit");
  menu[2].setPosition(sf::Vector2f(width/2, hight/(MAX_NUMBER_OF_ITEMS +1)*3));

  selectedItemIndex=0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
  for(int i=0; i<MAX_NUMBER_OF_ITEMS; i++)
  {
    window.draw(menu[i]);
  }
}

void Menu::MoveUp()
{
  if(selectedItemIndex -1 >= 0)
  {
    menu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex--;
    menu[selectedItemIndex].setColor(sf::Color::Black);
  }

}


void Menu::MoveDown()
{
  if(selectedItemIndex +1 < MAX_NUMBER_OF_ITEMS)
  {
    menu[selectedItemIndex].setColor(sf::Color::White);
    selectedItemIndex++;
    menu[selectedItemIndex].setColor(sf::Color::Black);
  }
}

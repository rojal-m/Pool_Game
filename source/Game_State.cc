#include <string>
#include <stdexcept>
#include "Game_State.h"

using namespace sf;
using namespace std;

Game_State :: Game_State (Item const & I)
  :bg{I.Background},
   Balls {Ball{Vector2f{413,413},I,Col::WHITE},
          Ball{Vector2f{1022,413},I,Col::YELLOW},
	  Ball{Vector2f{1056,393},I,Col::YELLOW},
	  Ball{Vector2f{1056,433},I,Col::RED},
	  Ball{Vector2f{1090,374},I,Col::RED},
	  Ball{Vector2f{1090,413},I,Col::BLACK},
	  Ball{Vector2f{1090,452},I,Col::YELLOW},
	  Ball{Vector2f{1126,354},I,Col::YELLOW},
	  Ball{Vector2f{1126,393},I,Col::RED},
	  Ball{Vector2f{1126,433},I,Col::YELLOW},
	  Ball{Vector2f{1126,472},I,Col::RED},
	  Ball{Vector2f{1162,335},I,Col::RED},
	  Ball{Vector2f{1162,374},I,Col::RED},
	  Ball{Vector2f{1162,413},I,Col::YELLOW},
	  Ball{Vector2f{1162,452},I,Col::RED},
	  Ball{Vector2f{1162,491},I,Col::YELLOW}},
   W_ball{*std::find_if(Balls.begin(),Balls.end(),[](auto const& b){
	 return b.color == Col::WHITE;
       })},
   stick{I, W_ball},
   wall{},
   hole{},
   GameOver{I.GameOver}
{GameOver.setPosition(-1000,-1000);}

void Game_State :: handle_event (Event & event)
{
  /*if ( event.type == Event::MouseButtonReleased )
    {
    if ( event.mouseButton.button == Mouse::Button::Left )
    {
    balls.emplace_back (
    // get the coordinates of the mouse right now
    event.mouseButton.x,
    event.mouseButton.y);
    }
    }
    else if ( event.type == Event::KeyPressed )
    {
    if ( event.key.code == Keyboard::Key::Return )
    end_game = true;
    }*/
  if ( event.type == Event::KeyPressed )
  {
    if ( event.key.code == Keyboard::Key::W )
      stick.increasePower();
    else if ( event.key.code == Keyboard::Key::S )
      stick.decreasePower();
    else if ( event.key.code == Keyboard::Key::Return )
      end_game = true;
  }
  if(event.type == Event::MouseButtonPressed and stick.power>0)
    stick.shoot();
}

void Game_State :: update ()
{
  stick.update();
  handleCollisions(Balls,wall,hole);
  std::for_each(Balls.begin(),Balls.end(),[](Ball & B){
      B.update();
    });

  if (!ballsMoving(Balls) && stick.shot)
    stick.reposition(W_ball.position);

  if (!W_ball.visible)
    GameOver.setPosition(100,0);
}

void Game_State :: render (RenderWindow & window)
{
  stick.updateRotation(window);
  window.draw(bg);
  std::for_each(Balls.begin(),Balls.end(),[&window](Ball & B){
      B.draw(window);
    });
  stick.draw(window);
  window.draw(GameOver);
}

int Game_State :: get_next_state()
{
  if (end_game)
  {
    end_game = false;
    return MENU_STATE;
  }
  return GAME_STATE;
}

bool Game_State :: ballsMoving(std::vector<Ball> & b)
{
  bool ballsMoving{false};
  for(auto it{b.begin()};it != b.end(); ++it){
    if(it->moving)
    {
      ballsMoving = true;
      break;
    }
  }
  return ballsMoving;
}

void Game_State :: handleCollisions(std::vector<Ball> & b, Wall & W, Hole & h)
{
  for(auto i{b.begin()};i != b.end(); ++i){
    i->handleBallInHole(h);
    i->collideWith(W);
    for(auto j{i+1};j != b.end(); ++j){
      /*auto & firstBall = *i;
	auto & secondBall = *j;
	firstBall.collideWith(secondBall);*/
      i->collideWith(*j);
    }
  }
}
void Game_State :: cleanup ()
{/*
  for ( auto it { std::begin (Balls) }; it != std::end (Balls); )
  {
    // get the global bounds of our current ball
    auto bounds { it -> bounds () };
    // get a rectangle representing the screen
    FloatRect screen { 0, 0, screen_width, screen_height };
    if ( !screen.intersects (bounds) )
      it = balls.erase (it);
    else
      ++it;
      }*/
}

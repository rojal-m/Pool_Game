#include <string>
#include <stdexcept>
#include "Game_State.h"
#include "SourceManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;

Game_State :: Game_State()
  :Balls{new W_Ball{file_name, Id::B0},
  new Solids{file_name, Id::B1},
  new Solids{file_name, Id::B2},
  new Solids{file_name, Id::B3},
  new Solids{file_name, Id::B4},
  new Solids{file_name, Id::B5},
  new Solids{file_name, Id::B6},
  new Solids{file_name, Id::B7},
  new B_Ball{file_name, Id::B8},
  new Stripes{file_name, Id::B9},
  new Stripes{file_name, Id::B10},
  new Stripes{file_name, Id::B11},
  new Stripes{file_name, Id::B12},
  new Stripes{file_name, Id::B13},
  new Stripes{file_name, Id::B14},
  new Stripes{file_name, Id::B15}},

   W_ball{*std::find_if(Balls.begin(),Balls.end(),[](auto const& b){
	 return b->color == Col::WHITE;
       })},
   B_ball{*std::find_if(Balls.begin(),Balls.end(),[](auto const& b){
	 return b->color == Col::BLACK;
       })},
   stick{new Stick{*W_ball}},
   wall{new Wall{}},
   hole{new Hole{}},
   p1{"Player1", true},
   p2{"Player2", false}
{

 bg.setTexture(SourceManager<Texture>::load("item/image/background-01.png"));
 GameOver.setTexture(SourceManager<Texture>::load("item/image/Game_Over.png"));
 GameOver.setOrigin(GameOver.getLocalBounds().width/2,GameOver.getLocalBounds().height/2);
 GameOver.setPosition(-1000,-1000);
}

Game_State::~Game_State()
{
  delete stick;
  delete wall;
  delete hole;
  for_each(Balls.begin(),Balls.end(),[](auto const& b){
	 delete b;
       });
}

void Game_State :: handle_event (Event & event)
{
  if ( event.type == Event::KeyPressed )
  {
    if ( event.key.code == Keyboard::Key::W )
      stick->increasePower();
    else if ( event.key.code == Keyboard::Key::S )
      stick->decreasePower();
    else if ( event.key.code == Keyboard::Key::Escape )
      end_game = true;
  }
  if(event.type == Event::MouseButtonPressed)
  {
    auto mouse{event.mouseButton};
    if(mouse.button == Mouse::Button::Left)
    {
      if (W_ball->ballInHand)
      {
	       W_ball->ballInHand = false;
	       stick->visible = true;
	       stick->reposition();
      }

      else if(stick->power>0)
	stick->shoot();
    }
  }
}

void Game_State :: update ()
{
  stick->update();
  stick->updateRotation(m);

  handleCollisions(Balls,wall,hole);

  std::for_each(Balls.begin(),Balls.end(),[](Ball * B){
      B->update();
    });

  if (!ballsMoving(Balls) && stick->shot)
  {
    stick->reposition();
    if(p1.turn)
      gameLogic(p1,p2);
    else
      gameLogic(p2,p1);
    firstTouch = false;
    ballInHole.clear();
  }

  if (!W_ball->visible || W_ball->ballInHand){
    W_ballInHand();
  }
  if (!B_ball->visible){
    GameOver.setPosition(screen_width/2,screen_height/2);
    stick->visible = false;
  }
}

void Game_State :: render (RenderWindow & window)
{
  m.x = Mouse::getPosition(window).x;
  m.y = Mouse::getPosition(window).y;
  window.draw(bg);
  std::for_each(Balls.begin(),Balls.end(),[&window](Ball * B){
      B->draw(window);
    });
  stick->draw(window);
  window.draw(GameOver);
  p1.render(window);
  p2.render(window);
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

bool Game_State :: ballsMoving(std::vector<Ball*> & b)
{
  bool ballsMoving{false};
  for(auto it{b.begin()};it != b.end(); ++it){
    if((*it)->moving)
    {
      ballsMoving = true;
      break;
    }
  }
  return ballsMoving;
}

void Game_State :: handleCollisions(std::vector<Ball*> & b, Wall* W, Hole* h)
{
  for(auto i{b.begin()};i != b.end(); ++i)
  {
    if((*i)->handleBallInHole(*h))
    {
      if((*i)->color != Col::WHITE && !firstBallIHole)
      {
        firstBallIHole = true;
        ballInHole.push_back((*i)->color);
        //std::cout << ballInHole.at(0) << '\n';
      }
      if((*i)->color != Col::WHITE && firstBallIHole)
      {
        ballInHole.push_back((*i)->color);
        //std::cout << ballInHole.at(0) << '\n';
      }
      if((*i)->color == Col::WHITE)
      {
        takeTurn(p1,p2);
      }
    }
    (*i)->collideWith(*W);
    for(auto j{i+1};j != b.end(); ++j)
    {
      if((*i)->collideWith(*(*j)))
      {
        if(!firstTouch)
        {
          firstTouch = true;
          firstTouchCol = (*j)->color;
          //std::cout << firstTouchCol << '\n';
        }
      }
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
void Game_State :: gameLogic(Player & p1, Player & p2)
{
  if(!firstTouch)
  {
    W_ballInHand();
    return;
  }
  if(p1.assigned)
  {
    if(p1.assignBalls == firstTouchCol)
    {
      if(ballInHole.size() > 0)
      {
        return;
      }
      else
      {
        takeTurn(p1,p2);
        return;
      }
    }
    else
    {
      takeTurn(p1,p2);
      W_ballInHand();
      return;
    }
  }
  else
  {
    if(ballInHole.size() > 0)
    {
      if(firstBallIHole)
      {
        p1.assignBalls = ballInHole.at(0);
        if(p1.assignBalls == Col::SOLIDS)
          p2.assignBalls = Col::STRIPES;
        else
          p2.assignBalls = Col::SOLIDS;
        p1.assigned = true;
        p2.assigned =true;
      }
      return;
    }
    else
    {
      takeTurn(p1,p2);
      return;
    }
  }
}

void Game_State::W_ballInHand()
{
  W_ball->ballInHand = true;
  stick->visible = false;
  W_ball->visible = true;
  W_ball->position = m;
  W_ball->velocity = Vector2f{0.f,0.f};
}

#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Game_State.h"
#include "SourceManager.h"
#include <string>

using namespace sf;
using namespace std;

Game_State :: Game_State()
  :Balls{},
   W_ball{},
   B_ball{},
   stick{new Stick{}},
   wall{new Wall{}},
   hole{new Hole{}},
   p1{"Player1", true},
   p2{"Player2", false}
{
  //std::cout << 0 << '\n';
  load_data();
  //std::cout << 1 << '\n';
  stick->referBall(W_ball);
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
      if(!ballsMoving(Balls))
      {
        if (W_ball->ballInHand)
        {
	        W_ball->ballInHand = false;
	        stick->visible = true;
	        stick->reposition();
        }
        else if(stick->hasPower())
	        stick->shoot();
      }
    }
  }
}

void Game_State :: update ()
{
  stick->update(m);

  handleCollisions(Balls,wall,hole);

  std::for_each(Balls.begin(),Balls.end(),[](Ball * B){
      B->update();
    });

  if (!ballsMoving(Balls) && stick->shot)
  {
    stick->visible = true;
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
      }
      if((*i)->color != Col::WHITE && firstBallIHole)
      {
        ballInHole.push_back((*i)->color);
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
        }
      }
    }
  }
}
void Game_State :: gameLogic(Player & p1, Player & p2)
{
  if(!firstTouch)
  {
    takeTurn(p1,p2);
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
void Game_State::load_data()
{
  ifstream file("item/ExternalSource/positions_8ball.txt");
  string trash{};
  getline(file,trash);
  int id;
  float x, y;
  while(file >> id >> x >> y)
  {
    if(id == 0)
    {
      W_ball = new W_Ball{x,y,static_cast<Id>(id)};
      Balls.push_back(W_ball);
    }
    else if(id >= 1 && id <= 7)
    {
      Balls.push_back(new Solids{x,y,static_cast<Id>(id)});
    }
    else if(id >= 9 && id <= 15)
    {
      Balls.push_back(new Stripes{x,y,static_cast<Id>(id)});
    }
    else if(id == 8)
    {
      B_ball = new B_Ball{x,y,static_cast<Id>(id)};
      Balls.push_back(B_ball);
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


  if(W_ball->position.x<(wall->leftX+19))
  W_ball->position.x = wall->leftX+19;

  if(W_ball->position.x>(wall->rightX-19))
  W_ball->position.x = wall->rightX-19;

  if(W_ball->position.y<(wall->topY+19))
  W_ball->position.y = wall->topY+19;

  if(W_ball->position.y>(wall->bottomY-19))
  W_ball->position.y = wall->bottomY-19;

  bool inHole{};
  for(auto const& p : hole->position)
  {
    inHole += distFrom(W_ball->position,p) < hole->radius+19;
  }
  if(inHole)
  W_ball->visible = false;
  else
  W_ball->visible = true;
}

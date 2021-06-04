#include <fstream>
#include <string>
#include <stdexcept>
#include "Game_State_2.h"
#include <iostream>

using namespace sf;
using namespace std;

Game_State_2 :: Game_State_2()
  :Balls{},
   W_ball{},
   stick{new Stick{}},
   wall{new Wall{}},
   hole{new Hole{}},
   p1{"Player1",true},
   p2{"Player2",false}
{
  load_data();
  stick->referBall(W_ball);
  std::for_each(Balls.begin(),Balls.end(), [this](Ball * B){
        if(B->id != Id::B0)
        ballOnBoard.push_back(B->id);
    });
  std::sort(ballOnBoard.begin(), ballOnBoard.end());
  bg.setTexture(SourceManager<Texture>::load("item/image/background-01.png"));
  GameOver.setTexture(SourceManager<Texture>::load("item/image/Game_Over.png"));
  GameOver.setOrigin(GameOver.getLocalBounds().width/2,GameOver.getLocalBounds().height/2);
  GameOver.setPosition(-1000,-1000);
}

Game_State_2::~Game_State_2()
{
  delete stick;
  delete wall;
  delete hole;
  for_each(Balls.begin(),Balls.end(),[](auto const& b){
	 delete b;
       });
}

void Game_State_2::handle_event (Event & event)
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

      else if(stick->hasPower())
	     stick->shoot();
    }
  }
}

void Game_State_2:: update ()
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
      ballInHole = false;
  }

  if (!W_ball->visible || W_ball->ballInHand){
    W_ball->InHand(m,wall,hole);
  }
  if (ballOnBoard.size() == 0 ){
    game_over = true;
    GameOver.setPosition(screen_width/2,screen_height/2);
    stick->visible = false;
  }
  else if (*ballOnBoard.rbegin() != Id::B9){
    game_over = true;
    GameOver.setPosition(screen_width/2,screen_height/2);
    stick->visible = false;
  }
}

void Game_State_2 :: render (RenderWindow & window)
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

int Game_State_2 :: get_next_state()
{
  if (end_game)
  {
    end_game = false;
    return MENU_STATE;
  }
  return GAME_STATE_2;
}

bool Game_State_2 :: ballsMoving(std::vector<Ball*> & b)
{
  if (game_over)
    return false;
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

void Game_State_2 :: handleCollisions(std::vector<Ball*> & b, Wall* W, Hole* h)
{
  if(W_ball->ballInHand == true || game_over)
    return;
  for(auto i{b.begin()};i != b.end(); ++i)
  {
    if((*i)->handleBallInHole(*h))
    {
      if((*i)->id != Id::B0)
      {
        ballInHole = true;
        auto it = std::find(ballOnBoard.begin(), ballOnBoard.end(), (*i)->id);
        ballOnBoard.erase(it);
        if(ballOnBoard.size() == 0 )
          return;
        continue;
      }
      else
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
          firstTouchId = (*j)->id;
        }
      }
    }
  }
}
void Game_State_2::gameLogic(Player & p1, Player & p2)
{
  if (game_over)
    return;
  if(!firstTouch)
  {
    takeTurn(p1,p2);
    std::cout << 1  << '\n';
    W_ball->InHand(m,wall,hole);
    return;
  }
  if(ballOnBoard.at(0) == firstTouchId)
  {
    if(ballInHole)
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
    if(ballInHole)
    {
      return;
    }
    else
    {
      takeTurn(p1,p2);
      W_ball->InHand(m,wall,hole);
      return;
    }
  }
}

void Game_State_2::load_data()
{
  ifstream file("item/ExternalSource/positions_9ball.txt");
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
    else if(id >= 1 && id <= 8)
    {
      Balls.push_back(new Solids{x,y,static_cast<Id>(id)});
    }
    else if(id == 9)
    {
      Balls.push_back(new B_Ball{x,y,static_cast<Id>(id)});
    }
  }
}
/*
void Game_State_2::W_ballInHand()
{
  if (game_over)
    return;
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
}*/

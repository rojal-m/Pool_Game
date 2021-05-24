#include<vector>
#include "State.h"
#include "Item.h"
#include "Ball.h"
#include "Stick.h"
#include "Wall.h"
#include "Hole.h"

class Game_State : public State
{
private:
  sf::Sprite bg;
  std::vector<Ball> Balls;
  Ball & W_ball;
  Ball & B_ball;
  Stick stick;
  Wall wall;
  Hole hole;
  bool end_game{false};
  sf::Sprite GameOver;

  bool ballsMoving(std::vector<Ball> &);
  void handleCollisions(std::vector<Ball> &, Wall &, Hole &);
  void cleanup ();
public:
  Game_State (Item const &);
  void handle_event (sf::Event &) override;
  void update () override;
  void render (sf::RenderWindow &) override;
  virtual int get_next_state() override;
};

#include <vector>
#include "State.h"
#include "Item.h"
#include "Ball.h"
#include "Stick.h"
#include "Wall.h"
#include "Hole.h"
#include "Player.h"

class Game_State_2 : public State
{
private:
  sf::Sprite bg;
  sf::Sprite GameOver;

  std::vector<Ball*> Balls;
  Ball * W_ball;
  Ball * B_ball;
  Stick * stick;
  Wall * wall;
  Hole * hole;
  Player p1;
  Player p2;
  sf::Vector2f m{};
  bool end_game{false};

  bool firstTouch{false};
  Col firstTouchCol{};

  bool firstBallIHole{false};
  std::vector<Col> ballInHole{};

  void ShootBall1();
  void W_ballInHand();
  bool ballsMoving(std::vector<Ball*> &);
  void handleCollisions(std::vector<Ball*> &, Wall*, Hole*);
  void gameLogic(Player&,Player&);
  void cleanup ();

public:
  Game_State_2 (Item &);
  ~Game_State_2();
  Game_State(const Game_State&) = default;
  Game_State operator=(const Game_State&);
  void handle_event (sf::Event &) override;
  void update () override;
  void render (sf::RenderWindow &) override;
  virtual int get_next_state() override;
};

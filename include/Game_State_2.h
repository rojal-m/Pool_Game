#include <vector>
#include <string>
#include "State.h"
#include "Item.h"
#include "Ball.h"
#include "Stick.h"
#include "Wall.h"
#include "Hole.h"
#include "Player.h"

std::string const fileName{"positions_9ball.txt"};

class Game_State_2 : public State
{
private:
  sf::Sprite bg{};
  sf::Sprite GameOver{};

  std::vector<Ball*> Balls;
  Ball * W_ball;
  Stick * stick;
  Wall * wall;
  Hole * hole;
  Player p1;
  Player p2;
  sf::Vector2f m{};
  bool end_game{false};

  bool firstTouch{false};
  Id firstTouchId{};

  std::vector<Id> ballOnBoard{};
  bool ballInHole{false};

  void ShootBall1();
  void W_ballInHand();
  bool ballsMoving(std::vector<Ball*> &);
  void handleCollisions(std::vector<Ball*> &, Wall*, Hole*);
  void gameLogic(Player&,Player&);
  void cleanup ();

public:
  Game_State_2();
  ~Game_State_2();
  Game_State_2 (const Game_State_2&) = default;
  Game_State_2 operator=(const Game_State_2&);
  void handle_event (sf::Event &) override;
  void update () override;
  void render (sf::RenderWindow &) override;
  virtual int get_next_state() override;
};

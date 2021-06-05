#include <vector>
#include <map>
#include "State.h"
#include "Ball.h"
#include "Stick.h"
#include "Wall.h"
#include "Hole.h"
#include "Player.h"

std::string const file_name{"positions_8ball.txt"};

class Game_State : public State
{
private:
  sf::Sprite bg{};
  sf::Sprite GameOver{};

  std::vector<Ball*> Balls;
  W_Ball * W_ball;
  Heavy * B_ball;
  std::map<Col,InvisiBall*> Invisi_ball;
  Stick* stick;
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

  //void W_ballInHand();
  bool ballsMoving(std::vector<Ball*> &);
  void handleCollisions(std::vector<Ball*> &, Wall*, Hole*);
  void gameLogic(Player&,Player&);
  void load_data();

public:
  Game_State ();
  ~Game_State();
  Game_State(const Game_State&) = default;
  Game_State operator=(const Game_State&);
  void handle_event (sf::Event &) override;
  void update () override;
  void render (sf::RenderWindow &) override;
  virtual int get_next_state() override;
};

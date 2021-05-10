#include "State.h"
#include "Game.h"

#include<vector>

class Game_State: public State{
//Allt som finns i state ska vara public här(polymorphism)

public:
  void Handle_Event (sf::Event);
  void update ();
  void render();
  void Get_Next_State();

private:
  bool game_end{false};
  void clean_After_Game();

  std::vector<Balls> All_Balls_Now{};
};

#endif

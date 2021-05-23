#include <SFML/Graphics.hpp> // includes most things in SFML
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
using namespace sf;

int main ()
{
  Clock clock{};
  Item I;
  RenderWindow window{VideoMode{width, height},"Pool"};
  Texture t1,t2;
<<<<<<< HEAD
    if (!t1.loadFromFile ("image/background.png"))
        return 1;
    if (!t2.loadFromFile ("image/stick.png"))
        return 1;

    // skapa sprite
    Sprite bg{I.Background};
    std::vector<Ball> Balls;
    std::transform(ConstantBalls.begin(),ConstantBalls.end(),std::back_inserter(Balls),
		   [&I](auto const& a){
		     return Ball{a.first,I,a.second};
		   });
    Ball& W_ball{ *std::find_if(Balls.begin(),Balls.end(),[](auto const& b){
	    return b.color == Col::WHITE;
	})};
    //Balls.at(Balls.size() -1)};
    Stick stick{I.Stick, I};
    Wall wall;
    Hole hole;
=======
  if (!t1.loadFromFile ("image/background.png"))
    return 1;
  if (!t2.loadFromFile ("image/stick.png"))
    return 1;

  // skapa sprite
  Sprite bg{I.Background};
  std::vector<Ball> Balls;
  std::transform(ConstantBalls.begin(),ConstantBalls.end(),std::back_inserter(Balls),
		 [&I](auto const& a){
		   return Ball{a.first,I,a.second};
		 });
  Ball& W_ball{ *std::find_if(Balls.begin(),Balls.end(),[](auto const& b){
	return b.color == Col::WHITE;
      })};
  //Balls.at(Balls.size() -1)};
  Stick stick{I.Stick};
  Wall wall;
  Hole hole;
>>>>>>> 0c2b3a552c048a3cb86f7f5d856d5eca2da78b61


  while ( window.isOpen () )
  {
    Event event;
    while ( window.pollEvent(event) )
    {
      if ( event.type == Event::Closed )
      {
	window.close ();
      }
    }

    window.clear();

    handleCollisions(Balls,wall,hole);

    stick.update(event,window,W_ball);
    std::for_each(Balls.begin(),Balls.end(),[](Ball & B){
	B.update();
      });
    if (!ballsMoving(Balls) && stick.shot)
    {
      stick.reposition(W_ball.position);
    }
    window.draw(bg);

    std::for_each(Balls.begin(),Balls.end(),[&window](Ball & B){
	B.draw(window);
      });
    stick.draw(window);
    window.display();
    delay(clock);
  }
}

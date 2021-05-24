#include "Item.h"
#include "Game.h"

int main ()
{
  Item I;
  Game g { "Pool", screen_width, screen_height, I};
  g.start();
}

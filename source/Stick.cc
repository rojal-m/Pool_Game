#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <random>
#include <math.h>
#include "Stick.h"
#include "SourceManager.h"

using namespace sf;
using namespace std;

Stick::Stick()
  :power{0}, rotation {0}, shot{false}, visible{true}
{
  load_data("stick.txt");
  stick.setOrigin(970,11);
}

void Stick::update(Vector2f & m)
{
  if(shot)
    visible = false;

  if (!visible)
    return;

  updateRotation(m);
}

void Stick::draw(RenderWindow& w)
{
  if (!visible)
    return;

  stick.setRotation(rotation);
  stick.setPosition(position);
  w.draw(stick);
}

void Stick::updateRotation(Vector2f & v)
{
  float opposite = v.y - position.y;
  float adjescent = v.x - position.x;
  if(opposite < 0 && adjescent < 0)
    rotation = 180+(180*atan(opposite/adjescent))/pi;
  if(opposite > 0 && adjescent < 0)
    rotation = 180+(180*atan(opposite/adjescent))/pi;
  if(opposite < 0 && adjescent > 0)
    rotation = 360+(180*atan(opposite/adjescent))/pi;
  if(opposite > 0 && adjescent > 0)
    rotation = (180*atan(opposite/adjescent))/pi;
}

void Stick::increasePower()
{
  if (!visible)
    return;
  if(power > max_power)
    return;
  power += 100;
  Vector2f v = stick.getOrigin();
  stick.setOrigin(v.x+5,v.y);
}

void Stick::decreasePower()
{
  if (!visible)
    return;
  if(power <= 0){
    power = 0;
    return;
  }
  power -= 100;
  Vector2f v = stick.getOrigin();
  stick.setOrigin(v.x-5,v.y);
}

bool Stick::hasPower()
{
  return power != 0;
}

void Stick::shoot()
{
  if (!visible || power == 0)
    return;
  random_device rd{};
  uniform_real_distribution<float> r_pow {power-power_interval, power+power_interval};
  uniform_real_distribution<float> r_angle {rotation-direction_interval, rotation+direction_interval};
  Wball->onShoot(r_pow(rd),r_angle(rd));
  power = 0;
  stick.setOrigin(950,11);
  shot = true;
  strike.play();
}

void Stick::reposition()
{
  if (!visible)
    return;
  position = Wball->position;
  stick.setOrigin(970,11);
  shot = false;
}
void Stick::referBall(W_Ball * B)
{
  Wball = B;
  position = Wball->position;
}
void Stick::load_data(std::string const & file_name)
{
  ifstream file("item/ExternalSource/"+file_name);
  string trash{};
  getline(file,trash);
  string textureFileName;
  string soundFileName;

  file >> power_interval >> direction_interval >> max_power >> textureFileName >> soundFileName;

  stick.setTexture(SourceManager<Texture>::load("item/image/"+textureFileName));
  strike.setBuffer(SourceManager<SoundBuffer>::load("item/Music/"+soundFileName));

  file.close();
}

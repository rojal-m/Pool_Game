#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <utility>
#include <stdexcept>

template <typename T>
class SourceManager
{

public:

    static T & load (const std::string & file);
private:

    static std::unordered_map <std::string, std::unique_ptr<T>> sources_map;

};

using Texture_Manager   = Manager <sf::Texture>;
using Font_Manager      = Manager <sf::Font>;
using Sound_Manager     = Manager <sf::SoundBuffer>;

#include "../source/SourceManager.tcc"

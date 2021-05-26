#include <iostream>

template <typename T>
T & SourceManager<T>::load (const std::string & file)
{
    auto it { sources_map.find(file) };
    if ( it == sources_map.end () )
    {
        std::unique_ptr<T> tmp { std::make_unique<T> () };
        if ( !tmp -> loadFromFile (file) )
	       throw std::logic_error { "Error loading file"};
         it = sources_map.insert (std::make_pair (file, std::move(tmp))).first;
    }
    return *(it->second);
}

template <typename T>
std::unordered_map<std::string, std::unique_ptr<T>> SourceManager<T>::sources_map { };

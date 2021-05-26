#ifndef SOURCEMANAGER_H
#define SOURCEMANAGER_H
#include <map>

template <typename T>
class SourceManager
{
private:
    static std::map<std::string, T> resources;
public:
    static T loadFromFile(std::string const &);
    static T& load(std::string const &);

};

#include "../source/SourceManager.tcc"

#endif

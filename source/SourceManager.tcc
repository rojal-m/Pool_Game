template <typename T>
std::map<std::string, T> SourceManager<T>::resources{};

template <typename T>
T& SourceManager<T>::load(std::string const & f)
{
    {
        auto it {resources.find(f)};
        if (it == end(resources))
        {
            T res{loadFromFile(f)};
            it = resources.insert(make_pair(f, res)).first;
        }
        return it->second;
    }
}

template <typename T>
T SourceManager<T>:: loadFromFile(std::string const & f)
{
    T item;
    if (!item.loadFromFile(f))
    {
      throw std::logic_error{"Failed to open file"};
    }

    return item;
}

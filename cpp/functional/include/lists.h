#pragma once

// Find and replace in templated data structure (procedural)
namespace lists { // Avoid the namespace collision with "replace"

template <typename It, typename T>
int replace(It a, It b, const T &search, const T &with) {
    int hits = 0;
    for (It i =a; i != b; ++i) {
        auto &thing = *i;
        if (thing == search) {
            thing = with;
            ++hits;
        }
    }
    return hits;
}
}

/* Find and replace in doubly linked list (procedural)
template <typename T>
int replace(std::list<T> &list, T search, T replace) {
    int hits = 0;
    for (auto &thing : list) {
        if (thing == search) {
            thing == replace;
            ++hits;
        }
    }
    return hits;
}*/




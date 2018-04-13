#include <iostream>
#include "map.h"
#include "unordered_set.h"


int main()
{
    auto s = new unordered_multiset<char>();

    s->insert('l');
    s->insert('a');
    s->insert('f');
    s->insert('b');
    s->insert('i');
    s->insert('m');
    s->insert('b');
    s->insert('b');
    s->insert('i');
    s->insert('m');
    s->insert('i');
    s->insert('m');
    s->afficher();

    std::cout << "end: " << *(--s->end()) << std::endl;
    for (auto it = s->end(); it != s->begin();) {
        auto value = *(--it);
        std::cout << value << " ";
    }

    std::cout.flush();
    return 0;
}


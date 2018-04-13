#include <iostream>
#include "map.h"
#include "unordered_set.h"


int main()
{
//    auto s = new unordered_multiset<char>();
//
//    s->insert('l');
//    s->insert('a');
//    s->insert('f');
//    s->insert('b');
//    s->insert('i');
//    s->insert('m');
//    s->insert('b');
//    s->insert('b');
//    s->insert('i');
//    s->insert('m');
//    s->insert('i');
//    s->insert('m');
//    s->afficher();

//    std::cout << "end: " << *(--s->end()) << std::endl;
//    for (auto it = s->end(); it != s->begin();) {
//        auto value = *(--it);
//        std::cout << value << " ";
//    }

    auto m = new map<int, int>();

    m->insert(9);
    m->insert(12);
    m->insert(4);
    m->insert(8);
    m->insert(6);

//    m->insert(4);
//    m->insert(6);
//    m->insert(8);

    m->afficher();

    std::cout.flush();
    return 0;
}


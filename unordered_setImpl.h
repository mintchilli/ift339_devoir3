//
//  unordered_setImpl.h
//  unordered_multiset
//
//  Auteur : Jean Goulet
//  Copyleft 2017
//
//  Modifie par : Vincent Ducharme, Hiver 2018
//
//  Devoir fait par
//     Co�quipier 1 : Marcel Michel 17 081 685
//     Co�quipier 2 : Hugo Truchon 17 078 127

#ifndef unordered_multisetImpl_h
#define unordered_multisetImpl_h


///////////////////////////////////////////
// avancer et reculer un iterateur

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::avancer()
{
    if (++POS != (*ALV)->end());
    else
    {
        do ALV++;
        while ((*ALV) == nullptr);
        POS = (*ALV)->begin();
    }
}

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::reculer()
{
    if (POS != (*ALV)->begin())
        POS--;
    else
    {
        do ALV--;
        while ((*ALV) == nullptr);
        POS = --(*ALV)->end();
    }
}

/////////////////////////////////////////////////////////////////////
// fonctions generatrices

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE, classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::insert(const TYPE& VAL)
{
    // get position with hash function
    size_t size = REP.size() - 1;
    size_t alv = disperseur(VAL) % size;
    // if alveolus is empty, create new list with VAL
    if (REP[alv] == nullptr)
        REP[alv] = new list<TYPE>();
    REP[alv]->push_back(VAL);
    // increment SIZE
    SIZE++;
    // if (average alveolus size > max size), call rehash
    double avg = (double)SIZE / (double)size;
    if (avg > facteur_max)
    {
        size_t newSize = (size *2) +1;
        rehash(newSize);
    }

    return typename unordered_multiset<TYPE, classe_de_dispersion>::iterator(
            REP.begin() + alv, REP[alv]->end());
}

template <typename TYPE,typename classe_de_dispersion>
size_t unordered_multiset<TYPE, classe_de_dispersion>::erase(const TYPE& VAL)
{
    size_t nb=0;

    size_t size = REP.size() - 1;
    size_t alv = disperseur(VAL) % size;
    if (REP[alv] == nullptr)
        return 0;
    list<TYPE> *newList = new list<TYPE>();
    for (auto v : *REP[alv])
        if (v == VAL) nb++;
        else newList->push_back(v);
    delete REP[alv];
    if (newList->size() > 0)
        REP[alv] = newList;
    else
        REP[alv] = nullptr;
    SIZE -= nb;

    double avg = (double)SIZE / (double)size;
    if (facteur_min > avg)
    {
        size_t newSize = (size -1) /2;
        rehash(newSize);
    }

    return nb;
}

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE, classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::erase(typename unordered_multiset<TYPE, classe_de_dispersion>::iterator i)
{
    (*i.ALV)->erase(i.POS);
    return i;
}

#endif // unordered_multisetImpl_h

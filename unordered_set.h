//
//  unordered_set.h
//  unordered_multiset
//
//  Jean Goulet
//  Copyleft 2017 UdeS
//

#ifndef unordered_multiset_h
#define unordered_multiset_h

#include <vector>
#include <list>
#include <sstream>

using std::vector;
using std::list;

template <typename TYPE,typename classe_de_dispersion=std::hash<TYPE>>
class unordered_multiset
{
private:
    classe_de_dispersion disperseur;
    double facteur_min, facteur_max;
    size_t SIZE;
    vector<list<TYPE>*> REP;
public:
    class iterator;
    unordered_multiset(size_t = 1);  //nombre minimal d'alveoles utiles
    ~unordered_multiset();
    unordered_multiset(const unordered_multiset&);
    unordered_multiset& operator=(const unordered_multiset&);

    void swap(unordered_multiset&);
    void rehash(size_t);

    iterator insert(const TYPE& VAL);
    size_t erase(const TYPE& VAL);
    iterator erase(iterator);

    size_t count(const TYPE& VAL) const;

    size_t size() const { return SIZE; }
    bool empty() const { return SIZE == 0; }

    iterator begin();
    iterator end();

    //mise au point
    void afficher() const;
    void ligne(std::stringstream& s) const;
};

template <typename TYPE,typename classe_de_dispersion>
class unordered_multiset<TYPE, classe_de_dispersion>::iterator
{
    friend class unordered_multiset<TYPE>;
private:
    typename vector<list<TYPE>*>::iterator ALV;
    typename list<TYPE>::iterator POS;
    void avancer();
    void reculer();
public:
    iterator() { }
    iterator(typename vector<list<TYPE>*>::iterator alv, typename list<TYPE>::iterator pos)
    {
        ALV = alv;
        POS = pos;
    }
    const TYPE& operator*() const { return *POS; }
    iterator& operator++() { avancer(); return *this; }
    iterator operator++(int) { iterator copie(*this); avancer(); return copie; }
    iterator& operator--() { reculer(); return *this; }
    iterator operator--(int) { iterator copie(*this); reculer(); return copie; }
    bool operator==(const iterator& dr) const
    {
        if (ALV != dr.ALV)
            return false;
        return POS == dr.POS;
    }
    bool operator!=(const iterator& dr) const { return !(*this == dr); }
};

/////////////////////////////////////////////////////////////////////
// fonctions de base (constructeur, copieur, destructeur)
template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE, classe_de_dispersion>::unordered_multiset(size_t alvmin)
{
    facteur_max = 2.0;
    facteur_min = 0.75;
    size_t nbalv = 1;
    while (nbalv <= alvmin)
        nbalv += nbalv;
    //nbalv est la puissance de 2 superieure a alvmin
    SIZE = 0;
    for (size_t i = 0;i < nbalv;++i)
        REP.push_back(nullptr);
    REP.back() = new list<TYPE>();;
}

template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE, classe_de_dispersion>::~unordered_multiset()
{
    facteur_max = 2.0;
    facteur_min = 0.5;
    SIZE = 0;
    for (auto& p : REP)delete p;
}

template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE, classe_de_dispersion>::unordered_multiset(const unordered_multiset& source)
{
    facteur_max = source.facteur_max;
    facteur_min = source.facteur_min;
    SIZE = source.SIZE;
    REP.resize(source.REP.size());
    for (size_t i = 0;i < REP.size();++i)
        if (source.REP[i] == nullptr)
            REP[i] = nullptr;
        else
            REP[i] = new list<TYPE>(*source.REP[i]);
}

template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE,classe_de_dispersion>& unordered_multiset<TYPE,classe_de_dispersion>
::operator=(const unordered_multiset& source)
{
    if (this != &source)
    {
        unordered_multiset<TYPE, classe_de_dispersion> copie(source);
        swap(copie);
    }
    return *this;
}

/////////////////////////////////////////////////////////////////////
// swap
template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::swap(unordered_multiset& deux)
{
    std::swap(facteur_min, deux.facteur_min);
    std::swap(facteur_max, deux.facteur_max);
    std::swap(SIZE, deux.SIZE);
    std::swap(REP, deux.REP);
}

/////////////////////////////////////////////////////////////////////
// rehash

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::rehash(size_t nbalv)
{
    unordered_multiset<TYPE, classe_de_dispersion> copie(nbalv);
    for (auto& x : *this)
        copie.insert(x);
    swap(copie);
}


/////////////////////////////////////////////////////////////////////
// count
template <typename TYPE,typename classe_de_dispersion>
size_t unordered_multiset<TYPE, classe_de_dispersion>::count(const TYPE& VAL) const
{
    size_t alv = disperseur(VAL) % (REP.size() - 1);
    if (REP[alv] == nullptr)
        return 0;
    return std::count(REP[alv]->begin(), REP[alv]->end(), VAL);
}

/////////////////////////////////////////////////////////////////////
// iteration

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::begin()
{
    auto i = REP.begin();
    while (*i == nullptr)
        ++i;
    return iterator(i, (*i)->begin());
}

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::end()
{
    iterator fin;
    fin.ALV = --REP.end();
    fin.POS = REP.back()->begin();
    return fin;
}

/////////////////////////////////////////////////////////////////////
// mise au point

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::afficher() const
{
    using namespace std;
    size_t largeur = 60;
    size_t i;
    size_t nba = REP.size() - 1;
    string s1;
    if (SIZE > 1)
        s1 = "s";
    string s2;
    if (nba > 1)
        s2 = "s";
    stringstream out;
    cout << " " << string(largeur - 1, '-') << endl;
    out << SIZE << " element" << s1;
    ligne(out);
    out << nba << " alveole" << s2;
    ligne(out);
    for (i = 0;i < nba;++i)
    {
        out << "[" << i << "] ";
        if (REP[i] != nullptr)
            for (auto x : *REP[i])
                out << x << " ";
        ligne(out);
    }
    out << "[" << i << "]" << " fin";
    ligne(out);
    cout << " " << string(largeur - 1, '-') << endl;
}

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::ligne(std::stringstream& out)const
{
    size_t largeur = 60;
    std::string s1 = std::string("| ") + out.str();
    s1 += std::string(largeur, ' ');
    s1 = s1.substr(0, largeur) + "|";
    out.str(" ");
    out.clear();
    std::cout << s1 << std::endl;
}

#include "unordered_setImpl.h"

#endif /* unordered_multiset_h */

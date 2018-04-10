//
//  mapImpl.h
//
//  Auteur : Jean Goulet
//  Copyleft  2017 UdeS
//
//  Modifie par : Vincent Ducharme, Hiver 2018
//
//  Devoir fait par
//     Coéquipier 1 : Marcel Michel 17 081 685
//     Coéquipier 2 :

#ifndef mapImpl_h
#define mapImpl_h

#include <algorithm>

///////////////////////////////////////////////////////////////////////////
// lower_bound O(log n)

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::lower_bound(const Tclef& c) const
{
	int compteur = 0;
	auto val = APRES->GAUCHE->CONTENU->first;
	auto noeud = APRES->GAUCHE;
	while (noeud->CONTENU->first != c)
	{
		if (c < noeud->CONTENU->first)
		{
			noeud = noeud->GAUCHE;
			compteur++;
		}
		else if (c > noeud->CONTENU->first)
		{
			noeud = noeud->DROITE;
			compteur++;
		}
		else if (c == noeud->CONTENU->first)
			return iterator(noeud);
		else if(compteur == SIZE)
		{
			break;
		}
	}
	//auto smeg = APRES->GAUCHE->CONTENU->first;
	//if(c == APRES->GAUCHE->CONTENU->first)
	//	return iterator(APRES->GAUCHE);
	//else
	//{

	//}
	return iterator(noeud);
}


///////////////////////////////////////////////////////////////////////////
//erase a partir d'une position

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::erase(iterator i)
{
    assert(i!=end());
    erase(i++->first);
    return i;
}

///////////////////////////////////////////////////////////////////////////
//insert avec indice

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::insert(iterator j, const Tclef& c)
{
    return insert(c).first;
}

///////////////////////////////////////////////////////////////////////////
// gestion de l'equilibre de l'arbre


//effectuer une rotation simple de la gauche vers la droite
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_gauche_droite(noeud*& p)
{
}

//effectuer une rotation simple de la droite vers la gauche
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_droite_gauche(noeud*& p)
{
}


#endif /* mapImpl_h */

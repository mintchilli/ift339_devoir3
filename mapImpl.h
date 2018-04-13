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
//     Coéquipier 2 : Hugo Truchon 17 078 127

#ifndef mapImpl_h
#define mapImpl_h

#include <algorithm>

///////////////////////////////////////////////////////////////////////////
// lower_bound O(log n)

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::lower_bound(const Tclef& c) const
{
	int compteur = 0;
	auto noeud = APRES->GAUCHE;
	while (noeud->CONTENU->first != c)
	{
		if (compteur == SIZE)
		{
			break;
		}
		else if (c < noeud->CONTENU->first)
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

	}
	return iterator(noeud);
}


///////////////////////////////////////////////////////////////////////////
//erase a partir d'une position

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::erase(iterator i)
{
	assert(i != end());
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
	noeud *temp = p->GAUCHE;
	int ia = temp->INDICE;
	int ib = p->INDICE;
	int nib = -ia - std::max(0, -ia) - 1 + ib;
	int nia = ia - std::max(0, -nib) - 1;
	temp->INDICE = nia;
	p->INDICE = nib;

	p->GAUCHE = temp->DROITE;
	if (p->GAUCHE != nullptr)
		p->GAUCHE->PARENT = p;
	temp->DROITE = p;
	temp->PARENT = p->PARENT;
	p->PARENT = temp;
	p = temp;
}

//effectuer une rotation simple de la droite vers la gauche
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_droite_gauche(noeud*& p)
{
	noeud *temp = p->DROITE;
//	int ia = temp->INDICE;
//	int ib = p->INDICE;
//	int nib = -ia - std::max(0, -ia) - 1 + ib;
//	int nia = ia - std::max(0, -nib) - 1;
	int ia = p->INDICE;
	int ib = temp->INDICE;
	int nia = ia + std::max(0, -ib) +1;
	int nib = ib + nia + std::max(0, -nia) +1;
	temp->INDICE = nib;
	p->INDICE = nia;

	p->DROITE = temp->GAUCHE;
	if (p->DROITE != nullptr)
		p->DROITE->PARENT = p;
	temp->GAUCHE = p;
	temp->PARENT = p->PARENT;
	p->PARENT = temp;
	p = temp;
}


#endif /* mapImpl_h */

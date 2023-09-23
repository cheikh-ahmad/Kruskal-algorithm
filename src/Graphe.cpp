#include "Graphe.hpp"
#include <algorithm>

Graphe::Graphe() : sommets_(), aretes_(), gc_()
{

}

Graphe::Graphe(std::vector<Sommet*>const& sommets, std::vector<Arete*>const& aretes) : sommets_(), aretes_(), gc_()
{
	for(Sommet* const sommet: sommets)
		ajoute_sommet(sommet);
	for(Arete* const arete: aretes)
		ajoute_arete(arete);
}

Graphe::Graphe(const Graphe * const graphe) : Graphe(graphe->get_sommets(), graphe->get_aretes())
{

}

/* On indique au garbage collector que l'on a perdu toutes les références vers les sommets et les arêtes dans ce Graphe. */
Graphe::~Graphe()
{	
	for(Sommet* const sommet: sommets_)
		gc_.supprime_reference_sommet(sommet);
	for(Arete* const arete: aretes_)
		gc_.supprime_reference_arete(arete);
}

void Graphe::ajoute_sommet(Sommet* const sommet)
{
	if(sommet == nullptr)
		return;
	sommets_.push_back(sommet);
	gc_.ajoute_reference_sommet(sommet);
}


void Graphe::ajoute_sommet(const std::string& etiquette)
{
	Sommet*	sommet = new Sommet(etiquette);
	sommets_.push_back(sommet);
	gc_.ajoute_reference_sommet(sommet);
}

void Graphe::ajoute_arete(const Arete* const arete)
{
	if(arete == nullptr)
		return;

	Arete* nouvelle_arete = new Arete(arete);
	aretes_.push_back(nouvelle_arete);
	gc_.ajoute_reference_arete(nouvelle_arete);
}

void Graphe::ajoute_arete(Sommet* src, Sommet* dest, int poids)
{
	if(src == nullptr || dest == nullptr)
		return;
	Arete* nouvelle_arete = new Arete(src, dest, poids);
	aretes_.push_back(nouvelle_arete);
	gc_.ajoute_reference_arete(nouvelle_arete);
}

void Graphe::ajoute_arete(const std::string& etiquette_src, const std::string& etiquette_dest,
		int poids)
{
	Arete* nouvelle_arete = new Arete(etiquette_src, etiquette_dest, poids);
	aretes_.push_back(nouvelle_arete);
	gc_.ajoute_reference_arete(nouvelle_arete);
	/* Étant donné que nous ajoutons une arête à partir de sommets non existants, il faut rajouter ces sommets dans notre graphe. */
	ajoute_sommet(nouvelle_arete->get_src());
	ajoute_sommet(nouvelle_arete->get_dest());
}

int Graphe::poids() const
{
	int poids_total = 0;
	for(const Arete* arete: aretes_)
	{
		poids_total += arete->get_poids();
	}

	return poids_total;
}

bool Graphe::symetrique_existe(const Arete* const arete) const
{
	for(unsigned int i = 0; i < aretes_.size(); ++i)
	{
		Arete* a = aretes_[i];
		// On compare par rapport à l'adresse
		if(arete->get_src() == a->get_dest() && arete->get_dest() == a->get_src() && arete->get_poids() == a->get_poids())
			return true;
	}

	return false;

}
/*  Non précisé dans le sujet, on admet ici que la méthode symétrise en place.
 *  Ainsi, l'algorithme de Kruskal symétrisera notre graphe.
 */
void Graphe::symetrise()
{
	for(unsigned int i = 0; i < aretes_.size(); ++i)
	{
		Arete* a = aretes_[i];
		// Si le symétrique de l'arete n'existe pas, alors on le rajoute dans le graphe.
		if(!symetrique_existe(a))
		{
			ajoute_arete(a->get_dest(), a->get_src(), a->get_poids());
		}
	}
}

int Graphe::find(const Sommet* const sommet) const
{
	return sommet->get_marque();
}

/* On fusionne les deux composantes connexes de s1 et s2 en donnant à tous les sommets appartenant à la composante connexe
 * de s1 la marque de la composante connexe de s2.
 */
void Graphe::reunion(const Sommet* const s1, const Sommet* const s2)
{
	int marque = s1->get_marque();
	for(Sommet* const s: sommets_)
	{
		if(s->get_marque() == marque)
			s->set_marque(s2->get_marque());
	}
}

Graphe* Graphe::kruskal()
{
	// Kruskal s'applique sur des graphes non orientés.
	symetrise();
		
	// Par défaut, il y a une composante connexe par sommet: 
	for(unsigned int i = 0; i < sommets_.size(); ++i)
	{
		sommets_[i]->set_marque(i);
	}

	// On trie les aretes, on utilise l'operateur < surchargé dans Arete.hpp
	std::sort(aretes_.begin(), aretes_.end(), [](const Arete* const a1, const Arete* const a2) -> bool
		{
		
			return *a1 < *a2;
		});
	
	// Vector d'aretes que nous allons garder pour faire notre arbre couvrant minimal.
	std::vector<Arete*> aretes;
	for(Arete* const a: aretes_)
	{
		if(find(a->get_src()) != find(a->get_dest()))
		{
			reunion(a->get_src(), a->get_dest());
			aretes.push_back(a);
		}
	}

	// On crée notre arbre couvrant minimal avec les sommets de notre graphe de départ, et les aretes
	// que l'on a choisi. C'est ici que l'on suppose que le graphe de départ est connexe.
	// Dans le cas contraire, Kruskal ne nous donnera pas un arbre.
	Graphe* acm = new Graphe(sommets_, aretes);

	// On symétrise l'arbre
	acm->symetrise();

	return acm;
}

std::vector<Sommet*> Graphe::get_sommets() const
{
	return sommets_;
}

std::vector<Arete*> Graphe::get_aretes() const
{
	return aretes_;
}

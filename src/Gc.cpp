#include "Gc.hpp"

std::unordered_map<Sommet*, unsigned int> Gc::sommetsCpt_ = std::unordered_map<Sommet*, unsigned int>();
std::unordered_map<Arete*, unsigned int> Gc::aretesCpt_ = std::unordered_map<Arete*, unsigned int>();

void Gc::ajoute_reference_sommet(Sommet* sommet)
{
	if(sommet == nullptr)
		return;
	std::unordered_map<Sommet*, unsigned int>::iterator it = sommetsCpt_.find(sommet);
	// Le sommet n'est pas encore dans le GC, on l'ajoute, et on lui met un compteur à 1.
	if(it == sommetsCpt_.end())
		sommetsCpt_.insert(std::make_pair(sommet, 1));
	else
		++(it->second);
}

void Gc::ajoute_reference_arete(Arete* arete)
{

	if(arete == nullptr)
		return;
	std::unordered_map<Arete*, unsigned int>::iterator it = aretesCpt_.find(arete);
	if(it == aretesCpt_.end())
		aretesCpt_.insert(std::make_pair(arete, 1));
	else
		++(it->second);
}

void Gc::supprime_reference_sommet(Sommet* sommet)
{

	if(sommet == nullptr)
		return;
	std::unordered_map<Sommet*, unsigned int>::iterator it = sommetsCpt_.find(sommet);
	// On peut désincrémenter le compte du sommet seulement s'il est déjà dans le GC
	if(it != sommetsCpt_.end())
	{
		--(it->second);
		// Le sommet n'est plus référencé par un graphe, on peut le "free", et le retirer du GC
		if(it->second == 0)
		{
			delete it->first;
			sommetsCpt_.erase(it);
		}
	}



}

void Gc::supprime_reference_arete(Arete* arete)
{
	if(arete == nullptr)
		return;

	std::unordered_map<Arete*, unsigned int>::iterator it = aretesCpt_.find(arete);
	if(it != aretesCpt_.end())
	{
		--(it->second);
		if(it->second == 0)
		{
			delete it->first;
			aretesCpt_.erase(it);
		}
	}
}



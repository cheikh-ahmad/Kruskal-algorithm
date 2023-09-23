#ifndef DEF_GC_HPP
#define DEF_GC_HPP

#include <vector>
#include <utility>
#include "Sommet.hpp"
#include "Arete.hpp"
#include <unordered_map>

/* Détail d'implémentation du GC
 * L'idée est de produire un ramasse miettes qui fonctionne par comptage.
 * À chaque création d'un sommet, on incrémente le compteur correspondant à ce sommet
 * afin d'indiquer au garbage collector que les graphes ont une référence de plus sur ce sommet.
 * Cela marche de manière équivalente avec les arêtes.
 * Lorsque l'on supprimera un graphe, les sommets appartenant à ce graphe auront tous leur compteur désincrémenté.
 * Lorsqu'un sommet arrive à un compteur égal à 0, cela indique qu'il n'est plus référencé par aucun graphe, et que
 * par ce fait, nous pouvons le supprimer.
 *
 * Nous avons décidé d'utiliser une hashtable pour stocker les correspondances pointeur à
 * comptage. La raison à cela plutôt qu'un vector de paires est que cette structure de données sera beaucoup plus
 * propice à la recherche de pointeurs (comme il est aisé de hashé un pointeur), et donc il sera plus rapide
 * d'incrémenter ou désincrémenter le nombre de références d'un pointeur donné.
 *
 * Les variables sommetsCpt_ et aretesCpt_ seront statiques, en effet, elles doivent être partagé parmi tous les graphes.
 */
class Gc
{
	private:
		/* Correspondance pointeur --> compteur */
		static std::unordered_map<Sommet*,  unsigned int> sommetsCpt_;
		static std::unordered_map<Arete*, unsigned int> aretesCpt_;
	public:
		/* Ces méthodes incrémente ou désincrémente le compteur correspondant à un pointeur donné 
		 * Quand on désincrémente le compteur d'un sommet ou d'une arête, on vérifie en même temps si
		 * ce compteur a atteint 0. Si c'est le cas, alors il n'est plus référencé dans aucun graphe, et donc
		 * on peut le supprimer */
		void ajoute_reference_sommet(Sommet* sommet);

		void ajoute_reference_arete(Arete* arete);


		void supprime_reference_sommet(Sommet* sommet);

		void supprime_reference_arete(Arete* arete);

};
#endif // DEF_GC_HPP

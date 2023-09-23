#ifndef DEF_GRAPHE_HPP
#define DEF_GRAPHE_HPP

#include "Arete.hpp"
#include <vector>
#include "Gc.hpp"

class Graphe
{
	private:
		std::vector<Sommet*> sommets_;
		std::vector<Arete*> aretes_;
		Gc gc_;
		/* Retourner vrai ou faux suivant si le symétrique de l'arete existe ou non dans le graphe.*/
		bool symetrique_existe(const Arete* const arete) const;

		int find(const Sommet* const sommet) const;
 
		void reunion(const Sommet* const s1, const Sommet* const s2);


	public:
		Graphe();

		Graphe(std::vector<Sommet*>const & sommets, std::vector<Arete*>const & aretes);

		Graphe(const Graphe * const graphe);

		~Graphe();

		void ajoute_sommet(Sommet* const sommet);

		void ajoute_sommet(const std::string& etiquette);

		void ajoute_arete(const Arete* const arete);

		void ajoute_arete(Sommet* src, Sommet* dest, int poids);

		void ajoute_arete(const std::string& etiquette_src, const std::string& etiquette_dest,
				int poids);

		/* Cette méthode calcule le poids sans distinction de si c'est un graphe symétrisé (c'est à dire non orienté) ou non.
		 * Par exemple, dans le cas où on applique Kruskal sur un graphe, le "vrai" poids de l'arbre sera arbre.poids() / 2 :
		 */
		int poids() const;

		void symetrise();

		/* L'algorithme de kruskal doit etre appliqué sur un graphe connexe. Si celui-ci n'est pas connexe,
		 * le graphe retourné ne sera pas un arbre. */
		Graphe* kruskal();

		std::vector<Sommet*> get_sommets() const;

		std::vector<Arete*> get_aretes() const;

};

inline std::ostream& operator<<(std::ostream& out, const Graphe& graphe)
{
	out << "Affichage du graphe : " << std::endl;
	out << "Sommets : " << std::endl;
	
	for(const Sommet* const sommet: graphe.get_sommets())
	{
		out << *sommet;
	}

	out << "Aretes : " << std::endl;

	for(const Arete* const arete: graphe.get_aretes())
	{
		out << *arete;
	}

	return out;
}

#endif // DEF_GRAPHE_HPP

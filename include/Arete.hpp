#ifndef DEF_ARETE_HPP
#define DEF_ARETE_HPP

#include "Sommet.hpp"

class Arete
{
	private:
		Sommet* src_;
		Sommet* dest_;
		int poids_;
	public:
		Arete(const std::string& etiquette_src, const std::string& etiquette_dest, int poids);	

		Arete(Sommet* const src, Sommet* const dest, int poids);

		Arete(const Arete* const arete);

		int get_poids() const;

		Sommet* get_src() const;

		Sommet* get_dest() const;

		void set_poids(int poids);

		bool operator<(const Arete& a) const;
};

inline std::ostream& operator<<(std::ostream& out, const Arete& arete)
{
	return out << "Arete tel que (src, dest, &src, &dest, poids) = (" << 
		arete.get_src()->get_etiquette() << ", " <<
	       	arete.get_dest()->get_etiquette() << ", " <<
		arete.get_src() << ", " <<
		arete.get_dest() << ", " <<
		arete.get_poids() << ")" << std::endl;
}

#endif // DEF_ARETE_HPP

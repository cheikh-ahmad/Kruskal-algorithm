#include "Arete.hpp"

Arete::Arete(const std::string& etiquette_src, const std::string& etiquette_dest, int poids) :
	src_(new Sommet(etiquette_src)), dest_(new Sommet(etiquette_dest)), poids_(poids)
{

}

Arete::Arete(Sommet* const src, Sommet* const dest, int poids) :
	src_(src), dest_(dest), poids_(poids)
{
	
}

Arete::Arete(const Arete* const arete) : src_(arete->get_src()),
	dest_(arete->get_dest()), poids_(arete->get_poids())
{
	
}

int Arete::get_poids() const
{
	return poids_;
}

Sommet* Arete::get_src() const
{
	return src_;
}

Sommet* Arete::get_dest() const
{
	return dest_;
}
void Arete::set_poids(int poids)
{
	poids_ = poids;
}

bool Arete::operator<(const Arete& a) const
{
	return get_poids() < a.get_poids();
}

#include "Sommet.hpp"

Sommet::Sommet(const std::string& etiquette) : etiquette_(etiquette)
{
	
}

Sommet::Sommet(const Sommet* const sommet) : etiquette_(sommet->get_etiquette())
{

}

std::string Sommet::get_etiquette() const
{
	return etiquette_;
}

void Sommet::set_marque(int marque)
{
	marque_ = marque;
}

int Sommet::get_marque() const
{
	return marque_;
}

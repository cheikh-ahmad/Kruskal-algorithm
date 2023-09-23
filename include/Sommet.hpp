#ifndef DEF_SOMMET_HPP
#define DEF_SOMMET_HPP

#include <iostream>

class Sommet
{
	private:
		std::string etiquette_;
		int marque_;
	public:
		Sommet(const std::string& etiquette);

		Sommet(const Sommet* const sommet);

		std::string get_etiquette() const;

		int get_marque() const;

		void set_marque(int marque);
};

inline std::ostream& operator<<(std::ostream& out, const Sommet& s)
{
	return out << "Sommet avec etiquette : " << s.get_etiquette() <<
		" et pointeur : " << &s << std::endl;
}

#endif // DEF_SOMMET_HPP


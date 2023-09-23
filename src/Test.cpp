#include "Graphe.hpp"

void aide()
{
	std::cout << "Les tests possibles sont : " << std::endl;
	std::cout << "make test_1 | graphe : test la création d'un graphe, avec des sommets, des aretes, avec un autre graphe, test les différentes méthodes" <<
		 " d'ajout de sommets, d'aretes, ..." << std::endl;
	std::cout << "make test_2 | garbage_collector : test le garbage collector" << std::endl;
	std::cout << "make test_3 | kruskal : test l'algorithme de kruskal" << std::endl;
	std::cout << "make test | Lance tous les tests à la fois" << std::endl;
}

void assert_test(std::string test_msg, bool condition)
{
	std::cerr << test_msg << " ";
	if(condition)
		std::cerr << "OK." << std::endl;
	else
	{
		std::cerr << "Failure." << std::endl;
		exit(EXIT_FAILURE);
	}
}
bool test_graphe()
{
	Graphe* g1 = new Graphe();

	// --------------------------------
	// Test ajoute_sommet et ajoute_arete
	std::cerr << "Creation d'un graphe g1 avec 8 sommets, et 4 aretes de poids : 20, -10, 5, 5" << std::endl;
	g1->ajoute_sommet("a");
	g1->ajoute_sommet("b");
	Sommet* s1 = new Sommet("c");
	Sommet* s2 = new Sommet("d");
	g1->ajoute_sommet(s1);
	g1->ajoute_sommet(s2);

	// Ici ajoute_arete devraient créer les 4 sommets.
	g1->ajoute_arete("abc", "def", 20);
	g1->ajoute_arete("abc", "def", -10);
	g1->ajoute_arete(s1, s2, 5);
	g1->ajoute_arete(new Arete(s1, s2, 5));

	assert_test("Poids(g1) == 20 ?", g1->poids() == 20);
	assert_test("Nombre de sommets de g1 == 8 ?", g1->get_sommets().size() == 8);


	// --------------------------------
	// Test création d'un graphe avec un autre graphe.
	std::cerr << "Creation d'un graphe g2 avec le graphe g2. On ajoute un sommet dans g2" << std::endl;
	Graphe* g2 = new Graphe(g1);
	g2->ajoute_sommet("nouveau sommet");
	assert_test("Nombre de sommets de g1 == 8 ?", g1->get_sommets().size() == 8);
	assert_test("Nombre de sommets de g2 == 9 ?", g2->get_sommets().size() == 9);
	assert_test("Poids(g1) == 20 ?", g1->poids() == 20);
	assert_test("Poids(g2) == 20 ?", g2->poids() == 20);

	delete g1;
	delete g2;

	// --------------------------------
	// Test création d'un graphe avec un vecteur d'arete et de sommets.
	std::cerr << "Creation d'un graphe g3 avec un vecteur d'aretes et de sommets" << std::endl;
	Sommet *s3 = new Sommet("a");
	Sommet *s4 = new Sommet("b");
	Arete* a1 = new Arete(s3, s4, 15);
	Graphe* g3 = new Graphe{{s3, s4}, {a1}};
	
	std::cerr << *g3 << std::endl;
	assert_test("Nombre de sommets de g3 == 2 ?", g3->get_sommets().size() == 2);
	assert_test("Poids(g3) == 15 ?", g3->poids() == 15);

	delete g3;
	return true;
}

bool test_garbage_collector()
{
	std::cerr << "On crée deux graphes, tel que un sommet est commun au deux" << std::endl;
	Sommet* s1 = new Sommet{"a"};
	Sommet* s2 = new Sommet{"b"};
	Graphe g1{};
	g1.ajoute_sommet(s1);
	std::cerr << "g1: " << g1 << std::endl;
	Arete* a1 = new Arete{s1, s2, 5};

	{
		Graphe g2{};
		g2.ajoute_sommet(s1);
		g2.ajoute_sommet(s2);
		g2.ajoute_arete(a1);
		std::cerr << "g2: " << g2 << std::endl;
		std::cerr << "Suppression du graphe g2" << std::endl;
	}

	std::cerr << "On s'attend à que le sommet b soit supprimé, mais pas le sommet a car il est encore dans g1, et que l'arête soit supprimé"
	       	<< std::endl;
	std::cerr << *s1 << std::endl;
	std::cerr << "Problème : Lorsque l'on delete un pointeur, celui-ci n'est pas mis à nullptr après."
		<< " Cela laisse aucun moyen de voir si un pointeur a bien été delete ou non. Après recherche sur Internet, nous avons"
		<< " rien trouvé de probant. Si ce n'est qu'utilisé des pointeurs intelligents (pas le sujet du TP), mettre nous même le pointeur"
		<< " à nullptr (ce qui n'est pas possible dans notre cas car il faudrait que cela affecte tous les pointeurs vers le sommet)."
		<< " La 'preuve' que nous avons que le sommet 'b' et l'arête sont bien supprimés et qu'en essayant de les afficher, on obtient"
		" un segfault. Nous avons mis l'affichage en commentaire pour ne pas faire échouer notre test, mais il est possible d'enlever le"
		<< " commentaire pour constater." << std::endl;
	/*
		std::cerr << *s2 << std::endl;
		std::cerr << *a1 << std::endl;
	*/
	
	return true;
}

bool test_kruskal()
{
	std::cerr << "On construit un graphe, dont l'acm a un poids de 39" << std::endl;

	Graphe * g1 = new Graphe{};
	Sommet* a = new Sommet("a");
	Sommet* b = new Sommet("b");
	Sommet* c = new Sommet("c");
	Sommet* d = new Sommet("d");
	Sommet* e = new Sommet("e");
	Sommet* f = new Sommet("f");
	Sommet* g = new Sommet("g");

	g1->ajoute_sommet(a);
	g1->ajoute_sommet(b);
	g1->ajoute_sommet(c);
	g1->ajoute_sommet(d);
	g1->ajoute_sommet(e);
	g1->ajoute_sommet(f);
	g1->ajoute_sommet(g);

	g1->ajoute_arete(a, d, 5);
	g1->ajoute_arete(a, b, 7);
	g1->ajoute_arete(b, d, 9);
	g1->ajoute_arete(d, e, 15);
	g1->ajoute_arete(d, f, 6);
	g1->ajoute_arete(f, e, 8);
	g1->ajoute_arete(f, g, 11);
	g1->ajoute_arete(e, g, 9);
	g1->ajoute_arete(b, e, 7);
	g1->ajoute_arete(e, c, 5);
	g1->ajoute_arete(e, c, 6);
	g1->ajoute_arete(b, c, 8);
	std::cerr << *g1 << std::endl;


	std::cerr << "Construction d'un acm" << std::endl;
	Graphe* acm = g1->kruskal();
	std::cerr << *acm << std::endl;
	// On divise par 2 car on la symétrie nous double les arêtes.
	assert_test("Poids(acm) == 39", acm->poids() / 2 == 39);
	std::cerr << "poids: " << acm->poids() / 2 << std::endl;

	delete g1;
	return true;
}
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		aide();
		exit(EXIT_SUCCESS);
	}

	bool test_ok = false;
	std::string arg = argv[1];
	if(arg == "graphe")
		test_ok = test_graphe();
	else if(arg == "kruskal")
		test_ok = test_kruskal();
	else if(arg == "garbage_collector")
		test_ok = test_garbage_collector();
	else
	{
		std::cerr << "Test non trouve" << std::endl;
		exit(EXIT_FAILURE);
	}

	if(test_ok)
	{
		std::cerr << "Test " << arg << " réalisé avec succes" << std::endl;
		exit(EXIT_SUCCESS);
	}
	else
	{
		std::cerr << "Test " << arg << " fini avec erreur" << std::endl;
		exit(EXIT_SUCCESS);
	}


}

#include "Teste.h"

#include <iostream>

void Teste::teste_all() const {
	teste_utils();
	teste_domain();
	teste_RepositoryOferta();
	teste_RepositoryLab();
	teste_RepositoryLabFailure();
	teste_service();
	teste_service_files();
	teste_service_lab();
	teste_undo();
}

void Teste::teste_utils() const {
	Utils utils;
	string s = utils.check_oferta("Sejur romantic", "Bahamas", "Calatorie cu avionul", "154.2");
	assert(s == "");
	s = utils.check_oferta("", "Bahamas", "Calatorie cu avionul", "154.2");
	assert(s == "Denumire invalida!\n");
	s = utils.check_oferta("Sejur romantic", "", "Calatorie cu avionul", "154.2");
	assert(s == "Destinatie invalida!\n");
	s = utils.check_oferta("Sejur romantic", "Bahamas", "", "154.2");
	assert(s == "Tip invalid!\n");
	s = utils.check_oferta("Sejur romantic", "Bahamas", "Calatorie cu avionul", "");
	assert(s == "Pret invalid!\n");
	s = utils.check_oferta("Sejur romantic", "Bahamas", "Calatorie cu avionul", "-5");
	assert(s == "Pret invalid!\n");
	s = utils.check_oferta("", "", "Calatorie cu avionul", "154.2");
	assert(s == "Denumire invalida!\nDestinatie invalida!\n");
	s = utils.check_oferta("", "Bahamas", "", "154.2");
	assert(s == "Denumire invalida!\nTip invalid!\n");
	s = utils.check_oferta("", "Bahamas", "Calatorie cu avionul", "");
	assert(s == "Denumire invalida!\nPret invalid!\n");
	s = utils.check_oferta("Sejur romantic", "", "", "154.2");
	assert(s == "Destinatie invalida!\nTip invalid!\n");
	s = utils.check_oferta("Sejur romantic", "", "Calatorie cu avionul", "");
	assert(s == "Destinatie invalida!\nPret invalid!\n");
	s = utils.check_oferta("Sejur romantic", "Bahamas", "", "");
	assert(s == "Tip invalid!\nPret invalid!\n");
	s = utils.check_oferta("", "", "", "154.2");
	assert(s == "Denumire invalida!\nDestinatie invalida!\nTip invalid!\n");
	s = utils.check_oferta("", "", "Calatorie cu avionul", "");
	assert(s == "Denumire invalida!\nDestinatie invalida!\nPret invalid!\n");
	s = utils.check_oferta("Sejur romantic", "", "", "");
	assert(s == "Destinatie invalida!\nTip invalid!\nPret invalid!\n");
	s = utils.check_oferta("", "", "", "");
	assert(s == "Denumire invalida!\nDestinatie invalida!\nTip invalid!\nPret invalid!\n");
	int nr = utils.check_nr("a2");
	assert(nr == 0);
	nr = utils.check_nr("223-2");
	assert(nr == 0);
	nr = utils.check_nr("13.23.21.");
	assert(nr == 0);
	nr = utils.check_nr("1221");
	assert(nr == 1);
	nr = utils.check_nr("-21");
	assert(nr == 1);
	nr = utils.check_nr("12.3");
	assert(nr == 2);
	nr = utils.check_nr("-.3");
	assert(nr == 2);
}

void Teste::teste_domain() const {
	Oferta of1{ "Road trip", "Franta", "Family",  static_cast <float>(12.3) };
	Oferta of2{ of1 };
	assert(of1 == of2);
	of1.set_denumire("Sejur romantic");
	assert(of1.get_denumire() == "Sejur romantic");
	assert((of1 == of2) == false);
	of1.set_denumire("Road trip");

	of1.set_destinatie("Bahamas");
	assert(of1.get_destinatie() == "Bahamas");
	assert(of1 == of2);
}

void Teste::teste_RepositoryOferta() const {
	RepositoryOferta repo;
	assert(repo.len() == 0);
	Oferta of1{ "Sejur romantic", "Bahamas", "Calatorie cu avionul", static_cast <float>(154.2) };
	repo.adauga(of1);
	assert(repo.len() == 1);
	try {
		repo.adauga(of1);
		assert(false);
	}
	catch (RepoExcept re) {
		assert (true);
	}
	try {
		repo.modifica(of1);
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
	Oferta of2{ "Sejur romantic", "Paris", "Calatorie cu avionul", static_cast <float>(154.2) };
	repo.modifica(of2);
	of2.set_denumire("Sejur");
	try {
		repo.modifica(of2);
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
	Oferta of3 = repo.cauta("Sejur romantic");
	try {
		of2 = repo.cauta("a");
		assert(false);
	}
	catch (RepoExcept se) {
		assert(true);
	}
	assert(of3.get_destinatie() == "Paris");
	vector<Oferta> repo_all = repo.get_all();
	assert(size(repo_all) == 1);
	try {
		repo.sterge("Sejur");
		assert(false);
	}
	catch (RepoExcept se) {
		assert(true);
	}
	repo.sterge("Sejur romantic");
	assert(repo.len() == 0);
	try {
		repo.sterge("Sejur romantic");
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
	try {
		repo.modifica(of2);
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
}

void Teste::teste_RepositoryLab() const {
	RepositoryLab repo{ 0 };
	assert(repo.len() == 0);
	Oferta of1{ "Sejur romantic", "Bahamas", "Calatorie cu avionul", static_cast <float>(154.2) };
	repo.adauga(of1);
	assert(repo.len() == 1);
	try {
		repo.adauga(of1);
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
	try {
		repo.modifica(of1);
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
	Oferta of2{ "Sejur romantic", "Paris", "Calatorie cu avionul", static_cast <float>(154.2) };
	repo.modifica(of2);
	of2.set_denumire("Sejur");
	try {
		repo.modifica(of2);
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
	Oferta of3 = repo.cauta("Sejur romantic");
	try {
		of2 = repo.cauta("a");
		assert(false);
	}
	catch (RepoExcept se) {
		assert(true);
	}
	assert(of3.get_destinatie() == "Paris");
	vector<Oferta> repo_all = repo.get_all();
	assert(size(repo_all) == 1);
	try {
		repo.sterge("Sejur");
		assert(false);
	}
	catch (RepoExcept se) {
		assert(true);
	}
	repo.sterge("Sejur romantic");
	assert(repo.len() == 0);
	try {
		repo.sterge("Sejur romantic");
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
	try {
		repo.modifica(of2);
		assert(false);
	}
	catch (RepoExcept re) {
		assert(true);
	}
}

void Teste::teste_RepositoryLabFailure() const {
	RepositoryLab repo{ 1 };
	assert(repo.len() == 0);
	Oferta of1{ "Sejur romantic", "Bahamas", "Calatorie cu avionul", static_cast <float>(154.2) };
	for (int i = 0; i < 100; i++) {
		assert(repo.len() == 0);
		try {
			repo.adauga(of1);
			assert(false);
		}
		catch (RepoExcept re) {
			assert(true);
		}
		try {
			repo.modifica(of1);
			assert(false);
		}
		catch (RepoExcept re) {
			assert(true);
		}
		try {
			repo.sterge("Sejur romantic");
			assert(false);
		}
		catch (RepoExcept re) {
			assert(true);
		}
		try {
			repo.cauta("Sejur romantic");
			assert(false);
		}
		catch (RepoExcept re) {
			assert(true);
		}
		try {
			assert(size(repo.get_all()) == 0);
			assert(false);
		}
		catch (RepoExcept re) {
			assert(true);
		}
	}
}

void Teste::teste_service() const {
	RepositoryOferta RepositoryOferta;
	Service service(RepositoryOferta);
	service.service_adauga("Sejur", "Paris", "Family", "13.4");
	try {
		service.service_adauga("Sejur romantic", "Paris", "", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	Oferta of = service.service_cauta("Sejur");
	assert(of.get_destinatie() == "Paris");
	service.service_modifica("Sejur", "Spania", "Family", "10");
	try {
		service.service_modifica("Sejur", "Paris", "", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	vector<Oferta> repo_all = service.service_get_all();
	assert(size(repo_all) == 1);
	service.service_sterge("Sejur");
	try {
		repo_all = service.service_sortare("ada", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("2", "ada");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("3", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("1", "4");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(se.get_message() == "Selectie invalid!\n");
	}

	service.service_adauga("a", "2", "e", "13.5");
	service.service_adauga("b", "3", "e", "13.4");
	service.service_adauga("d", "1", "X", "10");
	service.service_adauga("c", "1", "X", "10");

	
	repo_all = service.service_sortare("0", "0");
	assert(repo_all[0].get_denumire() == "a");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "c");
	assert(repo_all[3].get_denumire() == "d");
	service.service_sterge("d");

	repo_all = service.service_sortare("1", "0");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "b");

	repo_all = service.service_sortare("2", "0");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "a");

	repo_all = service.service_sortare("0", "1");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "a");

	repo_all = service.service_sortare("1", "1");
	assert(repo_all[0].get_denumire() == "b");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "c");

	service.service_adauga("d", "1", "z", "10");
	repo_all = service.service_sortare("2", "1");
	assert(repo_all[0].get_denumire() == "d");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "b");
	assert(repo_all[3].get_denumire() == "c");

	service.service_sterge("a");
	service.service_sterge("b");
	service.service_sterge("c");
	service.service_sterge("d");

	service.service_adauga("d", "1", "z", "10.123");
	try {
		repo_all = service.service_filtrare_destinatie("0", "d");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_filtrare_pret("0", "10.123");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_sterge("d");
	try {
		repo_all = service.service_filtrare_destinatie("a", "b");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_destinatie("2", "b");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("a", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("3", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("1", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}

	service.service_adauga("1", "a", "e", "13.5");
	service.service_adauga("2", "a", "e", "13.4");
	service.service_adauga("3", "b", "X", "10");

	repo_all = service.service_filtrare_destinatie("0", "a");
	assert(size(repo_all) == 2);
	repo_all = service.service_filtrare_destinatie("1", "a");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("0", "11");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("1", "13.4");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("2", "10");
	assert(size(repo_all) == 2);

	try {
		service.service_wishlist_adauga("");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_wishlist_adauga("1");
	assert(service.service_wishlist_get_total() == 1);
	service.service_wishlist_goleste();
	assert(service.service_wishlist_get_total() == 0);
	service.service_wishlist_genereaza("3");
	try {
		service.service_wishlist_genereaza("1.2");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	assert(service.service_wishlist_get_total() == 3);
	assert(size(service.service_wishlist_get_all()) == 3);
	try {
		service.service_wishlist_export_csv("");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_wishlist_export_csv("! DO NOT OPEN! TEST !");

	service.service_sterge("1");
	service.service_sterge("2");
	service.service_sterge("3");
	service.service_adauga("3", "1", "1", "1");
	service.service_adauga("1", "2", "1", "1");
	service.service_adauga("2", "2", "2", "2");
	const auto& repo_raort = service.service_raport();
	assert(size(repo_raort) == 2);
	for (const auto& el : repo_raort) {
		DTO p = el.second;
		if (el.first == "1")
			assert(p.get_count() == 0);
		else
			assert(p.get_count() == 1);
	}
	service.service_sterge("1");
	service.service_sterge("2");
	service.service_sterge("3");
}

void Teste::teste_service_files() const {
	RepositoryOfertaFile RepositoryOferta{ "teste.txt" };
	Service service(RepositoryOferta);
	service.service_adauga("Sejur", "Paris", "Family", "13.4");
	try {
		service.service_adauga("Sejur romantic", "Paris", "", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	Oferta of = service.service_cauta("Sejur");
	assert(of.get_destinatie() == "Paris");
	service.service_modifica("Sejur", "Spania", "Family", "10");
	try {
		service.service_modifica("Sejur", "Paris", "", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	vector<Oferta> repo_all = service.service_get_all();
	assert(size(repo_all) == 1);
	service.service_sterge("Sejur");
	try {
		repo_all = service.service_sortare("ada", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("2", "ada");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("3", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("1", "4");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(se.get_message() == "Selectie invalid!\n");
	}

	service.service_adauga("a", "2", "e", "13.5");
	service.service_adauga("b", "3", "e", "13.4");
	service.service_adauga("d", "1", "X", "10");
	service.service_adauga("c", "1", "X", "10");


	repo_all = service.service_sortare("0", "0");
	assert(repo_all[0].get_denumire() == "a");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "c");
	assert(repo_all[3].get_denumire() == "d");
	service.service_sterge("d");

	repo_all = service.service_sortare("1", "0");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "b");

	repo_all = service.service_sortare("2", "0");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "a");

	repo_all = service.service_sortare("0", "1");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "a");

	repo_all = service.service_sortare("1", "1");
	assert(repo_all[0].get_denumire() == "b");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "c");

	service.service_adauga("d", "1", "z", "10");
	repo_all = service.service_sortare("2", "1");
	assert(repo_all[0].get_denumire() == "d");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "b");
	assert(repo_all[3].get_denumire() == "c");

	service.service_sterge("a");
	service.service_sterge("b");
	service.service_sterge("c");
	service.service_sterge("d");

	service.service_adauga("d", "1", "z", "10.123");
	try {
		repo_all = service.service_filtrare_destinatie("0", "d");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_filtrare_pret("0", "10.123");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_sterge("d");
	try {
		repo_all = service.service_filtrare_destinatie("a", "b");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_destinatie("2", "b");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("a", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("3", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("1", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}

	service.service_adauga("1", "a", "e", "13.5");
	service.service_adauga("2", "a", "e", "13.4");
	service.service_adauga("3", "b", "X", "10");

	repo_all = service.service_filtrare_destinatie("0", "a");
	assert(size(repo_all) == 2);
	repo_all = service.service_filtrare_destinatie("1", "a");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("0", "11");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("1", "13.4");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("2", "10");
	assert(size(repo_all) == 2);

	try {
		service.service_wishlist_adauga("");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_wishlist_adauga("1");
	assert(service.service_wishlist_get_total() == 1);
	service.service_wishlist_goleste();
	assert(service.service_wishlist_get_total() == 0);
	service.service_wishlist_genereaza("3");
	try {
		service.service_wishlist_genereaza("1.2");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	assert(service.service_wishlist_get_total() == 3);
	assert(size(service.service_wishlist_get_all()) == 3);
	try {
		service.service_wishlist_export_csv("");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_wishlist_export_csv("! DO NOT OPEN! TEST !");

	service.service_sterge("1");
	service.service_sterge("2");
	service.service_sterge("3");
	service.service_adauga("3", "1", "1", "1");
	service.service_adauga("1", "2", "1", "1");
	service.service_adauga("2", "2", "2", "2");
	const auto& repo_raort = service.service_raport();
	assert(size(repo_raort) == 2);
	for (const auto& el : repo_raort) {
		DTO p = el.second;
		if (el.first == "1")
			assert(p.get_count() == 0);
		else
			assert(p.get_count() == 1);
	}
	service.service_sterge("1");
	service.service_sterge("2");
	service.service_sterge("3");
}

void Teste::teste_service_lab() const {
	RepositoryLab RepositoryOferta{ 0 };
	Service service(RepositoryOferta);
	service.service_adauga("Sejur", "Paris", "Family", "13.4");
	try {
		service.service_adauga("Sejur romantic", "Paris", "", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	Oferta of = service.service_cauta("Sejur");
	assert(of.get_destinatie() == "Paris");
	service.service_modifica("Sejur", "Spania", "Family", "10");
	try {
		service.service_modifica("Sejur", "Paris", "", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	vector<Oferta> repo_all = service.service_get_all();
	assert(size(repo_all) == 1);
	service.service_sterge("Sejur");
	try {
		repo_all = service.service_sortare("ada", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("2", "ada");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("3", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_sortare("1", "4");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(se.get_message() == "Selectie invalid!\n");
	}

	service.service_adauga("a", "2", "e", "13.5");
	service.service_adauga("b", "3", "e", "13.4");
	service.service_adauga("d", "1", "X", "10");
	service.service_adauga("c", "1", "X", "10");


	repo_all = service.service_sortare("0", "0");
	assert(repo_all[0].get_denumire() == "a");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "c");
	assert(repo_all[3].get_denumire() == "d");
	service.service_sterge("d");

	repo_all = service.service_sortare("1", "0");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "b");

	repo_all = service.service_sortare("2", "0");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "a");

	repo_all = service.service_sortare("0", "1");
	assert(repo_all[0].get_denumire() == "c");
	assert(repo_all[1].get_denumire() == "b");
	assert(repo_all[2].get_denumire() == "a");

	repo_all = service.service_sortare("1", "1");
	assert(repo_all[0].get_denumire() == "b");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "c");

	service.service_adauga("d", "1", "z", "10");
	repo_all = service.service_sortare("2", "1");
	assert(repo_all[0].get_denumire() == "d");
	assert(repo_all[1].get_denumire() == "a");
	assert(repo_all[2].get_denumire() == "b");
	assert(repo_all[3].get_denumire() == "c");

	service.service_sterge("a");
	service.service_sterge("b");
	service.service_sterge("c");
	service.service_sterge("d");

	service.service_adauga("d", "1", "z", "10.123");
	try {
		repo_all = service.service_filtrare_destinatie("0", "d");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		repo_all = service.service_filtrare_pret("0", "10.123");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_sterge("d");
	try {
		repo_all = service.service_filtrare_destinatie("a", "b");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_destinatie("2", "b");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("a", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("3", "1");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	try {
		service.service_filtrare_pret("1", "a");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}

	service.service_adauga("1", "a", "e", "13.5");
	service.service_adauga("2", "a", "e", "13.4");
	service.service_adauga("3", "b", "X", "10");

	repo_all = service.service_filtrare_destinatie("0", "a");
	assert(size(repo_all) == 2);
	repo_all = service.service_filtrare_destinatie("1", "a");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("0", "11");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("1", "13.4");
	assert(size(repo_all) == 1);
	repo_all = service.service_filtrare_pret("2", "10");
	assert(size(repo_all) == 2);

	try {
		service.service_wishlist_adauga("");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_wishlist_adauga("1");
	assert(service.service_wishlist_get_total() == 1);
	service.service_wishlist_goleste();
	assert(service.service_wishlist_get_total() == 0);
	service.service_wishlist_genereaza("3");
	try {
		service.service_wishlist_genereaza("1.2");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	assert(service.service_wishlist_get_total() == 3);
	assert(size(service.service_wishlist_get_all()) == 3);
	try {
		service.service_wishlist_export_csv("");
		assert(false);
	}
	catch (ServiceExcept se) {
		assert(true);
	}
	service.service_wishlist_export_csv("! DO NOT OPEN! TEST !");

	service.service_sterge("1");
	service.service_sterge("2");
	service.service_sterge("3");
	service.service_adauga("3", "1", "1", "1");
	service.service_adauga("1", "2", "1", "1");
	service.service_adauga("2", "2", "2", "2");
	const auto& repo_raort = service.service_raport();
	assert(size(repo_raort) == 2);
	for (const auto& el : repo_raort) {
		DTO p = el.second;
		if (el.first == "1")
			assert(p.get_count() == 0);
		else
			assert(p.get_count() == 1);
	}
	service.service_sterge("1");
	service.service_sterge("2");
	service.service_sterge("3");
}

void Teste::teste_undo() const {
	RepositoryOfertaFile RepositoryOferta{ "teste.txt" };
	Service service(RepositoryOferta);
	service.service_adauga("3", "3", "3", "3");
	service.service_adauga("1", "1", "1", "1");
	service.service_adauga("4", "4", "4", "4");
	service.service_undo();
	service.service_modifica("3", "2", "2", "2");
	service.service_sterge("3");
	assert(size(service.service_get_all()) == 1);
 	service.service_undo();
	assert(size(service.service_get_all()) == 2);
	service.service_undo();
	service.service_undo();
	service.service_undo();
	assert(size(service.service_get_all()) == 0);
	try {
		service.service_undo();
	}
	catch (ServiceExcept se) {
		assert(true);
	}
}
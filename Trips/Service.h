#ifndef SERVICE_H_
#define SERVICE_H_

#include <string>
#include <vector>
#include <exception>
#include <algorithm>
#include <unordered_map>
#include "Oferta.h"
#include "Utils.h"
#include "Repository.h"
#include "Service.h"
#include "Undo.h"
#include "Observer.h"
using std::copy_if;
using std::sort;
using std::unordered_map;
using std::unique_ptr;
using std::vector;
using std::make_unique;

class DTO
{
public:

	DTO() : type{ "" }, count{ 0 }{
	};

	DTO(string type) : type{ type }, count{ 0 }{
	};

	void inc() { 
		count++; };

	string get_type() {
		return type;
	}

	int get_count() {
		return count;
	}

private:
	string type;
	int count;
};

class Service : public Observable
{

public:

	Utils utils;

	//initializeaza obiectul cu un repo si o clasa de functii utile
	Service(RepoAbstract& RepoAbstract) :
		repo{ RepoAbstract }, wishlist{ repo }{}

	/*
		lanseaza construirea, validarea si adaugarea unui obiect
		preconditii : string denumire, destinatie, tip, pret - referinta la string
		postconditii : - obiectul este adaugat la finalul repo-ului daca nu sunt probleme
					   - ridica exceptie daca sunt
	*/
	void service_adauga(const string& denumire, const string& destinatie, const string& tip, const string& pret);

	/*
		lanseaza stergerea unui obiect
		preconditii : id - referinta la string
		postconditii : - obiectul este adaugat la finalul repo-ului daca nu sunt probleme
					   - ridica exceptie daca sunt
	*/
	void service_sterge(const string& id);

	/*
		lanseaza construirea, validarea si modificarea unui obiect
		preconditii : string denumire, destinatie, tip, pret - referinta la string
		postconditii : - obiectul este modifcat la finalul repo-ului daca nu sunt probleme
					   - ridica exceptie daca sunt
	*/
	void service_modifica(const string& denumire, const string& destinatie, const string& tip, const string& pret);

	// returneaza repo-ul de Oferte
	const vector<Oferta> service_get_all() const;

	/*
		lanseaza cautarea unui obiect
		preconditii : nume - referinta la string
		postconditii : - obiectul este returnat daca nu sunt probleme
					   - ridica exceptie daca sunt
	*/
	const Oferta& service_cauta(const string& nume);

	/*
		lanseaza sortatea repo-ului dupa mai multe conditii
		preconditii : string - mode - modul dupa care daca se sorteaza
						0 - dupa denumire
						1 - dupa destinatie
						2 - dupa tip + pret
					  string - ascending
						0 - ordonat crescator
						1 - ordonat crescator
		postconditii : - este returnata o copie a listei initiale, sortata, daca se poate
					   - ridica exceptie daca sunt
	*/
	vector<Oferta> service_sortare(const string& mode, const string& ascending);

	/*
		lanseaza filtrarea repo-ului dupa destinatie
		preconditii : string - filter - modul dupa care daca se sorteaza
						0 - returneaza doar obiectele care coincid la destinatie
						1 - returneaza obiectele care nu coincid la destinatie
		postconditii : - este returnata o copie a listei initiale, filtrata, daca se poate
					   - ridica exceptie daca sunt
	*/
	vector<Oferta> service_filtrare_destinatie(const string& filter, const string& destinatie_comp);

	/*
		lanseaza filtrarea repo-ului dupa pret
		preconditii : string - filter - modul dupa care daca se sorteaza
						0 - returneaza doar obiectele care coincid la pret
						1 - returneaza obiectele care nu coincid la pret
		postconditii : - este returnata o copie a listei initiale, filtrata, daca se poate
					   - ridica exceptie daca sunt
	*/
	vector<Oferta> service_filtrare_pret(const string& filter, const string& pret_comp);

	/*
	lanseaza adaugarea de oferte in wishlist
	preconditii: nume - stringul cu care se face compararea
	postconditii: se lanseaza operatia daca numele nu este vid, sau se ridica exceptie in caz contrar
	*/
	void service_wishlist_adauga(const string& denumire);

	//lanseaza operatia de golire a wishlistului
	void service_wishlist_goleste();

	/*
	lanseaza generarea de oferte in wishlist
	preconditii: n - numarul de obiecte ce se genreaza
	postconditii: se lanseaza operatia daca n e numar natural, sau se ridica exceptie in caz contrar
	*/
	void service_wishlist_genereaza(const string& n);

	/*
	lanseaza exportarea in csv
	preconditii: nume - numele fisierului unde se salveaza
	postconditii: se lanseaza operatia daca nume nu e vid, sau se ridica exceptie in caz contrar
	*/
	void service_wishlist_export_csv(const string& nume);

	//returneaza wish-listul
	const vector<Oferta>& service_wishlist_get_all();

	//returneaza numarul de oferte din wishlist
	int service_wishlist_get_total();

	//returneaza numarul de aparitii ale fiecarei destinatii
	unordered_map<string, DTO>service_raport();

	//lanseaza operatia de undo
	void service_undo();

private:

	RepoAbstract& repo;
	
	Wishlist wishlist;

	vector<unique_ptr<ActiuneUndo>> undo;

};
#endif
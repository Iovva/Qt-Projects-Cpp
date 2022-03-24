#ifndef RepositoryOfertaOfertaMemory_H_
#define RepositoryOfertaOfertaMemory_H_

#include <vector>
#include <random>
#include "Oferta.h"
#include "Exceptions.h"
#include "Utils.h"
#include <fstream>
#include <unordered_map>
using std::ofstream;
using std::vector;
using std::string;
using std::to_string;
using std::find_if;
using std::unordered_map;


class RepoAbstract {

public:

	// returneaza lungimea repo-ului
	virtual int len() = 0;

	/*
			adauga un element la finalul repo-ului
			preconditii : of - referinta la obiect Oferta
			postconditii : obiectul este adaugat
		*/
	virtual void adauga(Oferta& of) = 0;

	/*
		sterge un element din repo
		preconditii : int id - id-ul elementului ce trebuie sters
		postconditii : obiectul cu id-ul dat este sters, si se returneaza o copie a lui
	*/
	virtual const Oferta sterge(const string& denumire) = 0;

	/*
		modifica un element din repo
		preconditii : int id - id-ul elementului ce trebuie modificat
					  of - referinta la obiect Oferta
		postconditii : obiectul cu id-ul este suprascris cu noile date, si obiectul vechi este returnat
	*/
	virtual const Oferta modifica(Oferta& of) = 0;

	// returnezaza un vector cu Ofertele din repo
	virtual const vector<Oferta> get_all() = 0;

	/*
	cauta un element din repo
	preconditii : string id - denumirea elementului ce trebuie cautat
	postconditii : obiectul cu id-ul dat este returnat
	*/
	virtual const Oferta& cauta(const string& s) = 0;

};

class RepositoryLab : public RepoAbstract
{

public:

	// initializeaza un repo cu valorile default pentru componenetele listei (stringuri si un float)
	RepositoryLab(float failure_rate) :
		failure_rate{ failure_rate } {
	};

	// nu permite copierea repo-ului
	RepositoryLab(vector<Oferta> lista_new) = delete;

	// returneaza lungimea repo-ului
	int len() override;

	/*
		adauga un element la finalul repo-ului
		preconditii : of - referinta la obiect Oferta
		postconditii : obiectul este adaugat
	*/
	void adauga(Oferta& of) override;

	/*
		sterge un element din repo
		preconditii : int id - id-ul elementului ce trebuie sters
		postconditii : obiectul cu id-ul dat este sters, si se returneaza o copie a lui
	*/
	const Oferta sterge(const string& denumire) override;

	/*
		modifica un element din repo
		preconditii : int id - id-ul elementului ce trebuie modificat
					  of - referinta la obiect Oferta
		postconditii : obiectul cu id-ul este suprascris cu noile date, si obiectul vechi este returnat
	*/
	const Oferta modifica(Oferta& of) override;

	// returnezaza un vector cu Ofertele din repo
	const vector<Oferta> get_all() override;

	/*
	cauta un element din repo
	preconditii : string id - denumirea elementului ce trebuie cautat
	postconditii : obiectul cu id-ul dat este returnat
	*/
	const Oferta& cauta(const string& denumire) override;

	// produce un exception error bazat pe failure rate
	bool random_failure();

protected:

	//dictionar de Oferte
	unordered_map<string, Oferta> map;
	float failure_rate;

};


class RepositoryOferta : public RepoAbstract
{

public:
	
	// initializeaza un repo cu valorile default pentru componenetele listei (stringuri si un float)
	RepositoryOferta() = default;

	// nu permite copierea repo-ului
	RepositoryOferta(vector<Oferta> lista_new) = delete;

	// returneaza lungimea repo-ului
	int len() override;

	/*
		adauga un element la finalul repo-ului
		preconditii : of - referinta la obiect Oferta
		postconditii : obiectul este adaugat
	*/
	void adauga(Oferta& of) override;

	/*
		sterge un element din repo
		preconditii : int id - id-ul elementului ce trebuie sters
		postconditii : obiectul cu id-ul dat este sters, si se returneaza o copie a lui
	*/
	const Oferta sterge(const string& denumire) override;

	/*
		modifica un element din repo
		preconditii : int id - id-ul elementului ce trebuie modificat
					  of - referinta la obiect Oferta
		postconditii : obiectul cu id-ul este suprascris cu noile date, si obiectul vechi este returnat
	*/
	const Oferta modifica(Oferta& of) override;

	// returnezaza un vector cu Ofertele din repo
	const vector<Oferta> get_all() override;

	/*
	cauta un element din repo
	preconditii : string id - denumirea elementului ce trebuie cautat
	postconditii : obiectul cu id-ul dat este returnat
	*/
	const Oferta& cauta(const string& denumire) override;

protected:

	//vector de Oferte
	vector<Oferta> lista;

};


class RepositoryOfertaFile : public RepositoryOferta
{

public:
	
	// initializeaza un repo cu fisier, initializand si repo-ul de baza
	RepositoryOfertaFile(string file_name) : 
		RepositoryOferta(), file_name{ file_name } {
		read_from_file();
	};
	
	// returneaza lungimea repo-ului
	int len() override;

	/*
		adauga un element la finalul repo-ului
		preconditii : of - referinta la obiect Oferta
		postconditii : obiectul este adaugat
	*/
	void adauga(Oferta& of) override;

	/*
		sterge un element din repo
		preconditii : int id - id-ul elementului ce trebuie sters
		postconditii : obiectul cu id-ul dat este sters, si se returneaza o copie a lui
	*/
	const Oferta sterge(const string& denumire) override;

	/*
		modifica un element din repo
		preconditii : int id - id-ul elementului ce trebuie modificat
					  of - referinta la obiect Oferta
		postconditii : obiectul cu id-ul este suprascris cu noile date, si obiectul vechi este returnat
	*/
	const Oferta modifica(Oferta& of) override;

	// returnezaza un vector cu Ofertele din repo
	const vector<Oferta> get_all() override;

	/*
	cauta un element din repo
	preconditii : string id - denumirea elementului ce trebuie cautat
	postconditii : obiectul cu id-ul dat este returnat
	*/
	const Oferta& cauta(const string& denumire) override;



private:

	//numele fisierului in care se salveaza
	string file_name;
	
	// functia citeste din fisier ofertele si le introduce in repo-ul din memorie
	void read_from_file();
	
	// functia scrie valorile din repo-ul din memorie in fisier
	void write_to_file();

};


class Wishlist
{
private:

	RepoAbstract& repo;

	vector<Oferta>elems_wishlist;

public:

	// initializeaza obiectul cu un repo
	Wishlist(RepoAbstract& r) : repo{ r } {
	}

	/*
	cauta elementele cu denumirea identica cu stringul
	preconditii: nume - stringul cu care se face compararea
	postconditii: se adauga obiectul, daca exista
	*/
	void adauga(const string& nume);

	// se goleste wishlistul
	void goleste();

	/*
	adauga n elemente aleatorii din repo
	preconditii: n - numarul de elemente ce trebuie adaugate
	postconditii: se adauga obiectele
	*/
	void genereaza(int n);
	
	/*
	se exporteaza lista in csv, sau se lanseaza exceptie 
	daca nu se poate deschide pentru scriere
	preconditii: nume - numele fisierului unde se exporteaza
	postconditii: se adauga obiecte
	*/
	void export_csv(const string& nume);

	// se returneaza toate ofertele din wishlist
	const vector<Oferta>& get_all();

	// se returneaza numarul de oferte din wishlist
	const int get_total();

};

#endif


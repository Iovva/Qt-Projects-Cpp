#include "Repository.h"

bool RepositoryLab::random_failure() {
	Utils utils;
	int rndNr = utils.random_nr(1, 100);
	if (static_cast<float>(rndNr) - static_cast<float>(failure_rate * 100) < static_cast<float>(0.01))
		return true;
	return false;
}

int RepositoryLab::len() {
	return static_cast<int>(size(map));
}

void RepositoryLab::adauga(Oferta& of) {

	if (map.find(of.get_denumire()) != map.end() || random_failure() == true)
		throw(RepoExcept{ "Deja exista oferta data!\n" });
	map[of.get_denumire()] = of;
}

const Oferta RepositoryLab::sterge(const string& denumire) {
	if (len() == 0)
		throw(RepoExcept{ "Lista este goala!" });
	auto it = map.find(denumire);
	if (it == map.end() || random_failure() == true)
		throw RepoExcept("Produs inexistent !\n");
	Oferta aux = (*it).second;
	map.erase(it);
	return aux;
}

const Oferta RepositoryLab::modifica(Oferta& of) {
	const string& denumire = of.get_denumire();
	if (len() == 0)
		throw(RepoExcept{ "Lista este goala!" });
	auto it = map.find(denumire);
	if (it == map.end() || random_failure() == true)
		throw RepoExcept("Produs inexistent !\n");
	if (of.get_denumire() == (*it).second.get_denumire() && of.get_destinatie() == (*it).second.get_destinatie() &&
		of.get_tip() == (*it).second.get_tip() && of.get_pret() == (*it).second.get_pret()) {
		throw RepoExcept("Deja exista oferta data!\n");
	}
	Oferta aux = (*it).second;
	(*it).second = of;
	return aux;
}


const vector<Oferta> RepositoryLab::get_all() {
	if (random_failure() == true)
		throw(RepoExcept{ "Lista este goala!" });
	vector<Oferta> vector;
	for (const auto& el : map)
	{
		vector.push_back(el.second);
	}
	return vector;
}

const Oferta& RepositoryLab::cauta(const string& denumire) {
	auto it = map.find(denumire);
	if (it == map.end() || random_failure() == true)
		throw RepoExcept("Produs inexistent !\n");
	return (*it).second;
}

int RepositoryOferta::len(){
	return static_cast<int>(size(lista));
}

void RepositoryOferta::adauga(Oferta& of) {
	for (const auto& el : this->lista)
		if (el == of)
			throw(RepoExcept{ "Deja exista oferta data!\n" });
	this->lista.push_back(of);
}

const Oferta RepositoryOferta::sterge(const string& denumire) {
	if (this->len() == 0)
		throw(RepoExcept{ "Lista este goala!" });
	auto it = find_if(lista.begin(), lista.end(), [denumire](const Oferta& of) { return denumire == of.get_denumire(); });
	if (it == lista.end())
		throw RepoExcept("Produs inexistent !\n");
	const Oferta aux = *it;
	lista.erase(it);
	return aux;
}

const Oferta RepositoryOferta::modifica(Oferta& of) {
	const string& denumire = of.get_denumire();
	if (this->len() == 0)
		throw(RepoExcept{ "Lista este goala!" });
	auto it = find_if(lista.begin(), lista.end(), [denumire](const Oferta& of) { return denumire == of.get_denumire(); });
	if (it == lista.end())
		throw RepoExcept("Produs inexistent !\n");
	if (of.get_denumire() == (*it).get_denumire() && of.get_destinatie() == (*it).get_destinatie() &&
		of.get_tip() == (*it).get_tip() && of.get_pret() == (*it).get_pret()) {
		throw RepoExcept("Deja exista oferta data!\n");
	}
	const Oferta aux = *it;
	*it = of;
	return aux;
}


const vector<Oferta> RepositoryOferta::get_all(){
	return this->lista;
}

const Oferta& RepositoryOferta::cauta(const string& s) {
	auto it = find_if(lista.begin(), lista.end(), [s](const Oferta& of) { return s == of.get_denumire(); });
	if (it == lista.end())
		throw RepoExcept("Produs inexistent !\n");
	return *it;
}

void RepositoryOfertaFile::read_from_file() {
	lista.clear();
	std::ifstream fin(file_name);
	if (!fin.is_open()) throw RepoExcept("Fisierul ' " + file_name + " ' nu a putut fi deschis pentru citire! \n");
	while (!fin.eof()) {
		string denumire, destinatie, tip, pret, id;
		fin >> denumire;
		if (fin.eof()) 	break;
		fin >> destinatie;
		if (fin.eof()) break;
		fin >> tip;
		if (fin.eof()) break;
		fin >> pret;
		Oferta of{ denumire, destinatie, tip, stof(pret)};
		RepositoryOferta::adauga(of);
	}
	fin.close();
}

void RepositoryOfertaFile::write_to_file() {
	std::ofstream fout(file_name);
	if (!fout.is_open()) throw RepoExcept("Fisierul ' " + file_name + " ' nu a putut fi deschis pentru scriere! \n");
	for (const auto& of : RepositoryOferta::get_all()) {
		fout << of.get_denumire();
		fout << std::endl;
		fout << of.get_destinatie();
		fout << std::endl;
		fout << of.get_tip();
		fout << std::endl;
		fout << of.get_pret();
		fout << std::endl;
	}
	fout.close();
}

int RepositoryOfertaFile::len() {
	read_from_file();
	return RepositoryOferta::len();
}

void RepositoryOfertaFile::adauga(Oferta& of) {
	read_from_file();
	RepositoryOferta::adauga(of);
	write_to_file();
}

const Oferta RepositoryOfertaFile::sterge(const string& denumire) {
	read_from_file();
	const Oferta aux = RepositoryOferta::sterge(denumire);
	write_to_file();
	return aux;
}

const vector<Oferta> RepositoryOfertaFile::get_all() {
	read_from_file();
	return RepositoryOferta::get_all();
}

const Oferta RepositoryOfertaFile::modifica(Oferta& of) {
	read_from_file();
	const Oferta aux = RepositoryOferta::modifica(of);
	write_to_file();
	return aux;
}

const Oferta& RepositoryOfertaFile::cauta(const string& s) {
	read_from_file();
	return RepositoryOferta::cauta(s);
}

void Wishlist::adauga(const string& nume) {
	for (const auto& el : repo.get_all())
		if (el.get_denumire() == nume)
			elems_wishlist.push_back(el);
}

void Wishlist::goleste() {
	elems_wishlist.clear();
}

void Wishlist::genereaza(int n) {
	Utils utils;
	const auto& repo_all = repo.get_all();
	while (n > 0){
		n--;
		const int rndNr = utils.random_nr(0, repo.len() - 1);
		auto it = repo_all.begin();
		it = it + rndNr;
		elems_wishlist.push_back(*it);
	}
}

void Wishlist::export_csv(const string& nume)
{
	unsigned k{ 0 };
	ofstream out(nume + ".csv");
	if (!out.good()) throw RepoExcept("Fisierul nu a putut fi deschis !\n");
	out << "ID,Denumire,Destinatie,Tip,Pret\n";
	for (const auto& el : elems_wishlist)
		out << k++ << "," << el.get_denumire() << "," << el.get_destinatie() << "," <<
		el.get_tip() << "," << el.get_pret() << "\n";
	out << "\nTotal," << get_total() <<" oferte";
	out.close();
}

const vector<Oferta>& Wishlist::get_all() {
	return elems_wishlist;
}

const int Wishlist::get_total() {
	return static_cast<int>(size(elems_wishlist));
}





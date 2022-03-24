#include "FileRepo.h"
#include "Produs.h"
#include "ValidatorProdus.h"

#include <fstream>
#include <exception>

using std::ifstream;
using std::ofstream;
using std::exception;

void FileRepo::loadFromFile() {
	ifstream in;
	in.open(fName);

	if (!in.is_open())
		throw exception{ "Nu s-a putut deschide fisierul pentru citire!\n" };

	while (!in.eof())
	{
		int id;
		in >> id;

		if (in.eof())
			break;

		in.get();

		string nume;
		getline(in, nume);

		string tip;
		getline(in, tip);

		double pret;
		in >> pret;

		if (in.eof())
			break;

		Produs produs{ id, nume, tip, pret };

		ValidatorProdus valid;
		valid.valideaza(produs);

		Repo::add(produs);
	}

	in.close();
}

void FileRepo::storeToFile() {
	ofstream out;
	out.open(fName);

	if (!out.is_open())
		throw exception{ "Nu s-a putut deschide fisierul pentru scriere!\n" };

	const auto& all{ Repo::getAll() };

	for (const auto& p : all)
		out << p.str();

	out.close();
}

void FileRepo::add(const Produs& produs) {
	Repo::add(produs);
	storeToFile();
}

void FileRepo::modify(const Produs& produs) {
	Repo::modify(produs);
	storeToFile();
}

void FileRepo::del(int id) {
	Repo::del(id);
	storeToFile();
}
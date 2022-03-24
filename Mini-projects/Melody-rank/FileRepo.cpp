#include "FileRepo.h"

#include <fstream>
#include <exception>
#include <string>

using std::ifstream;
using std::ofstream;
using std::exception;
using std::string;

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

		string titlu;
		getline(in, titlu);

		string artist;
		getline(in, artist);

		int rank;
		in >> rank;

		if (in.eof())
			break;

		in.get();

		Melodie melodie{ id, titlu, artist, rank };

		ValidatorMelodie valid;
		valid.valideaza(melodie);

		InMemoryRepo::add(melodie);
	}

	in.close();
}

void FileRepo::storeToFile() {
	ofstream out;
	out.open(fName);

	if (!out.is_open())
		throw exception{ "Nu s-a putut deschide fisierul pentru scriere!\n" };

	const auto& all{ InMemoryRepo::getAll() };

	for (const auto& melodie : all)
		out << melodie.str();

	out.close();
}

void FileRepo::add(const Melodie& melodie) {
	InMemoryRepo::add(melodie);
	storeToFile();
}

void FileRepo::modify(const Melodie& melodie) {
	InMemoryRepo::modify(melodie);
	storeToFile();
}

void FileRepo::del(int id) {
	InMemoryRepo::del(id);
	storeToFile();
}
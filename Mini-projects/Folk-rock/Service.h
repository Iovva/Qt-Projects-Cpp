#pragma once
#include "Repo.h"
#include <algorithm>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::sort;
using std::count_if;

class Service
{
private:
	Repo& rep;
	string& denumire;
public:
	Service(Repo& rep_n, string& denumire_n) : rep{ rep_n }, denumire{denumire_n} {
		citesteFisier();
	};
	Service(const Service& ot) = delete;
	void addService(string& titlu, string& autor, string& gen) {
		if (gen == "pop" || gen == "rock" || gen == "folk" || gen == "disco")
		{
			int id = 1;
			while (true) {
				try {
					rep.search(id);
				}
				catch (exception& ex) {
					rep.add(Melodie(id, titlu, autor, gen));
					return;
				}
				id++;
			}
			scrieFisier();
		}
	}
	void citesteFisier() {
		ifstream f(denumire);
		int id;
		string titlu, autor, gen;
		while (!f.eof()) {
			f >> id;
			f.get();
			if (f.eof())
				return;
			f >> titlu;
			f >> autor;
			f >> gen;
			rep.add(Melodie(id, titlu, autor, gen));
		}
		f.close();
	}
	void scrieFisier() {
		ofstream g(denumire);
		for (const auto& it : rep.getAll()) {
			g << it.getId() << '\n';
			g << it.getTitle() << '\n';
			g << it.getArtist() << '\n';
			g << it.getGenre() << '\n';
		}
		g.close();
	}
	void deleteService(int id) {
		try {
			rep.search(id);
			rep.del(id);
			scrieFisier();
		}
		catch(exception& ex){

		}
	}
	const Melodie& searchService(int id) const {
			return rep.search(id);
	}
	vector<Melodie> getService() const {
		return rep.getAll();
	}
	vector<Melodie> getSortat() const {
		auto copie{ rep.getAll() };
		sort(copie.begin(), copie.end(), [&](const Melodie& m1, const Melodie& m2) {return m1.getArtist() < m2.getArtist(); });
		return copie;
	}
	int sameArtist(const string& artist) {
		auto copie{ rep.getAll() };
		return count_if(copie.begin(), copie.end(), [&](const Melodie& m) {return m.getArtist() == artist; });
	}

	int sameGenre(const string& gen) {
		auto copie{ rep.getAll() };
		return count_if(copie.begin(), copie.end(), [&](const Melodie& m) {return m.getGenre() == gen; });
	}
	~Service() {
		scrieFisier();
	}
};


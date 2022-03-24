#include "Service.h"

#include <algorithm>

using std::sort;
using std::count_if;

void Service::addServ(int id, const string& titlu, const string& artist, int rank) {
	Melodie melodie{ id, titlu, artist, rank };

	valid.valideaza(melodie);

	repo.add(melodie);
}

void Service::modifyServ(int id, const string& titlu, const string& artist, int rank) {
	Melodie melodie{ id, titlu, artist, rank };

	valid.valideaza(melodie);

	repo.modify(melodie);
}

void Service::delServ(int id) {
	if (id < 0)
		throw std::exception("Id invalid!\n");

	repo.del(id);
}

const Melodie& Service::searchServ(int id) const {
	if (id < 0)
		throw std::exception("Id invalid!\n");

	return repo.search(id);
}

vector<Melodie> Service::sortByRank(bool reversed) const {
	auto melodii{ repo.getAll() };

	if (!reversed)
		sort(begin(melodii), end(melodii), [](const Melodie& m1, const Melodie& m2) { return m1.getRank() < m2.getRank(); });
	else
		sort(begin(melodii), end(melodii), [](const Melodie& m1, const Melodie& m2) { return m1.getRank() > m2.getRank(); });

	return melodii;
}

int Service::lenServ() const {
	return repo.len();
}

const vector<Melodie>& Service::getAllServ() const {
	return repo.getAll();
}

int Service::countRank(int rank) const {
	const auto& melodii{ repo.getAll() };

	return count_if(begin(melodii), end(melodii), [rank](const Melodie& m) { return m.getRank() == rank; });
}
#include "Service.h"

#include <algorithm>

using std::sort;
using std::count_if;

void Service::add(int id, const string& nume, const string& tip, const double& pret) {
	Produs produs{ id, nume, tip, pret };

	valid.valideaza(produs);

	repo.add(produs);

	this->notify();
}

vector<Produs> Service::getSortat() const {
	auto sorted{ repo.getAll() };

	sort(sorted.begin(), sorted.end(), [](const Produs& p1, const Produs& p2) {return p1.getPret() < p2.getPret(); });

	return sorted;
}

set<string> Service::getSet() const {
	set<string> multime;

	const auto& produse{ repo.getAll() };

	for (const auto& produs : produse)
		multime.insert(produs.getTip());

	return multime;
}

int Service::countType(const string& type) const {
	const auto& produse{ repo.getAll() };

	return count_if(produse.begin(), produse.end(), [&type](const Produs& prod) { return prod.getTip() == type; });
}

const vector<Produs>& Service::getAllSrv() const {
	return repo.getAll();
}
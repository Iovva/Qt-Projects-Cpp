#include "Repo.h"

#include <exception>
#include <algorithm>

using std::exception;
using std::remove;

void Repo::add(const Produs& produs) {
	for (const auto& p : produse)
		if (p == produs)
			throw exception("Produs deja existent!\n");

	produse.push_back(produs);
}

void Repo::modify(const Produs& produs) {
	for (auto& p : produse)
		if (p == produs)
		{
			p.setNume(produs.getNume());
			p.setTip(produs.getTip());
			p.setPret(produs.getPret());

			return;
		}

	throw exception("Produs inexistent!\n");
}

void Repo::del(int id) {
	/*auto iter{ produse.begin() };

	while (iter != produse.end())
	{
		const auto& produs{ *iter };

		if (produs.getId() == id)
		{
			produse.erase(iter);

			return;
		}

		++iter;
	}*/

	for (auto it{ produse.begin() }; it != produse.end(); ++it)
	{
		const auto& produs{ *it };

		if (produs.getId() == id)
		{
			produse.erase(it);

			return;
		}
	}

	throw exception("Produs inexistent!\n");
}

const Produs& Repo::search(int id) const {
	for (const auto& p : produse)
		if (p.getId() == id)
			return p;

	throw exception("Produs inexistent!\n");
}

int Repo::len() const {
	return produse.size();
}

const vector<Produs>& Repo::getAll() const {
	return produse;
}
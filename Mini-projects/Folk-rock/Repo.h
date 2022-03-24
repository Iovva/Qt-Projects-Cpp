#pragma once
#include <vector>
#include "Melodie.h"

using std::vector;
using std::exception;

class Repo
{
private:
	vector<Melodie> elems;
public:
	Repo() = default;
	Repo(const Repo& ot) = delete;
	void add(const Melodie& m) {
		elems.push_back(m);
	}
	void del(int id) {
		for (auto it = elems.begin(); it != elems.end(); it++) {
			if (it->getId() == id) {
				elems.erase(it);
				return;
			}
		}
	}
	const Melodie& search(int id) const {
		for (const auto& it : elems) {
			if (it.getId() == id)
				return it;
		}
		throw exception("Element inexistent!\n");
	}
	vector<Melodie> getAll() const {
		return elems;
	}
};


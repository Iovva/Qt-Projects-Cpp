#pragma once

#include "Produs.h"

#include <vector>

using std::vector;

class Repo
{
private:
	vector<Produs> produse;

public:
	Repo() = default;

	Repo(const Repo&) = delete;

	Repo& operator=(const Repo&) = delete;

	virtual void add(const Produs& produs);

	virtual void modify(const Produs& produs);

	virtual void del(int id);

	virtual const Produs& Repo::search(int id) const;

	virtual int len() const;

	virtual const vector<Produs>& getAll() const;

	virtual ~Repo() = default;
};
#pragma once

#include "Melodie.h"

#include <vector>

using std::vector;

class InMemoryRepo
{
private:
	vector<Melodie> melodii;

public:
	InMemoryRepo() = default;

	InMemoryRepo(const InMemoryRepo& ot) = delete;

	InMemoryRepo(const InMemoryRepo&& ot) = delete;

	InMemoryRepo& operator=(const InMemoryRepo& ot) = delete;

	InMemoryRepo& operator=(const InMemoryRepo&& ot) = delete;

	virtual void add(const Melodie& melodie);

	virtual void modify(const Melodie& melodie);

	virtual void del(int id);

	virtual const Melodie& search(int id) const;

	virtual int len() const;

	virtual const vector<Melodie>& getAll() const;

	virtual ~InMemoryRepo() = default;
};


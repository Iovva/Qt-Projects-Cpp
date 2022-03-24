#pragma once

#include "InMemoryRepo.h"
#include "ValidatorMelodie.h"
#include "Melodie.h"

#include <vector>

using std::vector;

class Service
{
private:
	InMemoryRepo& repo;
	ValidatorMelodie& valid;

public:
	Service() = delete;

	Service(InMemoryRepo& repo, ValidatorMelodie& valid) : repo{ repo }, valid{ valid } {

	}

	void addServ(int id, const string& titlu, const string& artist, int rank);

	void modifyServ(int id, const string& titlu, const string& artist, int rank);

	void delServ(int id);

	const Melodie& searchServ(int id) const;

	vector<Melodie> sortByRank(bool reversed) const;

	int lenServ() const;

	const vector<Melodie>& getAllServ() const;

	Service(const Service& ot) = delete;

	Service(const Service&& ot) = delete;

	Service& operator=(const Service& ot) = delete;

	Service& operator=(const Service&& ot) = delete;

	int countRank(int rank) const;

	~Service() = default;
};


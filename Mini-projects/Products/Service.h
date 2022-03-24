#pragma once

#include "Produs.h"
#include "Repo.h"
#include "FileRepo.h"
#include "ValidatorProdus.h"
#include "Observer.h"

#include <vector>
#include <string>
#include <set>

using std::vector;
using std::string;
using std::set;

class Service : public Observable
{
private:
	Repo& repo;
	ValidatorProdus& valid;

public:
	Service() = delete;

	Service(Repo& repo, ValidatorProdus& valid) : repo{ repo }, valid{ valid } {

	}

	Service(const Service& ot) = delete;

	Service& operator=(const Service& ot) = delete;

	const vector<Produs>& getAllSrv() const;

	set<string> getSet() const;

	vector<Produs> getSortat() const;

	int countType(const string& type) const;

	void add(int id, const string& nume, const string& tip, const double& pret);

	~Service() = default;
};


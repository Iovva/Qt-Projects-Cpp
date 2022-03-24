#pragma once
#include "Repository.h"
#include "Observer.h"
#include <algorithm>

class Service : public Observable
{
private:
	Repository& repo;
public:
	Service(Repository& repo) :repo{repo}{}
	Service(const Service& ot) = delete;
	Service() = default;

	void Adauga(int id, string descriere, vector<string>programatori, string stare);

	void Modifica_stare(int id, string stare_noua);

	const Task& Cauta(const int id);

	vector<Task> Filtrare(const string& mod, const string& sub);

	vector<Task> GetAll() {
		return repo.get_all();
	}
};


#include "Service.h"

void Service::Adauga(int id, string descriere, vector<string> programatori, string stare)
{
	Task t{ id,descriere,programatori,stare };
	t.validare();
	repo.add(t);
	notify();
}

void Service::Modifica_stare(int id, string stare_noua)
{
	Task t{ 1,"ceva", vector<string>{"Cineva"},stare_noua };
	t.validare();
	repo.modif(id, stare_noua);
	notify();
}

const Task& Service::Cauta(const int id)
{
	if (id <= 0)
		throw exception("ID invalid !\n");
	return repo.cauta(id);
}

vector<Task> Service::Filtrare(const string& mod, const string& sub)
{
	vector<Task> rez;
	std::copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(rez), [&](Task& t) {
		if (mod == "programatori")
		{
			for (const auto& el : t.get_programatori())
				if (el.find(sub) != string::npos)
					return true;
			return false;
		}
		else if (mod == "stare")
			return t.get_stare() == sub;
		});
	return rez;
}

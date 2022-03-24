#pragma once
#include <string>
#include <vector>
#include <exception>

using std::string;
using std::vector;
using std::exception;

class Task
{
private:
	int id;
	string descriere;
	vector<string>programatori;
	string stare;
public:
	Task(int id, string descriere, vector<string>programatori, string stare) :id{ id }, descriere{ descriere }, programatori{ programatori }, stare{ stare }{}
	int get_id() const { return id; }
	const string& get_descriere() const { return descriere; }
	const vector<string>& get_programatori() const { return programatori; }
	const string& get_stare() const { return stare; }

	void set_stare(string stare_noua) { stare = stare_noua; }

	void validare() const {
		string eroare = "";
		if (id <= 0)
			eroare += "ID invalid !\n";
		if (descriere == "")
			eroare += "Descriere invalida !\n";
		if (programatori.size() <= 0 || programatori.size() >= 5)
			eroare += "Numar invalid de programatori\n";
		else
			for (auto& pr : programatori)
				if (pr == "")
				{
					eroare += "Numele unui programator este invalid !\n";
					break;
				}
		if (stare != "Open" && stare != "Inprogress" && stare != "Close")
			eroare += "Stare invalida (Atentie, prima litera trebuie sa fie majuscula !\n";
		if (eroare.size() != 0)
			throw exception(eroare.c_str());
	}
};


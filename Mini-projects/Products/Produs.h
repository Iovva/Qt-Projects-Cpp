#pragma once

#include <iostream>
#include <string>

using std::string;
using std::to_string;
using std::ostream;

class Produs
{
private:
	int id;
	string nume;
	string tip;
	double pret;

public:
	Produs() = default;

	Produs(const int& id, const string& nume, const string& tip, const double& pret);

	Produs(const Produs& ot);

	Produs& operator=(const Produs& ot);

	const int& getId() const;

	const string& getNume() const;

	const string& getTip() const;

	const double& getPret() const;

	int getNrVocale() const;

	void setNume(const string& nume_nou);

	void setTip(const string& tip_nou);

	void setPret(const double& pret_nou);

	bool operator==(const Produs& ot) const;

	string str() const;

	~Produs() = default;
};


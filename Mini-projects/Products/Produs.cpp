#include "Produs.h"
#include "Produs.h"

#include <algorithm>

using std::endl;
using std::find_if;

Produs::Produs(const int& id, const string& nume, const string& tip, const double& pret) : id{ id }, nume{ nume }, tip{ tip }, pret{ pret }{

}

Produs::Produs(const Produs& ot) : id{ ot.id }, nume{ ot.nume }, tip{ ot.tip }, pret{ ot.pret } {

}

Produs& Produs::operator=(const Produs& ot) {
	id = ot.id;
	nume = ot.nume;
	tip = ot.tip;
	pret = ot.pret;

	return *this;
}

const int& Produs::getId() const {
	return id;
}

const string& Produs::getNume() const {
	return nume;
}

const string& Produs::getTip() const {
	return tip;
}

const double& Produs::getPret() const {
	return pret;
}

int Produs::getNrVocale() const {
	const string vocale = { "aeiouAEIOU" };

	auto cont{ 0 };

	for (const auto& litera : nume)
		if (find_if(begin(vocale), end(vocale), [litera](const char& vocala) { return vocala == litera; }) != end(vocale))
			++cont;

	return cont;
}

void Produs::setNume(const string& nume_nou) {
	nume = nume_nou;
}

void Produs::setTip(const string& tip_nou) {
	tip = tip_nou;
}

void Produs::setPret(const double& pret_nou) {
	pret = pret_nou;
}

bool Produs::operator==(const Produs& ot) const {
	return id == ot.id;
}

string Produs::str() const {
	return to_string(id) + '\n' + nume + '\n' + tip + '\n' + to_string(pret) + '\n';
}
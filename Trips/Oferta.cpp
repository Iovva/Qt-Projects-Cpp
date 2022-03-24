#include "Oferta.h"

Oferta::Oferta(const string& denumire_new, const string& destinatie_new, const string& tip_new, const float pret_new):
denumire { denumire_new }, destinatie{ destinatie_new }, tip{ tip_new }, pret{ pret_new } {
}

Oferta::Oferta(const Oferta& of) :
	denumire{ of.denumire }, destinatie{ of.destinatie }, tip{ of.tip }, pret{ of.pret }{
	std::cout << "Copy constructor called! \n";
}

string Oferta::get_denumire() const {
	return this->denumire;
}

string Oferta::get_destinatie() const {
	return this->destinatie;
}

string Oferta::get_tip() const {
	return this->tip;
}

float Oferta::get_pret() const {
	return this->pret;
}

void Oferta::set_denumire(const string& denumire_new) {
	this->denumire = denumire_new;
}

void Oferta::set_destinatie(const string& destinatie_new) {
	this->destinatie = destinatie_new;
}

void Oferta::set_tip(const string& tip_new) {
	this->tip = tip_new;
}

void Oferta::set_pret(const float& pret_new) {
	this->pret = pret_new;
}

void Oferta::operator =(const Oferta& of) {
	this->set_denumire(of.denumire);
	this->set_destinatie(of.destinatie);
	this->set_tip(of.tip);
	this->set_pret(of.pret);
}

bool Oferta::operator ==(const Oferta& of) const {
	if (this->denumire == of.get_denumire())
		return true;
	return false;
}
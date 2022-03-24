#ifndef OFERTA_H_
#define OFERTA_H_

#include <string>
#include <iostream>
using std::string;
using std::getline;

class Oferta
{

public:

	Oferta() = default;

	//construieste un obiect Oferta, folosind 3 stringuri si un float
	Oferta(const string& denumire_new, const string& destinatie_new, const string& tip_new, const float pret_new);

	// construieste un obiect Oferta, realizand o copie a campurilor ditr-o alta oferta 
	Oferta(const Oferta& of);

	// returneaza denumirea ofertei
	string get_denumire() const;

	// returneaza destinatia ofertei
	string get_destinatie() const;

	// returneaza tipul ofertei
	string get_tip() const;
	
	// returneaza pretul ofertei
	float get_pret() const;

	// seteaza denumirea ofertei
	void set_denumire(const string& denumire_new);

	// seteaza destinatia ofertei
	void set_destinatie(const string& destinatie_new);

	// seteaza tipul ofertei
	void set_tip(const string& tip_new);

	// seteaza pretul ofertei
	void set_pret(const float& ret_new);

	// realizeaza override la operatorul =
	// postconditii: realizeaza o copie a obiectului apelat;
	void operator =(const Oferta& of);

	/* 
	realizeaza override la operatorul ==
	postconditii: - True, daca campurile obiectelor coincid
				  - False, in caz contrar 
	*/				 
	bool operator ==(const Oferta& of) const;

private:
	
	string denumire;
	string destinatie;
	string tip;
	float pret;

};

#endif
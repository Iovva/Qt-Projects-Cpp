#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <random>
#include "Oferta.h"

class Utils
{

public:

	string check_oferta(const string& denumire, const string& destinatie, const string& tip, const string& pret);

	int check_nr(const string& in);
	
	int random_nr(const int l, const int r);
};

#endif
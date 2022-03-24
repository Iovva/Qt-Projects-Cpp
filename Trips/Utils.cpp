#include "Utils.h"

string Utils::check_oferta(const string& denumire, const string& destinatie, const string& tip, const string& pret) {
	string err{ "" };
	if (denumire == "")
		err = err + "Denumire invalida!\n";
	if (destinatie == "")
		err = err + "Destinatie invalida!\n";
	if (tip == "")
		err = err + "Tip invalid!\n";
	if (check_nr(pret) == -1 || check_nr(pret) == 0)
		err = err + "Pret invalid!\n";
	else if (stof(pret) < 0)
		err = err + "Pret invalid!\n";
	return err;
}

int Utils::check_nr(const string& in) {
	int minus_count{ 0 }, dot_count{ 0 };
	if (in == "")
		return -1;
	for (unsigned i = 0; i < size(in); i++)
	{
		const auto& c = in[i];
		if (c == '-' && i == 0)
			minus_count++;
		else if (c == '-' && i != 0)
			return 0;
		else if (c == '.')
			dot_count++;
		else if (isdigit(c) == 0)
			return 0;
		else if (minus_count > 1 || dot_count > 1)
			return 0;
	}
	if (dot_count == 1)
		return 2;
	return 1;
}

int Utils::random_nr(const int l, const int r) {
	std::mt19937 mt{ std::random_device{}() };
	const std::uniform_int_distribution<> dist(l, r);
	return dist(mt);// numar aleator intre [l, r]
}
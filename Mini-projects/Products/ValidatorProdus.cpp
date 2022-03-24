#include "ValidatorProdus.h"

#include <exception>
#include <string>

using std::exception;
using std::string;

void ValidatorProdus::valideaza(const Produs& produs) const {
	string err{ "" };

	if (produs.getId() < 0)
		err += "Id invalid!\n";

	if (produs.getNume().empty())
		err += "Nume invalid!\n";

	if (produs.getTip().empty())
		err += "Tip invalid!\n";

	if (produs.getPret() < 1.0 || produs.getPret() > 100.0)
		err += "Pret invalid!\n";

	if (err.size())
		throw exception{ err.c_str() };
}
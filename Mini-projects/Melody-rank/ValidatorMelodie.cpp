#include "ValidatorMelodie.h"

#include <exception>

using std::exception;

void ValidatorMelodie::valideaza(const Melodie& bad_melodie) const {
	string err{ "" };

	if (bad_melodie.getId() < 0)
		err += "Id invalid!\n";

	if (bad_melodie.getTitlu().empty())
		err += "Titlu invalid!\n";

	if (bad_melodie.getArtist().empty())
		err += "Artist invalid!\n";

	if (bad_melodie.getRank() < 0 || bad_melodie.getRank() > 10)
		err += "Rank invalid!\n";

	if (!err.empty())
		throw exception{ err.c_str() };
}
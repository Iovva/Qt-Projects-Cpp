#pragma once

#include "Produs.h"

class ValidatorProdus
{
public:
	ValidatorProdus() = default;

	void valideaza(const Produs& produs) const;

	~ValidatorProdus() = default;
};
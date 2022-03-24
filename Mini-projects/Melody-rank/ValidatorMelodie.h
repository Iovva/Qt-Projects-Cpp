#pragma once

#include "Melodie.h"

class ValidatorMelodie
{
public:
	ValidatorMelodie() = default;

	void valideaza(const Melodie& bad_melodie) const;

	~ValidatorMelodie() = default;
};
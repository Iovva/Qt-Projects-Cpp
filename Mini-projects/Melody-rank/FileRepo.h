#pragma once

#include "InMemoryRepo.h"
#include "Melodie.h"
#include "ValidatorMelodie.h"

#include <string>

using std::string;

class FileRepo : public InMemoryRepo
{
private:
	string fName;

	void loadFromFile();
	void storeToFile();

public:
	FileRepo() = delete;

	FileRepo(const string& fName) : fName{ fName } {
		loadFromFile();
	}

	FileRepo(const FileRepo& ot) = delete;

	FileRepo(const FileRepo&& ot) = delete;

	FileRepo& operator=(const FileRepo& ot) = delete;

	FileRepo& operator=(const FileRepo&& ot) = delete;

	void add(const Melodie& melodie) override;

	void modify(const Melodie& melodie) override;

	void del(int id) override;

	~FileRepo() override = default;
};

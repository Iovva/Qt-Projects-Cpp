#pragma once

#include "Repo.h"

class FileRepo : public Repo
{
private:
	string fName;

	void loadFromFile();

	void storeToFile();

public:
	FileRepo(const string& fName) : Repo::Repo{}, fName{ fName } {
		loadFromFile();
	}

	FileRepo(const FileRepo&) = delete;

	FileRepo& operator=(const FileRepo&) = delete;

	void add(const Produs& produs) override;

	void modify(const Produs& produs) override;

	void del(int id) override;
};


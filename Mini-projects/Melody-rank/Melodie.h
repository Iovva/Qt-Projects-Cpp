#pragma once

#include <string>

using std::string;

class Melodie
{
private:
	int id;
	string titlu;
	string artist;
	int rank;

public:
	Melodie() = delete;

	Melodie(int id, const string& titlu, const string& artist, int rank);

	Melodie(const Melodie& ot);

	Melodie& operator=(const Melodie& ot);

	int getId() const;

	const string& getTitlu() const;

	const string& getArtist() const;

	int getRank() const;

	void setTitlu(const string& new_titlu);

	void setArtist(const string& new_artist);

	void setRank(int new_rank);

	string str() const;

	bool operator==(const Melodie& ot) const;

	~Melodie() = default;
};
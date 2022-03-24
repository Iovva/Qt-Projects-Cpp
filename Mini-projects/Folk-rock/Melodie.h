#pragma once
#include <string>

using std::string;

class Melodie
{
private:
	int id;
	string titlu, artist, gen;
public:
	Melodie(int id_n, string& titlu_n, string& artist_n, string& gen_n) : id{ id_n }, titlu{ titlu_n }, artist{ artist_n }, gen{gen_n} {
	}
	Melodie(const Melodie& ot) = default;
	int getId() const {
		return id;
	}
	string getTitle() const {
		return titlu;
	}
	string getArtist()	const {
		return artist;
	}
	string getGenre()	const {
		return gen;
	}
	void setTitle(string& titlu_n) {
		titlu=titlu_n;
	}
	void setArtist(string& artist_n) {
		artist = artist_n;
	}
	void setGenre(string& gen_n) {
		gen = gen_n;
	}
};


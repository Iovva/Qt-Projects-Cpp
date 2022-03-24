#include "Melodie.h"

#include <iostream>

using std::to_string;

Melodie::Melodie(int id, const string& titlu, const string& artist, int rank) : id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {

}

Melodie::Melodie(const Melodie& ot) : id{ ot.id }, titlu{ ot.titlu }, artist{ ot.artist }, rank{ ot.rank } {

}

Melodie& Melodie::operator=(const Melodie& ot) {
	id = ot.id;
	titlu = ot.titlu;
	artist = ot.artist;
	rank = ot.rank;

	return *this;
}

int Melodie::getId() const {
	return id;
}

const string& Melodie::getTitlu() const {
	return titlu;
}

const string& Melodie::getArtist() const {
	return artist;
}

int Melodie::getRank() const {
	return rank;
}

void Melodie::setTitlu(const string& new_titlu) {
	titlu = new_titlu;
}

void Melodie::setArtist(const string& new_artist) {
	artist = new_artist;
}

void Melodie::setRank(int new_rank) {
	rank = new_rank;
}

string Melodie::str() const {
	return to_string(id) + '\n' + titlu + '\n' + artist + '\n' + to_string(rank) + '\n';
}

bool Melodie::operator==(const Melodie& ot) const {
	return id == ot.id;
}
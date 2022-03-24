#include "InMemoryRepo.h"

#include <algorithm>
#include <exception>

using std::find_if;
using std::exception;

void InMemoryRepo::add(const Melodie& melodie) {
	const auto& it{ find_if(melodii.begin(), melodii.end(), [&melodie](const Melodie& m) { return melodie == m; }) };

	if (it != end(melodii))
		throw exception("Melodie deja existenta!\n");

	melodii.push_back(melodie);
}

void InMemoryRepo::modify(const Melodie& melodie) {
	auto& it{ find_if(melodii.begin(), melodii.end(), [&melodie](const Melodie& m) { return melodie == m; }) };

	if (it == end(melodii))
		throw exception("Melodie inexistenta!\n");

	auto& mel{ *it };

	mel.setTitlu(melodie.getTitlu());
	mel.setArtist(melodie.getArtist());
	mel.setRank(melodie.getRank());
}

void InMemoryRepo::del(int id) {
	const auto& it{ find_if(melodii.begin(), melodii.end(), [id](const Melodie& melodie) { return melodie.getId() == id; }) };

	if (it == end(melodii))
		throw exception("Melodie inexistenta!\n");

	melodii.erase(it);
}

const Melodie& InMemoryRepo::search(int id) const {
	const auto& it{ find_if(melodii.begin(), melodii.end(), [id](const Melodie& melodie) { return melodie.getId() == id; }) };

	if (it == end(melodii))
		throw exception("Melodie inexistenta!\n");

	return *it;
}

int InMemoryRepo::len() const {
	return melodii.size();
}

const vector<Melodie>& InMemoryRepo::getAll() const {
	return melodii;
}
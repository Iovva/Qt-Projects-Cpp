#pragma once
#include "Domain.h"
#include <exception>
#include <fstream>
#include <sstream>

using std::exception;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::stringstream;
using std::stoi;

class Repository
{
private:
	vector<Task> elems;
	string file_name;

	void read_from_file();
	void write_to_file();
public:
	Repository(string file_name) : file_name{ file_name } {
		read_from_file();
	}
	Repository(const Repository& other) = delete;
	Repository() = default;
	void add(const Task& t);

	void modif(int id, string stare);

	const Task& cauta(const int id);

	vector<Task>& get_all() {
		return elems;
	}
};


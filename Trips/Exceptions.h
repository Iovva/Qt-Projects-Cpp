#pragma once

#include <string>
using std::string;

class Exceptions
{

private:

	string ex;

public:

	Exceptions(const string& ex);
	
	string get_message() const;

};

class RepoExcept : public Exceptions{

public:

	RepoExcept(const string& ex) : Exceptions{ ex } {
	};

};

class ServiceExcept : public Exceptions {

public:

	ServiceExcept(const string& ex) : Exceptions{ ex } {
	};

};



#include "Exceptions.h"

Exceptions::Exceptions(const string& ex) : ex{ ex } {
}

string Exceptions::get_message() const {
	return ex;
}
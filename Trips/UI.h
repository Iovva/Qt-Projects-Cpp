#ifndef UI_H_
#define UI_H_

#include <iostream>
#include <string>
#include <exception>
#include "Service.h"

using std::cin;
using std::cout;
using std::string;
using std::getline;

class UI
{

public:

	UI(Service& service) : service{ service } {
	}

	void ui_run();

private:

	Service& service;

	void ui_adauga();

	void ui_sterge();

	void ui_modifica();

	void ui_print();

	void ui_cauta();

	void ui_help();

	void ui_sortare();

	void ui_filtrare();

	void ui_filtrare_destinatie();

	void ui_filtrare_pret();

	void check_cmd(string cmd);

	void ui_wishlist_adauga();

	void ui_wishlist_golire();

	void ui_wishlist_genereaza();

	void ui_wishlist_export_csv();

	void ui_wishlist_printeaza();

	void ui_raport();

	void ui_undo();
};
#endif

#include "UI.h"

void UI::ui_adauga() {
	string denumire, destinatie, tip, pret;
	cin.ignore();
	cout << "Introduceti denumirea:\n";
	getline(cin, denumire, '\n');
	cout << "Introduceti destinatia:\n";
	getline(cin, destinatie, '\n');
	cout << "Introduceti tipul:\n";
	getline(cin, tip, '\n');
	cout << "Introduceti pretul:\n";
	getline(cin, pret, '\n');
	service.service_adauga(denumire, destinatie, tip, pret);
	cout << "Adaugat cu succes!\n";
}

void UI::ui_sterge() {
	string id;
	cout << "Introduceti denumirea ofertei ce trebuie stearsa:\n";
	cin.ignore();
	getline(cin, id, '\n');
	service.service_sterge(id);
	cout << "Sters cu succes!\n";
}

void UI::ui_modifica() {
	string id, denumire, destinatie, tip, pret;
	cin.ignore();
	cout << "Introduceti denumirea ofertei ce trebuie modificate:\n";
	getline(cin, denumire, '\n');
	cout << "Introduceti destinatia:\n";
	getline(cin, destinatie, '\n');
	cout << "Introduceti tipul:\n";
	getline(cin, tip, '\n');
	cout << "Introduceti pretul:\n";
	getline(cin, pret, '\n');
	service.service_modifica(denumire, destinatie, tip, pret);
	cout << "Modificat cu succes!\n";
}

void UI::ui_print() {
	const auto& repo_all = service.service_get_all();
	if (size(repo_all) == 0) {
		cout << "Nu exista oferte!";
		return;
	}
	unsigned i = 0;
	for (const auto& el : repo_all)
	{
		cout << i << ".\n" <<
			"Denumirea: " << el.get_denumire() << "\n" <<
			"Destinatia: " << el.get_destinatie() << "\n" <<
			"Tipul: " << el.get_tip() << "\n" <<
			"Pretul: " << el.get_pret() << "\n";
		i++;
	}
}

void UI::ui_cauta() {
	string denumire;
	cin.ignore();
	cout << "Introduceti denumirea ofertei ce trebuie gasita:\n";
	getline(cin, denumire, '\n');
	const auto& oferta = service.service_cauta(denumire);
	cout << "Denumirea: " << oferta.get_denumire() << "\n" << 
	"Destinatia: " << oferta.get_destinatie() << "\n" <<
	"Tipul: " << oferta.get_tip() << "\n" <<
	"Pretul: " << oferta.get_pret() << "\n";
}

void UI::ui_sortare() {
	string mode, ascending;
	cin.ignore();
	cout << "Introduceti criteriul de sortare:\n"
		"0 - denumire\n"
		"1 - destinatie\n"
		"2 - tip + pret\n";
	getline(cin, mode, '\n');
	cout << "Cum doriti sa fie sortate elementele?:\n"
		"0 - Crescator\n"
		"1 - Descrescator\n";
	getline(cin, ascending, '\n');
	const auto& repo_all = service.service_sortare(mode, ascending);
	unsigned i = 0;
	for (const auto& el : repo_all)
	{
		cout << i << ".\n" <<
			"Denumirea: " << el.get_denumire() << "\n" <<
			"Destinatia: " << el.get_destinatie() << "\n" <<
			"Tipul: " << el.get_tip() << "\n" <<
			"Pretul: " << el.get_pret() << "\n";
		i++;
	}
}

void UI::ui_filtrare() {
	string mode;
	cin.ignore();
	cout << "Introduceti criteriul de filtrate:\n"
		"0 - destinatie\n"
		"1 - pret\n";
	getline(cin, mode, '\n');
	if (mode == "0")
		ui_filtrare_destinatie();
	else
		ui_filtrare_pret();
}

void UI::ui_filtrare_destinatie() {
	string filter, destinatie_comp;
	cout << "Cum doriti sa fie filtrate elementele?:\n"
		"0 - Toate cele care nu au destinatia data.\n"
		"1 - Toate cele care au au destinatia data.\n";
	getline(cin, filter, '\n');
	cout << "Introduceti destinatia:\n";
	getline(cin, destinatie_comp, '\n');
	const auto& repo_all = service.service_filtrare_destinatie(filter, destinatie_comp);
	unsigned i = 0;
	for (const auto& el : repo_all)
	{
		cout << i << ".\n" <<
			"Denumirea: " << el.get_denumire() << "\n" <<
			"Destinatia: " << el.get_destinatie() << "\n" <<
			"Tipul: " << el.get_tip() << "\n" <<
			"Pretul: " << el.get_pret() << "\n";
		i++;
	}
}

void UI::ui_filtrare_pret() {
	string filter, pret_comp;
	cout << "Cum doriti sa fie filtrate elementele?:\n"
		"0 - Toate mai mici la pret fata de pretul dat.\n"
		"1 - Toate egale la pret cu pretul dat\n"
		"2 - Toate mai mare la pret fata de pretul dat.\n";
	getline(cin, filter, '\n');
	cout << "Introduceti pretul:\n";
	getline(cin, pret_comp, '\n');
	const auto& repo_all = service.service_filtrare_pret(filter, pret_comp);
	unsigned i = 0;
	for (const auto& el : repo_all)
	{
		cout << i << ".\n" <<
			"Denumirea: " << el.get_denumire() << "\n" <<
			"Destinatia: " << el.get_destinatie() << "\n" <<
			"Tipul: " << el.get_tip() << "\n" <<
			"Pretul: " << el.get_pret() << "\n";
		i++;
	}
}

void UI::ui_wishlist_adauga() {
	string denumire;
	cin.ignore();
	cout << "Introduceti denumirea ofertelor ce trebuie adaugate:\n";
	getline(cin, denumire, '\n');
	service.service_wishlist_adauga(denumire);
}

void UI::ui_wishlist_golire() {
	service.service_wishlist_goleste();
	cout << "Golire efectuata cu succes!\n";
}

void UI::ui_wishlist_genereaza() {
	string n;
	cin.ignore();
	cout << "Introduceti numarul de oferte adaugate aleatoriu:\n";
	getline(cin, n, '\n');
	service.service_wishlist_genereaza(n);
	cout << "Elemente adaugate cu succes!\n";
}

void UI::ui_wishlist_export_csv() {
	string nume;
	cin.ignore();
	cout << "Introduceti numele fisierului unde trebuie exportat:\n";
	getline(cin, nume, '\n');
	service.service_wishlist_export_csv(nume);
	cout << "Adaugat cu succes!\n";
}

void UI::ui_wishlist_printeaza() {
	const vector<Oferta>& repo_all = service.service_wishlist_get_all();
	if (size(repo_all) == 0) {
		cout << "Nu exista oferte!";
		return;
	}
	unsigned i = 0;
	cout << "Exista " << service.service_wishlist_get_total() << " oferta(e):\n";
	for (const auto& el : repo_all)
	{
		cout << i << ".\n" <<
			"Denumirea: " << el.get_denumire() << "\n" <<
			"Destinatia: " << el.get_destinatie() << "\n" <<
			"Tipul: " << el.get_tip() << "\n" <<
			"Pretul: " << el.get_pret() << "\n";
		i++;
	}
}

void UI::ui_raport() {
	cout << "Numarul de oferte pentru fiecare destinatie:\n";
	const unordered_map <string, DTO>& repo_raport = service.service_raport();
	for (const auto& el : repo_raport) {
		DTO p = el.second;
		cout << el.first << " apare de " << p.get_count() + 1 << " ori \n";
	}
	cout << "\n";
}

void UI::ui_undo() {
	service.service_undo();
	cout << "Undo efectuat cu succes!\n";
}

void UI::ui_help() {
	cout << "\n-1. EXIT\n";
	cout << " 0. HELP\n";
	cout << " 1. Adaugare oferta.\n";
	cout << " 2. Sterge oferta.\n";
	cout << " 3. Modifica oferta.\n";
	cout << " 4. Printeaza oferte.\n";
	cout << " 5. Cauta oferta.\n";
	cout << " 6. Sortare oferte\n";
	cout << " 7. Filtrare oferte\n";
	cout << " 8. Adauga wishlist\n";
	cout << " 9. Golire wishlist\n";
	cout << " 10. Generare wishlist\n";
	cout << " 11. Export wishlist\n";
	cout << " 12. Printeaza wishlist\n";
	cout << " 13. Raport\n";
	cout << " 14. Undo\n";
}

void UI::check_cmd(string cmd) {
	if (service.utils.check_nr(cmd) != 1)
		throw(ServiceExcept{ "Comanda invalid!\n" });
}

void UI::ui_run() {
	string cmd;
	bool run{ true };
	this->ui_help();
	while (run == true)
	{

		cout << "\n";
		cin >> cmd;
		cout << "\n";
		try {
			check_cmd(cmd);
			switch (stoi(cmd)) {
			case -1:
				run = false;
				break;
			case 0:
				this->ui_help();
				break;
			case 1:
				this->ui_adauga();
				break;
			case 2:
				this->ui_sterge();
				break;
			case 3:
				this->ui_modifica();
				break;
			case 4:
				this->ui_print();
				break;
			case 5:
				this->ui_cauta();
				break;
			case 6:
				this->ui_sortare();
				break;
			case 7:
				this->ui_filtrare();
				break;
			case 8:
				this->ui_wishlist_adauga();
				break;
			case 9:
				this->ui_wishlist_golire();
				break;
			case 10:
				this->ui_wishlist_genereaza();
				break;
			case 11:
				this->ui_wishlist_export_csv();
				break;
			case 12:
				this->ui_wishlist_printeaza();
				break;
			case 13:
				this->ui_raport();
				break;
			case 14:
				this->ui_undo();
				break;
			default:
				cout << ("Comanda 0 afiseaza ajutorul!\n");
				break;
			}
		}
		catch (const RepoExcept& re){
			cout << re.get_message() << "\n";
		}
		catch (const ServiceExcept& re) {
			cout << re.get_message() << "\n";
		}
	}
	cout << "Au revoir!";
	return;
}
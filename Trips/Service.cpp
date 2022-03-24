#include "Service.h"

void Service::service_adauga(const string& denumire, const string& destinatie, const string& tip, const string& pret) {
	string err = utils.check_oferta(denumire, destinatie, tip, pret);
	if (err != "")
		throw(ServiceExcept{ err });
	Oferta of{ denumire, destinatie, tip, stof(pret)};
	repo.adauga(of);
	auto repo_all = repo.get_all();
	undo.push_back(make_unique<UndoAdauga>(repo, of.get_denumire()));
	notify();
}

void Service::service_sterge(const string& denumire) {
	const Oferta& aux = repo.sterge(denumire);
	undo.push_back(make_unique<UndoSterge>(repo, aux));
	notify();
}

void Service::service_modifica(const string& denumire, const string& destinatie, const string& tip, const string& pret) {
	string err = utils.check_oferta(denumire, destinatie, tip, pret);
	if (err != "")
		throw(ServiceExcept{ err });
	Oferta of{ denumire, destinatie, tip, stof(pret)};
	const Oferta& aux = repo.modifica(of);
	undo.push_back(make_unique<UndoModifica>(repo, aux));
	notify();
}

const vector<Oferta> Service::service_get_all() const {
	const auto repo_all = repo.get_all();
	return repo_all;
}

const Oferta& Service::service_cauta(const string& nume) {
	const Oferta& of = repo.cauta(nume);
	return of;
}

vector<Oferta> Service::service_sortare(const string& mode, const string& ascending) {
	if (utils.check_nr(mode) != 1)
		throw(ServiceExcept{ "Criteriu invalid!\n" });
	else if (stoi(mode) != 0 && stoi(mode) != 1 && stoi(mode) != 2)
		throw(ServiceExcept{  "Criteriu invalid!\n" });
	else if (utils.check_nr(ascending) != 1)
		throw(ServiceExcept{ "Selectie invalida!\n" });
	else if (stoi(ascending) != 0 && stoi(ascending) != 1)
		throw(ServiceExcept{ "Selectie invalid!\n" });
	vector<Oferta> repo_all = repo.get_all();
	if (stoi(mode) == 0 && stoi(ascending) == 0)
		sort(repo_all.begin(), repo_all.end(),
			[](const Oferta& of1, const Oferta& of2) {
				return of1.get_denumire() < of2.get_denumire();
			});
	else if (stoi(mode) == 1 && stoi(ascending) == 0)
		sort(repo_all.begin(), repo_all.end(),
			[](const Oferta& of1, const Oferta& of2) {
				return of1.get_destinatie() < of2.get_destinatie();
			});
	else if (stoi(mode) == 2 && stoi(ascending) == 0)
		sort(repo_all.begin(), repo_all.end(),
			[](const Oferta& of1, const Oferta& of2) {
				return (of1.get_tip() < of2.get_tip() || (of1.get_tip() == of2.get_tip() && of1.get_pret() < of2.get_pret()));
			});
	else if (stoi(mode) == 0 && stoi(ascending) == 1)
		sort(repo_all.begin(), repo_all.end(),
			[](const Oferta& of1, const Oferta& of2) {
				return of1.get_denumire() > of2.get_denumire();
			});
	else if (stoi(mode) == 1 && stoi(ascending) == 1)
		sort(repo_all.begin(), repo_all.end(),
			[](const Oferta& of1, const Oferta& of2) {
				return of1.get_destinatie() > of2.get_destinatie();
			});
	else 
		sort(repo_all.begin(), repo_all.end(),
			[](const Oferta& of1, const Oferta& of2) {
				return (of1.get_tip() > of2.get_tip() || (of1.get_tip() == of2.get_tip() && of1.get_pret() > of2.get_pret()));
			});
	return repo_all;
}


vector<Oferta> Service::service_filtrare_destinatie(const string& filter, const string& destinatie_comp) {
	if (utils.check_nr(filter) != 1)
		throw(ServiceExcept{ "Criteriu invalid!\n" });
	else if (stoi(filter) != 0 && stoi(filter) != 1)
		throw(ServiceExcept{ "Criteriu invalid!\n" });
	const auto& repo_all = repo.get_all();
	vector<Oferta> repo_filtrat;
	if (stoi(filter) == 0)
		copy_if(repo_all.begin(), repo_all.end(), std::back_inserter(repo_filtrat), [=](const Oferta& of) {
		return of.get_destinatie() == destinatie_comp; });
	else
		copy_if(repo_all.begin(), repo_all.end(), std::back_inserter(repo_filtrat), [=](const Oferta& of) {
		return of.get_destinatie() != destinatie_comp; });
	if (size(repo_filtrat) == 0) 
		throw(ServiceExcept{ "Lista este goala!\n" });
	return repo_filtrat;
}

vector<Oferta> Service::service_filtrare_pret(const string& filter, const string& pret_comp) {
	if (utils.check_nr(filter) != 1)
		throw(ServiceExcept{ "Filtru invalid!\n" });
	else if (stoi(filter) != 0 && stoi(filter) != 1 && stoi(filter) != 2)
		throw(ServiceExcept{ "Filtru invalid!\n" });
	if (utils.check_nr(pret_comp) == 0 || utils.check_nr(pret_comp) == -1)
		throw(ServiceExcept{ "Pret invalid!\n" });
	const auto& repo_all = repo.get_all();
	vector<Oferta> repo_filtrat;
	if (stoi(filter) == 0)
		copy_if(repo_all.begin(), repo_all.end(), std::back_inserter(repo_filtrat), [=](const Oferta& of) {
		return of.get_pret() < stof(pret_comp); });
	else if (stoi(filter) == 1)
		copy_if(repo_all.begin(), repo_all.end(), std::back_inserter(repo_filtrat), [=](const Oferta& of) {
		return (of.get_pret() - stof(pret_comp) < static_cast<float>(0.001) && of.get_pret() - stof(pret_comp) > static_cast<float>(-0.001)); });
	else
		copy_if(repo_all.begin(), repo_all.end(), std::back_inserter(repo_filtrat), [=](const Oferta& of) {
		return of.get_pret() > stof(pret_comp); });
	if (size(repo_filtrat) == 0)
		throw(ServiceExcept{ "Lista este goala!\n" });
	return repo_filtrat;
}	

void Service::service_wishlist_adauga(const string& denumire) {
	if (denumire == "")
		throw(ServiceExcept{ "Denumire invalda!\n" });
	wishlist.adauga(denumire);
	notify();
}

void Service::service_wishlist_goleste() {
	wishlist.goleste();
	notify();
}

void Service::service_wishlist_genereaza(const string& n) {
	if (utils.check_nr(n) != 1)
		throw(ServiceExcept{ "Numar invald!\n" });
	wishlist.genereaza(stoi(n));
	notify();
}

void Service::service_wishlist_export_csv(const string& nume) {
	if (nume == "")
		throw(ServiceExcept{ "Nume invald!\n" });
	wishlist.export_csv(nume);
}

const vector<Oferta>& Service::service_wishlist_get_all() {
	return wishlist.get_all();
}

int Service::service_wishlist_get_total() {
	return wishlist.get_total();
}

unordered_map <string, DTO> Service::service_raport() {
	unordered_map<string, DTO> map;
	const auto& repo_all = repo.get_all();
	for (const auto& el : repo_all) {
		const auto& destinatie = el.get_destinatie();
		if (map.find(destinatie) != map.end())
			map[destinatie].inc();
		else
			map[destinatie] = DTO(destinatie);
	}
	return map;
}

void Service::service_undo() {
	if (undo.empty() == true)
		throw ServiceExcept("Nu se mai poate realiza undo!\n");
	undo.back()->undo();
	undo.pop_back();
}
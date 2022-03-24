#ifndef UNDO_H_
#define UNDO_H_

#include "Oferta.h"
#include "Repository.h"

class ActiuneUndo
{

public:

	virtual void undo() = 0;

	virtual ~ActiuneUndo(){}

};

class UndoAdauga : public ActiuneUndo {

private:

	const string denumire_oferta;
	RepoAbstract& repo;

public:

	// initializeaza obiectul cu referinta la repo si id-ul ofertei adaugate
	UndoAdauga(RepoAbstract& repo, const string denumire_oferta) :
		repo{ repo }, denumire_oferta{ denumire_oferta }{};

	// sterge oferta de id dat
	void undo() override {
		repo.sterge(denumire_oferta);
	}
	

};

class UndoSterge : public ActiuneUndo {

private:

	Oferta oferta_stearsa;
	RepoAbstract& repo;

public:

	// initializeaza obiectul cu referinta la repo si oferta stearsa
	UndoSterge(RepoAbstract& repo, const Oferta& oferta_stearsa) :
		repo{ repo }, oferta_stearsa{ oferta_stearsa }{};

	// adauga oferta stearsa inapoi in lista
	void undo() override {
		repo.adauga(oferta_stearsa);
	}
};

class UndoModifica : public ActiuneUndo {

private:

	Oferta oferta_modificata;
	RepoAbstract& repo;

public:

	// initializeaza obiectul cu referinta la repo, oferta stearsa si id-ul ofertei modificate
	UndoModifica(RepoAbstract& repo, const Oferta& oferta_modificata) :
		repo{ repo }, oferta_modificata{ oferta_modificata } {};

	// modifica oferta la valoarea initiala
	void undo() override {
		repo.modifica(oferta_modificata);
	}
};

#endif
#ifndef GUI_H_
#define GUI_H

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qpushbutton.h>
#include <qheaderview.h>
#include <qgroupbox.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qspinbox.h>
#include "Service.h"
#include <qpainter.h>
#include <QtWidgets/qslider.h>
#include <qtableview.h>
#include "ModelView.h"

class GUI : public QWidget
{

private:

	Service& service;

	QTableView* table = new QTableView;
	QLineEdit* editDenumire = new QLineEdit;
	QLineEdit* editDestinatie = new QLineEdit;
	QLineEdit* editTip = new QLineEdit;
	QLineEdit* editPret = new QLineEdit;
	QPushButton* butonAdauga = new QPushButton{ "Adauga oferta" };
	QPushButton* butonSterge = new QPushButton{ "Stergere oferta" };
	QPushButton* butonModifica = new QPushButton{ "Modifica oferta dupa destinatie" };
	QPushButton* butonCauta = new QPushButton{ "Cauta oferta dupa destinatie" };
	QPushButton* butonFiltrare = new QPushButton{ "Filtrare" };
	QPushButton* butonWishlist = new QPushButton{ "Wishlist" };
	QPushButton* butonRaport = new QPushButton{ "Raport" };
	QPushButton* butonUndo = new QPushButton{ "Undo" };
	QPushButton* butonWishlistCrud = new QPushButton{ "CosCRUD" };
	QPushButton* butonWishlistReadOnly = new QPushButton{ "CosReadOnly" };
	QPushButton* butonAdaugaWishlist = new QPushButton{ "Adauga in wishlist" };
	QPushButton* butonGolesteWishlist = new QPushButton{ "Goleste wishlist" };
	QPushButton* butonGenereazaWishlist = new QPushButton{ "Genereaza wishlist" };
	// QSpinBox* sBoxWishlist = new QSpinBox;
	QSlider* sliderWishlist = new QSlider;
	QLineEdit* editInputWishlist = new QLineEdit;
	QLabel* labelWishlist = new QLabel;

	void initGUI();
	
	void connectSignals();

	MyTableModel* model;

public:

	GUI(Service& service) : service{ service } {
		model = new MyTableModel{ service };
		table->setModel(model);
		service.addObserver(model);
		initGUI();
		connectSignals(); 
	}
};

class GUIStergere : public QWidget {
private:
	GUI& gui;
	Service& service;
public:
	GUIStergere(GUI& gu, Service& serv);
};

class GUICauta : public QWidget {
private:
	GUI& gui;
	Service& service;
	QLineEdit* editDenumire = new QLineEdit;
	QLineEdit* editDestinatie = new QLineEdit;
	QLineEdit* editTip = new QLineEdit;
	QLineEdit* editPret = new QLineEdit;
public:
	GUICauta(GUI& gui, Service& serv);
};


class GUIFiltrare : public QWidget {
public:
	

	void addToList(const vector<Oferta>& lista_oferte);
	GUIFiltrare(Service& serv) : service{ serv } {
		initGUI();
		connectSignals();
		setInitialGUIState();
	}

private:
	void initGUI();
	void connectSignals();
	void setInitialGUIState();

	Service& service;
	QTableWidget* table = new QTableWidget(0, 4, this);
	QLineEdit* editInput = new QLineEdit;
	QComboBox* comboBox = new QComboBox();
	QPushButton* butonFiltrare = new QPushButton{ "Filtreaza" };

	QRadioButton* radioDestinatie0 = new QRadioButton();
	QRadioButton* radioDestinatie1 = new QRadioButton();
	QRadioButton* radioPret0 = new QRadioButton();
	QRadioButton* radioPret1 = new QRadioButton();
	QRadioButton* radioPret2 = new QRadioButton();
};

class GUIWishlist : public QWidget, public Observer {
public:

	void addToList(const vector<Oferta>& lista_oferte);
	GUIWishlist(Service& serv) : service{ serv } {
		service.addObserver(this);
		initGUI();
		connectSignals();
		setInitialGUIState();
	}

private:

	void update() override;
	void initGUI();
	void connectSignals();
	void setInitialGUIState();
	Service& service;
	QTableWidget* table = new QTableWidget(0, 4, this);
	QLineEdit* editInput = new QLineEdit;
	QPushButton* butonAdauga = new QPushButton{ "Adauga in wishlist" };
	QPushButton* butonGoleste = new QPushButton{ "Goleste wishlist" };
	QPushButton* butonGenereaza = new QPushButton{ "Genereaza wishlist" };
	QPushButton* butonExport = new QPushButton{ "Export" };
	QSpinBox* sBox = new QSpinBox;
};

class GUIWishlistCRUD : public QWidget, public Observer {
public:

	void addToList(const vector<Oferta>& lista_oferte);
	GUIWishlistCRUD(Service& serv) : service{ serv } {
		service.addObserver(this);
		initGUI();
		connectSignals();
		setInitialGUIState();
	}

private:

	void update() override;
	void initGUI();
	void connectSignals();
	void setInitialGUIState();
	Service& service;
	QTableWidget* table = new QTableWidget(0, 4, this);
	QLineEdit* editInput = new QLineEdit;
	QPushButton* butonGoleste = new QPushButton{ "Goleste wishlist" };
	QPushButton* butonGenereaza = new QPushButton{ "Genereaza wishlist" };
	QSpinBox* sBox = new QSpinBox;
};

class GUIWishlistReadOnly : public QWidget, public Observer {

public:

	GUIWishlistReadOnly(Service& serv) : service(serv) {
		service.addObserver(this);
	}

	~GUIWishlistReadOnly() {
		service.removeObserver(this);
	}

	void paintEvent(QPaintEvent* ev) override;

private:

	void update() override {
		repaint();
	}

	Service& service;

};

#endif
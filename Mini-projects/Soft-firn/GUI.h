#pragma once
#include "Service.h"
#include "MyModel.h"
#include <qapplication.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include <qtablewidget.h>

class GUI_stare : public QWidget, public Observer
{
private:
	Service& srv;
	string stare;
	string mod = "stare";
	int id = -5;

	QTableWidget* table = new QTableWidget{ 0,4 };

	QPushButton* btn_open = new QPushButton{ "Open" };
	QPushButton* btn_inprog = new QPushButton{ "Inprogress" };
	QPushButton* btn_close = new QPushButton{ "Close" };

	void update() override {
		addToTable(srv.Filtrare(mod, stare));
	}

	void initGUI() {
		this->setWindowTitle(QString::fromStdString(stare));
		QVBoxLayout* lay_main = new QVBoxLayout;
		setLayout(lay_main);
		lay_main->addWidget(table);
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		table->setSelectionMode(QAbstractItemView::SingleSelection);
		table->setMinimumHeight(326);

		QHBoxLayout* lay_btn = new QHBoxLayout;
		lay_btn->addWidget(btn_open);
		lay_btn->addWidget(btn_inprog);
		lay_btn->addWidget(btn_close);
		lay_main->addLayout(lay_btn);
		
	}
	void addToTable(vector<Task> v) {
		sort(v.begin(), v.end(), [](Task& t1, Task& t2) {
			return t1.get_stare() < t2.get_stare();
			});
		table->clear();
		id = -5;
		table->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
		table->setHorizontalHeaderItem(1, new QTableWidgetItem("Descriere"));
		table->setHorizontalHeaderItem(2, new QTableWidgetItem("Programatori"));
		table->setHorizontalHeaderItem(3, new QTableWidgetItem("Stare"));
		table->setRowCount(int(v.size()));
		int linie = 0;
		for (const Task& t : v)
		{
			table->setItem(linie, 0, new QTableWidgetItem(QString::number(t.get_id())));
			table->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(t.get_descriere())));
			table->setItem(linie, 2, new QTableWidgetItem(QString::number(t.get_programatori().size())));
			table->setItem(linie, 3, new QTableWidgetItem(QString::fromStdString(t.get_stare())));
			linie++;
		}
		table->resizeColumnsToContents();
		int width = table->columnWidth(0) + table->columnWidth(1) +
			table->columnWidth(2) + table->columnWidth(3) + 41;
		table->setMinimumWidth(width);
	}
	void connectSignals() {
		QObject::connect(table, &QTableWidget::itemSelectionChanged, this, [=]() {
			id = -5;
			auto sel = table->selectedItems();

			if (sel.isEmpty())
				return;

			id = sel.at(0)->data(0).toInt();
			});

		QObject::connect(btn_open, &QPushButton::clicked, this, [=]() {
			try {
				srv.Modifica_stare(id, "Open");
			}
			catch (exception) { QMessageBox::critical(this, "Eroare", "Selectie invalida"); }
			});
		QObject::connect(btn_inprog, &QPushButton::clicked, this, [=]() {
			try {
				srv.Modifica_stare(id, "Inprogress");
			}
			catch (exception) { QMessageBox::critical(this, "Eroare", "Selectie invalida"); }
			});
		QObject::connect(btn_close, &QPushButton::clicked, this, [=]() {
			try {
				srv.Modifica_stare(id, "Close");
			}
			catch (exception) { QMessageBox::critical(this, "Eroare", "Selectie invalida"); }
			});
	}
public:
	GUI_stare(Service& srv, string stare) :srv{ srv }, stare{ stare } {
		srv.addObserver(this);
		initGUI();
		addToTable(srv.Filtrare("stare", stare));
		connectSignals();
	}
	~GUI_stare() {
		srv.removeObserver(this);
	}
};

class GUI: public QWidget, public Observer
{
private:
	Service& srv;

	//MyModel* model = new MyModel{ srv, "" };
	QTableWidget* table = new QTableWidget{ 0,4 };

	QPushButton* btn_adauga = new QPushButton{ "Adauga" };

	QLineEdit* edit_id = new QLineEdit;
	QLineEdit* edit_descriere = new QLineEdit;
	vector<QLineEdit*> edit_progs;
	QLineEdit* edit_stare = new QLineEdit;
	QLineEdit* edit_search = new QLineEdit;

	void update() override {
		addToTable(srv.GetAll());
	}

	void clear_text() {
		edit_id->clear();
		edit_descriere->clear();
		for (auto el : edit_progs)
			el->clear();
		edit_stare->clear();
	}

	void initGUI() {
		for (int i = 0; i < 4; i++)
			edit_progs.push_back(new QLineEdit);

		QHBoxLayout* lay_main = new QHBoxLayout;
		setLayout(lay_main);
		lay_main->addWidget(table);
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		table->setSelectionMode(QAbstractItemView::SingleSelection);
		table->setMinimumHeight(326);

		QVBoxLayout* lay_dreapta = new QVBoxLayout;
		
		QFormLayout* form = new QFormLayout;
		form->addRow("ID", edit_id);
		form->addRow("Descriere", edit_descriere);
		form->addRow("Programator 1", edit_progs[0]);
		form->addRow("Programator 2", edit_progs[1]);
		form->addRow("Programator 3", edit_progs[2]);
		form->addRow("Programator 4", edit_progs[3]);
		form->addRow("Stare", edit_stare);
		lay_dreapta->addLayout(form);

		lay_dreapta->addStretch();

		lay_dreapta->addWidget(btn_adauga);
		QFormLayout* form2 = new QFormLayout;
		form2->addRow("Search", edit_search);
		lay_dreapta->addLayout(form2);

		lay_main->addLayout(lay_dreapta);
	}

	void connectSignals() {
		QObject::connect(table, &QTableWidget::itemSelectionChanged, this, [=]() {
			clear_text();
			auto sel = table->selectedItems();

			if (sel.isEmpty())
				return;

			int id = sel.at(0)->data(0).toInt();
			
			try {
				auto task = srv.Cauta(id);
				edit_id->setText(QString::number(task.get_id()));
				edit_descriere->setText(QString::fromStdString(task.get_descriere()));
				int i = 0;
				for (const auto& pr : task.get_programatori())
				{
					edit_progs[i]->setText(QString::fromStdString(pr));
					i++;
				}
				edit_stare->setText(QString::fromStdString(task.get_stare()));
			}
			catch(exception& ex){ QMessageBox::critical(this, "Eroare", ex.what()); }
			});
		QObject::connect(btn_adauga, &QPushButton::clicked, this, [=]() {
			int id = edit_id->text().toInt();
			string descriere = edit_descriere->text().toStdString();
			vector<string> programatori;
			for (auto el : edit_progs)
				if (el->text() != "")
					programatori.push_back(el->text().toStdString());
			string stare = edit_stare->text().toStdString();

			try {
				srv.Adauga(id, descriere, programatori, stare);
				addToTable(srv.GetAll());
			}
			catch (exception& ex) { QMessageBox::critical(this, "Eroare", ex.what()); }
			connectSignals();
			});
		QObject::connect(edit_search, &QLineEdit::textChanged, this, [=]() {
			string sub = edit_search->text().toStdString();
			addToTable(srv.Filtrare("programatori",sub));
			});
	}

	void addToTable(vector<Task> v) {
		sort(v.begin(), v.end(), [](Task& t1, Task& t2) {
			return t1.get_stare() < t2.get_stare();
			});
		table->clear();
		table->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
		table->setHorizontalHeaderItem(1, new QTableWidgetItem("Descriere"));
		table->setHorizontalHeaderItem(2, new QTableWidgetItem("Programatori"));
		table->setHorizontalHeaderItem(3, new QTableWidgetItem("Stare"));
		table->setRowCount(int(v.size()));
		int linie = 0;
		for (const Task& t : v)
		{
			table->setItem(linie, 0, new QTableWidgetItem(QString::number(t.get_id())));
			table->setItem(linie, 1, new QTableWidgetItem(QString::fromStdString(t.get_descriere())));
			table->setItem(linie, 2, new QTableWidgetItem(QString::number(t.get_programatori().size())));
			table->setItem(linie, 3, new QTableWidgetItem(QString::fromStdString(t.get_stare())));
			linie++;
		}
		table->resizeColumnsToContents();
		int width = table->columnWidth(0) + table->columnWidth(1) +
			table->columnWidth(2) + table->columnWidth(3) + 41;
		table->setMinimumWidth(width);
	}

public:
	GUI(Service& srv) :srv{ srv } {
		srv.addObserver(this);
		GUI_stare* gui_open = new GUI_stare{ srv, "Open" };
		GUI_stare* gui_inprog = new GUI_stare{ srv, "Inprogress" };
		GUI_stare* gui_close = new GUI_stare{ srv, "Close" };
		gui_open->show();
		gui_inprog->show();
		gui_close->show();
		initGUI();
		addToTable(srv.GetAll());
		connectSignals();
	}
	~GUI() {
		srv.removeObserver(this);
	}
	void closeEvent(QCloseEvent* ev) override {
		QWidget::closeEvent(ev);
		QApplication::quit();
	}
};
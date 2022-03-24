#pragma once

#include "Service.h"
#include "TableModel.h"
#include "TipProdus.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qlabel.h>

class GUI : public QWidget
{
private:
	Service& srv;

	QTableView* tbl = new QTableView;
	TableModel* model = new TableModel{ srv };

	QFormLayout* form = new QFormLayout;

	QLineEdit* id_edt = new QLineEdit;
	QLineEdit* nume_edt = new QLineEdit;
	QLineEdit* tip_edt = new QLineEdit;
	QLineEdit* pret_edt = new QLineEdit;

	QPushButton* btn_add = new QPushButton{ "Adaugare" };

	QSlider* sld = new QSlider;

	QLineEdit* val = new QLineEdit;

	QHBoxLayout* ly2 = new QHBoxLayout;

	QVBoxLayout* ly = new QVBoxLayout;

	QLabel* lbl = new QLabel{ "Valoare curenta slider" };

	void setInitialGUIState();
	void initGUICmps();
	void connectSignals();

public:
	GUI() = delete;

	GUI(Service& srv) : srv{ srv } {
		setInitialGUIState();
		initGUICmps();
		connectSignals();
	}

	~GUI() = default;
};


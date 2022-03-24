#pragma once

#include "Service.h"
#include "TableModel.h"
#include "Histogram.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <qpainter.h>

class GUI : public QWidget {
private:
	Service& srv;

	Histogram* hst = new Histogram{ srv };

	TableModel* model = new TableModel{ srv };

	QTableView* tbl = new QTableView;

	QVBoxLayout* main_ly = new QVBoxLayout;
	QVBoxLayout* ly = new QVBoxLayout;

	QLineEdit* id_edt = new QLineEdit;
	QLineEdit* titlu_edt = new QLineEdit;
	QLineEdit* artist_edt = new QLineEdit;
	QLineEdit* rank_edt = new QLineEdit;

	QPushButton* btn_add = new QPushButton{ "Adaugare melodie" };
	QPushButton* btn_modify = new QPushButton{ "Update melodie" };
	QPushButton* btn_delete = new QPushButton{ "Stergere melodie dupa id" };

	QHBoxLayout* btns_ly = new QHBoxLayout;

	QHBoxLayout* ly_sld = new QHBoxLayout;
	QSlider* sld = new QSlider;
	QLabel* lbl_sld = new QLabel;

	QHBoxLayout* ly_box = new QHBoxLayout;
	QSpinBox* sld_box = new QSpinBox;
	QLabel* lbl_box = new QLabel{ "Rank selectat" };

	QFormLayout* form = new QFormLayout;

	void setInitialGUIState();
	void connectSignals();
	void initGUICmps();

public:
	GUI() = delete;

	GUI(Service& srv) : srv{ srv } {
		this->setWindowTitle("Aplicatie melodii");

		initGUICmps();
		setInitialGUIState();
		connectSignals();
	}

	~GUI() = default;
};

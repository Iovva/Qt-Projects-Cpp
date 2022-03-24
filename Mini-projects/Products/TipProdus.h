#pragma once

#include "Observer.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qboxlayout.h>

#include <string>
#include "Service.h"

using std::string;

class TipProdus : public QWidget, public Observer
{
private:
	Service& srv;
	string tip;

	QLabel* label = new QLabel;

	QHBoxLayout* ly = new QHBoxLayout;

public:
	TipProdus() = delete;

	TipProdus(Service& srv, const string& tip) : srv{ srv }, tip{ tip } {
		srv.attachObserver(this);

		this->setWindowTitle(QString::fromStdString(tip));

		label->setText(QString::number(srv.countType(tip)));

		this->setLayout(ly);

		ly->addWidget(label);

		this->show();
	}

	void update() override {
		label->setText(QString::number(srv.countType(tip)));
	}

	void closeEvent(QCloseEvent* ev) override {
		this->~TipProdus();
	}

	~TipProdus() {
		srv.detachObserver(this);
	}
};
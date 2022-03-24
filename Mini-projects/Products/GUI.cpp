#include "GUI.h"

#include <qmessagebox.h>

#include <exception>

using std::exception;

void GUI::setInitialGUIState() {
	auto multime{ srv.getSet() };

	for (const auto& tip_produs : multime)
		TipProdus* wdg = new TipProdus{ srv, tip_produs };
}

void GUI::initGUICmps() {
	this->setLayout(ly);

	tbl->setModel(model);

	ly->addWidget(tbl);

	form->addRow("Id", id_edt);
	form->addRow("Nume", nume_edt);
	form->addRow("Tip", tip_edt);
	form->addRow("Pret", pret_edt);

	ly->addLayout(form);

	ly->addWidget(btn_add);

	sld->setMinimum(1);
	sld->setMaximum(100);
	sld->setValue(1);
	sld->setOrientation(Qt::Horizontal);

	ly->addWidget(sld);

	val->setReadOnly(true);

	ly->addLayout(ly2);

	ly2->addWidget(lbl);
	ly2->addWidget(val);
}

void GUI::connectSignals() {
	QObject::connect(btn_add, &QPushButton::clicked, [&]() {
		int id = id_edt->text().toInt();
		string nume = nume_edt->text().toStdString();
		string tip = tip_edt->text().toStdString();
		double pret = pret_edt->text().toDouble();

		try {
			srv.add(id, nume, tip, pret);
			model->setLayoutChanged(0);
		}
		catch (const exception& ex) {
			QMessageBox::warning(nullptr, "Date invalide", ex.what());
		}
		});

	QObject::connect(sld, &QSlider::sliderMoved, [&]() {
		val->setText(QString::number(sld->value()));

		model->setLayoutChanged(sld->value());
		});
}
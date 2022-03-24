#include "GUI.h"

#include <qmessagebox.h>
#include <qdebug.h>

#include <exception>

using std::exception;

void GUI::setInitialGUIState() {

}

void GUI::connectSignals() {
	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty())
		{
			id_edt->setText("");
			titlu_edt->setText("");
			artist_edt->setText("");
			rank_edt->setText("");

			sld->setValue(0);

			return;
		}

		auto selRow = tbl->selectionModel()->selectedIndexes().at(0).row();
		auto id = tbl->model()->data(tbl->model()->index(selRow, 0), Qt::DisplayRole).toInt();

		const auto& melodie{ srv.searchServ(id) };

		id_edt->setText(QString::number(id));
		titlu_edt->setText(QString::fromStdString(melodie.getTitlu()));
		artist_edt->setText(QString::fromStdString(melodie.getArtist()));
		rank_edt->setText(QString::number(melodie.getRank()));

		sld->setValue(melodie.getRank());
		});

	QObject::connect(btn_add, &QPushButton::clicked, [&]() {
		int id = id_edt->text().toInt();
		string titlu = titlu_edt->text().toStdString();
		string artist = artist_edt->text().toStdString();
		int rank = rank_edt->text().toInt();

		try {
			srv.addServ(id, titlu, artist, rank);

			model->modified();
		}
		catch (const exception& ex) {
			QMessageBox::warning(nullptr, "Melodie invalida", ex.what());
		}
		});

	QObject::connect(btn_modify, &QPushButton::clicked, [&]() {
		int id = id_edt->text().toInt();
		string titlu = titlu_edt->text().toStdString();
		string artist = artist_edt->text().toStdString();
		int rank = rank_edt->text().toInt();

		try {
			srv.modifyServ(id, titlu, artist, rank);

			model->modified();
		}
		catch (const exception& ex) {
			QMessageBox::warning(nullptr, "Melodie invalida", ex.what());
		}
		});

	QObject::connect(btn_delete, &QPushButton::clicked, [&]() {
		if (id_edt->text().isEmpty())
			return;

		int id = id_edt->text().toInt();

		if (srv.lenServ() == 1)
		{
			QMessageBox::information(nullptr, "Ultima melodie!", "Melodia nu a fost stearsa!");

			return;
		}

		try {
			srv.delServ(id);

			model->modified();
		}
		catch (const exception& ex) {
			QMessageBox::warning(nullptr, "Melodie invalida", ex.what());
		}
		});

	QObject::connect(sld, &QSlider::valueChanged, [&]() {
		sld_box->setValue(sld->value());

		rank_edt->setText(QString::number(sld->value()));
		});
}

void GUI::initGUICmps() {
	this->setLayout(main_ly);

	tbl->setModel(model);

	this->setMinimumHeight(tbl->height());
	this->setMinimumWidth(tbl->width());

	main_ly->addWidget(tbl);

	form->addRow("Id", id_edt);
	form->addRow("Titlu", titlu_edt);
	form->addRow("Artist", artist_edt);
	form->addRow("Rank", rank_edt);

	main_ly->addLayout(form);

	btns_ly->addWidget(btn_add);
	btns_ly->addWidget(btn_modify);
	btns_ly->addWidget(btn_delete);

	main_ly->addLayout(btns_ly);

	sld->setMinimum(0);
	sld->setMaximum(10);
	sld->setValue(0);
	sld->setOrientation(Qt::Horizontal);

	lbl_sld->setText("Rank curent");

	ly_sld->addWidget(lbl_sld);
	ly_sld->addWidget(sld);

	main_ly->addLayout(ly_sld);

	sld_box->setMinimum(0);
	sld_box->setMaximum(10);
	sld_box->setValue(0);
	sld_box->setReadOnly(true);

	ly_box->addWidget(lbl_box);
	ly_box->addWidget(sld_box);

	main_ly->addLayout(ly_box);

	ly->addWidget(hst);

	main_ly->addLayout(ly);
}
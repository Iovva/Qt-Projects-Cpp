#pragma once
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qtableview.h>
#include <QtWidgets\qboxlayout.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qlabel.h>
#include "TableModelView.h"
#include <QPainter>

class GUI : public QWidget
{
private:
	int id_sterge = -1;
	Service& srv;
	TableModelView* tbl_model;
	QTableView* tbl = new QTableView;
	QVBoxLayout* vb = new QVBoxLayout;
	QPushButton* btn_add = new QPushButton{ "&Adauga element" };
	QPushButton* btn_delete = new QPushButton{ "&Sterge element" };
	QLabel* label_title = new QLabel{ "Titlu" };
	QLabel* label_artist = new QLabel{ "Autor" };
	QLabel* label_genre = new QLabel{ "Gen" };
	QLineEdit* edit_title = new QLineEdit;
	QLineEdit* edit_artist = new QLineEdit;
	QLineEdit* edit_genre = new QLineEdit;
	QHBoxLayout* ly_adauga = new QHBoxLayout;
	QVBoxLayout* ly_edits = new QVBoxLayout;
	QVBoxLayout* ly_labels = new QVBoxLayout;

public:
	GUI(Service& srv_n) :srv{srv_n} {
		tbl_model = new TableModelView(srv);
		setInitialState();
		Connecturi();
	}
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int rock = srv.sameGenre("rock");
		int pop = srv.sameGenre("pop");
		int folk = srv.sameGenre("folk");
		int disco = srv.sameGenre("disco");
		for (int i = 0; i < rock; i++) {
			p.drawEllipse(QPoint(0, 0), (i+1)*10, (i + 1) *10);
		}
		for (int i = 0; i < pop; i++) {
			p.drawEllipse(QPoint(0, this->height()), (i + 1) * 10, (i + 1) * 10);
		}
		for (int i = 0; i < folk; i++) {
			p.drawEllipse(QPoint(this->width(), 0), (i + 1) * 10, (i + 1) * 10);
		}
		for (int i = 0; i < disco; i++) {
			p.drawEllipse(QPoint(this->width(), this->height()), (i + 1) * 10, (i + 1) * 10);
		}
	}
	void setInitialState() {
		this->setMinimumWidth(tbl->width());
		tbl->setModel(tbl_model);
		tbl_model->schimbare();
		ly_labels->addWidget(label_title);
		ly_labels->addWidget(label_artist);
		ly_labels->addWidget(label_genre);

		ly_edits->addWidget(edit_title);
		ly_edits->addWidget(edit_artist);
		ly_edits->addWidget(edit_genre);

		edit_title->setText("");
		edit_artist->setText("");
		edit_genre->setText("");
		
		ly_adauga->addLayout(ly_labels);
		ly_adauga->addLayout(ly_edits);

		vb->addWidget(tbl);
		vb->addLayout(ly_adauga);
		vb->addWidget(btn_add);
		vb->addWidget(btn_delete);

		this->setLayout(vb);
		this->show();
		repaint();
	}

	void Connecturi() {
		QObject::connect(btn_add, &QPushButton::clicked, [&]() {
			string titlu(edit_title->text().toStdString());
			string artist(edit_artist->text().toStdString());
			string gen(edit_genre->text().toStdString());
			if (!titlu.empty() && !artist.empty() && !gen.empty())
			{
				srv.addService(titlu, artist, gen);
				tbl_model->schimbare();
				repaint();
			}
		});

		QObject::connect(btn_delete, &QPushButton::clicked, [&]() {
			if (id_sterge != -1) {
				srv.deleteService(id_sterge);
				id_sterge = -1;
				tbl_model->schimbare();
				repaint();
			}
			});
		
		QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			if (tbl->selectionModel()->selectedRows().size() != 0)
			{
				auto idx = tbl->selectionModel()->selectedRows().at(0);
				auto titlu = tbl_model->data(idx.siblingAtColumn(1));
				auto artist = tbl_model->data(idx.siblingAtColumn(2));
				auto gen = tbl_model->data(idx.siblingAtColumn(3));
				edit_title->setText(titlu.toString());
				edit_artist->setText(artist.toString());
				edit_genre->setText(gen.toString());
				id_sterge = tbl_model->data(idx.siblingAtColumn(0)).toInt();
			}
		});

	}
};


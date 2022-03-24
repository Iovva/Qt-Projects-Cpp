#pragma once
#include <QtWidgets\qtableview.h>
#include "Service.h"

class TableModelView : public QAbstractTableModel
{
private:
	Service& srv;
public:
	TableModelView(Service& srv_n) : srv{ srv_n } {

	}
	int rowCount(const QModelIndex& index = QModelIndex()) const override {
		return srv.getService().size();
	}
	int columnCount(const QModelIndex& index = QModelIndex()) const override {
		return 6;
	}
	QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto copie{srv.getSortat()};
			int idx;
			if (index.row() < copie.size())
			{
				idx = index.row();
				if (index.column() == 0) {
					return QString(QString::number(copie.at(idx).getId()));
				}
				if (index.column() == 1) {
					return QString(QString::fromStdString(copie.at(idx).getTitle()));
				}
				if (index.column() == 2) {
					return QString(QString::fromStdString(copie.at(idx).getArtist()));
				}
				if (index.column() == 3) {
					return QString(QString::fromStdString(copie.at(idx).getGenre()));
				}
				if (index.column() == 4) {
					return QString(QString::number(srv.sameArtist(copie.at(idx).getArtist())));
				}
				if (index.column() == 5) {
					return QString(QString::number(srv.sameGenre(copie.at(idx).getGenre())));
				}
			}
			else {
				return QVariant();
			}
			
		}

		return QVariant();
	}
	void schimbare() {
		emit layoutChanged();
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (section==0	)
					return QString{ "Id" };
				else if (section == 1)
					return QString{ "Titlu" };
				else if (section == 2)
					return QString{ "Artist" };
				else if (section == 3)
					return QString{ "Gen" };
				else if (section == 4)
					return QString{ "Piese Autor" };
				else if (section == 5)
					return QString{ "Total de acest gen" };
			}
			else if (orientation == Qt::Vertical)
				return QString{ "%1" }.arg(section + 1);
		}

		return QVariant{};
	}

};


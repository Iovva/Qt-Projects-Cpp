#pragma once
#include <qtableview.h>
#include "Service.h"
#include "Observer.h"
#include <string.h>

using std::to_string;

class MyTableModel: public QAbstractTableModel, public Observer{
private:
	Service& serv;
	
	int sortare = -1;

	int sortareAsc = 0;

public:

	void update() override {
		emit layoutChanged();
	}

	MyTableModel(Service& serv) : serv{ serv } {

	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return serv.service_get_all().size();
	}
	 
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Oferta of = serv.service_get_all()[index.row()];
			if (sortare >= 0)
				of = serv.service_sortare(to_string(sortare), to_string(sortareAsc))[index.row()]; 
				

			if (index.column() == 0)
				return QString::fromStdString(of.get_denumire());
			else if (index.column() == 1)
				return QString::fromStdString(of.get_destinatie());
			else if (index.column() == 2)
				return QString::fromStdString(of.get_tip());
			else
				return QString::number(of.get_pret());
		}
		return {};
	}

	void set_sort(int i){
		if (sortare == i)
			sortareAsc = 1 - sortareAsc;
		else
		{
			sortareAsc = 0;
			sortare = i;
		}
		emit layoutChanged();
	}

};


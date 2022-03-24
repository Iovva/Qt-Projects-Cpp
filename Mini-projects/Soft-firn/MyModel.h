#pragma once
#include <QAbstractTableModel>
#include <algorithm>
#include "Service.h"

using std::vector;

class MyModel : public QAbstractTableModel, public Observer
{
private:
	Service& srv;
	string sub;
public:
	MyModel(Service& s, string sub) : srv{ s }, sub{ sub }{
		srv.addObserver(this);
	}

	void update() override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return !Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	}
};


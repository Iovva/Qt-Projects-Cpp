#pragma once

#include "Produs.h"

#include <QtWidgets/qabstractitemview.h>

#include <vector>
#include "Service.h"

using std::vector;

class TableModel : public QAbstractTableModel
{
private:
	Service& srv;
	int filter;

public:
	TableModel() = delete;

	TableModel(Service& srv) : srv{ srv }, filter{ 0 } {

	}

	TableModel(const TableModel& ot) = delete;

	TableModel& operator=(const TableModel& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return srv.getAllSrv().size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (!section)
					return QString{ "Id" };
				else if (section == 1)
					return QString{ "Nume" };
				else if (section == 2)
					return QString{ "Tip" };
				else if (section == 3)
					return QString{ "Pret" };
				else if (section == 4)
					return QString{ "Nr vocale" };
			}
			else if (orientation == Qt::Vertical)
				return QString{ "%1" }.arg(section + 1);
		}

		return QVariant{};
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole)
		{
			const auto& produse{ srv.getSortat() };

			const auto& produs{ produse.at(index.row()) };

			if (index.column() == 0)
				return QString::number(produs.getId());
			else if (index.column() == 1)
				return QString::fromStdString(produs.getNume());
			else if (index.column() == 2)
				return QString::fromStdString(produs.getTip());
			else if (index.column() == 3)
				return QString::number(produs.getPret());
			else
				return QString::number(produs.getNrVocale());
		}
		else if (role == Qt::BackgroundRole)
		{
			const auto& produse{ srv.getSortat() };

			const auto& produs{ produse.at(index.row()) };

			if (produs.getPret() < filter)
				return QBrush{ Qt::red, Qt::SolidPattern };

			return QBrush{ Qt::white, Qt::SolidPattern };
		}

		return QVariant{};
	}

	void setLayoutChanged(int flt) {
		this->filter = flt;

		emit layoutChanged();
	}

	~TableModel() = default;
};
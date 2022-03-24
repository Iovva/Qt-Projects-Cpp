#pragma once

#include <QtWidgets/qabstractitemview.h>
#include "Service.h"

class TableModel : public QAbstractTableModel {
private:
	Service& srv;

public:
	TableModel() = delete;

	TableModel(Service& srv) : srv{ srv } {

	}

	TableModel(const TableModel& ot) = delete;

	TableModel(const TableModel&& ot) = delete;

	TableModel& operator&(const TableModel& ot) = delete;

	TableModel& operator&(const TableModel&& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return srv.lenServ();
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
					return QString{ "Titlu" };
				else if (section == 2)
					return QString{ "Artist" };
				else if (section == 3)
					return QString{ "Rank" };
				else
					return QString{ "Same rank" };
			}
			else
				// return QString("%1").arg(section + 1);
				return QString::number(section + 1);
		}
		else if (role == Qt::TextAlignmentRole)
		{
			if (orientation == Qt::Horizontal)
				return Qt::AlignHCenter;
			else
				return Qt::AlignVCenter;
		}
		else if (role == Qt::FontRole)
		{
			QFont font;

			font.setItalic(false);
			font.setBold(true);

			return font;
		}

		return QVariant{};
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::BackgroundRole)
			return QBrush{ Qt::white, Qt::SolidPattern };
		else if (role == Qt::FontRole)
		{
			QFont font;

			font.setItalic(true);
			font.setBold(false);

			return font;
		}
		else if (role == Qt::DisplayRole)
		{
			const auto& sorted_melodii{ srv.sortByRank(false) };

			const auto& melodie{ sorted_melodii.at(index.row()) };

			if (!index.column())
				return QString::number(melodie.getId());
			else if (index.column() == 1)
				return QString::fromStdString(melodie.getTitlu());
			else if (index.column() == 2)
				return QString::fromStdString(melodie.getArtist());
			else if (index.column() == 3)
				return QString::number(melodie.getRank());
			else
				return QString::number(srv.countRank(melodie.getRank()));
		}
		else if (role == Qt::TextAlignmentRole)
			return Qt::AlignHCenter;
		else if (role == Qt::UserRole)
		{
			const auto& sorted_melodii{ srv.sortByRank(false) };

			const auto& melodie{ sorted_melodii.at(index.row()) };

			return melodie.getRank();
		}

		return QVariant{};
	}

	void modified() {
		emit layoutChanged();
	}

	~TableModel() = default;
};


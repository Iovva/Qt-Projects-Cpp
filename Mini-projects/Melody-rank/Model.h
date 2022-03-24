#pragma once

#include "Service.h"

#include <QtWidgets/qabstractitemview.h>

class Model : public QAbstractTableModel
{
private:
	Service& srv;

public:
	Model() = delete;

	Model(Service& srv) : srv{ srv } {

	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return srv.lenServ();
	}

	int columnCount(const QModelIndex& index = QModelIndex()) const override {
		return 4;
	}

	QVariant headerData(int section, const Qt::Orientation orientation, int role) const override {
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (!section)
					return QString{ "Id" };
				else if (section == 1)
					return QString{ "Titlu" };
				else if (section == 2)
					return QString{ "Autor" };
				else if (section == 3)
					return QString{ "Rank" };
			}
			else
				//return QString{ "%1" }.arg(section);
				return QString::number(section);
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

			font.setBold(true);
			font.setItalic(false);

			return font;
		}

		return QVariant{};
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::TextAlignmentRole)
			return Qt::AlignHCenter;
		else if (role == Qt::FontRole)
		{
			QFont font;

			font.setBold(false);
			font.setItalic(true);

			return font;
		}
		else if (role == Qt::BackgroundRole)
			return QBrush{ Qt::white, Qt::SolidPattern };
		else if (role == Qt::DisplayRole)
		{
			const auto& piese{ srv.getAllServ() };

			const auto& piesa{ piese.at(index.row()) };

			if (!index.column())
				return QString::number(piesa.getId());
			else if (index.column() == 1)
				return QString::fromStdString(piesa.getTitlu());
			else if (index.column() == 2)
				return QString::fromStdString(piesa.getArtist());
			else if (index.column() == 3)
				return QString::number(piesa.getRank());
		}
		else if (role == Qt::UserRole) {
			const auto& piese{ srv.getAllServ() };

			const auto& piesa{ piese.at(index.row()) };

			return piesa.getId();
		}

		return QVariant{};
	}

	void modified() {
		emit layoutChanged();
	}

	~Model() = default;
};


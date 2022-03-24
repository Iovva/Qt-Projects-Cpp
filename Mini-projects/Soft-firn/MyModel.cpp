#include "MyModel.h"

void MyModel::update()
{
	emit layoutChanged();
}

int MyModel::rowCount(const QModelIndex& parent) const
{
	if(sub == "")
		return (int)srv.GetAll().size();
	return (int)srv.Filtrare("programatori",sub).size();
}

int MyModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		vector<Task> alls;
		if (sub == "")
			alls = srv.GetAll();
		else
			alls = srv.Filtrare("programatori",sub);
		std::sort(alls.begin(), alls.end(), [](Task& t1, Task& t2) { return t1.get_stare() < t2.get_stare(); });
		Task t = alls[index.row()];
		if (index.column() == 0)
			return QString::number(t.get_id());
		else if (index.column() == 1)
			return QString::fromStdString(t.get_descriere());
		else if (index.column() == 2)
			return QString::number(t.get_programatori().size());
		else
			return QString::fromStdString(t.get_stare());
	}
	return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal && section == 0)
			return QString("ID").arg(section);
		else if (orientation == Qt::Horizontal && section == 1)
			return QString("Descriere").arg(section);
		else if (orientation == Qt::Horizontal && section == 2)
			return QString("Programatori").arg(section);
		else if (orientation == Qt::Horizontal && section == 3)
			return QString("Stare").arg(section);
	}
	return QVariant();
}

#pragma once

#include <QtWidgets/qwidget.h>
#include <qpainter.h>
#include "Service.h"

class Histogram : public QWidget
{
private:
	Service& srv;

public:
	Histogram() = delete;

	Histogram(Service& srv) : srv{ srv } {
		repaint();

		this->setMinimumHeight(150);
		this->setMinimumWidth(200);

		this->show();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter painter{ this };

		painter.setPen(Qt::green);

		for (auto i{ 0 }; i <= 10; ++i)
		{
			QRect rect;

			rect.setX(5);
			rect.setY(5 + 10 * i);

			rect.setWidth(25 * srv.countRank(i));
			rect.setHeight(10);

			painter.drawRect(rect);
		}
	}

	~Histogram() = default;
};

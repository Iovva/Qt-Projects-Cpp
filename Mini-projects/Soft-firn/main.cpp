#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{ "taskuri.txt" };
    Service srv{ repo };
    GUI* g = new GUI{ srv };
    g->show();
    return a.exec();
}

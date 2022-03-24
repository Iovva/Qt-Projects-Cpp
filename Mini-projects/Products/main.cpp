#include <QtWidgets/QApplication>

#include "Repo.h"
#include "FileRepo.h"
#include "ValidatorProdus.h"
#include "GUI.h"

#include <string>

using std::string;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    string filename{ "produse.txt" };
    FileRepo repo{ filename };

    ValidatorProdus valid;

    Service srv{ repo, valid };

    GUI* gui = new GUI{ srv };
    gui->show();

    return a.exec();
}

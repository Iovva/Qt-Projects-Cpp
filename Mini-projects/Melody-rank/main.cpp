#include <QtWidgets/QApplication>

#include "ValidatorMelodie.h"
#include "FileRepo.h"
#include "Service.h"
#include "GUI.h"

#include <string>

using std::string;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    ValidatorMelodie valid;

    const string filename{ "melodii.txt" };
    FileRepo repo{ filename };

    Service srv{ repo, valid };

    GUI* gui = new GUI{ srv };
    gui->show();

    return a.exec();
}

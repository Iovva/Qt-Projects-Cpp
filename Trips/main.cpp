#include "GUI.h"
#include <iostream>
#include "Utils.h"
#include "Repository.h"
#include "Service.h"
#include "teste.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Teste teste;
  //  teste.teste_all();
    RepositoryOfertaFile RepositoryOferta{ "oferte.txt" };
    Service service(RepositoryOferta);
    GUI* gui = new GUI{ service };
    gui->setWindowTitle("Hotel? Drivago!");
    gui->setWindowIcon(QIcon("airplane.png"));
    gui->show();
    return a.exec();
}

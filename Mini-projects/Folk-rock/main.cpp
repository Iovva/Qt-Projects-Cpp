#include "simulare_3.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qboxlayout.h>
#include "GUI.h"
#include <assert.h>

void testRepo() {
    Repo rep;
    assert(rep.getAll().size() == 0);
    Melodie m1(1, string{ "a" }, string{ "aa" }, string{ "pop" });
    Melodie m2(2, string{ "b" }, string{ "bb" }, string{ "rock" });
    Melodie m3(3, string{ "c" }, string{ "cc" }, string{ "folk" });
    rep.add(m1);
    rep.add(m2);
    rep.add(m3);
    assert(rep.getAll().size() == 3);
    assert(rep.search(3).getGenre() == "folk");
    rep.del(1);
    rep.del(2);
    assert(rep.getAll().size() == 1);
    assert(rep.getAll().at(0).getGenre() == "folk");
}

void testService() {
    Repo rep;
    Service srv(rep, string{ "test.txt" });
    assert(srv.getService().size() == 0);
    srv.addService(string{ "a" }, string{ "aa" }, string{ "pop" });
    srv.addService(string{ "b" }, string{ "bb" }, string{ "pop" });
    srv.addService(string{ "c" }, string{ "cc" }, string{ "folk" });
    srv.addService(string{ "d" }, string{ "aa" }, string{ "rock" });
    assert(srv.getService().size() == 4);
    assert(srv.sameArtist(string{ "aa" }) == 2);
    assert(srv.sameGenre(string{ "pop" }) == 2);
    assert(srv.getSortat().at(1).getArtist() == "aa");
    srv.deleteService(1);
    assert(srv.getService().size() == 3);
    try {
        srv.searchService(1);
        assert(false);
    }
    catch(exception & ex) {
        string str{ ex.what() };
        assert(str == "Element inexistent!\n");
    }
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    testRepo();
    testService();
    Repo rep;
    string denumire{ "data.txt" };
    Service srv(rep, denumire);
    GUI* gui = new GUI(srv);
    gui->show();
    return a.exec();
}

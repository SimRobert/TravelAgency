#include "lab1011.h"
#include <QtWidgets/QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    lab1011 w;
//    w.show();
//    return a.exec();
//}
#include "presentation.h"
#include "Agentie.h"
#include "OfertaRepo.h"
#include "validator.h"
#include "OfertaTeste.h"
#include "RepoTeste.h"
#include "ServiceTeste.h"
#include "TesteValidator.h"
#include "CosRepo.h"
#include "CosService.h"
#include "gui.h"

#include <QtWidgets/QApplication>
#include <QListWidget>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>

void adaugaCateva(Agentie& ctr) {
    ctr.addOferta("Sejur", "Ibiza", "all-inclusive", 699);
    ctr.addOferta("Croaziera", "Insulele Hawaii", "ultra all-inclusive", 1050);
    ctr.addOferta("Expeditie", "Padurea Neagra", "mic dejun", 230);
    ctr.addOferta("Drumetie", "Delta Dunarii", "mic dejun", 100);
}



void testAll() {
    testOferta();
    testAllRepo();
    testAllService();
    testValidator();
}



int main(int argc, char* argv[]) {
    testAll();

    QApplication app(argc, argv);


    OfertaRepo rep;
    CosRepo cRep;
    OfertaValidator val;
    Agentie ctr{ &rep ,val };
    CosService cServ{ rep, cRep, val };
    adaugaCateva(ctr);
    GUI gui(ctr, cServ);
    gui.run();
    //ConsoleUI ui{ ctr, cServ };
    //ui.start();
    return app.exec();

}

//#pragma once
#include <QtWidgets/QApplication>
#include <QListWidget>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>


#include "Agentie.h"
#include "CosService.h"
#include <string>

using std::to_string;


class GUI {
private:
    Agentie& ctr;
    CosService& cServ;

    QWidget* window, * cosWindow, * lftBox, * rgtBox, * forms, * filters, * btns, * btns2, * btnsSort, * formsCos, * btnsCos, * rgtCBox, * dynBtns;
    QVBoxLayout* lftBoxLayout, * rgtBoxLayout, * btnsCosLayout, * rgtCBoxLayout, * dynBtnsLayout;
    QHBoxLayout* windowLayout, * cosWindowLayout, * btnsSortLayout;
    QGridLayout* gridBtnsLayout, * filtersLayout;
    QFormLayout* formsLayout, * formsCosLayout;
    QListWidget* list, * cosList;
    QLabel* lbDenumire, * lbDestinatie, * lbTip, * lbPret, * lbFDestinatie, * lbFPret, * lbCDenumire;
    QLineEdit* txtDenumire, * txtDestinatie, * txtTip, * txtPret, * txtFDestinatie, * txtFPret, * txtCDenumire;
    QPushButton* btnAdd, * btnMod, * btnPop, * btnUndo, * btnCos, * btnFilter, * btnSortDen, * btnSortDes, * btnSortTP, * btnCAdd, * btnCGen, * btnCEmp, * btnCExp;
    vector<QPushButton*> dynBtnsList;

    QTableWidget* tableOferte;


public:
    GUI(Agentie& ctr, CosService& cServ) : ctr{ ctr }, cServ{ cServ } {
        initGUI();
        initConnections();
        loadData(list, ctr.getAll());
        loadData(cosList, cServ.getAll());
    }

    GUI(const GUI& ot) = delete;

    void initGUI();

    void initConnections();

    void run();

    void loadData(QListWidget* list, const vector<Oferta>& oList);
};
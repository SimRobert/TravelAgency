#include "gui.h"

void GUI::initGUI() {
    window = new QWidget();
    window->setWindowTitle("Agentia de turism OOP");
    windowLayout = new QHBoxLayout;

    lftBox = new QWidget();
    lftBoxLayout = new QVBoxLayout();

    list = new QListWidget;

    btnsSort = new QWidget();
    btnsSortLayout = new QHBoxLayout();
    btnSortDen = new QPushButton("&Sorteaza dupa denumire");
    btnsSortLayout->addWidget(btnSortDen);
    btnSortDes = new QPushButton("&Sorteaza dupa destinatie");
    btnsSortLayout->addWidget(btnSortDes);
    btnSortTP = new QPushButton("&Sorteaza dupa tip si pret");
    btnsSortLayout->addWidget(btnSortTP);
    btnsSort->setLayout(btnsSortLayout);


    int lines = 10;
    int columns = 4;
    this->tableOferte = new QTableWidget{ lines, columns };

    QStringList  tblHeaderList;
    tblHeaderList << "Denumire" << "Destinatie" << "Tip" << "Pret";
    this->tableOferte->setHorizontalHeaderLabels(tblHeaderList);

    this->tableOferte->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    lftBoxLayout->addWidget(tableOferte);
    lftBoxLayout->addWidget(list);
    lftBoxLayout->addWidget(btnsSort);
    lftBox->setLayout(lftBoxLayout);

    rgtBox = new QWidget();
    rgtBoxLayout = new QVBoxLayout();

    forms = new QWidget();
    formsLayout = new QFormLayout();
    lbDenumire = new QLabel("Denumire");
    txtDenumire = new QLineEdit;
    formsLayout->addRow(lbDenumire, txtDenumire);
    lbDestinatie = new QLabel("Destinatie");
    txtDestinatie = new QLineEdit;
    formsLayout->addRow(lbDestinatie, txtDestinatie);
    lbTip = new QLabel("Tip");
    txtTip = new QLineEdit;
    formsLayout->addRow(lbTip, txtTip);
    lbPret = new QLabel("Pret");
    txtPret = new QLineEdit;
    formsLayout->addRow(lbPret, txtPret);
    forms->setLayout(formsLayout);

    btns = new QWidget();
    gridBtnsLayout = new QGridLayout();
    btnAdd = new QPushButton("&Adauga");
    gridBtnsLayout->addWidget(btnAdd, 0, 0);
    btnMod = new QPushButton("&Modifica");
    gridBtnsLayout->addWidget(btnMod, 0, 1);
    btnPop = new QPushButton("&Sterge");
    gridBtnsLayout->addWidget(btnPop, 0, 2);
    btnUndo = new QPushButton("&Undo");
    gridBtnsLayout->addWidget(btnUndo, 1, 0);
    btnCos = new QPushButton("&Cos");
    gridBtnsLayout->addWidget(btnCos, 1, 1);
    btns->setLayout(gridBtnsLayout);

    filters = new QWidget();
    filtersLayout = new QGridLayout();

    btnFilter = new QPushButton("&Filtreaza dupa");
    filtersLayout->addWidget(btnFilter, 0, 0);
    lbFPret = new QLabel("Pret");
    txtFPret = new QLineEdit;
    filtersLayout->addWidget(lbFPret, 1, 0);
    filtersLayout->addWidget(txtFPret, 1, 1);
    lbFDestinatie = new QLabel("Destinatie");
    txtFDestinatie = new QLineEdit;
    filtersLayout->addWidget(lbFDestinatie, 2, 0);
    filtersLayout->addWidget(txtFDestinatie, 2, 1);

    filters->setLayout(filtersLayout);

    rgtBoxLayout->addWidget(forms);
    rgtBoxLayout->addWidget(btns);
    rgtBoxLayout->addWidget(filters);
    rgtBoxLayout->addStretch();
    rgtBox->setLayout(rgtBoxLayout);


    dynBtns = new QWidget();
    dynBtnsLayout = new QVBoxLayout();
    dynBtns->setLayout(dynBtnsLayout);

    windowLayout->addWidget(rgtBox);

    windowLayout->addWidget(lftBox);
    
    windowLayout->addWidget(dynBtns);

    window->setLayout(windowLayout);



    cosWindow = new QWidget();
    cosWindow->setWindowTitle("Optiuni pentru viitor");
    cosWindowLayout = new QHBoxLayout();

    cosList = new QListWidget();

    rgtCBox = new QWidget();
    rgtCBoxLayout = new QVBoxLayout();

    formsCos = new QWidget();
    formsCosLayout = new QFormLayout();
    lbCDenumire = new QLabel("Denumire");
    txtCDenumire = new QLineEdit;
    formsCosLayout->addRow(lbCDenumire, txtCDenumire);
    formsCos->setLayout(formsCosLayout);

    btnsCos = new QWidget();
    btnsCosLayout = new QVBoxLayout();
    btnCAdd = new QPushButton("&Adauga");
    btnsCosLayout->addWidget(btnCAdd);
    btnCGen = new QPushButton("&Genereaza");
    btnsCosLayout->addWidget(btnCGen);
    btnCEmp = new QPushButton("&Goleste");
    btnsCosLayout->addWidget(btnCEmp);
    btnCExp = new QPushButton("&Export");
    btnsCosLayout->addWidget(btnCExp);
    btnsCos->setLayout(btnsCosLayout);

    rgtCBoxLayout->addWidget(formsCos);
    rgtCBoxLayout->addWidget(btnsCos);
    rgtCBoxLayout->addStretch();
    rgtCBox->setLayout(rgtCBoxLayout);

    cosWindowLayout->addWidget(cosList);
    cosWindowLayout->addWidget(rgtCBox);
    cosWindow->setLayout(cosWindowLayout);
}

void GUI::initConnections() {
    QObject::connect(list, &QListWidget::itemClicked, [&]() {
        const string denumire = list->currentItem()->text().toStdString();
        const Oferta selectedOffer = ctr.find_oferta(denumire);
        txtDenumire->setText(QString::fromStdString(selectedOffer.getDenumire()));
        txtDestinatie->setText(QString::fromStdString(selectedOffer.getDestinatie()));
        txtTip->setText(QString::fromStdString(selectedOffer.getTip()));
        txtPret->setText(QString::fromStdString(to_string(selectedOffer.getPret())));
        });

    QObject::connect(cosList, &QListWidget::itemClicked, [&]() {
        txtCDenumire->setText(cosList->currentItem()->text());
        });

    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        try {
            const string denumire = txtDenumire->text().toStdString();
            const string destinatie = txtDestinatie->text().toStdString();
            const string tip = txtTip->text().toStdString();
            const int pret = atoi(txtPret->text().toStdString().c_str());
            ctr.addOferta(denumire, destinatie, tip, pret);
            loadData(list, ctr.getAll());

            const vector<Oferta>& oList = ctr.getAll();
            for (const auto& oferta : oList) {
                bool isPresent = false;
                for (const auto& button : dynBtnsList)
                    if (oferta.getTip() == button->text().toStdString()) {
                        isPresent = true;
                        break;
                    }
                if (isPresent == false) {
                    dynBtnsList.push_back(new QPushButton(QString::fromStdString((oferta.getTip()))));
                    dynBtnsLayout->addWidget(dynBtnsList.back());
                }
            }
            for (const auto& button : dynBtnsList) {
                button->disconnect();
                QObject::connect(button, &QPushButton::clicked, [&]() {
                    QMessageBox::information(nullptr, button->text(), QString::fromStdString(to_string(ctr.countTip(button->text().toStdString()))));
                    });
            }
        }
        catch (ValidateException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        catch (OfertaRepoException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        });

    QObject::connect(btnMod, &QPushButton::clicked, [&]() {
        try {
            const int index = list->currentRow();
            const string destinatie = txtDestinatie->text().toStdString();
            const string tip = txtTip->text().toStdString();
            const int pret = atoi(txtPret->text().toStdString().c_str());
            const vector<Oferta>& oList = ctr.getAll();
            ctr.modOferta(oList[index].getDenumire(), destinatie, tip, pret);
            loadData(list, ctr.getAll());

            for (const auto& oferta : oList) {
                bool isPresent = false;
                for (const auto& button : dynBtnsList)
                    if (oferta.getTip() == button->text().toStdString()) {
                        isPresent = true;
                        break;
                    }
                if (isPresent == false) {
                    dynBtnsList.push_back(new QPushButton(QString::fromStdString((oferta.getTip()))));
                    dynBtnsLayout->addWidget(dynBtnsList.back());
                }
            }
            for (const auto& button : dynBtnsList) {
                button->disconnect();
                QObject::connect(button, &QPushButton::clicked, [&]() {
                    QMessageBox::information(nullptr, button->text(), QString::fromStdString(
                        to_string(ctr.countTip(button->text().toStdString()))));
                    });
            }
        }
        catch (ValidateException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        catch (OfertaRepoException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        });

    QObject::connect(btnPop, &QPushButton::clicked, [&]() {
        try {
            const string denumire = txtDenumire->text().toStdString();
            ctr.popOferta(denumire);
            txtDenumire->clear();
            txtDestinatie->clear();
            txtTip->clear();
            txtPret->clear();
            loadData(list, ctr.getAll());

            const vector<Oferta>& oList = ctr.getAll();
            int i = 0;
            for (const auto& button : dynBtnsList) {
                bool isPresent = false;
                for (const auto& oferta : oList)
                    if (oferta.getTip() == button->text().toStdString()) {
                        isPresent = true;
                        break;
                    }
                if (isPresent == false) {
                    dynBtnsList.erase(dynBtnsList.begin() + i);
                }
                i++;
            }
            for (const auto& button : dynBtnsList) {
                button->disconnect();
                QObject::connect(button, &QPushButton::clicked, [&]() {
                    QMessageBox::information(nullptr, button->text(), QString::fromStdString(to_string(ctr.countTip(button->text().toStdString()))));
                    });
            }
        }
        catch (ValidateException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        catch (OfertaRepoException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        });

    QObject::connect(btnSortDen, &QPushButton::clicked, [&]() {
        loadData(list, ctr.sortByDenumire());
        });

    QObject::connect(btnSortDes, &QPushButton::clicked, [&]() {
        loadData(list, ctr.sortByDestinatie());
        });

    QObject::connect(btnSortTP, &QPushButton::clicked, [&]() {
        loadData(list, ctr.sortByTipPret());
        });

    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            ctr.undo();
            loadData(list, ctr.getAll());
        }
        catch (ValidateException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        catch (OfertaRepoException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        });

    QObject::connect(btnCos, &QPushButton::clicked, [&]() {
        cosWindow->show();
        });


    QObject::connect(btnFilter, &QPushButton::clicked, [&]() {
        if (txtFPret->text() != "")
            loadData(list, ctr.filtrarePret(txtFPret->text().toInt()));
        if (txtFDestinatie->text() != "")
            loadData(list, ctr.filtrareDestinatie(txtFDestinatie->text().toStdString()));
        });


    QObject::connect(btnCAdd, &QPushButton::clicked, [&]() {
        try {
            const string denumire = txtCDenumire->text().toStdString();;
            cServ.addOferta(denumire);
            loadData(cosList, cServ.getAll());
        }
        catch (ValidateException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        catch (OfertaRepoException e) { QMessageBox::warning(nullptr, "Warning", e.what().c_str()); }
        });

    QObject::connect(btnCGen, &QPushButton::clicked, [&]() {
        cServ.generateCos(rand() % ctr.getAll().size() + 1);
        txtCDenumire->clear();
        loadData(cosList, cServ.getAll());
        });

    QObject::connect(btnCEmp, &QPushButton::clicked, [&]() {
        cServ.emptyCos();
        txtCDenumire->clear();
        loadData(cosList, cServ.getAll());
        });

    QObject::connect(btnCExp, &QPushButton::clicked, [&]() {
        cServ.exportCos("cosData");
        });
}

void GUI::run() {
    window->show();
}

void GUI::loadData(QListWidget* list, const vector<Oferta>& oList) {
    int rowCount = 0;
    list->clear();
    for (const auto& oferta : oList)
        list->addItem(oferta.getDenumire().c_str());

    this->tableOferte->clearContents();
    this->tableOferte->setRowCount(oList.size());

    int lineNumber = 0;
    for (auto& oferta : oList) {
        this->tableOferte->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(oferta.getDenumire())));
        this->tableOferte->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(oferta.getDestinatie())));
        this->tableOferte->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(oferta.getTip())));
        this->tableOferte->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(oferta.getPret())));
        lineNumber++;
    }
}
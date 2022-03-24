#include "GUI.h"

GUICauta::GUICauta(GUI& gu, Service& serv) : gui{ gu }, service{ serv } {
	QHBoxLayout* layout = new QHBoxLayout;
	setLayout(layout);
	QVBoxLayout* verticalLayout = new QVBoxLayout;
	QLineEdit* editDenumireIn = new QLineEdit;
	QPushButton* butonCautare = new QPushButton{ "Cauta" };
	QFormLayout* LayoutForm = new QFormLayout;
	LayoutForm->addRow("Introduceti denumirea:", editDenumireIn);
	verticalLayout->addLayout(LayoutForm);
	verticalLayout->addWidget(butonCautare);
	layout->addLayout(verticalLayout);
	QFormLayout* LayoutForm1 = new QFormLayout;
	LayoutForm1->addRow("Denumire:", editDenumire);
	LayoutForm1->addRow("Destinatie:", editDestinatie);
	LayoutForm1->addRow("Tip:", editTip);
	LayoutForm1->addRow("Pret:", editPret);
	layout->addLayout(LayoutForm1);
	
	

	QObject::connect(butonCautare, &QPushButton::clicked, this, [=]() {
		try {
			
			const string denumire = (editDenumireIn->text()).QString::toStdString();
			const auto& of = service.service_cauta(denumire);
			editDenumire->setText(QString::fromStdString((of.get_denumire())));
			editDestinatie->setText(QString::fromStdString((of.get_destinatie())));
			editTip->setText(QString::fromStdString((of.get_tip())));
			editPret->setText(QString::number((of.get_pret())));
			
			
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
}

GUIStergere::GUIStergere(GUI& gu, Service& serv) : gui{ gu }, service{ serv } {
	QVBoxLayout* layout = new QVBoxLayout;
	setLayout(layout);
	QFormLayout* LayoutForm = new QFormLayout;
	QLineEdit* editDenumire = new QLineEdit;
	QPushButton* butonStergere = new QPushButton{ "Sterge" };
	LayoutForm->addRow("Introduceti denumirea:", editDenumire);
	layout->addLayout(LayoutForm);
	layout->addWidget(butonStergere);
	QObject::connect(butonStergere, &QPushButton::clicked, this, [=]() {
		try {
			const string denumire = (editDenumire->text()).QString::toStdString();
			service.service_sterge(denumire);
			this->close();
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
}

void GUIFiltrare::initGUI(){
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	mainLayout->addWidget(table);

	QVBoxLayout* verticalLayout = new QVBoxLayout;

	comboBox->addItem("Destinatie");
	comboBox->addItem("Pret");
	comboBox->setCurrentText("Pret");

	QFormLayout* LayoutForm = new QFormLayout;
	LayoutForm->addRow(editInput);
	
	QVBoxLayout* vboxDestinatie = new QVBoxLayout;
	radioDestinatie0->setText("Cu destinatia data");
	radioDestinatie0->setVisible(false);
	vboxDestinatie->addWidget(radioDestinatie0);
	radioDestinatie1->setText("Fara destinatia data");
	radioDestinatie1->setVisible(false);
	vboxDestinatie->addWidget(radioDestinatie1);
	radioPret0->setText("Mai mic decat un pret dat");
	radioPret0->setChecked(true);
	vboxDestinatie->addWidget(radioPret0);
	radioPret1->setText("Egal un pret dat");
	vboxDestinatie->addWidget(radioPret1);
	radioPret2->setText("Mai mare ca un pret dat");
	vboxDestinatie->addWidget(radioPret2);
	verticalLayout->addWidget(comboBox);
	verticalLayout->addLayout(vboxDestinatie);
	verticalLayout->addLayout(LayoutForm);
	verticalLayout->addWidget(butonFiltrare);
	mainLayout->addLayout(verticalLayout);
}

void GUIFiltrare::connectSignals() {
	
	QObject::connect(comboBox, &QComboBox::currentIndexChanged, this, [=]() {
		if (comboBox->currentText().QString::toStdString() == "Destinatie"){
			radioDestinatie0->setVisible(true);
			radioDestinatie1->setVisible(true);
			radioPret0->setVisible(false);
			radioPret1->setVisible(false);
			radioPret2->setVisible(false);
			radioDestinatie0->setChecked(true);
		}
		else
		{
			radioDestinatie0->setVisible(false);
			radioDestinatie1->setVisible(false);
			radioPret0->setVisible(true);
			radioPret1->setVisible(true);
			radioPret2->setVisible(true);
			radioPret0->setChecked(true);
		}
		});

	QObject::connect(butonFiltrare, &QPushButton::clicked, this, [=]() {
		try {
			if (comboBox->currentText().QString::toStdString() == "Destinatie")
			{
				if (radioDestinatie0->isChecked() == true) {
					const string deFiltrat = (editInput->text()).QString::toStdString();
					const auto& l = service.service_filtrare_destinatie("0", deFiltrat);
					addToList(l);
				}
				else {
					const string deFiltrat = (editInput->text()).QString::toStdString();
					const auto& l = service.service_filtrare_destinatie("1", deFiltrat);
					addToList(l);
				}
			}
			else {
				if (radioPret0->isChecked() == true) {
					const string deFiltrat = (editInput->text()).QString::toStdString();
					const auto& l = service.service_filtrare_pret("0", deFiltrat);
					addToList(l);
				}
				else if (radioPret1->isChecked() == true) {
					const string deFiltrat = (editInput->text()).QString::toStdString();
					const auto& l = service.service_filtrare_pret("1", deFiltrat);
					addToList(l);
				}
				else {
					const string deFiltrat = (editInput->text()).QString::toStdString();
					const auto& l = service.service_filtrare_pret("2", deFiltrat);
					addToList(l);
				}
			}
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
}

void GUIFiltrare::addToList(const vector<Oferta>& lista_oferte) {
	table->clear();
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Denumire"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Destinatie"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Tip"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Pret"));
	table->setRowCount(static_cast<int>(lista_oferte.size()));
	int line = 0;
	for (const Oferta& of : lista_oferte) {
		table->setItem(line, 0, new QTableWidgetItem(QString::fromStdString(of.get_denumire())));
		table->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(of.get_destinatie())));
		table->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(of.get_tip())));
		table->setItem(line, 3, new QTableWidgetItem(QString::number(of.get_pret())));
		line++;
	}
	table->resizeColumnsToContents();
	int width = table->columnWidth(0) + table->columnWidth(1) +
		table->columnWidth(2) + table->columnWidth(4) + 56;
	table->setFixedWidth(width);
}

void GUIFiltrare::setInitialGUIState() {
	addToList(service.service_get_all());
}

void GUIWishlist::update() {
	addToList(service.service_wishlist_get_all());
}

void GUIWishlist::initGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	QVBoxLayout* verticalLayout = new QVBoxLayout;
	QFormLayout* LayoutForm = new QFormLayout;
	LayoutForm->addRow("Denumire:", editInput);
	verticalLayout->addLayout(LayoutForm);
	verticalLayout->addWidget(butonAdauga);
	verticalLayout->addWidget(butonGoleste);
	verticalLayout->addWidget(butonGenereaza);
	verticalLayout->addWidget(butonExport);
	verticalLayout->addWidget(sBox);
	sBox->setMinimum(1);
	mainLayout->addWidget(table);
	mainLayout->addLayout(verticalLayout);
}

void GUIWishlist::connectSignals() {
	QObject::connect(butonAdauga, &QPushButton::clicked, this, [=]() {
		try {
			const string denumire = (editInput->text()).QString::toStdString();
			service.service_wishlist_adauga(denumire);
			addToList(service.service_wishlist_get_all());
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonGoleste, &QPushButton::clicked, this, [=]() {
		try {
			service.service_wishlist_goleste();
			addToList(service.service_wishlist_get_all());
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonGenereaza, &QPushButton::clicked, this, [=]() {
		try {
			const string nr = to_string(sBox->value());
			service.service_wishlist_genereaza(nr);
			addToList(service.service_wishlist_get_all());
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonExport, &QPushButton::clicked, this, [=]() {
		try {
			const string denumire = (editInput->text()).QString::toStdString();
			service.service_wishlist_export_csv(denumire);
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
}

void GUIWishlist::addToList(const vector<Oferta>& lista_oferte) {
	table->clear();
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Denumire"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Destinatie"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Tip"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Pret"));
	table->setRowCount(static_cast<int>(lista_oferte.size()));
	int line = 0;
	for (const Oferta& of : lista_oferte) {
		table->setItem(line, 0, new QTableWidgetItem(QString::fromStdString(of.get_denumire())));
		table->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(of.get_destinatie())));
		table->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(of.get_tip())));
		table->setItem(line, 3, new QTableWidgetItem(QString::number(of.get_pret())));
		line++;
	}
	table->resizeColumnsToContents();
	int width = table->columnWidth(0) + table->columnWidth(1) +
		table->columnWidth(2) + table->columnWidth(4) + 56;
	table->setFixedWidth(width);
}

void GUIWishlist::setInitialGUIState() {
	addToList(service.service_wishlist_get_all());
}

void GUIWishlistCRUD::update() {
	addToList(service.service_wishlist_get_all());
}

void GUIWishlistCRUD::initGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	QVBoxLayout* verticalLayout = new QVBoxLayout;
	QFormLayout* LayoutForm = new QFormLayout;
	LayoutForm->addRow("Denumire:", editInput);
	verticalLayout->addLayout(LayoutForm);
	verticalLayout->addWidget(butonGoleste);
	verticalLayout->addWidget(butonGenereaza);
	verticalLayout->addWidget(sBox);
	sBox->setMinimum(1);
	mainLayout->addWidget(table);
	mainLayout->addLayout(verticalLayout);
}

void GUIWishlistCRUD::connectSignals() {
	QObject::connect(butonGoleste, &QPushButton::clicked, this, [=]() {
		try {
			service.service_wishlist_goleste();
			addToList(service.service_wishlist_get_all());
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonGenereaza, &QPushButton::clicked, this, [=]() {
		try {
			const string nr = to_string(sBox->value());
			service.service_wishlist_genereaza(nr);
			addToList(service.service_wishlist_get_all());
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
}

void GUIWishlistCRUD::addToList(const vector<Oferta>& lista_oferte) {
	table->clear();
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Denumire"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Destinatie"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Tip"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Pret"));
	table->setRowCount(static_cast<int>(lista_oferte.size()));
	int line = 0;
	for (const Oferta& of : lista_oferte) {
		table->setItem(line, 0, new QTableWidgetItem(QString::fromStdString(of.get_denumire())));
		table->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(of.get_destinatie())));
		table->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(of.get_tip())));
		table->setItem(line, 3, new QTableWidgetItem(QString::number(of.get_pret())));
		line++;
	}
	table->resizeColumnsToContents();
	int width = table->columnWidth(0) + table->columnWidth(1) +
		table->columnWidth(2) + table->columnWidth(4) + 56;
	table->setFixedWidth(width);
}

void GUIWishlistCRUD::setInitialGUIState() {
	addToList(service.service_wishlist_get_all());
}

void GUIWishlistReadOnly::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	int x{ 10 }, y{ 10 };
	for (const auto& el : service.service_wishlist_get_all()) {
		//x = rand() % 400; y = rand() % 400;
		p.fillRect(x, y, 40, 40, QColor(255, 83, 139));
		x = x + 50;
		if (x > this->width()) {
			x = 10;
			y = y + 50;
		}
		//
		el.get_denumire();
		//
	}
	//
	QPaintEvent* copie = ev;
	copie = 0;
	//
}

void GUI::initGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	mainLayout->addWidget(table);

	QVBoxLayout* verticalLayout = new QVBoxLayout;
	QFormLayout* LayoutForm = new QFormLayout;
	LayoutForm->addRow("Denumire:", editDenumire);
	LayoutForm->addRow("Destinatie:", editDestinatie);
	LayoutForm->addRow("Tip:", editTip);
	LayoutForm->addRow("Pret:", editPret);

	verticalLayout->addLayout(LayoutForm);
	verticalLayout->addWidget(butonAdauga);
	verticalLayout->addWidget(butonModifica);
	verticalLayout->addWidget(butonSterge);
	verticalLayout->addWidget(butonCauta);
	verticalLayout->addWidget(butonFiltrare);

	verticalLayout->addWidget(butonRaport);
	verticalLayout->addWidget(butonUndo);
	verticalLayout->addWidget(butonWishlistCrud);
	verticalLayout->addWidget(butonWishlistReadOnly);
	mainLayout->addLayout(verticalLayout);

	QVBoxLayout* verticalLayout1 = new QVBoxLayout;
	QFormLayout* LayoutFormWishlist = new QFormLayout;
	LayoutFormWishlist->addRow("Denumire:", editInputWishlist);
	verticalLayout1->addLayout(LayoutFormWishlist);
	verticalLayout1->addWidget(butonAdaugaWishlist);
	verticalLayout1->addWidget(butonGolesteWishlist);
	verticalLayout1->addWidget(butonGenereazaWishlist);

	verticalLayout1->addWidget(sliderWishlist);
	verticalLayout1->addWidget(labelWishlist);
	labelWishlist->setText("0");
	sliderWishlist->setOrientation(Qt::Horizontal);
	verticalLayout1->addStretch();

	mainLayout->addLayout(verticalLayout1);

}

void GUI::connectSignals() {

	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [=]() {
		auto sel = table->selectionModel()->selectedIndexes();
		if (sel.isEmpty()) {
			editDenumire->setText("");
			editDestinatie->setText("");
			editTip->setText("");
			editPret->setText("");
		}
		else
		{
			int selRow = sel[0].row();
			auto model = table->model();
			auto denumireIndex = model->index(selRow, 0);
			auto denumire = model->data(denumireIndex, Qt::DisplayRole).toString().QString::toStdString();

			
			auto oferta = service.service_cauta(denumire);
			auto destinatie = oferta.get_destinatie();
			auto tip = oferta.get_tip();
			auto pret = oferta.get_pret();
			editDenumire->setText(denumire.c_str());
			editDestinatie->setText(destinatie.c_str());
			editTip->setText(tip.c_str());
			editPret->setText(QString::number(pret));
		}
		});

	QObject::connect(butonAdauga, &QPushButton::clicked, this, [=]() {
		try {
			const string denumire = (editDenumire->text()).QString::toStdString();
			const string destinatie = (editDestinatie->text()).QString::toStdString();
			const string tip = (editTip->text()).QString::toStdString();
			const string pret = (editPret->text()).QString::toStdString();
			service.service_adauga(denumire, destinatie, tip, pret);

		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(butonModifica, &QPushButton::clicked, this, [=]() {
		try {
			const string denumire = (editDenumire->text()).QString::toStdString();
			const string destinatie = (editDestinatie->text()).QString::toStdString();
			const string tip = (editTip->text()).QString::toStdString();
			const string pret = (editPret->text()).QString::toStdString();
			service.service_modifica(denumire, destinatie, tip, pret);
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(butonSterge, &QPushButton::clicked, this, [=]() {
		GUIStergere* gui = new GUIStergere{ *this, service };
		gui->show();
		});

	QObject::connect(butonCauta, &QPushButton::clicked, this, [=]() {
		GUICauta* gui = new GUICauta{ *this, service };
		gui->show();
		});

	QObject::connect(table->horizontalHeader(), &QHeaderView::sectionClicked, this, [=](int index) {
		try {
			model->set_sort(index);
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(butonFiltrare, &QPushButton::clicked, this, [=]() {
		GUIFiltrare* gui = new GUIFiltrare{ service };
		gui->show();
		});

	QObject::connect(butonWishlist, &QPushButton::clicked, this, [=]() {
		GUIWishlist* gui = new GUIWishlist{ service };
		gui->show();
		});

	QObject::connect(butonRaport, &QPushButton::clicked, this, [=]() {
		try {
			const unordered_map <string, DTO>& repo_raport = service.service_raport();
			string mesaj;
			for (const auto& el : repo_raport) {
				DTO p = el.second;
				mesaj = mesaj + el.first + " apare de " + to_string(p.get_count() + 1) + " ori \n";
			}
			QMessageBox::information(this, "Raport", QString::fromStdString(mesaj));
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(butonUndo, &QPushButton::clicked, this, [=]() {
		try {
			service.service_undo();
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(butonWishlistCrud, &QPushButton::clicked, this, [=]() {
		GUIWishlistCRUD* gui = new GUIWishlistCRUD{ service };
		gui->show();
		});

	QObject::connect(butonAdaugaWishlist, &QPushButton::clicked, this, [=]() {
		try {
			const string denumire = (editInputWishlist->text()).QString::toStdString();
			service.service_wishlist_adauga(denumire);
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonGolesteWishlist, &QPushButton::clicked, this, [=]() {
		try {
			service.service_wishlist_goleste();
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});
	QObject::connect(butonGenereazaWishlist, &QPushButton::clicked, this, [=]() {
		try {

			const string nr = to_string(sliderWishlist->value());
			service.service_wishlist_genereaza(nr);
		}
		catch (const RepoExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		catch (const ServiceExcept& re) { QMessageBox::critical(this, "Eroare", QString::fromStdString(re.get_message())); }
		});

	QObject::connect(sliderWishlist, &QSlider::valueChanged, this, [=]() {
		labelWishlist->setText(QString::number(sliderWishlist->value()));
		});

	QObject::connect(butonWishlistReadOnly, &QPushButton::clicked, this, [=]() {
		GUIWishlistReadOnly* gui = new GUIWishlistReadOnly{ service };
		gui->show();
		});
}


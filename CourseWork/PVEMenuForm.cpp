#include "PVEMenuForm.h"

PVEMenuForm::PVEMenuForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, this, &PVEMenuForm::button1_clicked);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &PVEMenuForm::button2_clicked);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &PVEMenuForm::button3_clicked);
	connect(ui.pushButton_4, &QPushButton::clicked, this, &PVEMenuForm::button4_clicked);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &PVEMenuForm::button5_clicked);
	connect(ui.pushButton_6, &QPushButton::clicked, this, &PVEMenuForm::button_user_clicked);
	connect(ui.pushButton_7, &QPushButton::clicked, this, &PVEMenuForm::close_click);
}

PVEMenuForm::~PVEMenuForm()
{
}

void PVEMenuForm::keyPressEvent(QKeyEvent * ev)
{
	if (ev->key() == Qt::Key::Key_Escape)
	{
		emit closed();
	}
}

void PVEMenuForm::button1_clicked()
{
	loadGame(":/maps/maps/map1.save");
}

void PVEMenuForm::button2_clicked()
{
	loadGame(":/maps/maps/map2.save");
}

void PVEMenuForm::button3_clicked()
{
	loadGame(":/maps/maps/map3.save");
}

void PVEMenuForm::button4_clicked()
{
	loadGame(":/maps/maps/map4.save");
}

void PVEMenuForm::button5_clicked()
{
	loadGame(":/maps/maps/map5.save");
}

void PVEMenuForm::button_user_clicked()
{
	auto res = QFileDialog::getOpenFileName(this, QString(), qApp->applicationDirPath(), "*.save");
	if (res.length())
	{
		loadGame(res);
	}
}

void PVEMenuForm::close_click()
{
	emit closed();
}

void PVEMenuForm::gameFormClosed()
{
	gameForm->hide();
	delete gameForm;
	show();
	grabKeyboard();
}

void PVEMenuForm::loadGame(QString filename)
{
	try
	{
		hide();
		gameForm = new GameForm(this->parentWidget());

		connect(gameForm, &GameForm::closed, this, &PVEMenuForm::gameFormClosed);
		gameForm->move(0, 20);


		auto gf = new PVEGameField(gameForm->infoScene, gameForm);

		gf->loadMapFromFile(filename);


		connect(gf, &GameField::closed, gameForm, &GameForm::gameClosed);
		connect(gf, &GameField::pauseClicked, gameForm, &GameForm::pause);
		gameForm->setGameField(gf);
		gameForm->show();
	}
	catch (std::exception ex)
	{
		gameFormClosed();
		QMessageBox::warning(nullptr, "Error", ex.what());
	}
}
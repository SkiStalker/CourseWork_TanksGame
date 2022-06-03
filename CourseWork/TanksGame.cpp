#include "TanksGame.h"


TanksGame::TanksGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pveButton, &QPushButton::clicked, this, &TanksGame::pveButton_clicked);
	connect(ui.conButton, &QPushButton::clicked, this, &TanksGame::conButton_clicked);
	connect(ui.pvpButton, &QPushButton::clicked, this, &TanksGame::pvpButton_clicked);

	connect(ui.actionAbout, &QAction::triggered, this, &TanksGame::helpAct);

	connect(ui.actionAbout_2, &QAction::triggered, this, &TanksGame::aboutAct);


	saveAct = new QAction("&Save", this);
	saveAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	connect(saveAct, &QAction::triggered, this, &TanksGame::sceneSave);
}

void TanksGame::conButton_clicked()
{

	ui.menuFile->addAction(saveAct);

	conForm = new ConForm(this);
	conForm->move(0, 21);

	connect(conForm, &ConForm::closed, this, &TanksGame::conFrom_closed);

	centralWidget()->hide();
	conForm->show();
	conForm->setFocus();
}

void TanksGame::pvemenu_closed()
{
	pvemenu->hide();
	delete pvemenu;
	centralWidget()->show();
}

void TanksGame::conFrom_closed()
{
	conForm->hide();
	delete conForm;
	centralWidget()->show();
}

void TanksGame::pvpGame_closed()
{
	gameForm->hide();
	delete gameForm;
	centralWidget()->show();
}

void TanksGame::pveButton_clicked()
{
	pvemenu = new PVEMenuForm(this);
	connect(pvemenu, &PVEMenuForm::closed, this, &TanksGame::pvemenu_closed);
	pvemenu->move(0, 20);
	centralWidget()->hide();
	pvemenu->show();
	pvemenu->grabKeyboard();
}

void TanksGame::pvpButton_clicked()
{
	centralWidget()->hide();
	gameForm = new GameForm(this);
	gameForm->grabKeyboard();

	connect(gameForm, &GameForm::closed, this, &TanksGame::pvpGame_closed);
	gameForm->move(0, 20);

	auto gf = new PVPGameField(gameForm->getGraphicsView());

	gf->loadMapFromFile(":/maps/maps/mappvp.save");


	connect(gf, &GameField::closed, gameForm, &GameForm::gameClosed);
	connect(gf, &GameField::pauseClicked, gameForm, &GameForm::pause);
	gameForm->show();
	gameForm->setGameField(gf);
}

void TanksGame::sceneSave()
{
	conForm->saveScene();
}

void TanksGame::helpAct()
{
	Help * help = new Help(this);
	help->exec();
	delete help;
}

void TanksGame::aboutAct()
{
	QMessageBox::information(nullptr, "", "Zabelin Nikita M8O-110b-20");
}


void TanksGame::keyPressEvent(QKeyEvent * e)
{

}


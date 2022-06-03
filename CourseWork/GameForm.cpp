#include "GameForm.h"

GameForm::GameForm(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::GameForm();
	ui->setupUi(this);
	ui->graphicsView->grabKeyboard();
	ui->graphicsView->setFocus();
	infoScene = new InfoPanel();
	ui->graphicsView_2->setScene(infoScene);
}


void GameForm::setGameField(GameField * field)
{

	if (gfield)
	{
		delete gfield;
		gfield = nullptr;
	}
	gfield = field;
	ui->graphicsView->setScene(gfield);
	ui->graphicsView->grabKeyboard();
}

void GameForm::keyPressEvent(QKeyEvent * e)
{
}

QWidget * GameForm::getGraphicsView()
{
	return ui->graphicsView;
}


void GameForm::gameClosed()
{
	emit closed();
}

void GameForm::pause()
{
	gfield->pause();
	auto res = QMessageBox::information(nullptr, "Pause", "Exit?", QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::No);
	if (res == QMessageBox::StandardButton::Ok)
	{
		emit closed();
	}
	else
	{
		gfield->pause();
	}
}



GameForm::~GameForm()
{
	delete infoScene;

	if(gfield)
		delete gfield;

	if(ui)
		delete ui;
}
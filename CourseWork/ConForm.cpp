#include "ConForm.h"

ConForm::ConForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	auto scene = new ConstructorGameField(this);


	// Добавляем разметку в конструктор
	for (int i = 0; i <= ui.graphicsView->width(); i += GameObject::getBASE_SIZE())
	{
		scene->addLine(QLineF(QPointF(i, 0), QPointF(i, ui.graphicsView->height())), QPen(QColor(255, 255, 255), 1));
		scene->addLine(QLineF(QPointF(0, i), QPointF(ui.graphicsView->width(), i)), QPen(QColor(255, 255, 255), 1));
	}

	// Костыль для выбора что строим
	connectRButtons();


	// Добавляем стандартный набор на сцену
	addDefaultItems(scene);



	ui.graphicsView->setScene(scene);
	ui.graphicsView->setMouseTracking(true);
	setMouseTracking(true);

	connect(ui.pushButton_r, &QPushButton::clicked, this, &ConForm::rotate);

	connect(scene, &ConstructorGameField::escape_clicked, this, &ConForm::escape);

}

void ConForm::escape()
{
	auto res = QMessageBox::information(nullptr, "Exiting", "Are you sure you want to exit?", QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No);
	if (res == QMessageBox::StandardButton::Yes)
	{
		emit closed();
	}
}

void ConForm::rotate()
{
	auto scene = (ConstructorGameField*)ui.graphicsView->scene();
	if (scene->getDirection() == GameObject::Direction::Up)
	{
		scene->setDirection(GameObject::Direction::Right);
		ui.pushButton->setIcon(QIcon(":/sprites/brick/sprites/brick/brickMainSkinV.png"));
		ui.pushButton->setIconSize(QSize(25, 50));
		ui.pushButton_2->setIcon(QIcon(":/sprites/brick/sprites/brick/wallMainSkinV.png"));
		ui.pushButton_2->setIconSize(QSize(25, 50));
	}
	else
	{
		scene->setDirection(GameObject::Direction::Up);
		ui.pushButton->setIcon(QIcon(":/sprites/brick/sprites/brick/brickMainSkin.png"));
		ui.pushButton->setIconSize(QSize(50, 25));
		ui.pushButton_2->setIcon(QIcon(":/sprites/brick/sprites/brick/wallMainSkin.png"));
		ui.pushButton_2->setIconSize(QSize(50, 25));
	}
}

ConForm::~ConForm()
{
}

void ConForm::mousePressEvent(QMouseEvent * ev)
{
}

void ConForm::mouseReleaseEvent(QMouseEvent * ev)
{

}

void ConForm::mouseMoveEvent(QMouseEvent * ev)
{
}

void ConForm::keyPressEvent(QKeyEvent * ev)
{
	if (ev->key() == Qt::Key::Key_Escape)
	{
		escape();
	}
}

void ConForm::saveScene()
{
	auto name = QFileDialog::getSaveFileName(this,QString(), qApp->applicationDirPath(), "*.save");
	if (name.length())
	{
		QFile sv(name);
		if (sv.open(QIODevice::WriteOnly))
		{
			QDataStream stream(&sv);
			stream << *((ConstructorGameField*)ui.graphicsView->scene());
		}
	}
}

void ConForm::rb_released()
{
	auto scene = (ConstructorGameField*)ui.graphicsView->scene();
	scene->setSelectedItem(0);
}

void ConForm::rb2_released()
{
	auto scene = (ConstructorGameField*)ui.graphicsView->scene();
	scene->setSelectedItem(1);
}

void ConForm::rb3_released()
{
	auto scene = (ConstructorGameField*)ui.graphicsView->scene();
	scene->setSelectedItem(2);
}

void ConForm::rb4_released()
{
	auto scene = (ConstructorGameField*)ui.graphicsView->scene();
	scene->setSelectedItem(3);
}

void ConForm::rb5_released()
{
	auto scene = (ConstructorGameField*)ui.graphicsView->scene();
	scene->setSelectedItem(4);
}

void ConForm::connectRButtons()
{
	connect(ui.pushButton, &QPushButton::released, this, &ConForm::rb_released);
	connect(ui.pushButton_2, &QPushButton::released, this, &ConForm::rb2_released);
	connect(ui.pushButton_3, &QPushButton::released, this, &ConForm::rb3_released);
	connect(ui.pushButton_4, &QPushButton::released, this, &ConForm::rb4_released);
	connect(ui.pushButton_5, &QPushButton::released, this, &ConForm::rb5_released);
}

void ConForm::addDefaultItems(ConstructorGameField* scene)
{
	scene->addItem(EnvironmentObject::getMyBase(QPointF(5.5 * 50, 11 * 50)));

	scene->addItem(EnvironmentObject::getBrick(QPointF(5 * GameObject::getBASE_SIZE(),
		11 * GameObject::getBASE_SIZE()), GameObject::Direction::Right));

	scene->addItem(EnvironmentObject::getBrick(QPointF(6.5 * GameObject::getBASE_SIZE(),
		11 * GameObject::getBASE_SIZE()), GameObject::Direction::Right));

	scene->addItem(EnvironmentObject::getBrick(QPointF(5 * GameObject::getBASE_SIZE(),
		10.5 * GameObject::getBASE_SIZE()), GameObject::Direction::Up));
	scene->addItem(EnvironmentObject::getBrick(QPointF(6 * GameObject::getBASE_SIZE(),
		10.5 * GameObject::getBASE_SIZE()), GameObject::Direction::Up));


	scene->addItem(TankObject::getMyTank(QPointF(5.5 * GameObject::getBASE_SIZE()+ 1,
		9 * GameObject::getBASE_SIZE() + 1)));

		scene->addRect(QRectF(5.5 * GameObject::getBASE_SIZE(), 9 * GameObject::getBASE_SIZE(),
		GameObject::getBASE_SIZE(), GameObject::getBASE_SIZE()),
		QPen(), QBrush(QColor(255, 255, 255),
			Qt::BrushStyle::FDiagPattern));

	scene->addRect(QRectF(0, 0, GameObject::getBASE_SIZE(), GameObject::getBASE_SIZE()),
		QPen(), QBrush(QColor(255, 255, 255),
			Qt::BrushStyle::FDiagPattern));

	scene->addRect(QRectF(5.5 * GameObject::getBASE_SIZE(), 0,
		GameObject::getBASE_SIZE(), GameObject::getBASE_SIZE()),
		QPen(), QBrush(QColor(255, 255, 255),
			Qt::BrushStyle::FDiagPattern));

	scene->addRect(QRectF(11 * GameObject::getBASE_SIZE(), 0,
		GameObject::getBASE_SIZE(), GameObject::getBASE_SIZE()),
		QPen(), QBrush(QColor(255, 255, 255),
			Qt::BrushStyle::FDiagPattern));
}


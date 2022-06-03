#include "PVPGameField.h"

PVPGameField::PVPGameField(QWidget * parent): GameField(parent)
{
	paused = false;
}

PVPGameField::~PVPGameField()
{
	alive = false;
	for (auto item : items())
		delete item;
}

bool PVPGameField::event(QEvent * ev)
{
	if (ev->type() == QEvent::Type::None && alive)
	{
		ObjectDestroyEvent * odev = (ObjectDestroyEvent *)ev;
		using ObjType = GameObject::ObjectType;
		ObjType obj_type = (ObjType)odev->object;
		switch (obj_type)
		{
		case ObjType::MyTank:
		case ObjType::MyBase:
		{
			enemyWin();
			break;
		}
		case ObjType::EnemyTank:
		case ObjType::EnemyBase:
		{
			meWin();
			break;
		}
		}
		return true;
	}
	return GameField::event(ev);
}

void PVPGameField::meWin()
{
	auto _items = items();
	for (int i = 0; i < _items.length(); i++)
	{
		((GameObject*)_items[i])->deleteLater();
	}
	auto text = new QGraphicsTextItem("You win");
	addItem(text);
	text->setPos(QPointF(sceneRect().width() / 2 - 100, sceneRect().height() / 2 - 100));
	text->setDefaultTextColor(QColor(255, 255, 255));
	QFont f;
	f.setPointSizeF(50);
	text->setFont(f);
	alive = false;
}

void PVPGameField::enemyWin()
{
	auto _items = items();
	for (int i = 0; i < _items.length(); i++)
	{
		((GameObject*)_items[i])->deleteLater();
	}
	auto text = new QGraphicsTextItem("Enemy win");
	addItem(text);
	text->setPos(QPointF(sceneRect().width() / 2 - 100, sceneRect().height() / 2 - 100));
	text->setDefaultTextColor(QColor(255, 255, 255));
	QFont f;
	f.setPointSizeF(50);
	text->setFont(f);
	alive = false;
}

void PVPGameField::loadMapFromFile(QString name)
{
	QFile f(name);
	if (f.open(QIODevice::OpenModeFlag::ReadOnly))
	{
		QDataStream stream(&f);
		int ID;
		stream >> ID;

		while (!stream.atEnd())
		{
			try
			{
				GameObject::ObjectType type;
				int i_type;
				stream >> i_type;
				type = (GameObject::ObjectType)i_type;
				readByType(stream, type);
			}
			catch (std::exception ex)
			{
				throw ex;
			}
		}

		addItem(EnvironmentObject::getEnemyBase(QPointF(5.5*GameObject::getBASE_SIZE(), 0)));
		addItem(TankObject::getEnemyTank(QPointF(5.5 * GameObject::getBASE_SIZE(), 2.5 * GameObject::getBASE_SIZE())));

		auto _items = items();

		for (int i = 0; i < _items.length(); i++)
		{
			((GameObject*)_items[i])->startObjectUpdating();
		}
	}
}

void PVPGameField::readByType(QDataStream & stream, GameObject::ObjectType type)
{
	// Откат для считывания типа объекта внутри ">>"
	stream.skipRawData(-sizeof(int));

	GameObject* cur = nullptr;
	switch (type)
	{
	case GameObject::ObjectType::MyTank:
	case GameObject::ObjectType::EnemyTank:
	case GameObject::ObjectType::BotTank:
	{
		TankObject* tank = nullptr;
		stream >> tank;
		cur = tank;
		break;
	}
	case GameObject::ObjectType::Brick:
	case GameObject::ObjectType::MyBase:
	case GameObject::ObjectType::EnemyBase:
	case GameObject::ObjectType::Wall:
	case GameObject::ObjectType::Water:
	case GameObject::ObjectType::Jungle:
	{
		EnvironmentObject* env = nullptr;
		stream >> env;
		cur = env;
		break;
	}
	case GameObject::ObjectType::Shell:
	{
		ShellObject * shell = nullptr;
		stream >> shell;
		cur = shell;
		break;
	}
	}
	addItem(cur);
}

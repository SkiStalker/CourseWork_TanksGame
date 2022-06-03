#include "PVEGameField.h"

using QK = Qt::Key;

PVEGameField::PVEGameField(InfoPanel * info, QWidget * parent): GameField(parent), info(info)
{
	cntBotTank = 0;
	cntFastBotTank = 0;
	cntHeavyBotTank = 0;
	curspawn = 0;
	paused = false;
}


PVEGameField::~PVEGameField()
{
	alive = false;
	for (auto item : items())
		delete item;
}

// Обработка уничтожения объекта на графической сцене
bool PVEGameField::event(QEvent * ev)
{
	if (added && alive)
	{
		m.lock();
		pause();
		pause();
		added--;
		m.unlock();
	}
	if (ev->type() == QEvent::Type::None && alive)
	{
		m.lock();
		ObjectDestroyEvent * odev = (ObjectDestroyEvent *)ev;
		using ObjType = GameObject::ObjectType;
		ObjType obj_type = (ObjType)odev->object;
		switch (obj_type)
		{
		case ObjType::BotTank:
		{
			if (cntBots > 1)
			{
				if (alive)
				{
					if (cntBotTank || cntFastBotTank || cntHeavyBotTank)
					{
						auto t = spawnBotTank();
						if (t)
						{
							addItem(t);
							added++;
						}
					}
					cntBots--;
				}
			}
			else
			{
				win();
			}
			break;
		}
		case ObjType::MyTank:
		case ObjType::MyBase:
		{
			lose();
			break;
		}
		}
		m.unlock();
		return true;
	}

	return GameField::event(ev);
}

void PVEGameField::loadMapFromFile(QString name)
{
	QFile f(name);
	if (f.open(QIODevice::OpenModeFlag::ReadOnly))
	{
		QDataStream stream(&f);
		int ID;
		stream >> ID;

		if (stream.atEnd())
			throw std::exception("Wrong file format");

		this->ID = ID;


		if (ID < -1 || ID > 5)
			throw std::exception("Wrong map ID");

		setDifficulty(ID);

		while (!stream.atEnd())
		{
			try
			{
				GameObject::ObjectType type;
				int i_type;
				stream >> i_type;

				if (i_type < 0 || i_type > 9)
					throw std::exception("Wrong object type");

				type = (GameObject::ObjectType)i_type;
				readByType(stream, type);
			}
			catch (std::exception ex)
			{
				throw ex;
			}
		}

		addItem(spawnBotTank());
		addItem(spawnBotTank());
		addItem(spawnBotTank());

		auto _items = items();

		for (int i = 0; i < _items.length(); i++)
		{
			((GameObject*)_items[i])->startObjectUpdating();
		}
	}
}

void PVEGameField::setDifficulty(int ID)
{
	switch (ID)
	{
	case 1:
		cntBotTank = 5;
		cntFastBotTank = 3;
		cntHeavyBotTank = 0;
		break;
	case 2:
		cntBotTank = 3;
		cntFastBotTank = 4;
		cntHeavyBotTank = 1;
		break;
	case 3:
		cntBotTank = 5;
		cntFastBotTank = 4;
		cntHeavyBotTank = 3;
		break;
	case 4:
		cntBotTank = 5;
		cntFastBotTank = 5;
		cntHeavyBotTank = 5;
		break;
	case 5:
		cntBotTank = 6;
		cntFastBotTank = 6;
		cntHeavyBotTank = 6;
		break;
	}
	cntBots = cntBotTank + cntFastBotTank + cntHeavyBotTank;
}

GameObject* PVEGameField::spawnBotTank()
{
	QPointF start_point(curspawn*5.5*GameObject::getBASE_SIZE() + 1, 1);

	TankObject* tank = nullptr;
	int cntr = 0;
	while (
		items(
		QRectF(start_point.x(), 
		start_point.y(), 
		GameObject::getBASE_SIZE() - 2, 
		GameObject::getBASE_SIZE() - 2)
		).length()

		&& 
		((GameObject*)items(QRectF(start_point.x(),
			start_point.y(),
			GameObject::getBASE_SIZE() - 2,
			GameObject::getBASE_SIZE() - 2)).last())->isMaterial()
		)
	{
		curspawn = (curspawn + 1) % 3;
		start_point = QPointF(curspawn*5.5*GameObject::getBASE_SIZE() + 1, 1);
		cntr++;
		if (cntr > 6)
			return nullptr;
	}
	if (cntBotTank)
	{
		tank = TankObject::getBotTank(start_point);
		cntBotTank--;
	}
	else if (cntFastBotTank)
	{
		tank = TankObject::getBotFastTank(start_point);
		cntFastBotTank--;
	}
	else // cntHeavyBotTank
	{
		tank = TankObject::getBotHeavyTank(start_point);
		cntHeavyBotTank--;
	}
	curspawn = (curspawn + 1) % 3;

	info->printInfo(cntBotTank, cntFastBotTank, cntHeavyBotTank);
	return tank;
}

void PVEGameField::win()
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

void PVEGameField::lose()
{
	auto _items = items();
	for (int i = 0; i < _items.length(); i++)
	{
		((GameObject*)_items[i])->deleteLater();
	}
	auto text = new QGraphicsTextItem("You lose");
	addItem(text);
	text->setPos(QPointF(sceneRect().width() / 2 - 100, sceneRect().height() / 2 - 100));
	text->setDefaultTextColor(QColor(255, 255, 255));
	QFont f;
	f.setPointSizeF(50);
	text->setFont(f);
	alive = false;
}

void PVEGameField::readByType(QDataStream & stream, GameObject::ObjectType type)
{
	// Откат для считывания типа объекта внутри ">>"
	stream.skipRawData(-sizeof(int));

	try
	{
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
	catch (std::exception ex)
	{
		throw ex;
	}
}

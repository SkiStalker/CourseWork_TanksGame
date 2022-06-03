#include "TankObject.h"

using QK = Qt::Key;

II::II(TankObject * tank) : tank(tank), rotations(0), shots(0)
{
}

void II::think()
{
	auto pol = getPolygon();
	bool polinscene = tank->scene()->sceneRect().contains(pol.at(0))
		&& tank->scene()->sceneRect().contains(pol.at(1))
		&& tank->scene()->sceneRect().contains(pol.at(2));

	auto items = tank->scene()->items(getPolygon());
	if (items.length())
	{
		bool isdestr = false;
		bool ismater = false;
		if (items.length())
		{
			EnvironmentObject* item = nullptr;
			for (int i = 0; i < items.length(); i++)
				if (((EnvironmentObject*)items[i])->isMaterial())
					item = (EnvironmentObject*)items[i];

			if (!item)
				item = (EnvironmentObject*)items.last();

			isdestr = item->isDestructible();
			ismater =  item->isMaterial();
		}

		if (isdestr && shots < 2)
		{
			tank->shot();
			shots++;
			rotations = 0;
		}
		else if(!ismater)
		{
			tank->speed = tank->max_speed;
		}
		else if (rotations < 4)
		{
			int r_to = (rand() % 2) ? 1 : -1;
			tank->rotateObject(r_to);
			rotations++;
			shots = 0;
		}
	}
	else
	{
		if (!polinscene)
		{
			int r_to = (rand() % 2) ? 1 : -1;
			tank->rotateObject(r_to);
		}
		else
		{
			tank->speed = tank->max_speed;
		}
	}
}

QPolygonF II::getPolygon()
{
	QPolygonF res;
	switch (tank->dir)
	{
	case GameObject::Direction::Up:
	{
		res << tank->rect().topLeft() + tank->pos() + QPointF(0, -1)
			<< tank->rect().topRight() + tank->pos() + QPointF(0, -1)
			<< tank->rect().topLeft() + tank->pos() + QPointF(tank->rect().width() / 2, -2);
		break;
	}
	case GameObject::Direction::Down:
	{
		res << tank->rect().bottomLeft() + tank->pos() + QPointF(0, 1)
			<< tank->rect().bottomRight() + tank->pos() + QPointF(0, 1)
			<< tank->rect().bottomLeft() + tank->pos() + QPointF(tank->rect().width() / 2, 2);
		break;
	}
	case GameObject::Direction::Left:
	{
		res << tank->rect().topLeft() + tank->pos() + QPointF(-1, 0)
			<< tank->rect().topLeft() + tank->pos() + QPointF(-1, 0)
			<< tank->rect().topLeft() + tank->pos() + QPointF(-2, tank->rect().height() / 2);
		break;
	}
	case GameObject::Direction::Right:
	{
		res << tank->rect().topRight() + tank->pos() + QPointF(1, 0)
			<< tank->rect().topRight() + tank->pos() + QPointF(1, 0)
			<< tank->rect().topRight() + tank->pos() + QPointF(2, tank->rect().height() / 2);
		break;
	}
	}
	return res;
}

void TankObject::iiTimerEvent()
{
	ii->think();
}


TankObject::TankObject(ObjectType type, QPointF start_point,
	ControlKeys keys, SpritesGroup group, Direction dir, int health, double speed)
	: GameObject(start_point, QRectF(0, 0, GameObject::BASE_SIZE*0.75, GameObject::BASE_SIZE*0.75), group, type, dir),
	keys(keys), health(health), speed(0), max_speed(speed)
{
	movable = true;
	update();
	setZValue(-1);
	if (!keys.isInit())
	{
		ii = new II(this);
		connect(&iitimer, &QTimer::timeout, this, &TankObject::iiTimerEvent);
		iitimer.start(50);
	}
}

TankObject::~TankObject()
{
	if (ii)
		delete ii;
}

void TankObject::updateObject()
{
	if (!this->material)
	{
		if (sprites.getCurrentGroup()->isPeriod())
		{
			iitimer.stop();
			deleteFromMap();
		}
		else
		{
			sprites.getCurrentGroup()->incCurrentTime();
		}
	}
	else
	{
		interactObjects();
		if (speed)
		{
			if (inSceneRect())
			{
				ride();
				sprites.getCurrentGroup()->incCurrentTime();
			}
			else
			{
				pushAway(nullptr);
			}
		}
	}
}

void TankObject::pressAction(QKeyEvent* e)
{
	auto key = e->key();
	if (!e->isAutoRepeat())
	{
		if (keys.isInit())
			if (key == keys.getUpKey())
			{
				speed = max_speed;
			}
			else if (key == keys.getLeftKey())
			{
				rotateObject(-1);
			}
			else if (key == keys.getDownKey())
			{
				speed = -max_speed;
			}
			else if (key == keys.getRightKey())
			{
				rotateObject(1);
			}
			else if (key == keys.getFireKey())
			{
				shot();
			}
	}
	QGraphicsItem::update();
}

void TankObject::releaseAction(QKeyEvent * e)
{
	if (!e->isAutoRepeat() && (e->key() == keys.getUpKey() || e->key() == keys.getDownKey()))
	{
		speed = 0;
	}
}

void TankObject::interactObjects()
{
	auto items = collidingItems();
	if (items.size())
	{
		for (int i = 0; i < items.length(); i++)
		{
			// Если объект танк (таким образом определяется просто принадлежность к классу танка
			// не важно какому)
			GameObject* item = (GameObject*)items[i];
			if (item->isMaterial())
			{
				if (auto tank = dynamic_cast<TankObject*>(item))
				{
					pushAway(item);
				}
				// Если объект снаряд
				else if (item->getObjectType() == GameObject::ObjectType::Shell)
				{
					health--;
					if (!health)
					{
						die();
					}
				}
				else
				{
					pushAway(item);
				}
			}
		}
	}
}

TankObject * TankObject::getMyTank(QPointF start_point)
{
	return new TankObject(GameObject::ObjectType::MyTank,
		start_point,
		ControlKeys(QK::Key_W, QK::Key_D, QK::Key_S, QK::Key_A, QK::Key_Space),
		SpritesGroup(
			{
			new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/mainTankSkin.png"),
						},
						500,
						50
					),
			new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/deadTankSkin.png")
						},
						1000,
						50
					)

			}
		),
		GameObject::Direction::Up,
		1
	);
}

TankObject * TankObject::getEnemyTank(QPointF start_point)
{
	return new TankObject(
		GameObject::ObjectType::EnemyTank,
		start_point,
		ControlKeys(QK::Key_Up, QK::Key_Right, QK::Key_Down, QK::Key_Left, QK::Key_0),
		SpritesGroup
		(
			{
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/enemyTankSkin.png")
						},
						500,
						50
					),
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/deadTankSkin.png")
						},
						1000,
						50
					)
			}
		),
		GameObject::Direction::Down
	);
}

TankObject * TankObject::getBotTank(QPointF start_point)
{
	return new TankObject(
		GameObject::ObjectType::BotTank,
		start_point,
		ControlKeys(),
		SpritesGroup
		(
			{
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/botTank.png")
						},
						500,
						50
					),
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/deadTankSkin.png")
						},
						1000,
						50
					)
			}
		),
		Direction::Down,
		1,
		2
	);
}

TankObject * TankObject::getBotFastTank(QPointF start_point)
{
	return new TankObject(
		GameObject::ObjectType::BotTank,
		start_point,
		ControlKeys(),
		SpritesGroup
		(
			{
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/botFastTank.png")
						},
						500,
						50
					),
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/deadTankSkin.png")
						},
						1000,
						50
					)
			}
		),
		GameObject::Direction::Down,
		1,
		2.5
	);
}

TankObject * TankObject::getBotHeavyTank(QPointF start_point)
{
	return new TankObject(
		GameObject::ObjectType::BotTank,
		start_point,
		ControlKeys(),
		SpritesGroup
		(
			{
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/botHeavyTank.png")
						},
						500,
						50
					),
					new Sprites
					(
						{
							new Image(":/sprites/tank/sprites/tank/deadTankSkin.png")
						},
						1000,
						50
					)
			}
		),
		GameObject::Direction::Down,
		2,
		1
	);
}

void TankObject::die()
{
	this->material = false;
	sprites.setCurrentGroup(1);
	sprites.getCurrentGroup()->restart();
	update();
}

void TankObject::pushAway(GameObject* item)
{
	auto off = -moveByDir()*(speed+0.1);
	moveBy(off.x(), off.y());
	speed = 0;
}

void TankObject::rotateObject(double angle)
{
	pushAway(nullptr);
	int t = (int)dir;
	t = (t + ((int)angle)) % 4;
	if (t < 0)
	{
		t = (4 + t) % 4;
	}

	dir = (Direction)t;
	setTransformOriginPoint(boundingRect().center());
	setRotation((int)dir * 90);
}

void TankObject::shot()
{
	auto p = pos();
	auto r = rect();
	QPointF start_p;
	switch (dir)
	{
	case GameObject::Direction::Up:
		start_p.setX(pos().x() + (rect().width() / 2) - 2.5);
		start_p.setY(pos().y() - 1 - 15);
		break;
	case GameObject::Direction::Right:
		start_p.setY(pos().y() + (rect().height() / 2) - 2.5);
		start_p.setX(pos().x() + rect().width() + 1 + 15);
		break;
	case GameObject::Direction::Down:
		start_p.setX(pos().x() + (rect().width() / 2) - 2.5);
		start_p.setY(pos().y() + rect().height() + 1 + 15);
		break;
	case GameObject::Direction::Left:
		start_p.setY(pos().y() + (rect().height() / 2) - 2.5);
		start_p.setX(pos().x() - 1 - 15);
		break;
	}
	ShellObject * shell = ShellObject::getShell(start_p, dir);
	scene()->addItem(shell);
 	shell->startObjectUpdating();
}

void TankObject::ride()
{
	QPointF offset = moveByDir() * speed;
	moveBy(offset.x(), offset.y());
}

QPointF TankObject::moveByDir()
{
	switch (dir)
	{
	case GameObject::Direction::Right:
		return { 1, 0 };
	case GameObject::Direction::Down:
		return { 0, 1 };
	case GameObject::Direction::Left:
		return { -1, 0 };
	case GameObject::Direction::Up:
		return { 0, -1 };
	}
	return { 0, 0 };
}

void TankObject::writeToStream(QDataStream & stream)
{
	auto type = (int)getObjectType();
	stream << (int)getObjectType();

	stream << QRectF(pos().x(), pos().y(), rect().width(), rect().height());

	stream << sprites;

	stream << (int)dir;

	stream << health;

	stream << keys;
}

QDataStream & operator>>(QDataStream & stream, TankObject *& obj)
{
	try
	{
		int i_t;

		stream >> i_t;

		if (i_t < 0 || i_t > 9)
			throw std::exception("Wrong object type");

		GameObject::ObjectType t = (GameObject::ObjectType)i_t;

		QRectF r;
		stream >> r;

		QPointF p = r.topLeft();
		r.moveTo(0, 0);

		SpritesGroup sg;
		stream >> sg;

		GameObject::Direction dir;

		int i_dir;

		stream >> i_dir;

		if (i_dir < 0 || i_dir > 3)
			throw std::exception("Wrong object direction");

		dir = (GameObject::Direction)i_dir;


		int health;

		stream >> health;

		if (health < 0)
			throw std::exception("Wrong tank health");

		ControlKeys keys;

		try
		{
			stream >> keys;
		}
		catch (std::exception ex)
		{
			throw ex;
		}

		obj = new TankObject(t, p, keys, sg, dir, health);
	}
	catch(std::exception ex)
	{
		throw ex;
	}
	return stream;
}

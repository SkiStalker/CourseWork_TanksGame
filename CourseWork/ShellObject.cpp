#include "ShellObject.h"

ShellObject::ShellObject(QPointF start_point, Direction dir)
	: GameObject(start_point,
		QRectF(0, 0, 10, 15),
		SpritesGroup(
			{
				new Sprites(
						{
							new Image(":/sprites/shell/sprites/shell/shellSprite.png"),
						},
						1,
						5,
						10
						),
				new Sprites(
						{
							new Image(":/sprites/tank/sprites/tank/deadTankSkin.png")
						},
						1000,
						50,
						50
						)
			}
		),
		GameObject::ObjectType::Shell,
		dir
	),
	speed(1)
{
	switch (dir)
	{
	case GameObject::Direction::Up:
		break;
	case GameObject::Direction::Right:
		setRotation(90);
		break;
	case GameObject::Direction::Down:
		setRotation(180);
		break;
	case GameObject::Direction::Left:
		setRotation(-90);
		break;
	}
	movable = true;
}

ShellObject::~ShellObject()
{
}

void ShellObject::updateObject()
{
	if (!material)
	{
		if (sprites.getCurrentGroup()->isPeriod())
		{
			deleteLater();
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
				speed = 0;
				sprites.setCurrentGroup(1);
				sprites.getCurrentGroup()->restart();
				setRect(QRectF(0, 0, GameObject::BASE_SIZE / 2, GameObject::BASE_SIZE / 2));
				material = false;
				update();
			}
		}
	}
}

void ShellObject::interactObjects()
{
	auto items = collidingItems();
	if (items.length())
	{
		auto g_item = (GameObject*)items.last();
		if (g_item->isMaterial())
		{
			if(g_item->getObjectType() != GameObject::ObjectType::Shell)
				g_item->interactObjects();

			if (g_item->getObjectType() != GameObject::ObjectType::Water)
			{
				speed = 0;
				sprites.setCurrentGroup(1);
				setRect(QRectF(-12.5, -12.5, 25, 25));
				material = false;
				update();
			}
		}
	}
}

ShellObject * ShellObject::getShell(QPointF start_point, GameObject::Direction dir)
{
	return new ShellObject(start_point, dir);
}

void ShellObject::writeToStream(QDataStream & stream)
{
	//QPointF start_point, Direction dir
	QPointF p;
	stream << p;
	stream << (int)dir;
}

void ShellObject::ride()
{
	QPointF offset = moveByDir() * speed * elapsed();
	moveBy(offset.x(), offset.y());
}

QPointF ShellObject::moveByDir()
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

QDataStream & operator>>(QDataStream & stream, ShellObject *& obj)
{
	QPointF p;
	stream >> p;
	GameObject::Direction  dir;
	int i_dir;
	stream >> i_dir;

	if (i_dir < 0 || i_dir > 3)
		throw std::exception("Wrong object direction");


	dir = (GameObject::Direction)i_dir;
	obj = new ShellObject(p, dir);
	return stream;
}

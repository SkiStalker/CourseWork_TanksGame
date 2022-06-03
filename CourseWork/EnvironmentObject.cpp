#include "EnvironmentObject.h"

EnvironmentObject::EnvironmentObject(ObjectType type, QPointF start_point, SpritesGroup group, bool destructible, bool material, Direction dir, QRectF rect)
	: GameObject(start_point, rect, group, type, dir), destructible(destructible)
{
	this->material = material;
	if ((int)(this->dir))
	{
		rotateObject(-1);
		setTransformOriginPoint(QPointF(
			boundingRect().width() / 4, boundingRect().height() / 2
		));
		setRotation((int)dir * 90);
		this->dir = Direction::Right;
	}
}

EnvironmentObject::~EnvironmentObject()
{
}

void EnvironmentObject::updateObject()
{
}

void EnvironmentObject::interactObjects()
{
	if (destructible)
	{
		deleteFromMap();
		deleteLater();
	}
}

EnvironmentObject * EnvironmentObject::getBrick(QPointF start_point, Direction dir)
{
	return new EnvironmentObject(GameObject::ObjectType::Brick, start_point,
		SpritesGroup({
			new Sprites(
				new Image(":/sprites/brick/sprites/brick/brickMainSkin.png")
				,1, 50, 25)
			}),
		true,
		true,
		dir,
		QRectF(0, 0, 50, 25)
	);
}

EnvironmentObject * EnvironmentObject::getWall(QPointF start_point, Direction dir)
{
	return new EnvironmentObject(GameObject::ObjectType::Wall, start_point,
		SpritesGroup({
			new Sprites(
				new Image(":/sprites/brick/sprites/brick/wallMainSkin.png")
				,1, 50, 25)
			}),
		false,
		true,
		dir,
		QRectF(0, 0, 50, 25)
	);
}

EnvironmentObject * EnvironmentObject::getWater(QPointF start_point)
{
	return new EnvironmentObject(GameObject::ObjectType::Water, start_point,
		SpritesGroup({
			new Sprites(
				new Image(":/sprites/brick/sprites/brick/waterMainSkin.png")
				,1, 50)
			}),
		false,
		true,
		Direction::Up
	);
}

EnvironmentObject * EnvironmentObject::getJungle(QPointF start_point)
{
	return new EnvironmentObject(GameObject::ObjectType::Jungle, start_point,
		SpritesGroup({
			new Sprites(
				new Image(":/sprites/brick/sprites/brick/leavesMainSkin.png")
				,1, 50)
			}),
		false,
		false,
		Direction::Up
	);
}

EnvironmentObject * EnvironmentObject::getMyBase(QPointF start_point)
{
	return new EnvironmentObject(GameObject::ObjectType::MyBase, start_point,
		SpritesGroup(
			{
				new Sprites(
					new Image(":/sprites/base/sprites/base/myBaseMainSkin.png"),
					1, 50
				)
			}
		),
		true,
		true
	);
}

EnvironmentObject * EnvironmentObject::getEnemyBase(QPointF start_point)
{
	return new EnvironmentObject(GameObject::ObjectType::EnemyBase, start_point,
		SpritesGroup(
			{
				new Sprites(
					new Image(":/sprites/base/sprites/base/enemyBaseMainSkin.png"),
					1, 50
				)
			}
		),
		true,
		true
	);;
}

void EnvironmentObject::writeToStream(QDataStream & stream)
{
	stream << (int)(object_type);
	stream << sprites;
	stream << destructible << material;
	int i_dir = (int)dir;
	stream << (int)dir;
	stream << QRect(pos().x(), pos().y(), rect().width(), rect().height());
}

bool EnvironmentObject::isDestructible()
{
	return destructible;
}


QDataStream & operator>>(QDataStream & stream, EnvironmentObject *& obj)
{
	try
	{
		GameObject::ObjectType obj_type;
		int i_obj_type;
		stream >> i_obj_type;

		if (i_obj_type < 0 || i_obj_type > 9)
			throw std::exception("Wrong object type");

		obj_type = (GameObject::ObjectType)i_obj_type;

		SpritesGroup gr;

		try
		{
			stream >> gr;
		}
		catch (std::exception ex)
		{
			throw ex;
		}

		bool dest, mater;

		try
		{
			stream >> dest >> mater;
		}
		catch (std::exception ex)
		{
			throw ex;
		}
		

		GameObject::Direction dir;
		int i_dir = -1;
		stream >> i_dir;

		if (i_dir < 0 || i_dir > 3)
			throw std::exception("Wrong object direction");

		dir = (GameObject::Direction)i_dir;
		QPoint p;
		QRect r;

		stream >> r;
		p = r.topLeft();
		r = QRect(0, 0, r.width(), r.height());
		obj = new EnvironmentObject(obj_type, p, gr, dest, mater, dir, r);
	}
	catch (std::exception ex)
	{
		throw ex;
	}
	return stream;
}

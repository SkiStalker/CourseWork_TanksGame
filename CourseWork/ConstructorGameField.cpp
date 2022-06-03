#include "ConstructorGameField.h"

ConstructorGameField::ConstructorGameField(QWidget* parent) : GameField(parent)
{
	dir = GameObject::Direction::Up;
	selected = 0;
	pressed = false;
}

ConstructorGameField::~ConstructorGameField()
{
}

void ConstructorGameField::keyPressEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key::Key_Escape)
		emit escape_clicked();
}

void ConstructorGameField::keyReleaseEvent(QKeyEvent * e)
{
}

void ConstructorGameField::mousePressEvent(QGraphicsSceneMouseEvent * ev)
{
	pressed = true;
	switch (selected)
	{
	case 4:
	{
		auto n_pos = normalizePos(ev->scenePos());
		QRect r(n_pos.x() + 2, n_pos.y() + 2,
			GameObject::getBASE_SIZE() - 4, GameObject::getBASE_SIZE() - 4);
		auto _items = items(r);
		if (_items.length())
		{
			for (int i = 0; i < _items.length(); i++)
				if (notStandartItem(_items[i])
					&& !dynamic_cast<QGraphicsLineItem*>(_items[i])
					&& !dynamic_cast<TankObject*>(_items[i])
					)
				{
					removeItem(_items[i]);
				}
		}
		break;
	}

	case 0:
	{
		if (noItemsInBoundRect(ev->scenePos(), GameObject::ObjectType::Brick, dir))
		{
			addObject(normalizePosHalf(ev->scenePos()).toPoint(),
				GameObject::ObjectType::Brick, dir);
		}
		break;
	}

	case 1:
	{
		if (noItemsInBoundRect(ev->scenePos(), GameObject::ObjectType::Wall, dir))
		{
			addObject(normalizePosHalf(ev->scenePos()).toPoint()
				, GameObject::ObjectType::Wall, dir);
		}
		break;
	}

	case 2:
	{
		if (noItemsInBoundRect(ev->scenePos(), GameObject::ObjectType::Jungle))
		{
			addObject(normalizePosHalf(ev->scenePos()).toPoint(),
				GameObject::ObjectType::Jungle, GameObject::Direction::Up);
		}
		break;
	}

	case 3:
	{
		if (noItemsInBoundRect(ev->scenePos(), GameObject::ObjectType::Water))
		{
			addObject(normalizePosHalf(ev->scenePos()).toPoint(),
				GameObject::ObjectType::Water, GameObject::Direction::Up);
		}
		break;
	}
	}
}

void ConstructorGameField::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	pressed = false;
}

void ConstructorGameField::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	mousePressEvent(mouseEvent);
}

void ConstructorGameField::mouseMoveEvent(QGraphicsSceneMouseEvent * ev)
{
	if (pressed)
		mousePressEvent(ev);
}

void ConstructorGameField::setSelectedItem(int selected)
{
	this->selected = selected;
}

void ConstructorGameField::addObject(QPoint start_point, GameObject::ObjectType type, GameObject::Direction dir)
{
	switch (type)
	{
	case GameObject::ObjectType::Brick:
		addItem(EnvironmentObject::getBrick(start_point, dir));
		break;
	case GameObject::ObjectType::Wall:
		addItem(EnvironmentObject::getWall(start_point, dir));
		break;
	case GameObject::ObjectType::Jungle:
		addItem(EnvironmentObject::getJungle(start_point));
		break;
	case GameObject::ObjectType::Water:
		addItem(EnvironmentObject::getWater(start_point));
	}
	update();
}

void ConstructorGameField::setDirection(GameObject::Direction dir)
{
	this->dir = dir;
}

GameObject::Direction ConstructorGameField::getDirection()
{
	return dir;
}

bool ConstructorGameField::notStandartItem(QGraphicsItem * item)
{
	return item->pos() != QPointF(5.5 * 50, 11 * 50)
		&& item->pos() != QPointF(5 * 50, 11 * 50)
		&& item->pos() != QPointF(6.5 * 50, 11 * 50)
		&& item->pos() != QPointF(5 * 50, 10.5 * 50)
		&& item->pos() != QPointF(6 * 50, 10.5 * 50)
		&& item->pos() != QPointF(5.5 * GameObject::getBASE_SIZE(), 0)
		&& item->pos() != QPointF(11 * GameObject::getBASE_SIZE(), 0)
		&& item->pos() != QPointF(0, 0);
}

bool ConstructorGameField::noItemsInBoundRect(QPointF point, GameObject::ObjectType type, GameObject::Direction dir)
{
	QList<QGraphicsItem*> res;
	switch (type)
	{
	case GameObject::ObjectType::Brick:
	case GameObject::ObjectType::Wall:
	{
		point = normalizePosHalf(point);
		if (dir == GameObject::Direction::Up)
		{
			point += QPointF(GameObject::getBASE_SIZE() / 2, GameObject::getBASE_SIZE() / 4);

		}
		else
		{
			point += QPointF(GameObject::getBASE_SIZE() / 4, GameObject::getBASE_SIZE() / 2);
		}

		if (point.y() >= views().last()->height() || point.x() >= views().last()->width())
			return false;

		QRectF r(point.x() - 1, point.y() - 1, 2, 2);
		res = items(r);

		for (int i = 0; i < res.length(); i++)
		{
			if (dynamic_cast<QGraphicsRectItem*>(res[i]))
				return false;
		}
		return true;
		break;
	}

	case GameObject::ObjectType::Water:
	case GameObject::ObjectType::Jungle:
	{
		point = normalizePosHalf(point);
		point += QPoint(GameObject::getBASE_SIZE() / 2, GameObject::getBASE_SIZE() / 2);

		if (point.y() >= views().last()->height() || point.x() >= views().last()->width())
			return false;

		QRectF r(point.x() - 1, point.y() - 1, 2, 2);
		auto res = items(r);


		for (int i = 0; i < res.length(); i++)
			if (dynamic_cast<QGraphicsRectItem*>(res[i]))
				return false;
		return true;
	}
	}

	return false;
}

QPointF ConstructorGameField::normalizePos(QPointF _point)
{
	auto point = _point.toPoint();
	return QPoint(point.x() - (point.x() % GameObject::getBASE_SIZE()), point.y() - (point.y() % GameObject::getBASE_SIZE()));
}

QPointF ConstructorGameField::normalizePosHalf(QPointF _point)
{
	auto point = _point.toPoint();
	return QPointF(point.x() - (point.x() % (GameObject::getBASE_SIZE() / 2)), point.y() - (point.y() % (GameObject::getBASE_SIZE() / 2)));
}

QDataStream & operator<<(QDataStream & stream, ConstructorGameField & field)
{
	int ID = 5;
	stream << ID;
	for (auto item : field.items())
	{
		if (!dynamic_cast<QGraphicsLineItem*>(item))
		{
			if (auto tank = dynamic_cast<TankObject*>(item))
			{
				tank->writeToStream(stream);
			}
			else if(auto env = dynamic_cast<EnvironmentObject*>(item))
			{
				env->writeToStream(stream);
			}
		}
	}
	return stream;
}

#include "GameObject.h"

double GameObject::BASE_SIZE = 50;

GameObject::GameObject(QPointF start_point, QRectF rect, SpritesGroup group, ObjectType type, Direction dir) : QGraphicsRectItem(rect), sprites(group)
{
	object_type = type;
	setPos(start_point);
	this->dir = dir;
	setTransformOriginPoint(boundingRect().center());
	objectTimer = new QTimer();
	connect(objectTimer, &QTimer::timeout, this, &GameObject::updateObject);
	material = true;
	movable = false;
	rotateObject(0);
	last = std::chrono::steady_clock::now();
}

GameObject::~GameObject()
{

	for (int i = 0; i < sprites.countGroups(); i++)
	{
		sprites.setCurrentGroup(i);
		delete sprites.getCurrentGroup();
	}
	if (objectTimer->isActive())
		objectTimer->stop();
	delete objectTimer;
}

void GameObject::pressAction(QKeyEvent * e)
{
}

void GameObject::releaseAction(QKeyEvent * e)
{
}

void GameObject::paint(QPainter * qp, const QStyleOptionGraphicsItem * qopt, QWidget * parent)
{
	qp->drawImage(boundingRect(), *sprites.getCurrentGroup()->getCurList(), 
		QRectF(sprites.getCurrentGroupOffset(), 0, sprites.getCurrentGroup()->getFrameWidth(), 
			sprites.getCurrentGroup()->getFrameHeight())
	);
}

void GameObject::startObjectUpdating()
{
	if (objectTimer)
		objectTimer->start(2);
}

void GameObject::stopObjectUpdating()
{
	if (objectTimer)
		objectTimer->stop();
}

void GameObject::rotateObject(double angle)
{
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

void GameObject::interactObjects()
{
}

void GameObject::updateSlot()
{
	updateObject();
}

bool GameObject::isMovable()
{
	return movable;
}

bool GameObject::isMaterial()
{
	return material;
}

bool GameObject::inSceneRect()
{
	auto _rect = rect();
	_rect.moveTo(pos());
	return scene()->sceneRect().contains(_rect);
}

bool GameObject::isUpdating()
{
	if(objectTimer)
		return objectTimer->isActive();
	return false;
}

int GameObject::getBASE_SIZE()
{
	return BASE_SIZE;
}

GameObject::ObjectType GameObject::getObjectType()
{
	return object_type;
}

void GameObject::deleteFromMap()
{
	auto _scene = scene();
	int type = (int)object_type;
	deleteLater();
	qApp->sendEvent(_scene, new ObjectDestroyEvent(type));
}

double GameObject::elapsed()
{
	std::chrono::steady_clock::time_point next = std::chrono::steady_clock::now();
	int d = std::chrono::duration_cast<std::chrono::milliseconds>(next - last).count();
	last = next;
	return d;
}

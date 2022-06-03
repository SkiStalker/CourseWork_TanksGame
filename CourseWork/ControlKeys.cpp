#include "ControlKeys.h"

ControlKeys::ControlKeys(): initializate(false)
{

}

ControlKeys::ControlKeys(Key up, Key right, Key down, Key left, Key fire)
	: up(up), down(down), left(left), right(right), fire(fire), initializate(true)
{
}

Key ControlKeys::getUpKey()
{
	return up;
}

Key ControlKeys::getDownKey()
{
	return down;
}

Key ControlKeys::getLeftKey()
{
	return left;
}

Key ControlKeys::getRightKey()
{
	return right;
}

Key ControlKeys::getFireKey()
{
	return fire;
}

bool ControlKeys::isInit()
{
	return initializate;
}

QDataStream & operator<<(QDataStream & stream, ControlKeys & obj)
{
	stream << (int)obj.up << (int)obj.down << (int)obj.right << (int)obj.left << (int)obj.fire;
	return stream;
}

QDataStream & operator>>(QDataStream & stream, ControlKeys & obj)
{
	int up, down, right, left, fire;

	stream >> up >> down >> right >> left >> fire;

	obj = ControlKeys((Qt::Key)up, (Qt::Key) right, (Qt::Key)down, (Qt::Key)left, (Qt::Key)fire);
	return stream;
}

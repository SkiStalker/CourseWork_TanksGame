#include "ObjectDestroyEvent.h"

ObjectDestroyEvent::ObjectDestroyEvent(int obj) : QEvent(QEvent::Type::None)
{
	object = obj;
}

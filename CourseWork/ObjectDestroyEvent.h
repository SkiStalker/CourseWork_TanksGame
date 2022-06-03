#pragma once
#include <qcoreevent.h>

// Класс события уничтожения объекта на игровой сцене
class ObjectDestroyEvent :
	public QEvent
{
public:
	// Конструктор
	// int obj - тип объекта в int
	ObjectDestroyEvent(int obj);

	int object;
};


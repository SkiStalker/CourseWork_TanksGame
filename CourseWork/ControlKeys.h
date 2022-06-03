#pragma once
#include "INCLUDES_QT.h"

using namespace Qt;

// Класс кнопок управления танком
class ControlKeys
{
public:
	// Конструктор неинициализированного класса
	ControlKeys();

	// Конструктор
	ControlKeys(Key up, Key right, Key down, Key left, Key fire);

	// Получение значения для up
	Key getUpKey();

	// Получение значения для down
	Key getDownKey();

	// Получение значения для left
	Key getLeftKey();

	// Получение значения для right
	Key getRightKey();

	// Получение значения для fire
	Key getFireKey();

	// Запись в поток объекта
	// QDataStream& stream - поток для записи
	// ControlKeys& obj - текущий объект
	friend QDataStream & operator << (QDataStream& stream, ControlKeys& obj);

	// Чтение объекта из потока
	// QDataStream& stream - поток для чтения
	// ControlKeys& obj - текущий объект
	friend QDataStream & operator >> (QDataStream& stream, ControlKeys& obj);

	// Инициализирован ли объект
	bool isInit();
	
private:
	bool initializate;
	Key up;
	Key right;
	Key down;
	Key left;
	Key fire;
};



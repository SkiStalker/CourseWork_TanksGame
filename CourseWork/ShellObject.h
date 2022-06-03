#pragma once
#include "GameObject.h"


class ShellObject :
	public GameObject
{
public:

	// Деструктор
	~ShellObject();

	// Обновление состояния объекта
	void updateObject() override;

	// Провзаимодействовать с другими объектами
	void interactObjects() override;

	// Получение объекта снаряда
	// QPointF start_point - начальная позиция
	// GameObject::Direction dir - направление полета
	static ShellObject* getShell(QPointF start_point, GameObject::Direction dir);

	// Запись в поток текущего объекта
	// QDataStream & stream - поток для записи
	void writeToStream(QDataStream & stream) override;

	// Чтение объекта из потока
	// QDataStream& stream - поток для чтения
	// EnvironmentObject*& obj - объект для инициализации
	friend QDataStream& operator >> (QDataStream& stream, ShellObject*& obj);



private:
	// Конструктор
	// QPointF start_point - начальная позиция
	// GameObject::Direction dir - направление полета
	ShellObject(QPointF start_point, Direction dir);

	// Функция передвижения объекта
	// в соответствии с его направлением и скоростью
	void ride();

	// Единичное перемещение объекта,
	// зависящее от dir
	QPointF moveByDir();

	// Начальная точка
	QPointF start_point;

	// Скорость передвижения
	double speed;
};


#pragma once
#include "GameField.h"
#include <QPushButton>

class ConstructorGameField :
	public GameField
{
	Q_OBJECT
public:
	
	// Стандартный QT констуктор
	// QWidget *parent - родитель класса
	ConstructorGameField(QWidget* parent = nullptr);

	// Деструктор
	~ConstructorGameField();

	// (Пустые потому что иначе будет вызываться 
	// обработка незапущенных объектов)
	// Считывание нажатия клавиш в текущем окне
	// QKeyEvent * e - событие нажатой клавиши
	void keyPressEvent(QKeyEvent* e) override;

	// Считывание "отпускания" клавиши мыши в текущем окне
	// QKeyEvent * e - событие отпущенной клавиши
	void keyReleaseEvent(QKeyEvent * e) override;

	// Событие нажатия кнопки мыши
	// QGraphicsSceneMouseEvent *mouseEvent * ev - Событие мыши
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	// Событие "отпускания" кнопки мыши
	// QMouseEvent * ev - Событие мыши - Событие мыши
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	// Событие двойного нажатия кнопки мыши
	// QGraphicsSceneMouseEvent *mouseEvent - Событие мыши
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	// Событие движения мышью
	// QGraphicsSceneMouseEvent *mouseEvent - Событие мыши
	void mouseMoveEvent(QGraphicsSceneMouseEvent * ev) override;

	// Задание элемента для строительства
	// int selected - номер элемента
	void setSelectedItem(int selected);

	// Внешняя функция для добавления оюъекта на сцену
	// QPoint start_point - начальная точка
	// GameObject::ObjectType type - тип объекта
	// GameObject::Direction dir - ориентация объекта (в пространстве)
	void addObject(QPoint start_point, GameObject::ObjectType type, GameObject::Direction dir);

	// Смена ориентации объекта на карте
	// GameObject::Direction dir - ориентация объекта
	void setDirection(GameObject::Direction dir);

	// Получение ориентации текущего объекта
	GameObject::Direction getDirection();

	// Функция записи состояния сцены в поток
	// QDataStream& stream - ссылка на поток
	// ConstructorGameField & field - ссылка на объект
	friend QDataStream& operator << (QDataStream& stream, ConstructorGameField & field);

signals:

	void escape_clicked();

private:

	// Функция проверки на принадлежность объекта к стандартному набору
	// QGraphicsItem* item - объект
	bool notStandartItem(QGraphicsItem* item);

	// Переменная отображающее состояние кнопки мыши
	bool pressed;

	// Проверка наличия других объектов в педполагаемом месте размещения
	// текущего объекта
	// QPointF point - Нормализированная точка отсчета для rect
	// GameObject::ObjectType type - тип объекта
	// GameObject::Direction dir - направление объекта
	bool noItemsInBoundRect(QPointF point, GameObject::ObjectType type, 
		GameObject::Direction dir = GameObject::Direction::Up);

	// Нормализация точки на карте
	// QPointF point - точка
	QPointF normalizePos(QPointF point);

	// Нормализация точки на карте с двойной точностью
	// QPointF point - точка
	QPointF normalizePosHalf(QPointF point);

	// Текущий объект для строительства
	int selected;

	// Ориентация текущего объекта
	GameObject::Direction dir;
};


#pragma once
#include "GameObject.h"
#include "ShellObject.h"
#include "EnvironmentObject.h"


class TankObject;

// Класс искусственного интеллекта танка бота
class II
{
public:
	// Конструктор
	// TankObject * tank - объект для обработки
	II(TankObject * tank);

	// Функция принятия решения
	void think();

private:
	// Количество выстрелов подряд
	int shots;

	// Количество поворотов подряд
	int rotations;

	// Объект для обработки
	TankObject * tank = nullptr;

	// Область перед объектом обработки
	QPolygonF getPolygon();
};

// Игровой объект представляющий танк на игровом поле
class TankObject :
	public GameObject
{
	friend class II;

	Q_OBJECT
public:
	// Деструктор
	~TankObject();

	// Обновление состояния объекта
	void updateObject() override;

	// Действие при нажатии кнпоки клавиатуры
	// QKeyEvent* e - событие клавиатуры
	void pressAction(QKeyEvent* e) override;

	// Действие при отпускании кнпоки клавиатуры
	// QKeyEvent* e - событие клавиатуры
	void releaseAction(QKeyEvent* e) override;

	// Запись в поток объекта
	// QDataStream & stream - поток для записи
	void writeToStream(QDataStream & stream) override;

	// Чтение объекта из потока
	// QDataStream& stream - поток для чтения
	// EnvironmentObject*& obj - объект для инициализации
	friend QDataStream& operator >> (QDataStream& stream, TankObject*& obj);

	// Провзаимодействовать с другими объектами
	void interactObjects() override;

	// Получение объекта союзного танка
	// QPointF start_point - начальная позиция
	static TankObject* getMyTank(QPointF start_point);

	// Получение объекта вражеского танка
	// QPointF start_point - начальная позиция
	static TankObject* getEnemyTank(QPointF start_point);

	// Получение объекта танка бота
	// QPointF start_point - начальная позиция
	static TankObject* getBotTank(QPointF start_point);

	// Получение объекта быстрого танка бота
	// QPointF start_point - начальная позиция
	static TankObject* getBotFastTank(QPointF start_point);

	// Получение объекта тяжелого танка бота
	// QPointF start_point - начальная позиция
	static TankObject* getBotHeavyTank(QPointF start_point);

public slots:
	// Слот таймера "думания" ии
	void iiTimerEvent();

private:

	// Таймер "мыслей" ии
	QTimer iitimer;

	// Объект искусственного интеллекта
	II * ii = nullptr;

	// Конструктор
	// ObjectType type - тип объекта
	// QPointF start_point - позиция объекта
	// ControlKeys keys - кнопки управления танком
	// SpritesGroup group - группа спрайтов для объекта
	// Direction dir - направление объекта
	// int health - жизни танка
	// double speed - скорость передвижения
	TankObject(ObjectType type, QPointF start_point, ControlKeys keys,
		SpritesGroup group, Direction dir = Direction::Up, int health = 1, double speed = 3.0);

	// Отталкивание от объекта с которым объект столкнулся
	void pushAway(GameObject* item);

	// Поворот такнка
	// double angle - угол поворота
	virtual void rotateObject(double angle);

	// Жизни
	int health;

	// Выстрел
	void shot();

	// Кнопки управления
	ControlKeys keys;

	// Функция передвижения объекта
	// в соответствии с его направлением и скоростью
	void ride();

	// Единичное перемещение объекта,
	// зависящее от dir
	QPointF moveByDir();

	// Текущая скорость
	double speed;

	// Максимальная скорость
	double max_speed;

	// Функция смерти
	void die();
};


#pragma once
#include "INCLUDES_QT.h"
#include "Sprite.h"
#include "ControlKeys.h"
#include "ObjectDestroyEvent.h"


// Базовый абстракный класс игрового объекта
class GameObject:public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	// Типы объектов
	enum class ObjectType;

	// Ориентация объекта
	enum class Direction;

	// Конструктор объекта
	// QPointF start_point - позиция объекта
	// SpritesGroup group - группа спрайтов для объекта
	// QRectF rect - прямоугольник коллизий объекта
	// ObjectType type - тип объекта
	// Direction dir - направление объекта
	GameObject(QPointF start_point, QRectF rect, SpritesGroup group, ObjectType type, Direction dir);
	
	// Деструктор объекта
	~GameObject();


	enum class Direction
	{
		Up,
		Right,
		Down,
		Left
	};

	enum class ObjectType
	{
		MyTank,
		EnemyTank,
		BotTank,
		Brick,
		MyBase,
		EnemyBase,
		Shell,
		Wall,
		Water,
		Jungle
	};


	// Действие при нажатии кнпоки клавиатуры
	// QKeyEvent* e - событие клавиатуры
	void virtual pressAction(QKeyEvent* e);

	// Действие при отпускании кнпоки клавиатуры
	// QKeyEvent* e - событие клавиатуры
	void virtual releaseAction(QKeyEvent* e);

	// Начало обработки событий объекта
	void startObjectUpdating();

	// Функция обработки событий объекта
	void virtual updateObject() = 0;

	// Остановка обработки событий объекта
	void stopObjectUpdating();

	// Отрисовка объекта на карте
	virtual void paint(QPainter * qp, const QStyleOptionGraphicsItem * qopt, QWidget * parent) override;

	// Поворот объекта на заданый угол
	// double angle - угол
	virtual void rotateObject(double angle);

	// Взаимодействие с объектами
	virtual void interactObjects();

	// Может ли объект перемещаться
	bool isMovable();

	// Материален ли объект
	bool isMaterial();

	// Находится ли объект в поле видимости
	bool inSceneRect();

	// Активен ли объект
	bool isUpdating();

	// Переменная базовой единицы измерения
	static int getBASE_SIZE();

	// Получение типа объекта
	ObjectType getObjectType();

	// Запись в поток объекта
	// QDataStream & stream - поток для записи
	// (не << потому то так сложились звезды)
	virtual void writeToStream(QDataStream & stream) = 0;


	// Удаление объекта со сцены с сообщением
	// о его удалении игровому полю
	void deleteFromMap();


public slots:
	// Слот для обновления объекта
	void updateSlot();

protected:
	// Базовая единица измерения
	static double BASE_SIZE;

	// Тип объекта
	ObjectType object_type;

	// Таймер обновления объекта
	QTimer *objectTimer = nullptr;

	// Спрайты объекта
	SpritesGroup sprites;

	// Ориентация объекта
	Direction dir;

	// Время последнего вызова elapsed()
	std::chrono::steady_clock::time_point last;

	// Получение прошедшего времени с прошлого использования elapsed()
	double elapsed();

	// Материальность объекта
	bool material;

	// Подвижность объекта
	bool movable;
};


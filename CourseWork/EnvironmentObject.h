#pragma once
#include "GameObject.h"

// Игровой объект представляющий окружение на карте
class EnvironmentObject :
	public GameObject
{
public:
	// Дестуктор
	~EnvironmentObject();
	
	// Обновление состояния объекта
	void updateObject() override;

	// Провзаимодействовать с другими объектами
	void interactObjects() override;

	// Получение объекта типа Brick
	// QPointF start_point - координаты объекта
	// Direction dir - направление лбъекта
	static EnvironmentObject* getBrick(QPointF start_point, Direction dir);

	// Получение объекта типа Wall
	// QPointF start_point - координаты объекта
	// Direction dir - направление лбъекта
	static EnvironmentObject* getWall(QPointF start_point, Direction dir);

	// Получение объекта типа Water
	// QPointF start_point - координаты объекта
	static EnvironmentObject* getWater(QPointF start_point);

	// Получение объекта типа Jungle
	// QPointF start_point - координаты объекта
	static EnvironmentObject* getJungle(QPointF start_point);

	// Получение объекта типа MyBase
	// QPointF start_point - координаты объекта
	static EnvironmentObject* getMyBase(QPointF start_point);

	// Получение объекта типа EnemyBase
	// QPointF start_point - координаты объекта
	static EnvironmentObject* getEnemyBase(QPointF start_point);

	// Запись в поток текущего объекта
	// QDataStream & stream - поток для записи
	void writeToStream(QDataStream & stream) override;

	// Разрушаемый ли объект
	bool isDestructible();

	// Чтение объекта из потока
	// QDataStream& stream - поток для чтения
	// EnvironmentObject*& obj - объект для инициализации
	friend QDataStream& operator >> (QDataStream& stream, EnvironmentObject*& obj);

private:
	// Приватный конструктор (чтобы не создать чего-нибудь не того)
	// ObjectType type - тип объекта
	// QPointF start_point - позиция объекта
	// SpritesGroup group - группа спрайтов для объекта
	// bool destructible - разрушаемый ли объект
	// bool material - материальный ли объект
	// Direction dir - направление объекта
	// QRectF rect - прямоугольник коллизий объекта
	EnvironmentObject(ObjectType type, QPointF start_point,
		SpritesGroup group, bool destructible, bool material, Direction dir = Direction::Up, 
		QRectF rect = QRectF(0, 0, GameObject::BASE_SIZE, GameObject::BASE_SIZE));

	// Разрушаемый ли объект
	bool destructible;
};


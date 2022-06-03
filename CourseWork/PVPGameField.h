#pragma once
#include "GameField.h"

// Класс реализующий игру против человека
class PVPGameField :
	public GameField
{
public:

	// Стандартный QT констуктор
	// QWidget *parent - родитель класса
	PVPGameField(QWidget* parent = nullptr);

	// Деструктор
	~PVPGameField();

	// Обработка всех событий окна
	// Используется для обработки уничтожения GameObject
	// на карте
	// QEvent *e - событие
	bool event(QEvent *ev) override;

	// Загрузка карты из файла
	// QString name - имя файла
	void loadMapFromFile(QString name);

private:

	// Считывание объекта из потока по его типу
	// QDataStream & stream - поток
	// GameObject::ObjectType type - тип объекта
	void readByType(QDataStream & stream, GameObject::ObjectType type);

	// Победа нижнего игрока
	void meWin();

	// Победа верхнего игрока
	void enemyWin();
};


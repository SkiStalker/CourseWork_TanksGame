#pragma once
#include "GameField.h"
#include "InfoPanel.h"


// Класс реализующий игру против бота
class PVEGameField :
	public GameField
{

	Q_OBJECT
public:
	// Стандартный QT констуктор
	// QWidget *parent - родитель класса
	PVEGameField(InfoPanel * info, QWidget * parent = nullptr);

	// Деструктор
	~PVEGameField();

	// Обработка всех событий окна
	// Используется для обработки уничтожения GameObject
	// на карте
	// QEvent *e - событие
	bool event(QEvent *ev) override;

	// Загрузка карты из файла
	// QString name - имя файла
	void loadMapFromFile(QString name);


private:
	// Мютекс для предотвращения обновления удаляемого объекта
	QMutex m;

	// Переменная отражающая, добавляется ли сейчас объект на сцену
	int added = 0;

	// Панель для отображения счета
	InfoPanel* info;

	// Количество оставшихся танков ботов
	int cntBotTank;
	int cntFastBotTank;
	int cntHeavyBotTank;
	int cntBots;

	// Номер текущего спавна ботов
	int curspawn;

	// Задание сложности игры
	// int ID - сложность
	void setDifficulty(int ID);

	// Спавн бота танка
	GameObject* spawnBotTank();

	// Победа
	void win();

	// Поражение
	void lose();

	// Сложность текущей игры
	// (ID потому что лучше difficulty)
	int ID;

	// Считывание объекта из потока по его типу
	// QDataStream & stream - поток
	// GameObject::ObjectType type - тип объекта
	void readByType(QDataStream & stream, GameObject::ObjectType type);
};


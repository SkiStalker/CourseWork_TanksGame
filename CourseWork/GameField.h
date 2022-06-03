#pragma once
#include "INCLUDES_QT.h"

#include "GameObject.h"
#include "TankObject.h"
#include "EnvironmentObject.h"

#include "ObjectDestroyEvent.h"

// Класс реализации игрового поля
class GameField: public QGraphicsScene
{
	Q_OBJECT

public :

	// Стандартный QT констуктор
	// QWidget *parent - родитель класса
	GameField(QWidget* parent = Q_NULLPTR);

	// Деструктор
	~GameField();

	// Обработка всех событий окна
	// QEvent *event - событие
	virtual bool event(QEvent *event) override;

	// Считывание нажатия клавиш в текущем окне
	// QKeyEvent * e - событие нажатой клавиши
	void keyPressEvent(QKeyEvent* e) override;

	// Считывание "отпускания" клавиши мыши в текущем окне
	// QKeyEvent * e - событие отпущенной клавиши
	void keyReleaseEvent(QKeyEvent * e) override;

	// Пауза в игре
	void pause();

	// Отображение состояния игры
	bool isPaused();

	// Задание значение bool для обновления игровой сцены
	void setAlive(bool a);

signals:
	// Сигнал о закрытии текущей формы
	void closed();

	// Сигнал о вызове паузы
	void pauseClicked();

protected:
	// Значение обновления игрового поля
	bool alive = true;

	// Состояние игры
	bool paused;

};


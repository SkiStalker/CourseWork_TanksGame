#pragma once

#include "INCLUDES_QT.h"
#include "TankObject.h"

// Класс для отображения текущего счета в игре
class InfoPanel :
	public QGraphicsScene
{
public:

	// Конструктор
	InfoPanel();

	// Деструктор
	~InfoPanel();

	// Вывод информации о текущем счете игры
	void printInfo(int cntTank, int cntFTank, int cntHTank);

private:
	// Счет танков ботов
	QGraphicsTextItem* t;

	// Счет быстрых танков ботов
	QGraphicsTextItem* ft;

	// Счет тяжелых танков ботов
	QGraphicsTextItem* ht;
};


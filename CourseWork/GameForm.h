#pragma once

#include "INCLUDES_QT.h"
#include "ui_GameForm.h"
#include "PVEGameField.h"
#include "ConstructorGameField.h"
#include "InfoPanel.h"

namespace Ui { class GameForm; };


// Класс для отображения игрового процесса
class GameForm : public QWidget
{
	Q_OBJECT

public:

	// Стандартный QT констуктор
	// QWidget *parent - родитель класса
	GameForm(QWidget *parent = Q_NULLPTR);

	// Деструктор
	~GameForm();

	// Загрузка игрового поля 
	// (Оно происходит позже потому что так надо)
	// GameField* field - Игровое поле
	void setGameField(GameField* field);


	// Считывание нажатия клавиш в текущем окне
	// QKeyEvent * e - событие нажатой клавиши
	void keyPressEvent(QKeyEvent * e);

	// Панель для отображения текущего счета
	InfoPanel *infoScene = nullptr;

	// Получения виджета отображения игровой сцены
	// (Мне было лень разбираться и я сделал так)
	QWidget* getGraphicsView();


public slots:
	// Слот для паузы в игровом процессе
	void pause();

	// Слот завершения игры
	void gameClosed();

signals:
	// Сигнал о необходимости закрыть текущую форму
	void closed();

private:

	// Пользовательский интерфейс
	Ui::GameForm *ui = nullptr;

	// Игровое поле
	GameField * gfield = nullptr;
};

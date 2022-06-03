#pragma once

#include "INCLUDES_QT.h"
#include "ui_TanksGame.h"
#include "PVEMenuForm.h"
#include "PVPGameField.h"
#include "ConForm.h"
#include "GameForm.h"
#include "Help.h"

// Класс главного окна игры, унаследованный от QMainWindow
class TanksGame : public QMainWindow
{
    Q_OBJECT

public:
	// Конструктор, созданный QT автоматически
	// QWidget *parent - родитель класса
    TanksGame(QWidget *parent = Q_NULLPTR);

	// Обработка нажатия клавиш в главном окне
	// QKeyEvent * e - событие нажатой клавиши
	void keyPressEvent(QKeyEvent * e) override;

public slots:
	// Слот для нажатой pve кнопки
	// Открывает pve меню выбора уровня
	void pveButton_clicked();

	// Слот для нажатой pvp кнопки
	// Запускает игру против человека
	void pvpButton_clicked();

	// Слот для нажатой con кнопки
	// Запускает конструктор карт
	void conButton_clicked();

	// Слот для закрытия окна pvemenu
	void pvemenu_closed();

	// Слот для закрытия окна конструктора карт
	void conFrom_closed();

	// Слот для закрытия 
	void pvpGame_closed();

	// Сохранение карты созданной в конструкторе карт
	void sceneSave();

	// Слот для выведения help сообщения
	void helpAct();

	// Слот для выведения about сообщения
	void aboutAct();



private:
	// Действие сохранения карты
	QAction * saveAct = nullptr;

	// Пользовательский интерфейс
    Ui::TanksGameClass ui;

	// Форма конструктора карт
	ConForm* conForm = nullptr;

	// Форма выбора pve уровня
	PVEMenuForm* pvemenu = nullptr;

	// Форма игрового процесса
	GameForm* gameForm = nullptr;
};

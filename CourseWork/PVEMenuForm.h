#pragma once

#include <QWidget>
#include "ui_PVEMenu.h"
#include "GameForm.h"
#include "INCLUDES_QT.h"


// Класс выбора уровня для pve игры
class PVEMenuForm : public QWidget
{
	Q_OBJECT

public:
	// Стандартный QT констуктор
	// QWidget *parent - родитель класса
	PVEMenuForm(QWidget *parent = Q_NULLPTR);

	// Деструктор
	~PVEMenuForm();

	// Считывание нажатия клавиш в текущем окне
	// QKeyEvent * e - событие нажатой клавиши
	void keyPressEvent(QKeyEvent* ev) override;


public slots:
	// Загрузка первого уровня игры
	void button1_clicked();

	// Загрузка первого уровня игры
	void button2_clicked();

	// Загрузка первого уровня игры
	void button3_clicked();

	// Загрузка первого уровня игры
	void button4_clicked();

	// Загрузка первого уровня игры
	void button5_clicked();

	// Загрузка пользовательского уровня игры
	// Файл *.save открвается через встроенные стредства
	void button_user_clicked();

	// Слот возврата в главное меню
	void close_click();

	// Слот завершения игры
	void gameFormClosed();
	
signals:
	// Сигнал о необходимости закрыть текущую форму
	void closed();

private:

	// Общая функция загрузки игрового поля из файла
	void loadGame(QString filename);

	// Форма для игры
	GameForm *gameForm = nullptr;

	// Пользовательский интерфейс
	Ui::PVEMenu ui;
};

#pragma once

#include "INCLUDES_QT.h"
#include "ui_Help.h"

// Класс окна с информацией
class Help : public QDialog
{
	Q_OBJECT

public:
	// Стандартный QT констуктор
	// QWidget *parent - родитель класса
	Help(QWidget *parent = Q_NULLPTR);

	// Деструктор
	~Help();




private:

	// Пользовательский интерфейс
	Ui::Help ui;
};

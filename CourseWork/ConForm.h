#pragma once

#include "INCLUDES_QT.h"
#include "ui_ConForm.h"
#include "ConstructorGameField.h"


// Класс для отображения конструктора карт
class ConForm : public QWidget
{
	Q_OBJECT

public:

	// Стандартный QT констуктор
    // QWidget *parent - родитель класса
	ConForm(QWidget *parent = Q_NULLPTR);

	// Деструктор
	~ConForm();

	// Событие нажатия кнопки мыши
	// QMouseEvent * ev - Событие мыши
	void mousePressEvent(QMouseEvent * ev) override;

	// Событие "отпускания" кнопки мыши
	// QMouseEvent * ev - Событие мыши
	void mouseReleaseEvent(QMouseEvent * ev) override;

	// Событие движения мышью
	// QMouseEvent * ev - Событие мыши
	void mouseMoveEvent(QMouseEvent * ev) override;

	// Считывание нажатия клавиш в текущем окне
	// QKeyEvent * e - событие нажатой клавиши
	void keyPressEvent(QKeyEvent* ev) override;

	// Сохранение созданной карты в файл встроенными средствами
	void saveScene();


public slots:

	// Слот предварительного выхода из конструктора
	void escape();

	// Слот поворота кирпичей и стены на 90
	void rotate();

	// (Просто анрил костыли, из за передачи в scene)

	// Слот выбора 1 пункта в конструкторе
	void rb_released();

	// Слот выбора 2 пункта в конструкторе
	void rb2_released();

	// Слот выбора 3 пункта в конструкторе
	void rb3_released();

	// Слот выбора 4 пункта в конструкторе
	void rb4_released();

	// Слот выбора 5 пункта в конструкторе
	void rb5_released();

signals:
	// Сигнал о необходимости закрыть текущую форму
	void closed();

private:

	// Функция объединяющая connect-ы check-ов со слотами
	void connectRButtons();

	// Добавление стандартного наполнения на карту
	// ConstructorGameField* scene - карта куда добавляем
	void addDefaultItems(ConstructorGameField* scene);

	// Пользовательский интерфейс
	Ui::ConForm ui;
};

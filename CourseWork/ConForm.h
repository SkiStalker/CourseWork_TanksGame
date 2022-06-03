#pragma once

#include "INCLUDES_QT.h"
#include "ui_ConForm.h"
#include "ConstructorGameField.h"


// ����� ��� ����������� ������������ ����
class ConForm : public QWidget
{
	Q_OBJECT

public:

	// ����������� QT ����������
    // QWidget *parent - �������� ������
	ConForm(QWidget *parent = Q_NULLPTR);

	// ����������
	~ConForm();

	// ������� ������� ������ ����
	// QMouseEvent * ev - ������� ����
	void mousePressEvent(QMouseEvent * ev) override;

	// ������� "����������" ������ ����
	// QMouseEvent * ev - ������� ����
	void mouseReleaseEvent(QMouseEvent * ev) override;

	// ������� �������� �����
	// QMouseEvent * ev - ������� ����
	void mouseMoveEvent(QMouseEvent * ev) override;

	// ���������� ������� ������ � ������� ����
	// QKeyEvent * e - ������� ������� �������
	void keyPressEvent(QKeyEvent* ev) override;

	// ���������� ��������� ����� � ���� ����������� ����������
	void saveScene();


public slots:

	// ���� ���������������� ������ �� ������������
	void escape();

	// ���� �������� �������� � ����� �� 90
	void rotate();

	// (������ ����� �������, �� �� �������� � scene)

	// ���� ������ 1 ������ � ������������
	void rb_released();

	// ���� ������ 2 ������ � ������������
	void rb2_released();

	// ���� ������ 3 ������ � ������������
	void rb3_released();

	// ���� ������ 4 ������ � ������������
	void rb4_released();

	// ���� ������ 5 ������ � ������������
	void rb5_released();

signals:
	// ������ � ������������� ������� ������� �����
	void closed();

private:

	// ������� ������������ connect-� check-�� �� �������
	void connectRButtons();

	// ���������� ������������ ���������� �� �����
	// ConstructorGameField* scene - ����� ���� ���������
	void addDefaultItems(ConstructorGameField* scene);

	// ���������������� ���������
	Ui::ConForm ui;
};

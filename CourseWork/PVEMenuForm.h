#pragma once

#include <QWidget>
#include "ui_PVEMenu.h"
#include "GameForm.h"
#include "INCLUDES_QT.h"


// ����� ������ ������ ��� pve ����
class PVEMenuForm : public QWidget
{
	Q_OBJECT

public:
	// ����������� QT ����������
	// QWidget *parent - �������� ������
	PVEMenuForm(QWidget *parent = Q_NULLPTR);

	// ����������
	~PVEMenuForm();

	// ���������� ������� ������ � ������� ����
	// QKeyEvent * e - ������� ������� �������
	void keyPressEvent(QKeyEvent* ev) override;


public slots:
	// �������� ������� ������ ����
	void button1_clicked();

	// �������� ������� ������ ����
	void button2_clicked();

	// �������� ������� ������ ����
	void button3_clicked();

	// �������� ������� ������ ����
	void button4_clicked();

	// �������� ������� ������ ����
	void button5_clicked();

	// �������� ����������������� ������ ����
	// ���� *.save ���������� ����� ���������� ���������
	void button_user_clicked();

	// ���� �������� � ������� ����
	void close_click();

	// ���� ���������� ����
	void gameFormClosed();
	
signals:
	// ������ � ������������� ������� ������� �����
	void closed();

private:

	// ����� ������� �������� �������� ���� �� �����
	void loadGame(QString filename);

	// ����� ��� ����
	GameForm *gameForm = nullptr;

	// ���������������� ���������
	Ui::PVEMenu ui;
};

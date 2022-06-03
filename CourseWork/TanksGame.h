#pragma once

#include "INCLUDES_QT.h"
#include "ui_TanksGame.h"
#include "PVEMenuForm.h"
#include "PVPGameField.h"
#include "ConForm.h"
#include "GameForm.h"
#include "Help.h"

// ����� �������� ���� ����, �������������� �� QMainWindow
class TanksGame : public QMainWindow
{
    Q_OBJECT

public:
	// �����������, ��������� QT �������������
	// QWidget *parent - �������� ������
    TanksGame(QWidget *parent = Q_NULLPTR);

	// ��������� ������� ������ � ������� ����
	// QKeyEvent * e - ������� ������� �������
	void keyPressEvent(QKeyEvent * e) override;

public slots:
	// ���� ��� ������� pve ������
	// ��������� pve ���� ������ ������
	void pveButton_clicked();

	// ���� ��� ������� pvp ������
	// ��������� ���� ������ ��������
	void pvpButton_clicked();

	// ���� ��� ������� con ������
	// ��������� ����������� ����
	void conButton_clicked();

	// ���� ��� �������� ���� pvemenu
	void pvemenu_closed();

	// ���� ��� �������� ���� ������������ ����
	void conFrom_closed();

	// ���� ��� �������� 
	void pvpGame_closed();

	// ���������� ����� ��������� � ������������ ����
	void sceneSave();

	// ���� ��� ��������� help ���������
	void helpAct();

	// ���� ��� ��������� about ���������
	void aboutAct();



private:
	// �������� ���������� �����
	QAction * saveAct = nullptr;

	// ���������������� ���������
    Ui::TanksGameClass ui;

	// ����� ������������ ����
	ConForm* conForm = nullptr;

	// ����� ������ pve ������
	PVEMenuForm* pvemenu = nullptr;

	// ����� �������� ��������
	GameForm* gameForm = nullptr;
};

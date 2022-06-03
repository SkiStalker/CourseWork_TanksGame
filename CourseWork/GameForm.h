#pragma once

#include "INCLUDES_QT.h"
#include "ui_GameForm.h"
#include "PVEGameField.h"
#include "ConstructorGameField.h"
#include "InfoPanel.h"

namespace Ui { class GameForm; };


// ����� ��� ����������� �������� ��������
class GameForm : public QWidget
{
	Q_OBJECT

public:

	// ����������� QT ����������
	// QWidget *parent - �������� ������
	GameForm(QWidget *parent = Q_NULLPTR);

	// ����������
	~GameForm();

	// �������� �������� ���� 
	// (��� ���������� ����� ������ ��� ��� ����)
	// GameField* field - ������� ����
	void setGameField(GameField* field);


	// ���������� ������� ������ � ������� ����
	// QKeyEvent * e - ������� ������� �������
	void keyPressEvent(QKeyEvent * e);

	// ������ ��� ����������� �������� �����
	InfoPanel *infoScene = nullptr;

	// ��������� ������� ����������� ������� �����
	// (��� ���� ���� ����������� � � ������ ���)
	QWidget* getGraphicsView();


public slots:
	// ���� ��� ����� � ������� ��������
	void pause();

	// ���� ���������� ����
	void gameClosed();

signals:
	// ������ � ������������� ������� ������� �����
	void closed();

private:

	// ���������������� ���������
	Ui::GameForm *ui = nullptr;

	// ������� ����
	GameField * gfield = nullptr;
};

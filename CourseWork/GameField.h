#pragma once
#include "INCLUDES_QT.h"

#include "GameObject.h"
#include "TankObject.h"
#include "EnvironmentObject.h"

#include "ObjectDestroyEvent.h"

// ����� ���������� �������� ����
class GameField: public QGraphicsScene
{
	Q_OBJECT

public :

	// ����������� QT ����������
	// QWidget *parent - �������� ������
	GameField(QWidget* parent = Q_NULLPTR);

	// ����������
	~GameField();

	// ��������� ���� ������� ����
	// QEvent *event - �������
	virtual bool event(QEvent *event) override;

	// ���������� ������� ������ � ������� ����
	// QKeyEvent * e - ������� ������� �������
	void keyPressEvent(QKeyEvent* e) override;

	// ���������� "����������" ������� ���� � ������� ����
	// QKeyEvent * e - ������� ���������� �������
	void keyReleaseEvent(QKeyEvent * e) override;

	// ����� � ����
	void pause();

	// ����������� ��������� ����
	bool isPaused();

	// ������� �������� bool ��� ���������� ������� �����
	void setAlive(bool a);

signals:
	// ������ � �������� ������� �����
	void closed();

	// ������ � ������ �����
	void pauseClicked();

protected:
	// �������� ���������� �������� ����
	bool alive = true;

	// ��������� ����
	bool paused;

};


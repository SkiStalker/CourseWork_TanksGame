#pragma once
#include "GameObject.h"
#include "ShellObject.h"
#include "EnvironmentObject.h"


class TankObject;

// ����� �������������� ���������� ����� ����
class II
{
public:
	// �����������
	// TankObject * tank - ������ ��� ���������
	II(TankObject * tank);

	// ������� �������� �������
	void think();

private:
	// ���������� ��������� ������
	int shots;

	// ���������� ��������� ������
	int rotations;

	// ������ ��� ���������
	TankObject * tank = nullptr;

	// ������� ����� �������� ���������
	QPolygonF getPolygon();
};

// ������� ������ �������������� ���� �� ������� ����
class TankObject :
	public GameObject
{
	friend class II;

	Q_OBJECT
public:
	// ����������
	~TankObject();

	// ���������� ��������� �������
	void updateObject() override;

	// �������� ��� ������� ������ ����������
	// QKeyEvent* e - ������� ����������
	void pressAction(QKeyEvent* e) override;

	// �������� ��� ���������� ������ ����������
	// QKeyEvent* e - ������� ����������
	void releaseAction(QKeyEvent* e) override;

	// ������ � ����� �������
	// QDataStream & stream - ����� ��� ������
	void writeToStream(QDataStream & stream) override;

	// ������ ������� �� ������
	// QDataStream& stream - ����� ��� ������
	// EnvironmentObject*& obj - ������ ��� �������������
	friend QDataStream& operator >> (QDataStream& stream, TankObject*& obj);

	// �������������������� � ������� ���������
	void interactObjects() override;

	// ��������� ������� �������� �����
	// QPointF start_point - ��������� �������
	static TankObject* getMyTank(QPointF start_point);

	// ��������� ������� ���������� �����
	// QPointF start_point - ��������� �������
	static TankObject* getEnemyTank(QPointF start_point);

	// ��������� ������� ����� ����
	// QPointF start_point - ��������� �������
	static TankObject* getBotTank(QPointF start_point);

	// ��������� ������� �������� ����� ����
	// QPointF start_point - ��������� �������
	static TankObject* getBotFastTank(QPointF start_point);

	// ��������� ������� �������� ����� ����
	// QPointF start_point - ��������� �������
	static TankObject* getBotHeavyTank(QPointF start_point);

public slots:
	// ���� ������� "�������" ��
	void iiTimerEvent();

private:

	// ������ "������" ��
	QTimer iitimer;

	// ������ �������������� ����������
	II * ii = nullptr;

	// �����������
	// ObjectType type - ��� �������
	// QPointF start_point - ������� �������
	// ControlKeys keys - ������ ���������� ������
	// SpritesGroup group - ������ �������� ��� �������
	// Direction dir - ����������� �������
	// int health - ����� �����
	// double speed - �������� ������������
	TankObject(ObjectType type, QPointF start_point, ControlKeys keys,
		SpritesGroup group, Direction dir = Direction::Up, int health = 1, double speed = 3.0);

	// ������������ �� ������� � ������� ������ ����������
	void pushAway(GameObject* item);

	// ������� ������
	// double angle - ���� ��������
	virtual void rotateObject(double angle);

	// �����
	int health;

	// �������
	void shot();

	// ������ ����������
	ControlKeys keys;

	// ������� ������������ �������
	// � ������������ � ��� ������������ � ���������
	void ride();

	// ��������� ����������� �������,
	// ��������� �� dir
	QPointF moveByDir();

	// ������� ��������
	double speed;

	// ������������ ��������
	double max_speed;

	// ������� ������
	void die();
};


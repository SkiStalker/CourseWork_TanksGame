#pragma once
#include "GameObject.h"

// ������� ������ �������������� ��������� �� �����
class EnvironmentObject :
	public GameObject
{
public:
	// ���������
	~EnvironmentObject();
	
	// ���������� ��������� �������
	void updateObject() override;

	// �������������������� � ������� ���������
	void interactObjects() override;

	// ��������� ������� ���� Brick
	// QPointF start_point - ���������� �������
	// Direction dir - ����������� �������
	static EnvironmentObject* getBrick(QPointF start_point, Direction dir);

	// ��������� ������� ���� Wall
	// QPointF start_point - ���������� �������
	// Direction dir - ����������� �������
	static EnvironmentObject* getWall(QPointF start_point, Direction dir);

	// ��������� ������� ���� Water
	// QPointF start_point - ���������� �������
	static EnvironmentObject* getWater(QPointF start_point);

	// ��������� ������� ���� Jungle
	// QPointF start_point - ���������� �������
	static EnvironmentObject* getJungle(QPointF start_point);

	// ��������� ������� ���� MyBase
	// QPointF start_point - ���������� �������
	static EnvironmentObject* getMyBase(QPointF start_point);

	// ��������� ������� ���� EnemyBase
	// QPointF start_point - ���������� �������
	static EnvironmentObject* getEnemyBase(QPointF start_point);

	// ������ � ����� �������� �������
	// QDataStream & stream - ����� ��� ������
	void writeToStream(QDataStream & stream) override;

	// ����������� �� ������
	bool isDestructible();

	// ������ ������� �� ������
	// QDataStream& stream - ����� ��� ������
	// EnvironmentObject*& obj - ������ ��� �������������
	friend QDataStream& operator >> (QDataStream& stream, EnvironmentObject*& obj);

private:
	// ��������� ����������� (����� �� ������� ����-������ �� ����)
	// ObjectType type - ��� �������
	// QPointF start_point - ������� �������
	// SpritesGroup group - ������ �������� ��� �������
	// bool destructible - ����������� �� ������
	// bool material - ������������ �� ������
	// Direction dir - ����������� �������
	// QRectF rect - ������������� �������� �������
	EnvironmentObject(ObjectType type, QPointF start_point,
		SpritesGroup group, bool destructible, bool material, Direction dir = Direction::Up, 
		QRectF rect = QRectF(0, 0, GameObject::BASE_SIZE, GameObject::BASE_SIZE));

	// ����������� �� ������
	bool destructible;
};


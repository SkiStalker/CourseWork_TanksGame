#pragma once
#include "GameObject.h"


class ShellObject :
	public GameObject
{
public:

	// ����������
	~ShellObject();

	// ���������� ��������� �������
	void updateObject() override;

	// �������������������� � ������� ���������
	void interactObjects() override;

	// ��������� ������� �������
	// QPointF start_point - ��������� �������
	// GameObject::Direction dir - ����������� ������
	static ShellObject* getShell(QPointF start_point, GameObject::Direction dir);

	// ������ � ����� �������� �������
	// QDataStream & stream - ����� ��� ������
	void writeToStream(QDataStream & stream) override;

	// ������ ������� �� ������
	// QDataStream& stream - ����� ��� ������
	// EnvironmentObject*& obj - ������ ��� �������������
	friend QDataStream& operator >> (QDataStream& stream, ShellObject*& obj);



private:
	// �����������
	// QPointF start_point - ��������� �������
	// GameObject::Direction dir - ����������� ������
	ShellObject(QPointF start_point, Direction dir);

	// ������� ������������ �������
	// � ������������ � ��� ������������ � ���������
	void ride();

	// ��������� ����������� �������,
	// ��������� �� dir
	QPointF moveByDir();

	// ��������� �����
	QPointF start_point;

	// �������� ������������
	double speed;
};


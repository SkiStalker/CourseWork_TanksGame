#pragma once
#include "INCLUDES_QT.h"

using namespace Qt;

// ����� ������ ���������� ������
class ControlKeys
{
public:
	// ����������� ��������������������� ������
	ControlKeys();

	// �����������
	ControlKeys(Key up, Key right, Key down, Key left, Key fire);

	// ��������� �������� ��� up
	Key getUpKey();

	// ��������� �������� ��� down
	Key getDownKey();

	// ��������� �������� ��� left
	Key getLeftKey();

	// ��������� �������� ��� right
	Key getRightKey();

	// ��������� �������� ��� fire
	Key getFireKey();

	// ������ � ����� �������
	// QDataStream& stream - ����� ��� ������
	// ControlKeys& obj - ������� ������
	friend QDataStream & operator << (QDataStream& stream, ControlKeys& obj);

	// ������ ������� �� ������
	// QDataStream& stream - ����� ��� ������
	// ControlKeys& obj - ������� ������
	friend QDataStream & operator >> (QDataStream& stream, ControlKeys& obj);

	// ��������������� �� ������
	bool isInit();
	
private:
	bool initializate;
	Key up;
	Key right;
	Key down;
	Key left;
	Key fire;
};



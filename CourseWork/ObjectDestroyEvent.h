#pragma once
#include <qcoreevent.h>

// ����� ������� ����������� ������� �� ������� �����
class ObjectDestroyEvent :
	public QEvent
{
public:
	// �����������
	// int obj - ��� ������� � int
	ObjectDestroyEvent(int obj);

	int object;
};


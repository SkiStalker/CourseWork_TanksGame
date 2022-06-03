#pragma once

#include "INCLUDES_QT.h"
#include "TankObject.h"

// ����� ��� ����������� �������� ����� � ����
class InfoPanel :
	public QGraphicsScene
{
public:

	// �����������
	InfoPanel();

	// ����������
	~InfoPanel();

	// ����� ���������� � ������� ����� ����
	void printInfo(int cntTank, int cntFTank, int cntHTank);

private:
	// ���� ������ �����
	QGraphicsTextItem* t;

	// ���� ������� ������ �����
	QGraphicsTextItem* ft;

	// ���� ������� ������ �����
	QGraphicsTextItem* ht;
};


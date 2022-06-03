#pragma once
#include "GameField.h"
#include "InfoPanel.h"


// ����� ����������� ���� ������ ����
class PVEGameField :
	public GameField
{

	Q_OBJECT
public:
	// ����������� QT ����������
	// QWidget *parent - �������� ������
	PVEGameField(InfoPanel * info, QWidget * parent = nullptr);

	// ����������
	~PVEGameField();

	// ��������� ���� ������� ����
	// ������������ ��� ��������� ����������� GameObject
	// �� �����
	// QEvent *e - �������
	bool event(QEvent *ev) override;

	// �������� ����� �� �����
	// QString name - ��� �����
	void loadMapFromFile(QString name);


private:
	// ������ ��� �������������� ���������� ���������� �������
	QMutex m;

	// ���������� ����������, ����������� �� ������ ������ �� �����
	int added = 0;

	// ������ ��� ����������� �����
	InfoPanel* info;

	// ���������� ���������� ������ �����
	int cntBotTank;
	int cntFastBotTank;
	int cntHeavyBotTank;
	int cntBots;

	// ����� �������� ������ �����
	int curspawn;

	// ������� ��������� ����
	// int ID - ���������
	void setDifficulty(int ID);

	// ����� ���� �����
	GameObject* spawnBotTank();

	// ������
	void win();

	// ���������
	void lose();

	// ��������� ������� ����
	// (ID ������ ��� ����� difficulty)
	int ID;

	// ���������� ������� �� ������ �� ��� ����
	// QDataStream & stream - �����
	// GameObject::ObjectType type - ��� �������
	void readByType(QDataStream & stream, GameObject::ObjectType type);
};


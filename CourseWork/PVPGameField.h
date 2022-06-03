#pragma once
#include "GameField.h"

// ����� ����������� ���� ������ ��������
class PVPGameField :
	public GameField
{
public:

	// ����������� QT ����������
	// QWidget *parent - �������� ������
	PVPGameField(QWidget* parent = nullptr);

	// ����������
	~PVPGameField();

	// ��������� ���� ������� ����
	// ������������ ��� ��������� ����������� GameObject
	// �� �����
	// QEvent *e - �������
	bool event(QEvent *ev) override;

	// �������� ����� �� �����
	// QString name - ��� �����
	void loadMapFromFile(QString name);

private:

	// ���������� ������� �� ������ �� ��� ����
	// QDataStream & stream - �����
	// GameObject::ObjectType type - ��� �������
	void readByType(QDataStream & stream, GameObject::ObjectType type);

	// ������ ������� ������
	void meWin();

	// ������ �������� ������
	void enemyWin();
};


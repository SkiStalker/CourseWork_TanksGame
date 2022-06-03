#pragma once
#include "GameField.h"
#include <QPushButton>

class ConstructorGameField :
	public GameField
{
	Q_OBJECT
public:
	
	// ����������� QT ����������
	// QWidget *parent - �������� ������
	ConstructorGameField(QWidget* parent = nullptr);

	// ����������
	~ConstructorGameField();

	// (������ ������ ��� ����� ����� ���������� 
	// ��������� ������������ ��������)
	// ���������� ������� ������ � ������� ����
	// QKeyEvent * e - ������� ������� �������
	void keyPressEvent(QKeyEvent* e) override;

	// ���������� "����������" ������� ���� � ������� ����
	// QKeyEvent * e - ������� ���������� �������
	void keyReleaseEvent(QKeyEvent * e) override;

	// ������� ������� ������ ����
	// QGraphicsSceneMouseEvent *mouseEvent * ev - ������� ����
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	// ������� "����������" ������ ����
	// QMouseEvent * ev - ������� ���� - ������� ����
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	// ������� �������� ������� ������ ����
	// QGraphicsSceneMouseEvent *mouseEvent - ������� ����
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	// ������� �������� �����
	// QGraphicsSceneMouseEvent *mouseEvent - ������� ����
	void mouseMoveEvent(QGraphicsSceneMouseEvent * ev) override;

	// ������� �������� ��� �������������
	// int selected - ����� ��������
	void setSelectedItem(int selected);

	// ������� ������� ��� ���������� ������� �� �����
	// QPoint start_point - ��������� �����
	// GameObject::ObjectType type - ��� �������
	// GameObject::Direction dir - ���������� ������� (� ������������)
	void addObject(QPoint start_point, GameObject::ObjectType type, GameObject::Direction dir);

	// ����� ���������� ������� �� �����
	// GameObject::Direction dir - ���������� �������
	void setDirection(GameObject::Direction dir);

	// ��������� ���������� �������� �������
	GameObject::Direction getDirection();

	// ������� ������ ��������� ����� � �����
	// QDataStream& stream - ������ �� �����
	// ConstructorGameField & field - ������ �� ������
	friend QDataStream& operator << (QDataStream& stream, ConstructorGameField & field);

signals:

	void escape_clicked();

private:

	// ������� �������� �� �������������� ������� � ������������ ������
	// QGraphicsItem* item - ������
	bool notStandartItem(QGraphicsItem* item);

	// ���������� ������������ ��������� ������ ����
	bool pressed;

	// �������� ������� ������ �������� � ������������� ����� ����������
	// �������� �������
	// QPointF point - ����������������� ����� ������� ��� rect
	// GameObject::ObjectType type - ��� �������
	// GameObject::Direction dir - ����������� �������
	bool noItemsInBoundRect(QPointF point, GameObject::ObjectType type, 
		GameObject::Direction dir = GameObject::Direction::Up);

	// ������������ ����� �� �����
	// QPointF point - �����
	QPointF normalizePos(QPointF point);

	// ������������ ����� �� ����� � ������� ���������
	// QPointF point - �����
	QPointF normalizePosHalf(QPointF point);

	// ������� ������ ��� �������������
	int selected;

	// ���������� �������� �������
	GameObject::Direction dir;
};


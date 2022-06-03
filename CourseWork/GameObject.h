#pragma once
#include "INCLUDES_QT.h"
#include "Sprite.h"
#include "ControlKeys.h"
#include "ObjectDestroyEvent.h"


// ������� ���������� ����� �������� �������
class GameObject:public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	// ���� ��������
	enum class ObjectType;

	// ���������� �������
	enum class Direction;

	// ����������� �������
	// QPointF start_point - ������� �������
	// SpritesGroup group - ������ �������� ��� �������
	// QRectF rect - ������������� �������� �������
	// ObjectType type - ��� �������
	// Direction dir - ����������� �������
	GameObject(QPointF start_point, QRectF rect, SpritesGroup group, ObjectType type, Direction dir);
	
	// ���������� �������
	~GameObject();


	enum class Direction
	{
		Up,
		Right,
		Down,
		Left
	};

	enum class ObjectType
	{
		MyTank,
		EnemyTank,
		BotTank,
		Brick,
		MyBase,
		EnemyBase,
		Shell,
		Wall,
		Water,
		Jungle
	};


	// �������� ��� ������� ������ ����������
	// QKeyEvent* e - ������� ����������
	void virtual pressAction(QKeyEvent* e);

	// �������� ��� ���������� ������ ����������
	// QKeyEvent* e - ������� ����������
	void virtual releaseAction(QKeyEvent* e);

	// ������ ��������� ������� �������
	void startObjectUpdating();

	// ������� ��������� ������� �������
	void virtual updateObject() = 0;

	// ��������� ��������� ������� �������
	void stopObjectUpdating();

	// ��������� ������� �� �����
	virtual void paint(QPainter * qp, const QStyleOptionGraphicsItem * qopt, QWidget * parent) override;

	// ������� ������� �� ������� ����
	// double angle - ����
	virtual void rotateObject(double angle);

	// �������������� � ���������
	virtual void interactObjects();

	// ����� �� ������ ������������
	bool isMovable();

	// ���������� �� ������
	bool isMaterial();

	// ��������� �� ������ � ���� ���������
	bool inSceneRect();

	// ������� �� ������
	bool isUpdating();

	// ���������� ������� ������� ���������
	static int getBASE_SIZE();

	// ��������� ���� �������
	ObjectType getObjectType();

	// ������ � ����� �������
	// QDataStream & stream - ����� ��� ������
	// (�� << ������ �� ��� ��������� ������)
	virtual void writeToStream(QDataStream & stream) = 0;


	// �������� ������� �� ����� � ����������
	// � ��� �������� �������� ����
	void deleteFromMap();


public slots:
	// ���� ��� ���������� �������
	void updateSlot();

protected:
	// ������� ������� ���������
	static double BASE_SIZE;

	// ��� �������
	ObjectType object_type;

	// ������ ���������� �������
	QTimer *objectTimer = nullptr;

	// ������� �������
	SpritesGroup sprites;

	// ���������� �������
	Direction dir;

	// ����� ���������� ������ elapsed()
	std::chrono::steady_clock::time_point last;

	// ��������� ���������� ������� � �������� ������������� elapsed()
	double elapsed();

	// �������������� �������
	bool material;

	// ����������� �������
	bool movable;
};


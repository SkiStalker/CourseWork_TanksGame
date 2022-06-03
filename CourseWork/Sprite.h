#pragma once
#include "INCLUDES_QT.h"

// ����� ��������
class Image : public QImage
{
public:
	// �����������
	// const QString & filename - ������������ ��������
	Image(const QString & filename);

	// ����������
	~Image();
	QString name;
};

// ����� ��������
class Sprites
{
public:
	// ������������
	// Image* list - ��������� �� ���������� ����������
	// int update_interval - ����� ������������ ����� �������
	// int frame_width - ������ �����
	// int frame_height - ������ �����
	Sprites(Image* list, int update_interval, int frame_width);
	Sprites(Image* list, int update_interval, int frame_width, int frame_height);

	// ����������
	~Sprites();

	// ���������� ������� ���������� �������
	void restart();

	// ���������� ���������� �������
	void incCurrentTime();

	// �������� �� ��, ������ �� ������ ������
	bool isPeriod();

	// ������� ������� ������
	void setPeriod(int n);

	// ��������� ������� ������
	int getPeriod();

	// ������� ������ ����� 
	void setFrameWidth(int width);

	// ��������� ������ ����� 
	int getFrameWidth();

	// ������� ������ ����� 
	void setFrameHeight(int height);

	// ��������� ������ ����� 
	int getFrameHeight();

	// ������ ��������� �������� ����� 
	void setCurSprite(int n);

	// ������ ������ �����
	void upsetCurList(Image* im);

	// ������� ��������� ����� �������
	void setUpdateInterval(int msec);

	// ��������� ��������� ����� �������
	int getUpdateInterval();

	// ��������� ������ �����
	Image* getCurList();

	// ��������� ������ �������� �����
	int getnumCurSprite();

	// ��������� ���������� ������
	int countSprites();

	// ���������� ���������� ��������� �������
	int elapsed();

	// ������ � ����� �������
	// QDataStream& stream - ����� ��� ������
	void writeToStream(QDataStream & stream);

	// ������ ������� �� ������
	// QDataStream& stream - ����� ��� ������
	// Sprites *& obj - ������� ������
	friend QDataStream& operator >> (QDataStream& stream, Sprites *& obj);


private:
	// ����� ������� ���������� elapsed()
	std::chrono::steady_clock::time_point last;

	// ��������������� ���� � ������� � �����
	// int n - ����� ���� � �������
	static QString numberToPath(int n);

	// ��������������� ����� � ���� �� �������
	// QString path - ���� �� �������
	static int pathToNumber(QString path);


	Image* list = nullptr;
	int period_len;
	int cur_sprite;
	int cur_time;
	int update_interval;
	int frame_width;
	int frame_height;

	// ������� ����� �� ��������
	static QString PATH[];
};

// ������ ��������
class SpritesGroup
{
public:
	// �����������
	SpritesGroup();

	// �����������
	// QList<Sprites*> sprites - ������ ��������
	SpritesGroup(QList<Sprites*> sprites);

	// ����������
	~SpritesGroup();

	// ������� �������� �����������
	void setCurrentGroup(int n);

	// ��������� ���������� ������������
	int countGroups();

	// ��������� �������� � ������� �����������,
	// �� �������� �����
	int getCurrentGroupOffset();

	// ��������� �������� �����������
	Sprites* getCurrentGroup();

	// ������ � ����� �������
	// QDataStream& stream - ����� ��� ������
	// SpritesGroup& obj - ������� ������
	friend QDataStream& operator << (QDataStream& stream, SpritesGroup& obj);

	// ������ ������� �� ������
	// QDataStream& stream - ����� ��� ������
	// SpritesGroup& obj - ������� ������
	friend QDataStream& operator >> (QDataStream& stream, SpritesGroup& obj);

private:
	QList<Sprites*> _sprites;
	int cur_group;
};


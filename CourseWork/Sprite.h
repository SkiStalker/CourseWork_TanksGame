#pragma once
#include "INCLUDES_QT.h"

// Класс картинки
class Image : public QImage
{
public:
	// Конструктор
	// const QString & filename - расположение картинки
	Image(const QString & filename);

	// Деструктор
	~Image();
	QString name;
};

// Класс спрайтов
class Sprites
{
public:
	// Конструкторы
	// Image* list - указатель на загруженый спрайтлист
	// int update_interval - время переключения между кадрами
	// int frame_width - ширина кадра
	// int frame_height - высота кадра
	Sprites(Image* list, int update_interval, int frame_width);
	Sprites(Image* list, int update_interval, int frame_width, int frame_height);

	// Деструктор
	~Sprites();

	// Перезапуск отсчета прошедшего времени
	void restart();

	// Увеличение прошедшего времени
	void incCurrentTime();

	// Проверка на то, прошел ли период кадров
	bool isPeriod();

	// Задание периода кадров
	void setPeriod(int n);

	// Получение периода кадров
	int getPeriod();

	// Задание ширины кадра 
	void setFrameWidth(int width);

	// Получение ширины кадра 
	int getFrameWidth();

	// Задание высоты кадра 
	void setFrameHeight(int height);

	// Получение высоты кадра 
	int getFrameHeight();

	// Ручная установка текущего кадра 
	void setCurSprite(int n);

	// Замена спрайт листа
	void upsetCurList(Image* im);

	// Задание интервала между кадрами
	void setUpdateInterval(int msec);

	// Получение интервала между кадрами
	int getUpdateInterval();

	// Получение спрайт листа
	Image* getCurList();

	// Получение номера текущего кадра
	int getnumCurSprite();

	// Получение количества кадров
	int countSprites();

	// Обновление прошедшего реального времени
	int elapsed();

	// Запись в поток объекта
	// QDataStream& stream - поток для записи
	void writeToStream(QDataStream & stream);

	// Чтение объекта из потока
	// QDataStream& stream - поток для чтения
	// Sprites *& obj - текущий объект
	friend QDataStream& operator >> (QDataStream& stream, Sprites *& obj);


private:
	// Точка времени последнего elapsed()
	std::chrono::steady_clock::time_point last;

	// Конвертирование пути к спрайту в число
	// int n - номер пути в таблице
	static QString numberToPath(int n);

	// Конвертирование числа в путь до спрайта
	// QString path - путь до спрайта
	static int pathToNumber(QString path);


	Image* list = nullptr;
	int period_len;
	int cur_sprite;
	int cur_time;
	int update_interval;
	int frame_width;
	int frame_height;

	// Таблица путей до спрайтов
	static QString PATH[];
};

// Группа спрайтов
class SpritesGroup
{
public:
	// Конструктор
	SpritesGroup();

	// Конструктор
	// QList<Sprites*> sprites - список спрайтов
	SpritesGroup(QList<Sprites*> sprites);

	// Деструктор
	~SpritesGroup();

	// Задание текущего спрайтлиста
	void setCurrentGroup(int n);

	// Получение количества спрайтлистов
	int countGroups();

	// Получение смещения в текущем спрайтлисте,
	// до текущего кадра
	int getCurrentGroupOffset();

	// Получение текущего спрайтлиста
	Sprites* getCurrentGroup();

	// Запись в поток объекта
	// QDataStream& stream - поток для записи
	// SpritesGroup& obj - текущий объект
	friend QDataStream& operator << (QDataStream& stream, SpritesGroup& obj);

	// Чтение объекта из потока
	// QDataStream& stream - поток для чтения
	// SpritesGroup& obj - текущий объект
	friend QDataStream& operator >> (QDataStream& stream, SpritesGroup& obj);

private:
	QList<Sprites*> _sprites;
	int cur_group;
};


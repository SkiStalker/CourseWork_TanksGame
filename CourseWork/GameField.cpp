#include "GameField.h"

GameField::GameField(QWidget * parent) : QGraphicsScene(parent)
{
	setSceneRect(QRect(0, 0, 600, 600));
}

GameField::~GameField()
{
}

void GameField::keyPressEvent(QKeyEvent * e)
{
	if (alive)
	{
		auto _items = items();
		for (int i = 0; i < _items.length(); i++)
		{
			GameObject * item = (GameObject*)_items[i];
			item->pressAction(e);
			update();
		}
		if (e->key() == Qt::Key::Key_Escape)
			emit pauseClicked();
	}
	else if(!e->isAutoRepeat())
	{
		emit closed();
	}
}

void GameField::keyReleaseEvent(QKeyEvent * e)
{
	if (alive)
	{
		auto _items = items();
		for (int i = 0; i < _items.length(); i++)
		{
			GameObject * item = (GameObject*)_items[i];
			item->releaseAction(e);
			update();
		}
	}
}

bool GameField::isPaused()
{
	return paused;
}

void GameField::setAlive(bool a)
{
	alive = a;
}

void GameField::pause()
{
	if (paused)
	{
		paused = false;
		for (int i = 0; i < items().length(); i++)
		{
			GameObject* item = (GameObject*)items()[i];
			item->startObjectUpdating();
			update();
		}
	}
	else
	{
		paused = true;
		for (int i = 0; i < items().length(); i++)
		{
			GameObject* item = (GameObject*)items()[i];
			item->stopObjectUpdating();
			update();
		}
	}
}

bool GameField::event(QEvent * ev)
{
	return QGraphicsScene::event(ev);
}





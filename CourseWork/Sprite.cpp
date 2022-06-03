#include "Sprite.h"

QString Sprites::PATH[] = {
	":/sprites/tank/sprites/tank/deadTankSkin.png",
	":/sprites/tank/sprites/tank/enemyTankSkin.png",
	":/sprites/tank/sprites/tank/mainTankSkin.png",
	":/sprites/shell/sprites/shell/shellSprite.png",
	":/sprites/brick/sprites/brick/brickMainSkin.png",
	":/sprites/brick/sprites/brick/leavesMainSkin.png",
	":/sprites/brick/sprites/brick/wallMainSkin.png",
	":/sprites/brick/sprites/brick/waterMainSkin.png",
	":/sprites/base/sprites/base/myBaseMainSkin.png",
	":/sprites/base/sprites/base/enemyBaseMainSkin.png",
};

Sprites::Sprites(Image* list, int update_interval, int frame_width)
	:Sprites(list, update_interval, frame_width, frame_width)
{

}

Sprites::Sprites(Image * list, int update_interval, int frame_width, int frame_height)
	:update_interval(update_interval), list(list), frame_width(frame_width), 
	frame_height(frame_height)
{
	period_len = list->width() / frame_width;
	cur_sprite = 0;
	cur_time = 1;
	last = std::chrono::steady_clock::now();
}

Sprites::~Sprites()
{
	delete list;
}

void Sprites::restart()
{
	cur_time = 1;
	last = std::chrono::steady_clock::now();
}

void Sprites::incCurrentTime()
{
	int d = elapsed();
	cur_time += (d > 0 ? d : 1);
	cur_time = (cur_time > update_interval ? update_interval : cur_time);

	if (isPeriod())
	{
		cur_time = 0;
		cur_sprite = (cur_sprite + 1) % period_len;
		setCurSprite(cur_sprite);
	}
}

bool Sprites::isPeriod()
{
	return !(cur_time % update_interval);
}

void Sprites::setPeriod(int n)
{
	period_len = n;
}

int Sprites::getPeriod()
{
	return period_len;
}

void Sprites::setFrameWidth(int width)
{
	frame_width = width;
}

int Sprites::getFrameWidth()
{
	return frame_width;
}

void Sprites::setFrameHeight(int height)
{
	frame_height = height;
}

int Sprites::getFrameHeight()
{
	return frame_height;
}

void Sprites::setCurSprite(int n)
{
	cur_sprite = n;
}

void Sprites::upsetCurList(Image * im)
{
	delete list;
	list = im;
}

void Sprites::setUpdateInterval(int msec)
{
	update_interval = msec;
}

int Sprites::getUpdateInterval()
{
	return update_interval;
}

Image * Sprites::getCurList()
{
	return list;
}

int Sprites::getnumCurSprite()
{
	return cur_sprite;
}

int Sprites::countSprites()
{
	return period_len;
}

QString Sprites::numberToPath(int n)
{
	if (n < 0 || n > 9)
		throw std::exception("Wrong path to sprite");
	return PATH[n];
}

int Sprites::pathToNumber(QString path)
{
	for (int i = 0; i < sizeof(PATH) / sizeof(char*); i++)
		if (path == PATH[i])
			return i;
	return -1;
}

SpritesGroup::SpritesGroup(): cur_group(-1)
{

}

SpritesGroup::SpritesGroup(QList<Sprites*> sprites): _sprites(sprites), cur_group(0)
{
}

SpritesGroup::~SpritesGroup()
{
}

void SpritesGroup::setCurrentGroup(int n)
{
	if(n>-1 && n < _sprites.length())
		cur_group = n;
}

int SpritesGroup::countGroups()
{
	return this->_sprites.length();
}

int SpritesGroup::getCurrentGroupOffset()
{
	return getCurrentGroup()->getnumCurSprite() * getCurrentGroup()->getFrameWidth();
}

Sprites * SpritesGroup::getCurrentGroup()
{
	if(cur_group>-1)
		return _sprites[cur_group];
	return nullptr;
}

QDataStream & operator>>(QDataStream & stream, Sprites *& obj)
{
	QString path;
	int i_path = 0, update_interval, frame_width, frame_height;
	stream >> i_path;
	path = Sprites::numberToPath(i_path);
	stream >> update_interval >> frame_width >> frame_height;

	if (update_interval < 0 || frame_width < 0 || frame_height < 0)
		throw std::exception("Wrong sprite params");
	obj = new Sprites(new Image(path), update_interval, frame_width, frame_height);
	return stream;
}

QDataStream & operator<<(QDataStream & stream, SpritesGroup & obj)
{
	stream << obj._sprites.length();
	for (auto item : obj._sprites)
	{
		item->writeToStream(stream);
	}
	return stream;
}

QDataStream & operator>>(QDataStream & stream, SpritesGroup & obj)
{
	int group_count;
	stream >> group_count;

	if (group_count < 0)
		throw std::exception("Wrong count sprite groups");

	while (group_count--)
	{
		try
		{
			Sprites* s_temp = nullptr;
			stream >> s_temp;
			obj._sprites.append(s_temp);
		}
		catch (std::exception ex)
		{
			throw ex;
		}
	}
	obj.cur_group = 0;

	return stream;
}

Image::Image(const QString & filename): QImage(filename)
{
	name = filename;
}

Image::~Image()
{
}

int Sprites::elapsed()
{
	std::chrono::steady_clock::time_point next = std::chrono::steady_clock::now();
	int d = std::chrono::duration_cast<std::chrono::milliseconds>(next - last).count();
	last = next;
	return d;
}

void Sprites::writeToStream(QDataStream & stream)
{
	stream << Sprites::pathToNumber(list->name);
	stream << update_interval << frame_width << frame_height;
}

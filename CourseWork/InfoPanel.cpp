#include "InfoPanel.h"

InfoPanel::InfoPanel() : QGraphicsScene(QRectF(0, 0, 100, 600))
{
	addItem(TankObject::getBotTank({ 10, 10 }));
	addItem(TankObject::getBotFastTank({ 10, 100 }));
	addItem(TankObject::getBotHeavyTank({ 10, 200 }));
	t = new QGraphicsTextItem(": 0");
	addItem(t);
	t->setPos({ 50, 10 });
	ft = new QGraphicsTextItem(": 0");
	addItem(ft);
	ft->setPos({ 50, 100 });
	ht = new QGraphicsTextItem(": 0");
	addItem(ht);
	ht->setPos({ 50, 200 });
}

InfoPanel::~InfoPanel()
{
}

void InfoPanel::printInfo(int cntTank, int cntFTank, int cntHTank)
{
	QString text;
	text = ": " + QString::number(cntTank);
	t->setPlainText(text);
	text = ": " + QString::number(cntFTank);
	ft->setPlainText(text);
	text = ": " + QString::number(cntHTank);
	ht->setPlainText(text);
}

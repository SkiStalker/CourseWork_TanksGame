#include "TanksGame.h"
#include "INCLUDES_QT.h"

int main(int argc, char *argv[])
{
	srand(time(nullptr));
	QApplication a(argc, argv);
    TanksGame w;
    w.show();
    return a.exec();
}

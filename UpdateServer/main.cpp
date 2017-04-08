#include "updateserver.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UpdateServer w;
	w.show();
	return a.exec();
}

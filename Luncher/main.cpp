#include "Luncher.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Luncher w;
	w.show();
	return a.exec();
}

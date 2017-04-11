#include "Luncher.h"
#include <QtGui/QApplication>
#include "NetCore/UpdataXml.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Luncher w;
	UpdataXml xml;
	xml.praseXmlFile("C:\\Users\\strive\\Desktop\\updatalist.xml");
	w.show();
	return a.exec();
}

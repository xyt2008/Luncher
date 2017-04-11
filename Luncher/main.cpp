#include "Luncher.h"
#include <QApplication>
#include "NetCore/FileUtils.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileUtils::ins()->initApplication(QApplication::applicationDirPath()
		.append("/../../client"));
	FileUtils::ins()->initScene(QApplication::applicationDirPath()
		.append("/../../client"));
	Luncher w;
	w.show();
	return a.exec();
}

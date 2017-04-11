#include "updateserver.h"
#include <QtGui/QApplication>
#include "NetCore/FileUtils.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileUtils::ins()->initApplication(QApplication::applicationDirPath()
		.append("/../../data"));
	FileUtils::ins()->initScene(QApplication::applicationDirPath()
		.append("/../../data"));
	UpdateServer w;
	w.show();
	w.initFileInfo();
	return a.exec();
}

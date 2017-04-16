#include "MakeList.h"
#include <QFileDialog>
#include <QCryptographicHash>
#include <QDirIterator>

MakeList::MakeList(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_strBaseDir.clear();

	ui.tableWidget->setColumnWidth(0, 300);
	ui.tableWidget->setColumnWidth(1, 100);
	ui.tableWidget->setColumnWidth(2, 160);
	ui.tableWidget->setColumnWidth(3, 100);

	connect(ui.pushButtonBrowse, SIGNAL(clicked()), this, SLOT(slotBrowse()));
	connect(ui.pushButtonMake, SIGNAL(clicked()), this, SLOT(slotMakeList()));
	connect(ui.pushButtonMD5, SIGNAL(clicked()), this, SLOT(slotMakeMd5()));
}

MakeList::~MakeList()
{

}

void MakeList::slotBrowse()
{
	QString strDir = QFileDialog::getExistingDirectory(this, 
		QString::fromLocal8Bit("请选择路径"), "", QFileDialog::ShowDirsOnly);

	if (!strDir.isEmpty() && QFile::exists(strDir))
	{
		ui.lineEditDir->setText(strDir);
		
		m_strBaseDir = strDir;
		getDirFiles(strDir);
	}
}

void MakeList::slotMakeList()
{

}

void MakeList::slotMakeMd5()
{
	for (int i = 0; i < ui.tableWidget->rowCount(); ++i)
	{
		QString strPath = m_strBaseDir + ui.tableWidget->item(i, 0)->text();
		if (QFile::exists(strPath))
		{
			QFile file(strPath);
			if (file.open(QIODevice::ReadOnly))
			{
				QByteArray bArray = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
				QTableWidgetItem* pItem = ui.tableWidget->item(i, 2);
				if (pItem == 0)
				{
					pItem = new QTableWidgetItem;
					ui.tableWidget->setItem(i, 2, pItem);
				}
				pItem->setText(bArray.toHex());

				file.close();
			}
		}
	}
}

void MakeList::getDirFiles(const QString& strDir)
{
	QDir dir;
	dir.setPath(strDir);

	QString strFiles;
	// 获取目录下所有文件
	int i = 0;
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
	QDirIterator iter(strDir, QDirIterator::Subdirectories);
	while (iter.hasNext())
	{
		iter.next();
		QFileInfo info = iter.fileInfo();
		if (info.isFile())
		{
			ui.tableWidget->insertRow(i);

			// 把文件名填充到表格第0列
			QTableWidgetItem* pItem = new QTableWidgetItem;
			QString fullPath = info.filePath();
			pItem->setText(fullPath.right(fullPath.length() - m_strBaseDir.length()));
			ui.tableWidget->setItem(i, 0, pItem);

			// 把文件大小填充到表格第1列
			pItem = new QTableWidgetItem;
			qint64 size = info.size();
			QString strSize;
			if (size > 1024)
			{
				float sizeCount = size / 1024.0;
				if (sizeCount > 1024)
				{
					sizeCount /= 1024.0;
					if (sizeCount > 1024)
					{
						strSize = QString("%1 Gb").arg(QString::number(sizeCount / 1024.0, 'f', 2));
					}
					else
					{
						strSize = QString("%1 Mb").arg(QString::number(sizeCount, 'f', 2));
					}
				}
				else
				{
					strSize = QString("%1 kb").arg(QString::number(sizeCount, 'f', 2));
				}
			}
			else
			{
				strSize = QString("%1 bit").arg(QString::number(size));
			}
			pItem->setText(strSize);
			pItem->setData(Qt::UserRole, size);
			pItem->setTextAlignment(Qt::AlignRight);
			ui.tableWidget->setItem(i++, 1, pItem);
		}
	}
}

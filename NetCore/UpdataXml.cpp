#include "UpdataXml.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>

UpdataXml::UpdataXml()
{
	m_strVersion.clear();
	m_strError.clear();
	m_mapFileList.clear();
}

UpdataXml::~UpdataXml()
{

}

bool UpdataXml::praseXmlFile(const QString& fileName)
{
	if (fileName.isEmpty() || !QFile::exists(fileName))
	{
		m_strError = QString::fromLocal8Bit("文件 %1 不存在!").arg(fileName);
		return false;
	}

	m_strVersion.clear();
	m_mapFileList.clear();

	// 打开文件io
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		m_strError = QString::fromLocal8Bit("打开文件 %1 失败！").arg(fileName);
		return false;
	}

	QDomDocument document;
	QString strError;  
	int iRow = 0, iColumn = 0;  
	if(!document.setContent(&file, false, &strError, &iRow, &iColumn))
	{
		file.close();
		m_strError = QString::fromLocal8Bit("解析文件 %1 第%2行，第%3列 失败！")
			.arg(fileName).arg(QString::number(iRow, 10)).arg(QString::number(iColumn, 10));
		return false;
	}

	// 读取完毕，关闭文件
	file.close();

	// 解析版本号
	QDomElement elements = document.documentElement();
	if (elements.hasAttribute(g_strVersion))
	{
		m_strVersion = elements.attributeNode(g_strVersion).value();
	}

	// 解析文件列表
	for(QDomNode node = elements.firstChild(); !node.isNull(); node = node.nextSibling())
	{
		// 找到所有的files节点
		QDomElement parant = node.toElement();
		if (!parant.isNull())
		{
			if (parant.tagName() == QString("files"))
			{
				// 读取单个File内容
				QDomNodeList nodeList = parant.childNodes();
				for (int i = 0; i < nodeList.size(); ++i)
				{
					readFileDom(nodeList.at(i).toElement());
				}
			}
		}
	}

	return true;
}

bool UpdataXml::writeXmlFile(const QString& fileName, const QString& version,
							 const std::map<QString, FileList>& filelist)
{
	if (fileName.isEmpty() || filelist.size() <= 0)
	{
		m_strError = QString::fromLocal8Bit("写入的文件名或者内容不能为空！");
		return false;
	}

	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		m_strError = QString::fromLocal8Bit("文件:%1打开失败，无法写入！");
		return false;
	}

	QDomDocument document;
	// app version
	QDomElement versionElem = document.createElement("app");
	document.appendChild(versionElem);
	versionElem.setAttribute("version", version);

	// files
	QDomElement filesElem = document.createElement("files");
	versionElem.appendChild(filesElem);

	// file
	std::map<QString, FileList>::const_iterator iter = filelist.begin();
	for (; iter != filelist.end(); ++iter)
	{
		QDomElement fileElem = document.createElement("file");
		filesElem.appendChild(fileElem);

		QDomElement fileName = document.createElement(g_strXmlFile);
		fileElem.appendChild(fileName);
		fileName.setAttribute(g_strXmlFile, iter->first);

		QDomElement sizeElem = document.createElement(g_strFileSize);
		fileElem.appendChild(sizeElem);
		sizeElem.setAttribute(g_strFileSize, iter->second.m_fSize);

		QDomElement md5Elem = document.createElement(g_strFileMd5);
		fileElem.appendChild(md5Elem);
		md5Elem.setAttribute(g_strFileMd5, iter->second.m_strMd5);
	}

	QTextStream out(&file);
	document.save(out, 3);
	file.close();

	return true;
}

std::map<QString, FileList> UpdataXml::getFileLists()
{
	return m_mapFileList;
}

QString UpdataXml::getVersion()
{
	return m_strVersion;
}

QString UpdataXml::getLastError()
{
	return m_strError;
}

void UpdataXml::readFileDom(const QDomElement& parant)
{
	if (parant.isNull())
	{
		return;
	}
	FileList list;
	QString strName;
	QDomNodeList nodeList = parant.childNodes();
	for (int i = 0; i < nodeList.size(); ++i)
	{
		QDomElement element = nodeList.at(i).toElement();
		QString tag = element.tagName();
		QString text = element.text();
		if (element.tagName() == g_strXmlFile)
		{
			// 文件名
			strName = element.text();
		}
		else if (element.tagName() == g_strFileSize)
		{
			// 文件大小
			list.m_fSize = element.text().toFloat();
		}
		else if (element.tagName() == g_strFileMd5)
		{
			// 文件md5
			list.m_strMd5 = element.text();
		}
	}
	m_mapFileList[strName] = list;
}

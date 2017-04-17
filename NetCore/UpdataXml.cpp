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
		m_strError = QString::fromLocal8Bit("�ļ� %1 ������!").arg(fileName);
		return false;
	}

	m_strVersion.clear();
	m_mapFileList.clear();

	// ���ļ�io
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		m_strError = QString::fromLocal8Bit("���ļ� %1 ʧ�ܣ�").arg(fileName);
		return false;
	}

	QDomDocument document;
	QString strError;  
	int iRow = 0, iColumn = 0;  
	if(!document.setContent(&file, false, &strError, &iRow, &iColumn))
	{
		file.close();
		m_strError = QString::fromLocal8Bit("�����ļ� %1 ��%2�У���%3�� ʧ�ܣ�")
			.arg(fileName).arg(QString::number(iRow, 10)).arg(QString::number(iColumn, 10));
		return false;
	}

	// ��ȡ��ϣ��ر��ļ�
	file.close();

	// �����汾��
	QDomElement elements = document.documentElement();
	if (elements.hasAttribute(g_strVersion))
	{
		m_strVersion = elements.attributeNode(g_strVersion).value();
	}

	// �����ļ��б�
	for(QDomNode node = elements.firstChild(); !node.isNull(); node = node.nextSibling())
	{
		// �ҵ����е�files�ڵ�
		QDomElement parant = node.toElement();
		if (!parant.isNull())
		{
			if (parant.tagName() == QString("files"))
			{
				// ��ȡ����File����
				QDomNodeList nodeList = parant.childNodes();
				for (int i = 0; i < nodeList.size(); ++i)
				{
					FileList list;
					QDomElement element = nodeList.at(i).toElement();

					// �ļ���С
					list.m_fSize = element.attribute(g_strFileSize).toLongLong();
					// �ļ�md5
					list.m_strMd5 = element.attribute(g_strFileMd5);

					m_mapFileList[element.attribute(g_strXmlFile)] = list;
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
		m_strError = QString::fromLocal8Bit("д����ļ����������ݲ���Ϊ�գ�");
		return false;
	}

	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		m_strError = QString::fromLocal8Bit("�ļ�:%1��ʧ�ܣ��޷�д�룡");
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

		fileElem.setAttribute(g_strXmlFile, iter->first);
		fileElem.setAttribute(g_strFileSize, iter->second.m_fSize);
		fileElem.setAttribute(g_strFileMd5, iter->second.m_strMd5);
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

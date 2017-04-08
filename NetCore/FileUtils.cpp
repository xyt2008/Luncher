#include "FileUtils.h"
#include <QFileInfo>

FileUtils* FileUtils::m_pIns = NULL;

FileUtils::FileUtils()
{
	m_strAppRoot = "";
	m_strSceneRoot = "";
}

FileUtils::~FileUtils()
{

}

FileUtils* FileUtils::ins()
{
	if (m_pIns == NULL)
	{
		m_pIns = new FileUtils;
	}

	return m_pIns;
}

void FileUtils::del()
{
	delete m_pIns;
}

void FileUtils::initApplication(const QString& name)
{
	m_strAppRoot = name;
	QFileInfo info(m_strAppRoot);
	m_strAppRoot = info.canonicalFilePath();
	QString str = m_strAppRoot.right(1);
	if (str != "/" ||  str != "\\")
	{
		m_strAppRoot.append("/");
	}
}

void FileUtils::initScene(const QString& name)
{
	m_strSceneRoot = name;
	QFileInfo info(m_strSceneRoot);
	m_strSceneRoot = info.canonicalFilePath();
	QString str = m_strSceneRoot.right(1);
	if (str != "/" ||  str != "\\")
	{
		m_strSceneRoot.append("/");
	}
}

QString FileUtils::getApplicationPath(const QString& name)
{
	return m_strAppRoot + name;
}

QString FileUtils::getScenePath(const QString& name)
{
	return m_strSceneRoot + name;
}

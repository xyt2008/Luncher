/************************************************************ 
  Copyright (C), 2014-2016, SSIT Tech. Co., Ltd. 
  �ļ���: FileUtils.h
  ����: lyk
  �汾: V0.1.0
  ����: 2016/09/23
  ģ������:��ȡ·���ӿ�
  ��Ҫ�������书��:
  ��ʷ�޸ļ�¼:
***********************************************************/
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include "Export.h"

////////////////////////////////////////////////
// ʹ�÷�ʽΪ��main��������ڴ�������init,
// ����Ŀ¼��Ϊ��Ŀ¼��֮���ȡ��Ŀ¼���Դ�Ϊ��Ŀ¼
// FileUtils::ins()->init("D:/project/");
////////////////////////////////////////////////
class NETCORE_EXPORT FileUtils
{
public:
	static FileUtils* ins();
	static void del();

	/*
	 * @param name:Ӧ�ó���Ŀ¼
	 * @see   FileUtils:initScene
	 * @note  ����Ӧ�ó������ڵ�Ŀ¼
	 */
	void initApplication(const QString& name);

	/*
	 * @param name:����Ŀ¼
	 * @see   FileUtils:initApplication
	 * @note  ���ó������ڵ�Ŀ¼
	 */
	void initScene(const QString& name);

	/*
	 * @return name:Ӧ�ó���Ŀ¼
	 * @see    FileUtils:getScenePath
	 * @note   ��ȡӦ�ó������ڵ�Ŀ¼
	 */
	QString getApplicationPath(const QString& name);

	/*
	 * @return name:����Ŀ¼
	 * @see    FileUtils:getApplicationPath
	 * @note   ��ȡ�������ڵ�Ŀ¼
	 */
	QString getScenePath(const QString& name);

private:
	FileUtils();
	~FileUtils();

private:
	static FileUtils* m_pIns;
	QString m_strAppRoot;
	QString m_strSceneRoot;
};

#endif // FILEUTILS_H

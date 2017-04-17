/************************************************************ 
  Copyright (C), 2014-2016, SSIT Tech. Co., Ltd. 
  文件名: FileUtils.h
  作者: lyk
  版本: V0.1.0
  日期: 2016/09/23
  模块描述:获取路径接口
  主要函数及其功能:
  历史修改记录:
***********************************************************/
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include "Export.h"

////////////////////////////////////////////////
// 使用方式为在main函数的入口处，调用init,
// 所得目录即为根目录，之后获取的目录都以此为基目录
// FileUtils::ins()->init("D:/project/");
////////////////////////////////////////////////
class NETCORE_EXPORT FileUtils
{
public:
	static FileUtils* ins();
	static void del();

	/*
	 * @param name:应用程序目录
	 * @see   FileUtils:initScene
	 * @note  设置应用程序所在的目录
	 */
	void initApplication(const QString& name);

	/*
	 * @param name:场景目录
	 * @see   FileUtils:initApplication
	 * @note  设置场景所在的目录
	 */
	void initScene(const QString& name);

	/*
	 * @param name:应用程序目录
	 * @see    FileUtils:getScenePath
	 * @note   获取应用程序所在的目录
	 */
	QString getApplicationPath(const QString& name);

	/*
	 * @param name:场景目录
	 * @see    FileUtils:getApplicationPath
	 * @note   获取场景所在的目录
	 */
	QString getScenePath(const QString& name);

	/*
	 * @param  szie:文件实际大小，bit数
	 * @return QString:文件显示大小
	 * @see    
	 * @note   获取文件显示大小，合适用户看的
	 */
	QString getFileSize(qint64 size);

private:
	FileUtils();
	~FileUtils();

private:
	static FileUtils* m_pIns;
	QString m_strAppRoot;
	QString m_strSceneRoot;
};

#endif // FILEUTILS_H

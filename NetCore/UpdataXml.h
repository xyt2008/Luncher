/*  	
 *@file   UpdataXml.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/10
 *@version 0.1.0
 *@note   更新文件列表
 */
#ifndef UPDATAXML_H
#define UPDATAXML_H
#include <map>
#include "Global.h"
#include "Export.h"

class QDomElement;

class NETCORE_EXPORT UpdataXml
{
public:
	UpdataXml();
	~UpdataXml();
	
	/*
	 * @param  fileName:xml文件路径
	 * @return True:文件解析成功；FALSE：文件解析失败
	 * @ref 
	 * @see   getFileLists
	 * @note  解析给定的xml文件
	 */
	bool praseXmlFile(const QString& fileName);

	/*
	 * @param  fileName:xml文件路径
	 * @param  version:版本号
	 * @param  filelist:所有文件
	 * @return True:写入文件成功；FALSE：写入文件失败
	 * @ref 
	 * @see   praseXmlFile
	 * @note  给定的文件信息写入xml文件
	 */
	bool writeXmlFile(const QString& fileName,
		const QString& version, const std::map<QString, FileList>& filelist);

	/*
	 * @return std::map<QString, FileList>:解析结果
	 * @ref 
	 * @see   praseXmlFile
	 * @note  返回解析给定的xml文件的结果
	 */
	std::map<QString, FileList> getFileLists();

	/*
	 * @return QString:版本号
	 * @ref 
	 * @see   praseXmlFile
	 * @note  返回服务器版本号
	 */
	QString getVersion();

	/*
	 * @return QString:错误信息
	 * @ref 
	 * @note   获取解析文件错误的原因
	 */
	QString getLastError();

private:
	void readFileDom(const QDomElement& parant);

private:
	std::map<QString, FileList> m_mapFileList;
	QString m_strVersion;
	QString m_strError;
};

#endif // UPDATAXML_H

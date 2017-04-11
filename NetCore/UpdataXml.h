/*  	
 *@file   UpdataXml.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/10
 *@version 0.1.0
 *@note   �����ļ��б�
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
	 * @param  fileName:xml�ļ�·��
	 * @return True:�ļ������ɹ���FALSE���ļ�����ʧ��
	 * @ref 
	 * @see   getFileLists
	 * @note  ����������xml�ļ�
	 */
	bool praseXmlFile(const QString& fileName);

	/*
	 * @param  fileName:xml�ļ�·��
	 * @param  version:�汾��
	 * @param  filelist:�����ļ�
	 * @return True:д���ļ��ɹ���FALSE��д���ļ�ʧ��
	 * @ref 
	 * @see   praseXmlFile
	 * @note  �������ļ���Ϣд��xml�ļ�
	 */
	bool writeXmlFile(const QString& fileName,
		const QString& version, const std::map<QString, FileList>& filelist);

	/*
	 * @return std::map<QString, FileList>:�������
	 * @ref 
	 * @see   praseXmlFile
	 * @note  ���ؽ���������xml�ļ��Ľ��
	 */
	std::map<QString, FileList> getFileLists();

	/*
	 * @return QString:�汾��
	 * @ref 
	 * @see   praseXmlFile
	 * @note  ���ط������汾��
	 */
	QString getVersion();

	/*
	 * @return QString:������Ϣ
	 * @ref 
	 * @note   ��ȡ�����ļ������ԭ��
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

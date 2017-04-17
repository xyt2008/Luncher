/*  	
 *@file   Global.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/07
 *@version V0.1.0
 *@note   ����ͨѶ���ݶ��崦
 */
#ifndef NETCORE_GLOBAL_H
#define NETCORE_GLOBAL_H
#include <QString>

// ����tcp����ͷ
const char* const g_strPush = "Push";                   // ����ϴ���������
const char* const g_strPull = "Pull";                   // ������أ�������
const char* const g_strData = "Data";                   // ���ͣ�����
const char* const g_strFile = "File";                   // ���ͣ��ļ�
const char* const g_strValue = "Value";                 // ����ֵ��Ϣ���ļ����ļ��������ݣ�������
const char* const g_strLength = "ContentLength";        // ����
const char* const g_strEnding = "\r\n";                 // ������

// ��λxml�ļ�����
const QString g_strVersion = "version";                 // �汾��
const QString g_strXmlFile = "name";                    // �ļ�����
const QString g_strFileSize = "size";                   // �ļ�����
const QString g_strFileMd5 = "md5";                     // �ļ�����

// ����״̬
enum ConnState{
	Conn_Init,            // ��ʼ��
	Conn_Read,            // ��ȡ����
	Conn_Write,           // д������
	Conn_Conn,            // ����
	Conn_DisConn,         // �Ͽ�����
	Conn_End
};

// �ļ����Ա�
struct FileList
{
	FileList()
	{
		m_fSize = 0;
		m_strMd5.clear();
	}

	qint64 m_fSize;
	QString m_strMd5;
};

#endif // NETCORE_GLOBAL_H

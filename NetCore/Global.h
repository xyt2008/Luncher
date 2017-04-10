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

// ��������ͷ
const char* const g_strPush = "Push";                   // ����ϴ���������
const char* const g_strPull = "Pull";                   // ������أ�������
const char* const g_strData = "Data";                   // ���ͣ�����
const char* const g_strFile = "File";                   // ���ͣ��ʼ�
const char* const g_strFileName = "FileName";           // �ļ�����
const char* const g_strLength = "ContentLength";        // ����
const char* const g_strEnding = "\r\n";                 // ������

// ����״̬
enum ConnState{
	Conn_Init,            // ��ʼ��
	Conn_Read,            // ��ȡ����
	Conn_Write,           // д������
	Conn_Conn,            // ����
	Conn_DisConn,         // �Ͽ�����
	Conn_End
};

#endif // NETCORE_GLOBAL_H

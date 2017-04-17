/*  	
 *@file   Global.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/07
 *@version V0.1.0
 *@note   网络通讯数据定义处
 */
#ifndef NETCORE_GLOBAL_H
#define NETCORE_GLOBAL_H
#include <QString>

// 定义tcp数据头
const char* const g_strPush = "Push";                   // 命令：上传，即接收
const char* const g_strPull = "Pull";                   // 命令：下载，即发送
const char* const g_strData = "Data";                   // 类型：数据
const char* const g_strFile = "File";                   // 类型：文件
const char* const g_strValue = "Value";                 // 类型值信息：文件：文件名；数据：数据名
const char* const g_strLength = "ContentLength";        // 长度
const char* const g_strEnding = "\r\n";                 // 结束符

// 定位xml文件常量
const QString g_strVersion = "version";                 // 版本号
const QString g_strXmlFile = "name";                    // 文件名称
const QString g_strFileSize = "size";                   // 文件名称
const QString g_strFileMd5 = "md5";                     // 文件名称

// 连接状态
enum ConnState{
	Conn_Init,            // 初始化
	Conn_Read,            // 读取数据
	Conn_Write,           // 写入数据
	Conn_Conn,            // 连接
	Conn_DisConn,         // 断开连接
	Conn_End
};

// 文件属性表
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

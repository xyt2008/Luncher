/*  	
 *@file   Global.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/07
 *@version 3.1
 *@note   网络通讯数据定义处
 */
#ifndef NETCORE_GLOBAL_H
#define NETCORE_GLOBAL_H

// 定义数据头
const char* g_strPush = "Push";                   // 命令：上传，即接收
const char* g_strPull = "Pull";                   // 命令：下载，即发送
const char* g_strData = "Data";                   // 类型：数据
const char* g_strFile = "File";                   // 类型：问价
const char* g_strFileName = "FileName";           // 文件名称
const char* g_strLength = "ContentLength";        // 长度
const char* g_strEnding = "\r\n";                 // 结束符

#endif // NETCORE_GLOBAL_H

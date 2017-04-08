/*  	
 *@file   Export.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/06
 *@version V0.1.0
 *@note  
 */
#ifndef NETCORE_EXPORT_H
#define NETCORE_EXPORT_H

#ifndef NETCORE_EXPORTS
#define NETCORE_EXPORT __declspec(dllimport)
#else
#define NETCORE_EXPORT __declspec(dllexport)
#endif

#endif // NETCORE_EXPORT_H

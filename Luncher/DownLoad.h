/*  	
 *@file   DownLoad.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/17
 *@version V0.1.0
 *@note   œ¬‘ÿπ‹¿Ì
 */
#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <map>
#include "NetCore/Global.h"

class DownThread;
class Client;

class DownLoad : public QObject
{
	Q_OBJECT

public:
	DownLoad(QObject *parent = 0);
	~DownLoad();

	void setDownLoadList(const std::map<QString, FileList>& mapUpdateList);

	void start(QString strIp, int port);

private slots:
	void slotFinishedDownFile(const QString& file);

private:
	void doThread();

private:
	std::map<QString, FileList> m_mapUpdateList;
	QString m_strIp;
	int m_iPort;
};

#endif // DOWNLOAD_H

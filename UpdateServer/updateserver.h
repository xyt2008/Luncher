#ifndef UPDATESERVER_H
#define UPDATESERVER_H

#include <QDialog>
#include <QHostInfo>
#include "ui_updateserver.h"
#include "TCPServer.h"

class UpdateServer : public QDialog
{
	Q_OBJECT

public:
	UpdateServer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~UpdateServer();

private slots:
	void slotLookHost(const QHostInfo& info);

private:
	Ui::UpdateServerClass ui;
	TCPServer* m_pServer;
};

#endif // UPDATESERVER_H

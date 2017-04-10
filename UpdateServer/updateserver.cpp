#include "updateserver.h"
#include <QNetworkInterface>

UpdateServer::UpdateServer(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	m_pServer = new TCPServer(ui, this);
	if (!m_pServer->listen(QHostAddress::Any, 24732))
	{
		ui.textEdit->append(QString::fromLocal8Bit("����������"));
		close();
		return;
	}

	QHostInfo::lookupHost(QHostInfo::localHostName(), this, SLOT(slotLookHost(const QHostInfo&)));
	QString ipAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (int i = 0; i < ipAddressesList.size(); ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address())
		{
				ipAddress = ipAddressesList.at(i).toString();
				break;
		}
	}

	if (ipAddress.isEmpty())
	{
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	}
	ui.textEdit->append(QString::fromLocal8Bit("������IP:%1, port:%2").arg(ipAddress).arg(m_pServer->serverPort()));
}

UpdateServer::~UpdateServer()
{

}

void UpdateServer::slotLookHost(const QHostInfo& info)
{
	if (!info.addresses().isEmpty())
	{
		foreach(QHostAddress addr, info.addresses())
		{
			ui.textEdit->append(QString::fromLocal8Bit("������IP:%1, port:%2")
				.arg(addr.toString())
				.arg(m_pServer->serverPort()));
		}
// 		QHostAddress address = info.addresses().first();
// 		ui.textEdit->append(QString::fromLocal8Bit("������IP:%1, port:%2")
// 			.arg(address.toString())
// 			.arg(m_pServer->serverPort()));
	}
}
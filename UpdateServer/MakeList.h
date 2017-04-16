/*  	
 *@file   MakeList.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/15
 *@version 3.0.1
 *@note   制作更新列表文件功能
 */
#ifndef MAKELIST_H
#define MAKELIST_H

#include <QDialog>
#include "ui_MakeList.h"

class MakeList : public QDialog
{
	Q_OBJECT

public:
	MakeList(QWidget *parent = 0);
	~MakeList();

private slots:
	void slotBrowse();
	void slotMakeList();
	void slotMakeMd5();

private:
	void getDirFiles(const QString& strDir);

private:
	Ui::MakeList ui;
	QString m_strBaseDir;
};

#endif // MAKELIST_H

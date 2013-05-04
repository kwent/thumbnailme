/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockThreadsPool.h
*       @class  DockThreadsPool
*	Cette classe permet la de voir les threads actifs
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      3.5
*	@version    3.5
*       @date       2011-2012
*******************************************************************************/

#include "DockThreadsPool.h"
#include <QApplication>
#include <QDesktopWidget>

DockThreadsPool::DockThreadsPool(QWidget *parent) : QDockWidget(parent)
{
    this->setMinimumWidth(QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).width()/4);
    this->setObjectName("DockThreadsPool");
    this->setWindowTitle("Tasks");

    threeWidget = new QTreeWidget(this);
    threeWidget->setColumnCount(2);
    threeWidget->setHeaderLabels(QStringList() << "Path" << "State");
    this->setWidget(threeWidget);
}

void DockThreadsPool::addThumbnailItem(ThumbnailItem* item)
{
    QTreeWidgetItem *three_item = new QTreeWidgetItem();
    three_item->setText(0,item->getFilePath().toString());
    three_item->setText(1,tr("QUEUING"));
    this->threeWidget->addTopLevelItem(three_item);
}

void DockThreadsPool::threadStarted(ThumbnailItem* item)
{
    QList<QTreeWidgetItem*> itemFound = this->threeWidget->findItems(item->getFilePath().toString(),Qt::MatchExactly);
    itemFound.last()->setText(1,tr("STARTED"));
}

void DockThreadsPool::threadFinished(ThumbnailItem* item)
{
    QList<QTreeWidgetItem*> itemFound = this->threeWidget->findItems(item->getFilePath().toString(),Qt::MatchExactly);
    itemFound.last()->setText(1,tr("FINISHED"));
}

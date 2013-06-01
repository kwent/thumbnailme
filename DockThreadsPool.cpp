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

#include <QApplication>
#include <QDesktopWidget>
#include "DockThreadsPool.h"
#include "ThumbnailTreeItem.h"
#include <QHeaderView>
#include "MainWindow.h"

DockThreadsPool::DockThreadsPool(QWidget *main_window) : QDockWidget(main_window)
{
    this->main_window = (MainWindow*) main_window;
    this->setMinimumWidth(QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).width()/4);
    this->setObjectName("DockThreadsPool");
    this->setWindowTitle("Tasks");

    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(2);
    treeWidget->setHeaderLabels(QStringList() << tr("Path") << tr("State"));
    treeWidget->header()->resizeSection(0,this->width()*2/3);
    treeWidget->header()->resizeSection(1,this->width()/3);

    this->setWidget(treeWidget);
}

void DockThreadsPool::addThumbnailItem(ThumbnailItem* item)
{
    ThumbnailTreeItem *three_item = new ThumbnailTreeItem(item);
    three_item->setThreadStatus(tr("QUEUED"));
    this->treeWidget->addTopLevelItem(three_item);
}

void DockThreadsPool::threadStarted(ThumbnailItem* item)
{
    QList<QTreeWidgetItem*> itemFound = this->treeWidget->findItems(item->getFilePath().toString(),Qt::MatchExactly);
    ((ThumbnailTreeItem*) itemFound.last())->setThreadStatus(tr("STARTED"));
}

void DockThreadsPool::threadFinished(ThumbnailItem* item)
{
    QList<QTreeWidgetItem*> itemFound = this->treeWidget->findItems(item->getFilePath().toString(),Qt::MatchExactly);
    ((ThumbnailTreeItem*) itemFound.last())->setThreadStatus(tr("FINISHED"));
}

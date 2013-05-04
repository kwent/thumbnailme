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

#ifndef DOCKTHREADSPOOL_H
#define DOCKTHREADSPOOL_H

#include <QDockWidget>
#include <QTreeWidget>
#include "ThumbnailItem.h"

class DockThreadsPool : public QDockWidget
{
    Q_OBJECT

    public:
    explicit DockThreadsPool(QWidget *parent = 0);

    public:
    void addThumbnailItem(ThumbnailItem* item);

    public:
    QTreeWidget *threeWidget;

    public slots:
    void threadStarted(ThumbnailItem* item);
    void threadFinished(ThumbnailItem* item);
    
};

#endif // DOCKTHREADSPOOL_H

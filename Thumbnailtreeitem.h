/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ThumbnailTreeItem.h
*       @class  ThumbnailTreeItem
*	QListWidget de ThumbnailItem.
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      3.0
*	@version    3.5
*       @date       2011-2012
*******************************************************************************/

#ifndef THUMBNAILTREEITEM_H
#define THUMBNAILTREEITEM_H

#include <QTreeWidgetItem>
#include "ThumbnailItem.h"

class ThumbnailTreeItem : public QTreeWidgetItem
{

public:
    explicit ThumbnailTreeItem(ThumbnailItem* thumbnailItem);

public:
    ThumbnailItem* thumbnailItem;

public:
    void setThreadStatus(QString status);

};

#endif // THUMBNAILTREEITEM_H

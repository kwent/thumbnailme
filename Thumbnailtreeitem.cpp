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

#include "Thumbnailtreeitem.h"

ThumbnailTreeItem::ThumbnailTreeItem(ThumbnailItem* thumbnailItem) : QTreeWidgetItem ()
{
    this->thumbnailItem = thumbnailItem;
    this->setText(0,this->thumbnailItem->getFilePath().toString());
}

void ThumbnailTreeItem::setThreadStatus(QString status)
{
    this->setText(1,status);
}

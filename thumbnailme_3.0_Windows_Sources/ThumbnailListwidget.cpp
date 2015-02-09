#include "ThumbnailListwidget.h"

/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ThumbnailListwidget.h
*       @class  ThumbnailListwidget
*	QListWidget de ThumbnailItem.
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      3.0
*	@version    3.0
*       @date       2011-2012
*******************************************************************************/


/**
*@brief Constructeur.
*/
ThumbnailListWidget::ThumbnailListWidget(QWidget * parent) : QListWidget(parent)
{
    this->setDragDropMode(QAbstractItemView::NoDragDrop);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

/**
*@brief Destructeur.
*/
ThumbnailListWidget::~ThumbnailListWidget()
{
}

/**
*@brief KeyPressEvent.
*@param e   Evenement.
*/
void ThumbnailListWidget::keyPressEvent ( QKeyEvent * e )
{
    if (e->key() == Qt::Key_Delete)
    {
        emit itemDeleted();
    }
    QListWidget::keyPressEvent(e);
}

/**
*@brief Ajout d'un ThumbnailItem.
*@param item   Item à ajouter.
*/
void ThumbnailListWidget::addItem(ThumbnailItem* item)
{
    QListWidget::addItem(item);
}

/**
*@brief Création et ajout d'un ThumbnailItem.
*@param item   Item à ajouter.
*/
void ThumbnailListWidget::addItem(QString item)
{
    ThumbnailItem *i = new ThumbnailItem(QUrl(item));
    QListWidget::addItem(i);
}

/**
*@brief Création et ajout de ThumbnailItem.
*@param items   Items à ajouter.
*/
void ThumbnailListWidget::addItems(QStringList items)
{
    foreach(QString path, items)
    {
        this->addItem(path);
    }
    this->setCurrentRow(0,QItemSelectionModel::SelectCurrent);
}

/**
*@brief  Retourne la liste des ThumbnailItem.
*@return QLinkedList <ThumbnailItem*> - Liste des ThumbnailItem.
*/
QLinkedList <ThumbnailItem*> ThumbnailListWidget::getItemsListWidget()
{
    QLinkedList <ThumbnailItem*> l;

    for(int i = 0 ; i < this->count() ; i++)
        l << static_cast <ThumbnailItem*> (this->item(i));

    return l;
}

/**
*@brief Supprime les items sélectionnés
*/
void ThumbnailListWidget::removeItemSelection()
{
    if(!removeSelectedItems(qobject_cast<QListWidget *>(this)))
        QMessageBox::information(this, _ERROR_, tr("You must select a file to remove it from the list"));
}

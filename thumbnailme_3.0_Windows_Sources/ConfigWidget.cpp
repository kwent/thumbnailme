/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ConfigWidget.cpp
*       @class  ConfigWidget
*	Cette classe permet de personnaliser un objet QxtConfigWidget.
*       @attention  Qt eXTension library required - http://www.libqxt.org/
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      3.0
*       @version    3.0
*       @date       2011-2012
*******************************************************************************/

#include "ConfigWidget.h"

/**
*@brief Constructeur.
*/
ConfigWidget::ConfigWidget(QWidget *parent) : QxtConfigWidget(parent)
{
    this->splitter()->setChildrenCollapsible(false);
}

/**
*@brief Destructeur.
*/
ConfigWidget::~ConfigWidget()
{
}


/**
*@brief Corrige la taille des icônes.
*/
void ConfigWidget::fixedSize()
{
    int height = this->tableWidget()->rowHeight(0)+this->tableWidget()->rowHeight(1);
    height -= 25;
    this->setIconSize(QSize(this->tableWidget()->columnWidth(0),height));
}



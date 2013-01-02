/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ConfigWidget.h
*       @class	ConfigWidget
*	Cette classe permet de personnaliser un objet QxtConfigWidget.
*       @attention  Qt eXTension library required - http://www.libqxt.org/
*
*	@author	Quentin Rousseau\n
*	@note  	Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      3.0
*	@version    3.0
*       @date       2011-2012
*******************************************************************************/

#ifndef HEADER_CONFIGWIDGET
#define HEADER_CONFIGWIDGET

#include <QDebug>
#include <QEvent>
#include <QHeaderView>
#include <QLayout>
#include <QSplitter>
#include <QStackedWidget>
#include <QTableView>
#include <QTableWidget>
#include "Qxt/qxtconfigwidget.h"

class ConfigWidget : public QxtConfigWidget
{
    public:
    explicit ConfigWidget(QWidget *parent = 0);
    virtual ~ConfigWidget();

    public:
    void    fixedSize();
};

#endif // HEADER_CONFIGWIDGET

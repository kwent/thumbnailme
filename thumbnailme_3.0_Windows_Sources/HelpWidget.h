/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	HelpWidget.cpp
*       @class  HelpWidget
*	Cette classe permet la génération du widget "Aide" pour l'utilisateur.
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

#ifndef HEADER_HELPWIDGET
#define HEADER_HELPWIDGET

#include <QtHelp/QHelpContentWidget>
#include <QtHelp/QHelpEngine>
#include <QGridLayout>
#include <QMouseEvent>
#include <QSplitter>
#include <QObject>
#include "HelpBrowser.h"
#include "defines.h"

#include <libQt+.h>

class HelpWidget : public QDialog
{
    Q_OBJECT

    public:
    explicit HelpWidget(QWidget *parent = 0);
    virtual ~HelpWidget();

    private:
    QHelpEngine *helpEngine;
    HelpBrowser *helpBrowser;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    private slots:
    void showHomePage();
};

#endif // HEADER_HELPWIDGET

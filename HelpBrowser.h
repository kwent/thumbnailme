/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	HelpBrowser.h
*       @class  HelpBrowser
*	Cette classe permet la génération d'un visualisateur simple de page HTML.
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

#ifndef HEADER_HELPBROWSER
#define HEADER_HELPBROWSER

#include <QTextBrowser>
#include <QtHelp/QHelpEngine>

class HelpBrowser : public QTextBrowser
{
    Q_OBJECT

    public:
    explicit HelpBrowser(QHelpEngine *helpEngine);
    virtual ~HelpBrowser();

    private:
    QHelpEngine *helpEngine;

    private:
    QVariant loadResource(int type,const QUrl &url);
};

#endif // HEADER_HELPBROWSER

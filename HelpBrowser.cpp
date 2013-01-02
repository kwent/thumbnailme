/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	HelpBrowser.cpp
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

#include "HelpBrowser.h"

/**
*@brief Constructeur.
*/
HelpBrowser::HelpBrowser(QHelpEngine *helpEngine)
{
    this->helpEngine = helpEngine;
    this->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred));
}

/**
*@brief Destructeur.
*/
HelpBrowser::~HelpBrowser()
{
    delete helpEngine;
}

/**
*@brief Charge la documentation.
*@param type    Type de ressource.
*@param name    Chemin vers la ressource.
*/
QVariant HelpBrowser::loadResource(int type, const QUrl & name)
{
    if (name.scheme() == "qthelp")
        return QVariant(helpEngine->fileData(name));
    else
        return QTextBrowser::loadResource(type, name);
}

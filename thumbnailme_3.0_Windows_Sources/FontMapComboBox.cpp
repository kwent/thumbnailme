/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	FontMapComboBox.cpp
*       @class  FontMapComboBox
*	Cette classe permet de générer un QFontComboBox avec un QMap("Famille de la police","Chemin de la police")
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

#include "FontMapComboBox.h"

/**
*@brief Constructeur.
*@param *parent    Widget parent.
*/
FontMapComboBox::FontMapComboBox(QWidget *parent) : QFontComboBox(parent)
{
    this->setFontFilters(QFontComboBox::ScalableFonts);
    this->setEditable(false);
    this->noFontDefined = true;
}

/**
*@brief Destructeur.
*/
FontMapComboBox::~FontMapComboBox()
{
}

/**
*@brief Setter de la map.
*@param map   Map de correspondance "Famille - Chemin de la police".
*/
void FontMapComboBox::setMap(QMap<QString,QString> map)
{
    this->map = map;
}

/**
*@brief Retourne le chemin de la police famille.
*@param family   Famille.
*@return QString - Chemin de la police.
*/
QString FontMapComboBox::path(QString family)
{
    QString path;
    path = this->map.value(family);
    return path;
}

/**
*@brief Retourne le chemin de la police courante.
*@return QString - Chemin de la police.
*/
QString FontMapComboBox::currentFontPath()
{
    return this->path(this->currentText());
}


/**
*@brief Retourne le nom du fichier de la police
*@return QString - Nom du fichier de la police
*/
QString FontMapComboBox::currentFontFileName()
{
    QFileInfo fontInfo (QDir::toNativeSeparators(this->currentFontPath()));
    if (fontInfo.exists())
    {
        return fontInfo.fileName();
    }
    else return QString();
}

/**
*@brief Retourne une liste des familles de police.
*@return QStringList - Familles de police.
*/
QStringList FontMapComboBox::family()
{
    QStringList familyList;

    if(!map.isEmpty())
    {
        foreach(QString family , map.keys())
        {
            familyList << family;
            QCoreApplication::processEvents();
        }
    }
    return familyList;
}


/**
*@brief Retourne une liste des familles de police.
*@return QStringList - Familles de police.
*/
void FontMapComboBox::addFamilyItems(QStringList items)
{
   this->clear();
   if(items.isEmpty() && !map.isEmpty())
   {
       this->addItems(this->family());
       emit loadFontsFinished();
       this->setnoFontDefined(false);
   }
   else this->addItems(items);
}

/**
*@brief Setteur de noFontDefined.
*@return QStringList - Familles de police.
*/
void FontMapComboBox::setnoFontDefined(bool value)
{
    this->noFontDefined = value;
    if(value)
    {
        this->clear();
        this->addItem(tr("No fonts defined"));
    }
}

/**
*@brief Si aucune police définie -> Vrai.
*@return bool - Vrai ou faux.
*/
bool FontMapComboBox::isNoFontDefined()
{
    return this->noFontDefined;
}

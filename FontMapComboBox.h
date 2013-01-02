/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	FontMapComboBox.h
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


#ifndef FONTMAPCOMBOBOX_H
#define FONTMAPCOMBOBOX_H

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFontComboBox>

class FontMapComboBox : public QFontComboBox
{
    Q_OBJECT

    public:
    explicit FontMapComboBox(QWidget *parent = 0);
    virtual ~FontMapComboBox();

    private:
    QMap<QString,QString> map;
    bool                  noFontDefined;

    public:
    void        setMap(QMap<QString,QString> map);
    void        addFamilyItems(QStringList items = QStringList());
    QString     path(QString family);
    QString     currentFontPath();
    QString     currentFontFileName();
    QStringList family();
    void        setnoFontDefined(bool value);
    bool        isNoFontDefined();

    signals:
    /**
    *@brief SIGNAL émis lorsque le chargement des polices est terminé.
    */
    void loadFontsFinished();
};

#endif // FONTMAPCOMBOBOX_H

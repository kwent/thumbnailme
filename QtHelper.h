/***************************************************************************//**
*	@brief libQt+
*       Librairie de fonctions usuelles.
*
*	@file	libQt+.h
*
*	@author		Quentin Rousseau\n
*	@note   	Copyright: Quentin Rousseau (c) 2011 2010, Quentin Rousseau\n
*                       Sous licence: Creative Commons GNU GPL - http://creativecommons.org/licenses/GPL/3.0/\n
*                       email: kwent_78@hotmail.fr
*
*	@version	1.0
*       @date           2010 - 2011
*******************************************************************************/

#ifndef LIBQT_H
#define LIBQT_H

#include <QListWidget>
#include <QApplication>
#include <QFrame>
#include <QDesktopWidget>
#include <QFontDatabase>
#include <QDir>
#include <QTime>
#include <QSettings>
#include <QStringList>

//#include "mtn/mtn.h"

class QtHelper
{
public:
    static QFrame                 *addHSeparator();
    static QFrame                 *addVSeparator();
    static void                   centerWidget(QWidget *widget);
    static QStringList            getItemsListWidget(QListWidget *listWidget);
    static QStringList            getItemsListWidget(QListWidget *listWidget, Qt::CheckState state);
    static bool                   removeSelectedItems(QListWidget *listWidget);
    static QString                qColor2rgbNoSharp(QColor color);
    static QColor                 rgbNoSharp2qColor(QString rgbNoSharp);
    //static rgb_color              qColor2RGB(QColor color);
    static QString                msecs2Hmn(qint64 msecs);
    static QString                secs2Hmn(int secs);
    static QMap <QString,QString> exploreTTFDir(QStringList dirPath);
    static QStringList            readPathsFontsValueIni(QSettings *settings);
};
#endif // LIBQT_H

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

#include <QApplication>
#include <QtGui>

QFrame                 *addHSeparator();
QFrame                 *addVSeparator();
void                   centerWidget(QWidget *widget);
QStringList            getItemsListWidget(QListWidget *listWidget);
QStringList            getItemsListWidget(QListWidget *listWidget, Qt::CheckState state);
bool                   removeSelectedItems(QListWidget *listWidget);
QString                qColor2rgbNoSharp(QColor color);
QColor                 rgbNoSharp2qColor(QString rgbNoSharp);
QString                msecs2Hmn(qint64 msecs);
QString                secs2Hmn(int secs);
QMap <QString,QString> exploreTTFDir(QStringList dirPath);
QStringList            readPathsFontsValueIni(QSettings *settings);

#endif // LIBQT_H

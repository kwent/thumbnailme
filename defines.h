/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	defines.h
*
*	@author		Quentin Rousseau\n
*	@note   	Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*   @since      3.0
*	@version	3.0
*   @date       2011-2012
*******************************************************************************/

#ifndef HEADER_DEFINES
#define HEADER_DEFINES

#include <QtGlobal>

#define APPLICATION_NAME        QString("Thumbnail me")
#define VERSION                 QString("3.5")
#define WEBSITE_URL             QString("http://www.thumbnailme.com")
#define AUTHOR_EMAIL            QString("quentin.rousseau@thumbnailme.com")
#define TRANSLATION_HELP_URL    QString("http://www.thumbnailme.com/translation-instructions")
#define DONATION_URL            QString("http://www.paypal.fr/cgi-bin/webscr?cmd=_donations&business= kwent_78@hotmail.fr&item_name=Donation_thumbnailme")
#define IMAGESHACK_DEVELOPERKEY QString("EFI0O4JZd1897eb3d86758fa0ee582a34385405e")

#define _ERROR_       tr("Error")
#define _INFORMATION_ tr("Information")
#define _WARNING_     tr("Warning")

#define STYLE                 QPlastiqueStyle
#define DEFAULT_TMP_EXTENSION QString(".tbme")
#define TRANSLATORS           QString(":/system_translators/")
#define FONTS_CACHING         QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/fontscache.dat")

#if defined(Q_OS_WIN32)
#include <qt_windows.h>
#define usleep(ms)            Sleep(ms);
#define FACTOR_TIME           1
#define DEFAULT_PATH_FONT     QStandardPaths::writableLocation(QStandardPaths::FontsLocation)
#define DEFAULT_PATH_INI      QSettings::UserScope
#define DEFAULT_FILE_INI      QString("settings")
#define DEFAULT_PATH_LANG     QString("./lang/")
#define DOCS_PATH             QString("./doc/thumbnailme_3.0.qhc")
#endif

#if defined(Q_OS_LINUX)
#include <unistd.h>
#include <stdlib.h>
#define FACTOR_TIME           1000
#define DEFAULT_PATH_FONT     QString("/usr/share/fonts/truetype/freefont")
#define DEFAULT_PATH_INI      QSettings::UserScope
#define DEFAULT_FILE_INI      QString("settings")
#define DEFAULT_PATH_LANG     QString("./lang/")
#define DOCS_PATH             QString("./doc/thumbnailme_3.0.qhc")
#endif

#define OUTPUT_FORMAT   "bmp" << "jpeg" << "png" << "tiff"

#define VALID_EXTENSIONS   "avi" \
                        << "mpeg"\
                        << "mpg" \
                        << "mkv" \
                        << "m2ts"\
                        << "ts"  \
                        << "wmv" \
                        << "ogg" \
                        << "3gp" \
                        << "dat" \
                        << "mp4" \
                        << "m4v" \
                        << "mov" \
                        << "flv" \
                        << "swf" \
                        << "vob"

#endif // HEADER_DEFINES

/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ThumbnailRunnable.h
*       @class  ThumbnailRunnable
*	Représente une instance runnable (thread).
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      3.5
*	@version    3.5
*       @date       2011-2012
*******************************************************************************/

#ifndef THUMBNAILRUNNABLE_H
#define THUMBNAILRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QByteArray>

#include "mtn/mtn.h"

#ifdef __cplusplus
extern "C"
 {
 extern struct params parameters; // params data & info
 extern int process_file();
 }
#endif

class ThumbnailItem;
class MainWindow;

class ThumbnailRunnable : public QRunnable
{
    public:
    explicit ThumbnailRunnable(MainWindow *main_window, ThumbnailItem *item);

    private:
    ThumbnailItem *item;
    MainWindow    *main_window;
    QByteArray     argv0Array;
    QByteArray     F_ts_fontnameArray;
    QByteArray     f_fontnameArray;
    QByteArray     o_suffixArray;
    QByteArray     O_outdir;
    QByteArray     T_textArray;

    protected:
    void run();
};

#endif // THUMBNAILRUNNABLE_H

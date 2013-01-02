/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ThumbnailItem.h
*       @class  ThumbnailItem
*	Représente un item de type Thumbnail.
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

#ifndef THUMBNAILITEM_H
#define THUMBNAILITEM_H

#include <QObject>
#include <QTime>
#include <QUrl>
#include <QListWidgetItem>
#include <QMediacontent>
#include <QMediaplayer>

class ThumbnailItem : public QObject , public QListWidgetItem
{
    Q_OBJECT

    public:
    explicit ThumbnailItem(QUrl filepath);
    explicit ThumbnailItem(ThumbnailItem &other);
    virtual ~ThumbnailItem();

    private:
    bool          readable;
    QUrl          filePath;
    QUrl          filePathOutput;
    QTime         lowerQTime;
    QTime         upperQTime;
    QTime         totalDurationQTime;
    QMediaPlayer* mediaPlayer;

    public:
    void setFilePath(QUrl path);
    void setFilePathOutput(QUrl path);
    void setLowerTime(QTime t);
    void setUpperTime(QTime t);
    void setTotalDuration(QTime t);

    QUrl    getFilePath();
    QUrl    getFilePathOutput();
    QTime   getLowerTime();
    QTime   getUpperTime();
    QTime   getTotalDuration();
    double  getBeginOmmitSecs();
    double  getEndOmmitSecs();

    /**
    *@brief Vrai si le média est lisible, faux sinon.
    *@return Bool - Vrai ou faux.
    */
    bool   isReadable() {return readable;}

    private slots:
    void manageDuration(qint64 duration);
    void manageError(QMediaPlayer::Error error);
};

#endif // THUMBNAILITEM_H

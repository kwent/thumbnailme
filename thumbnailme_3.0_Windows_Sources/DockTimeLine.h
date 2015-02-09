/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockTimeLine.cpp
*       @class  DockTimeLine
*	Cette classe permet la génération du dock TimeLine.
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


#ifndef HEADER_DOCKTIMELINE
#define HEADER_DOCKTIMELINE

#include <QDockWidget>
#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QtMultimediaKit/qmediaplayer.h>
#include <QObject>
#include <QTime>
#include <QxtSpanSlider>

#include "ThumbnailItem.h"
#include "libQt+.h"

class DockTimeLine : public QFrame
{
    Q_OBJECT

    public:
    explicit DockTimeLine(QWidget *main_window = 0);
    virtual ~DockTimeLine();

    private:
    ThumbnailItem *thumbnailItem;
    QxtSpanSlider *spanSlider;
    QLabel        *titleWidgetLabel;
    QLabel        *spanSliderDuration;
    QLabel        *spanSliderLowerLabel;
    QLabel        *spanSliderUpperLabel;
    QTime         lowerQTime;
    QTime         upperQTime;

    private:
    void retranslate();

    public:
    ThumbnailItem* getCurrentItem();

    protected:
    void changeEvent(QEvent* event);

    public slots:
    void update(QListWidgetItem *item);
    void manageErrors(QMediaPlayer::Error error);
    void updateLowerLabel(int lower);
    void updateUpperLabel(int upper);
    void clear();
};

#endif // HEADER_DOCKTIMELINE

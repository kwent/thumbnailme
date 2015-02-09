/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ProcessingStatusBar.h
*       @class  ProcessingStatusBar
*	Cette classe permet la génération de la fenêtre de chargement lors du lancement de la génération de la vignette.
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      2.0
*	@version    3.0
*       @date       2011-2012
*******************************************************************************/

#ifndef HEADER_PROCESSINGSTATUSBAR
#define HEADER_PROCESSINGSTATUSBAR

#include "defines.h"
#include <QtGui/QStatusBar>
#include <QEvent>
#include <QLabel>
#include <QProgressBar>


class ProcessingStatusBar : public QStatusBar
{

    Q_OBJECT

    public:
    explicit ProcessingStatusBar(QWidget *parent = 0);
    virtual ~ProcessingStatusBar();

    private:
    int          i; // current file's number
    int          total; // number of files to process
    QString      fileName; // current file's name
    QLabel       *progressionlabel;
    QLabel       *statusLabel;
    QProgressBar *progressBar;

    private:
    void retranslate();

    public:
    void setFilesCount(int count);

    protected:
    void changeEvent(QEvent* event);

    public slots:
    void setStatus(int current, QString fileName);
};

#endif // HEADER_PROCESSINGSTATUSBAR

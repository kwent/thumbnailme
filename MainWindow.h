/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	MainWindow.h
*       @class  MainWindow
*	Cette classe permet la génération  de la fenêtre principale de Thumbnail Me.
*       @attention  Qt eXTension library required - http://www.libqxt.org/
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

#ifndef HEADER_MainWindow
#define HEADER_MainWindow

#include <QtGui>
#include <QObject>
#include <QMainWindow>

class ConfigWidget;
class DockInputOutput;
class DockConf;
class DockStyles;
class DockTimeLine;
class DockThreadsPool;
class DockThreadsLog;
class ImageShackLoginWidget;
class IniManager;
class PreviewGraphicView;
class SettingsWidget;
class SuccessDialog;
class ThumbnailEngine;
class ProcessingStatusBar;
class HelpWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    explicit MainWindow();
    virtual ~MainWindow();

    private:

    QSettings   *settings;
    bool        loadingFinishedBoolean;

    QToolBar    *toolBar;

    QMenu       *fileMenu;
        QAction *openMediasAction;
        QAction *openSettingsAction;

    QMenu   *openRecentSettingsAction;
        QAction *saveAction;
        QAction *saveUnderAction;
        QAction *printAction;
        QAction *quitAction;

    QMenu       *editionMenu;
        QAction *settingsAction;

    QMenu       *viewMenu;
        QAction *zoomInAction;
        QAction *zoomOutAction;
        QAction *clearSceneAction;
        QAction *fullScreenAction;

    QMenu       *configurationMenu;
		QAction *configuration1;
		QAction *configuration2;
		QAction *configuration3;
		QAction *configuration4;

		QAction *configuration5;
		QAction *configuration6;
		QAction *configuration7;
		QAction *configuration8;

		QAction *configuration9;
		QAction *configuration10;
		QAction *configuration11;
		QAction *configuration12;

		QAction *configuration13;
		QAction *configuration14;
		QAction *configuration15;
		QAction *configuration16;

		QAction *configuration17;
		QAction *configuration18;
		QAction *configuration19;
		QAction *configuration20;

		QAction *configuration21;
		QAction *configuration22;
		QAction *configuration23;
		QAction *configuration24;

    QMenu       *aboutMenu;
        QAction *aboutThumbnailMeAction;
        QAction *aboutQtAction;
        QAction *helpAction;
        QAction *donateAction;
        QAction *websiteAction;

    QDockWidget *configurationDockWidget;

    private:

    void    buildFontsCache();

    void    createDocks();
    void    createMenuBar();
    void    createMenuConnections();
    void    createToolBar();

    void    initializeMenuItems();
    void    initializeActions();
    bool    isvalidExtension(QString filePath);

    void    restoreWindowState();

    void    retranslate();

    protected:
    void    changeEvent(QEvent * e);
    void    closeEvent(QCloseEvent *e);
    void    dragEnterEvent(QDragEnterEvent *e);
    void    dropEvent(QDropEvent *e);
    void    keyPressEvent(QKeyEvent *e);
    void    showEvent (QShowEvent *e);

    public:
    DockInputOutput         *mpDockInputOutput;
    DockConf                *mpDockConf;
    DockStyles              *mpDockStyles;
    DockTimeLine            *mpDockTimeline;
    DockThreadsPool         *mpDockThreadsPool;
    ImageShackLoginWidget   *mpImageShackLoginWidget;
    HelpWidget              *mpHelpWidget;
    IniManager              *mpIniManager;
    PreviewGraphicView      *mpPreviewGraphicView;
    SettingsWidget          *mpSettingsWidget;
    SuccessDialog           *mpSuccessDialog;
    ThumbnailEngine         *mpThumbnailEngine;
    DockThreadsLog          *mpDockThreadsLog;
    ProcessingStatusBar     *processStatusBar;

    public:
    QMenu *getActionOpenRecent();

    private slots:
    void buildFontsCacheEngine();

    public slots:
    void aboutThumbnailme();
    void donateThumbnailme();
    void loadLastConfiguration();
    void manageFullScreen();
    void websiteThumbnailme();

};
#endif

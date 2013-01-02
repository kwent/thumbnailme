/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	PreviewGraphicView.h
*       @class  PreviewGraphicView
*	Cette classe permet la génération du Dock de prévisualisation.
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

#ifndef HEADER_PREVIEWGRAPHICVIEW
#define HEADER_PREVIEWGRAPHICVIEW

#include <QtOpenGL>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrinterInfo>

class MainWindow;

class PreviewGraphicView: public QGraphicsView
{
    Q_OBJECT

    public:
    explicit PreviewGraphicView(MainWindow * main_window, QAction *zoomInAction, QAction *clearSceneAction, QAction *zoomOutAction , QAction *printAction);
    virtual ~PreviewGraphicView();

    private:
    MainWindow              *main_window;

    QSettings               *settings;
    QGraphicsPixmapItem     *previewPixmapItem;
    QGraphicsScene          *scene;
    QString                 currentPixmapPathLoaded;
    bool                    animatedPixmap;

    QMenu          *contextMenu;
        QAction    *openInViewerSystemAction;
        QAction    *zoomInAction;
        QAction    *zoomOutAction;
        QAction    *clearSceneAction;
        QAction    *saveAsAction;
        QAction    *copyAction;
        QAction    *printAction;


    private:
    void animationIntro(QGraphicsPixmapItem *pixmap);
    void animationPixmap(QGraphicsPixmapItem *pixmap);
    void retranslate();

    protected:
    void changeEvent(QEvent* event);
    void contextMenuEvent( QContextMenuEvent *e );
    void keyPressEvent ( QKeyEvent * e ) ;
    void mouseDoubleClickEvent ( QMouseEvent * e ) ;
    void wheelEvent ( QWheelEvent * e );

    public:
    QPixmap getCurrentPixmap();
    void    setAnimatedPixmap(bool value);
    void    setViewportModeOpenGL(bool value);

    public slots:
    void copyToClipboard();
    void clear();
    void manageQActionsState();
    void openInViewerSystem();
    void openPrintPreviewDialog();
    void print(QPrinter *printer);
    void saveAs();
    void setPreview(QString Namefile);
    void zoomIn ();
    void zoomOut();
};

#endif // HEADER_PREVIEWGRAPHICVIEW

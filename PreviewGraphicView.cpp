/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	PreviewGraphicView.cpp
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
*       @version    3.0
*       @date       2011-2012
*******************************************************************************/

#include "defines.h"
#include "PreviewGraphicView.h"
#include "DockConf.h"
#include "SuccessDialog.h"
#include "MainWindow.h"
#include "ThumbnailListwidget.h"

/**
*@brief Constructeur.
*@param *main_window        Fenêtre principale de Thumbnail me.
*@param *zoomInAction       QAction de la fonction zoomIn.
*@param *zoomOutAction      QAction de la fonction zoomOut.
*@param *clearSceneAction   QAction de la fonction clearScene.
*@param *printAction        QAction de la fonction Impression.
*/
PreviewGraphicView::PreviewGraphicView(MainWindow * main_window, QAction *zoomInAction, QAction *zoomOutAction ,QAction *clearSceneAction, QAction *printAction) : QGraphicsView(main_window)
{
    this->main_window = main_window;
    this->zoomInAction = zoomInAction;
    this->zoomOutAction = zoomOutAction;
    this->clearSceneAction = clearSceneAction;
    this->printAction = printAction;
    this->animatedPixmap = true;
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true); //ignore mouse
    this->setFocusPolicy( Qt::NoFocus );//ignore keyboard

    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    scene = new QGraphicsScene(this);
    previewPixmapItem = scene->addPixmap(QPixmap(":sprites/about.png"));

    animationIntro(previewPixmapItem);

    this->setScene(scene);
    this->setInteractive(false);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QTimer::singleShot(3000, scene, SLOT(clear()));

    if (settings->value("Extras/backgroundColorPreviewWindow").toString().isEmpty())
        setBackgroundBrush(QBrush(Qt::lightGray));
    else
        setBackgroundBrush(QBrush(QColor("#"+settings->value("Extras/backgroundColorPreviewWindow").toString())));

    //Construit le contextMenu-> contextuel
    contextMenu = new QMenu(this);

    openInViewerSystemAction = contextMenu->addAction(QIcon( ":/sprites/run.png" ),QString());
    contextMenu->addSeparator ();
        contextMenu->addAction(zoomInAction);
        contextMenu->addAction(zoomOutAction);
        contextMenu->addAction(clearSceneAction);
    contextMenu->addSeparator ();
        saveAsAction =  contextMenu->addAction(QIcon( ":/sprites/save.png" ),QString());
        saveAsAction->setShortcut(QKeySequence(QKeySequence::SaveAs));
        copyAction =  contextMenu->addAction(QIcon( ":/sprites/picture clipping.png" ),QString());
        copyAction->setShortcut(QKeySequence(QKeySequence::Copy));
        contextMenu->addAction(printAction);

    this->retranslate();

    connect(openInViewerSystemAction, SIGNAL(triggered()),this, SLOT(openInViewerSystem()));
    connect(zoomInAction,             SIGNAL(triggered()),this, SLOT(zoomIn()));
    connect(zoomOutAction,            SIGNAL(triggered()),this, SLOT(zoomOut()));
    connect(clearSceneAction,         SIGNAL(triggered()),this, SLOT(clear()));
    connect(saveAsAction,             SIGNAL(triggered()),this, SLOT(saveAs()));
    connect(copyAction,               SIGNAL(triggered()),this, SLOT(copyToClipboard()));
    connect(printAction,              SIGNAL(triggered()),this, SLOT(openPrintPreviewDialog()));
    connect(scene,                    SIGNAL(changed(const QList<QRectF> &)),this,SLOT(manageQActionsState()));
}

/**
*@brief Destructeur.
*/
PreviewGraphicView::~PreviewGraphicView()
{
}

/**
*@brief Setter de la vignette à afficher.
*@param absolutePathFile    Chemin absolu du fichier.
*/
void PreviewGraphicView::setPreview(QString absolutePathFile)
{
    qDebug() << "PREVIEW PATH" << absolutePathFile;

    this->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    this->currentPixmapPathLoaded = absolutePathFile;

    //Clear previous scene
    scene->clear();

    previewPixmapItem = scene->addPixmap(QPixmap(absolutePathFile));

    //200 pour décalage verticale de l'image vers le haut OK doit être égale au i de l'animation.
    int verticalOffset = 200;
    if(!this->animatedPixmap)
      verticalOffset=0;

    scene->setSceneRect(0,verticalOffset,previewPixmapItem->pixmap().width(),previewPixmapItem->pixmap().height());

    animationPixmap(previewPixmapItem);

    this->setScene(scene);
    this->setInteractive(true);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setTransformationAnchor(AnchorUnderMouse);
    this->setResizeAnchor(AnchorViewCenter);
    this->fitInView(previewPixmapItem,Qt::KeepAspectRatio);

    contextMenu->setEnabled(true);
    if (absolutePathFile.contains(QDir::toNativeSeparators(QDir::tempPath()), Qt::CaseInsensitive))
        openInViewerSystemAction->setDisabled(true);
    else openInViewerSystemAction->setEnabled(true);
}


/**
*@brief Anime le pixmap d'introduction lors de son affichage.
*/
void PreviewGraphicView::animationIntro(QGraphicsPixmapItem *pixmap)
{
    /*-------------Animation rebond-------------*/
     QTimeLine *timeline = new QTimeLine(2000);
      timeline->setEasingCurve(QEasingCurve::OutBounce);
     QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
      animation->setItem(pixmap);
      animation->setTimeLine(timeline);

      for (int i = 0; i < 200; ++i)
        animation->setTranslationAt(i / 200.0,  0 , i  );

      timeline->start();
    /*------------------------------------------*/
}

/**
*@brief Anime le pixmap lors de son affichage.
*/
void PreviewGraphicView::animationPixmap(QGraphicsPixmapItem *pixmap)
{
    if(this->animatedPixmap)
    {
    /*-------------Animation rebond-------------*/
     QTimeLine *timeline = new QTimeLine(2000);
      timeline->setEasingCurve(QEasingCurve::OutBounce);
     QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
      animation->setItem(pixmap);
      animation->setTimeLine(timeline);

      for (int i = 0; i < 200; ++i)
        animation->setTranslationAt(i / 200.0,  0 , i  );

      timeline->start();
    }
    /*------------------------------------------*/
}

/**
*@brief Réimplémentation de wheelEvent pour zoomer/dézoomer la vignette à l'aide de la molette souris.
*@param *e    Evénement.
*/
void PreviewGraphicView::wheelEvent ( QWheelEvent * e )
{
    if(!scene->items().isEmpty())
    {
        if (e->delta() > 0)
           zoomIn();
        else if (e->delta() < 0)
           zoomOut();
    }

    QGraphicsView::wheelEvent(e);
}


/**
*@brief  Retourne le Pixmap courant.
*@return QPixmap.
*/
QPixmap PreviewGraphicView::getCurrentPixmap()
{
    //if(this->previewPixmapItem != 0)
         return this->previewPixmapItem->pixmap();
    //else return QPixmap;
}

/**
*@brief Zoom In.
*/
void PreviewGraphicView::zoomIn()
{
    scale(1.2, 1.2);
}

/**
*@brief Zoom Out.
*/
void PreviewGraphicView::zoomOut()
{
    scale(1 / 1.2, 1 / 1.2);
}

/**
*@brief Réimplémentation de mouseDoubleClickEvent pour ouvrir la vignette dans le visionneur d'image par défaut du système.
*@param *e    Evénement.
*/
void PreviewGraphicView::mouseDoubleClickEvent ( QMouseEvent * e )
{
    if (!scene->items().isEmpty() && e->button() == Qt::LeftButton && !currentPixmapPathLoaded.contains(QDir::toNativeSeparators(QDir::tempPath()),Qt::CaseInsensitive))
            openInViewerSystem();

    QGraphicsView::mouseDoubleClickEvent(e);
}

/**
*@brief Réimplémentation de keyPressEvent pour zoomer/dézoomer la vignette à l'aide du clavier.
*@param *e    Evénement.
*/
void PreviewGraphicView::keyPressEvent ( QKeyEvent * e )
{
    if(e->matches(QKeySequence::ZoomIn))
        zoomIn();
    else if (e->matches(QKeySequence::ZoomOut))
        zoomOut();

    QGraphicsView::keyPressEvent(e);
}

/**
*@brief Réimplémentation de contextMenuEvent pour dérouler le menu clic droit.
*@param *e    Evénement.
*/
void PreviewGraphicView::contextMenuEvent( QContextMenuEvent * e )
{
    if (!currentPixmapPathLoaded.isEmpty())
        contextMenu->exec(e->globalPos());

    QGraphicsView::contextMenuEvent(e);
}

/**
*@brief Ouvre la vignette courante dans le visionneur d'image par défaut du système.
*/
void PreviewGraphicView::openInViewerSystem()
{
    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(currentPixmapPathLoaded)))
        QMessageBox::critical(this,_ERROR_, APPLICATION_NAME +" "+ tr("failed to open this file in your default image viewer."));
}

/**
*@brief Copie la vignette courante dans presse-papier.
*/
void PreviewGraphicView::copyToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(previewPixmapItem->pixmap(),QClipboard::Clipboard);
}

/**
*@brief Enregistre l'image sous...
*/
void PreviewGraphicView::saveAs()
{
    QFileDialog saveAsDialog(this,tr("Save File"),QString(),"Windows bitmap (*.bmp);;Joint Photographic Experts Group (*.jpeg);;Portable Network Graphics (*.png);;Tagged Image File Format (*.tiff)");
    saveAsDialog.setAcceptMode(QFileDialog::AcceptSave);

    if (saveAsDialog.exec())
    {
        if (!saveAsDialog.selectedFiles().isEmpty())
        {
            QString format;

            if(saveAsDialog.selectedNameFilter().contains(".bmp"))
                format = "bmp";
            else if(saveAsDialog.selectedNameFilter().contains(".jpeg"))
                format = "jpeg";
            else if(saveAsDialog.selectedNameFilter().contains(".png"))
                format = "png";
            else if(saveAsDialog.selectedNameFilter().contains(".tiff"))
                format = "tiff";

            saveAsDialog.setDefaultSuffix(format);

            if(previewPixmapItem->pixmap().save(saveAsDialog.selectedFiles().first(),format.toLatin1().constData(),main_window->mpDockConf->getQuality()))
            {
                SuccessDialog successDialog(main_window,saveAsDialog.directory().absolutePath());
                successDialog.getListWidget()->addItem(saveAsDialog.selectedFiles().first());
                successDialog.exec();
            }
            else QMessageBox::warning(this,_WARNING_,tr("Saving the file failed"));
        }
    }
}

/**
*@brief Ouvre la fenêtre de prévisualisation du QPixmap courant.
*/
void PreviewGraphicView::openPrintPreviewDialog()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);

    if(!QPrinterInfo::availablePrinters().isEmpty())
    {
        QPrintPreviewDialog *preview = new QPrintPreviewDialog(&printer,this);
        connect(preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
        preview->exec();
    }
    else QMessageBox::critical(this, _ERROR_, tr("No Printer Detected"));
}

/**
*@brief Imprime la vignette courante.
*@param *printer - QPrinter Object.
*/
void PreviewGraphicView::print(QPrinter *printer)
{
    QPainter painter(printer);
    this->scene->render(&painter);
}

/**
*@brief Active ou désactive l'openGL sur la fenêtre de prévisualisation.
*@param value    Vrai ou faux.
*/
void PreviewGraphicView::setViewportModeOpenGL(bool value)
{
    if (value)
    {
        QGLWidget *openGL =  new QGLWidget(QGLFormat(QGL::SampleBuffers));
        this->setViewport(openGL);
    }
    else
    {
        this->setViewport(0);
    }
}


/**
*@brief Efface la scène.
*/
void PreviewGraphicView::clear()
{
    scene->clear();
    contextMenu->setDisabled(true);
}

/**
*@brief Gère les QAction en fonction de la présence de vignette dans la fenêtre de prévisualisation.
*/
void PreviewGraphicView::manageQActionsState()
{
    bool state = (scene->items().isEmpty()) ? false : true;

    zoomInAction->setEnabled(state);
    zoomOutAction->setEnabled(state);
    clearSceneAction->setEnabled(state);
    printAction->setEnabled(state);
}

/**
*@brief Setter qui permet d'animer le pixmap lors de l'affichage du rendu.
*@param value   Vrai ou faux.
*/
void PreviewGraphicView::setAnimatedPixmap(bool value)
{
  this->animatedPixmap = value;
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void PreviewGraphicView::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();

     QGraphicsView::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void PreviewGraphicView::retranslate()
{
    openInViewerSystemAction->setText( tr("Open to my default picture viewer") );
    saveAsAction->setText( tr("Save As") );
    copyAction->setText( tr("Copy to clipboard") );
}

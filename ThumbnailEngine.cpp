/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ThumbnailEngine.cpp
*       @class  ThumbnailEngine
*	Cette classe est le moteur de ThumbnailMe, c'est dans cette classe que le processus est exécuté.
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

#include "defines.h"
#include "ThumbnailEngine.h"
#include "MainWindow.h"
#include "DockInputOutput.h"
#include "DockStyles.h"
#include "DockConf.h"
#include "DockTimeLine.h"
#include "DockThreadsPool.h"
#include "SuccessDialog.h"
#include "PreviewGraphicView.h"
#include "ThumbnailItem.h"
#include <QDebug>
#include "ThumbnailListwidget.h"
#include "ThumbnailRunnable.h"
#include "VerboseWindow.h"

/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/
ThumbnailEngine::ThumbnailEngine(MainWindow *main_window)
{
    this->main_window = main_window;
    this->currentItem = 0;
    pool = new QThreadPool(this);
    pool->setMaxThreadCount(QThread::idealThreadCount());
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);
    connect( this, SIGNAL(itemTooShortDuration (ThumbnailItem *)), this , SLOT(successDialogItemRemove(ThumbnailItem *)) );
}

/**
*@brief Destructeur.
*/
ThumbnailEngine::~ThumbnailEngine()
{
    delete main_window;
    delete img;
    delete currentItem;
}

/**
*@brief  Vérifie si le binaire "mtn" existe bien.
*@return bool - Vrai ou faux.
*/
bool ThumbnailEngine::isBinaryExists()
{
    return QFile::exists(DEFAULT_PATH_MTN);
}

/**
*@brief Lance le processus de génération de vignette.
*@param mode    Mode de conversion.
*/
void ThumbnailEngine::run(int mode)
{
   switch (mode)
   {
     case(1):this->modeConversion = SIMPLEMOD;break;
     case(2):this->modeConversion = PREVIEWMOD;break;
   }

    if (modeConversion == SIMPLEMOD)
    {
        if (main_window->mpDockInputOutput->getListWidget()->count() != 0)
        {
            if(!main_window->mpDockInputOutput->isSameSourceChecked())
            {
                if (!main_window->mpDockInputOutput->getPathOutput().isEmpty())
                    if(QDir(main_window->mpDockInputOutput->getPathOutput()).exists())
                        if(!main_window->mpDockStyles->isNoFontDefined())
                          //if(isBinaryExists())
                            launchProcess(main_window->mpDockInputOutput->getThumbnailList());
                          //else QMessageBox::critical((QWidget *) this->parent(),_ERROR_,tr("Mtn binary not found. Operation cancelled."));
                        else QMessageBox::warning(main_window,_WARNING_,tr("No fonts defined"));
                    else QMessageBox::warning(main_window,_ERROR_,tr("Output path does not exist"));
               else QMessageBox::warning(main_window,_WARNING_,tr("Select an output folder, please"));
            }
            else
            {
                if(!main_window->mpDockStyles->isNoFontDefined())
                  //if(isBinaryExists())
                    launchProcess(main_window->mpDockInputOutput->getThumbnailList());
                  //else QMessageBox::critical((QWidget *) this->parent(),_ERROR_,tr("Mtn binary not found. Operation cancelled."));
                else QMessageBox::warning(main_window,_WARNING_,tr("No fonts defined"));
            }
        }
        else QMessageBox::warning(main_window,_WARNING_,tr("No file(s) loaded"));

    }
    else if (modeConversion == PREVIEWMOD)
    {
        if (!main_window->mpDockInputOutput->getListWidget()->selectedItems().isEmpty())
            if(!main_window->mpDockStyles->isNoFontDefined())
                //if(isBinaryExists())
                {
                    QLinkedList <ThumbnailItem*> l;
                    l.append(main_window->mpDockInputOutput->getCurrentItem());
                    launchProcess(l);
                }
                //else QMessageBox::critical((QWidget *) this->parent(),_ERROR_,tr("Mtn binary not found. Operation cancelled."));
            else QMessageBox::warning(main_window,_WARNING_,tr("No fonts defined"));
        else QMessageBox::warning(main_window,_WARNING_,tr("No file selected"));
    }
}

/**
*@brief Lance le processus.
*@param listInputFile    Liste des fichiers à vignetter.
*/
void ThumbnailEngine::launchProcess(QLinkedList <ThumbnailItem*> listInputFile)
{
    //Disable Docks - Security
    this->main_window->mpDockInputOutput->setDisabled(true);
    this->main_window->mpDockTimeline->setDisabled(true);

    //Init
    this->listInputFile =  QLinkedList <ThumbnailItem*> (listInputFile);
    this->initSuccessDialog(QLinkedList<ThumbnailItem*> (this->listInputFile));

    main_window->mpDockThreadsPool->threeWidget->clear();

    while(!this->listInputFile.isEmpty())
    {
        currentItem = this->listInputFile.takeFirst();
        ThumbnailRunnable *task = new ThumbnailRunnable(this->main_window, currentItem, settings->value("Extras/outputSuffix").toString() , this->modeConversion);
        task->setAutoDelete(true);

        main_window->mpDockThreadsPool->setWindowTitle(QString("Threads actifs: %1").arg(pool->activeThreadCount()));
        main_window->mpDockThreadsPool->addThumbnailItem(currentItem);
        connect(task, SIGNAL(started(ThumbnailItem*)), main_window->mpDockThreadsPool, SLOT(threadStarted(ThumbnailItem*)), Qt::QueuedConnection);
        connect(task, SIGNAL(finished(ThumbnailItem*)), main_window->mpDockThreadsPool, SLOT(threadFinished(ThumbnailItem*)), Qt::QueuedConnection);
        connect(task, SIGNAL(finished(ThumbnailItem*)), this, SLOT(success(ThumbnailItem*)), Qt::QueuedConnection);
        pool->start(task);
    }
}

/**
*@brief Détermine le chemin absolu d'un fichier selon ses paramètres.
*@param pathOutput           Chemin de sortie du fichier.
*@param absolutePathInput    Chemin absolu du fichier d'entrée.
*@param suffix               Suffixe du fichier.
*@param format               Format du fichier.
*/
QString ThumbnailEngine::absoluteFilePathOutput(QString pathOutput, QString absolutePathInput,QString suffix,QString format)
{
    QString absolutPathOutput;

    QFileInfo fileInfo (QDir::toNativeSeparators(absolutePathInput));
    if (!format.isEmpty())
      absolutPathOutput = QDir::toNativeSeparators(pathOutput + "/" + fileInfo.fileName().replace("."+fileInfo.suffix(),suffix+"."+format));
    else absolutPathOutput = QDir::toNativeSeparators(pathOutput + "/" + fileInfo.fileName().replace("."+fileInfo.suffix(),suffix));

    return absolutPathOutput.replace("\\\\","\\").replace("//","/");
}

/**
*@brief  Apelle la fenêtre de succès.
*/
void ThumbnailEngine::initSuccessDialog(QLinkedList <ThumbnailItem*> listInputFile)
{
    main_window->mpSuccessDialog->clearListWidget();

    if(!main_window->mpDockInputOutput->isSameSourceChecked() && this->mode() == SIMPLEMOD)
    {
        main_window->mpSuccessDialog->setPathOpenFolder(main_window->mpDockInputOutput->getPathOutput());

        foreach(ThumbnailItem *item, listInputFile)
        {
            item->setFilePathOutput(QUrl::fromLocalFile(absoluteFilePathOutput(main_window->mpDockInputOutput->getPathOutput(),item->getFilePath().toString(),settings->value("Extras/outputSuffix").toString(),main_window->mpDockConf->getFormatFile())));
            main_window->mpSuccessDialog->addItem(item);
        }
    }
    else if(main_window->mpDockInputOutput->isSameSourceChecked() && this->mode() == SIMPLEMOD)
    {
        main_window->mpSuccessDialog->setPathOpenFolder(QString());

        foreach(ThumbnailItem *item, listInputFile)
        {
            item->setFilePathOutput(QUrl::fromLocalFile(absoluteFilePathOutput(QDir::toNativeSeparators(QFileInfo(item->getFilePath().toString()).canonicalPath()),item->getFilePath().toString(),settings->value("Extras/outputSuffix").toString(),main_window->mpDockConf->getFormatFile())));
            main_window->mpSuccessDialog->addItem(item);
        }
    }
}

/**
*@brief Converti le fichier crées temporairement dans le format et la qualité sélectionné par l'utilisateur.
*@param o   Item à convertir.
*/
void ThumbnailEngine::convertToFormat(QObject *o)
{
    ThumbnailItem *item = qobject_cast<ThumbnailItem*>(o);

    QString suffix = settings->value("Extras/outputSuffix").toString();

    QString path = absoluteFilePathOutput(QDir::tempPath(),item->getFilePath().toString(),DEFAULT_TMP_EXTENSION);

    QString output;
    if (modeConversion == SIMPLEMOD && !main_window->mpDockInputOutput->isSameSourceChecked())
        output = main_window->mpDockInputOutput->getPathOutput() + "/" + QFileInfo(path).completeBaseName() + suffix +"."+ main_window->mpDockConf->getFormatFile();
    else if (modeConversion == SIMPLEMOD && main_window->mpDockInputOutput->isSameSourceChecked())
        output = QDir::toNativeSeparators(QFileInfo(currentItem->getFilePath().toString()).canonicalPath() + "/")+ QFileInfo(path).completeBaseName() + suffix + "."+ main_window->mpDockConf->getFormatFile();

    img = new QImage(path);
        img->save(output,0,main_window->mpDockConf->getQuality());
}


/**
*@brief   Supprimer les fichiers temporaires générés par le moteur.
*@remarks DEFAULT_TMP_EXTENSION définit dans defines.h.
*/
void ThumbnailEngine::deleteTemporaryFiles()
{
    QDir tmpFolder = QDir::tempPath();
    QStringList filters;
    filters << "*" + DEFAULT_TMP_EXTENSION;
    tmpFolder.setNameFilters(filters);

    QFileInfoList temporaryFiles = tmpFolder.entryInfoList();

    while (!temporaryFiles.isEmpty())
    {
        QFile::remove(temporaryFiles.first().absoluteFilePath());
        temporaryFiles.removeFirst();
    }
}

/**
*@brief Change le mode du moteur.
*@param mode    Mode du moteur.
*/
void ThumbnailEngine::setMode(Mode mode)
{
    modeConversion = mode;
}

/**
*@brief  Retourne le mode du moteur.
*@return mode - Mode du moteur.
*/
ThumbnailEngine::Mode ThumbnailEngine::mode() const
{
    return this->modeConversion;
}

/**
*@brief Construit le QStringList Output.
*/
void ThumbnailEngine::buildOutput()
{
    QString outputString = process->readAllStandardOutput().trimmed();
    currentOutput << outputString.split(QString("\n"),QString::SkipEmptyParts);
}

/**
*@brief Détecte si le fichier est trop court pour être traité par Mtn.
*@brief Trop court si Mtn génère moins de 4 lignes.
*/
void ThumbnailEngine::detectShortDuration()
{
    this->main_window->mpVerboseWindow->setVerbose(currentOutput);

    if (currentOutput.count() <= 4)
    {
        this->main_window->mpVerboseWindow->setVerbose("<font color=\"red\">Error: The duration of this file seems too short.</font>");
        emit itemTooShortDuration(this->currentItem);
    }
}

/**
*@brief Retire les items non traité de la successDialog car trop court via le signal itemTooShortDuration.
*@param item - Item à retirer.
*/
void ThumbnailEngine::successDialogItemRemove(ThumbnailItem * item)
{
    main_window->mpSuccessDialog->removeItem(item);
}

/**
*@brief  Envoie une image en preview.
*/
void ThumbnailEngine::success(ThumbnailItem* item)
{
    if(listInputFile.isEmpty())
    {
    //1 Re Enable Docks
        this->main_window->mpDockInputOutput->setEnabled(true);

        if(this->main_window->mpDockTimeline->getCurrentItem() != NULL && this->main_window->mpDockTimeline->getCurrentItem()->isReadable())
          this->main_window->mpDockTimeline->setEnabled(true);

    //2 Preview
        QString suffix = settings->value("Extras/outputSuffix").toString();

        if (modeConversion == SIMPLEMOD && !main_window->mpDockInputOutput->isSameSourceChecked())
            main_window->mpPreviewGraphicView->setPreview(absoluteFilePathOutput(main_window->mpDockInputOutput->getPathOutput(),item->getFilePath().toString(),suffix,main_window->mpDockConf->getFormatFile()));
        else if (modeConversion == SIMPLEMOD && main_window->mpDockInputOutput->isSameSourceChecked())
            main_window->mpPreviewGraphicView->setPreview(absoluteFilePathOutput(QDir::toNativeSeparators(QFileInfo(item->getFilePath().toString()).canonicalPath()),item->getFilePath().toString(),suffix,main_window->mpDockConf->getFormatFile()));
        else if (modeConversion == PREVIEWMOD)
            main_window->mpPreviewGraphicView->setPreview(absoluteFilePathOutput(QDir::tempPath(),item->getFilePath().toString(),DEFAULT_TMP_EXTENSION));

    //3 Show SuccessDialog
        if(modeConversion == SIMPLEMOD && main_window->mpSuccessDialog->getListWidget()->count() != 0)
            main_window->mpSuccessDialog->exec();
    }
}

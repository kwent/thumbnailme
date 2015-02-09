/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	SuccessDialog.h
*       @class  SuccessDialog
*	Cette classe permet la génération de la fenêtre "Succès" lorsque la vignette a été générée avec succès.
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

#ifndef HEADER_SUCESSDIALOG
#define HEADER_SUCESSDIALOG

#include <QtGui>
#include <libQt+.h>
#include "ImageShackUploadWidget.h"
#include "ThumbnailListwidget.h"

class SuccessDialog : public QDialog
{
    Q_OBJECT

    public:
    explicit SuccessDialog(QWidget *parent = 0, QString openFolderPath = "");
    virtual ~SuccessDialog();

    private:
    ImageShackUploadWidget *imageShackUploadWidget;
    QLabel                 *textSaveLabel;
    ThumbnailListWidget    *listWidget;
    QString                openFolderPath;
    QPushButton            *openFolderButton;
    QPushButton            *uploadImageShackButton;
    QPushButton            *closeDialogButton;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public:
    int                  addItem(ThumbnailItem *item);
    void                 removeItem(ThumbnailItem *item);
    ThumbnailListWidget* getListWidget();
    void                 setPathOpenFolder(QString path);
    void                 exec();

    private slots:
    void enableUploadButton();

    public slots:   
    void clearListWidget();
    void openFolder();
    void setDoubleClickPathOpenFolder(QListWidgetItem* item);
    void setSelectionPathOpenFolder();
    void uploadToImageShack();
};
#endif // HEADER_SUCESSDIALOG

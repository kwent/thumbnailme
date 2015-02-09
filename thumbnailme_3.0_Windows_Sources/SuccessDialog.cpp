/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	SuccessDialog.cpp
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

#include "SuccessDialog.h"

/**
*@brief Constructeur.
*@param *parent           Widget parent.
*@param openFolderPath    Chemin du dossier à ouvrir pour le bouton "Ouvrir le dossier".
*/
SuccessDialog::SuccessDialog(QWidget *parent, QString openFolderPath) : QDialog(parent)
{
    this->setWindowTitle(parent->windowTitle());
    this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->openFolderPath = openFolderPath;

    textSaveLabel = new QLabel(this);

    openFolderButton = new QPushButton(QIcon(":/sprites/openfolder.png"),QString(),this);
    uploadImageShackButton = new QPushButton(QIcon(":/sprites/imageShack_frog.png"),QString(),this);
    closeDialogButton = new QPushButton(QIcon(":/sprites/quit.png"),QString(),this);

    QLabel *pixmapLabel = new QLabel(this);
        pixmapLabel->setPixmap(QPixmap( ":/sprites/thumbnails-folder.png" ));

    listWidget = new ThumbnailListWidget(this);
        listWidget->setFixedWidth(500);

    QDialogButtonBox *buttonBoxDialog = new QDialogButtonBox(this);
        buttonBoxDialog->addButton(openFolderButton,QDialogButtonBox::AcceptRole);
        buttonBoxDialog->addButton(uploadImageShackButton,QDialogButtonBox::RejectRole);
        buttonBoxDialog->addButton(closeDialogButton,QDialogButtonBox::RejectRole);
        buttonBoxDialog->setCenterButtons(true);

    QVBoxLayout *leftLayout = new QVBoxLayout;
        leftLayout->addWidget(textSaveLabel);
        leftLayout->addWidget(pixmapLabel);

    QHBoxLayout *centerLayout = new QHBoxLayout;
        centerLayout->addLayout(leftLayout);
        centerLayout->addWidget(listWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addLayout(centerLayout);
        mainLayout->addWidget(addHSeparator());
        mainLayout->addWidget(buttonBoxDialog);

    imageShackUploadWidget = new ImageShackUploadWidget(this);

    this->setLayout(mainLayout);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    this->retranslate();

    /*Connections*/
    connect(openFolderButton,       SIGNAL(clicked()), this , SLOT(openFolder()));
    connect(uploadImageShackButton, SIGNAL(clicked()), this , SLOT(uploadToImageShack()));
    connect(closeDialogButton,      SIGNAL(clicked()), this , SLOT(accept()));
    connect(listWidget,             SIGNAL(itemDoubleClicked (QListWidgetItem*)), this, SLOT(setDoubleClickPathOpenFolder(QListWidgetItem*)));
    connect(listWidget,             SIGNAL(itemSelectionChanged()), this, SLOT(setSelectionPathOpenFolder()));
    connect(listWidget,             SIGNAL(itemChanged (QListWidgetItem *)), this, SLOT(enableUploadButton()));

}

/**
*@brief Destructeur.
*/
SuccessDialog::~SuccessDialog()
{
    delete imageShackUploadWidget;
}

/**
*@brief  Ajoute un item à la ThumbnailListWidget.
*@param  item   Item à ajouter.
*@return int - Nombre d'item dans la QListWidget.
*/
int SuccessDialog::addItem(ThumbnailItem *item)
{
    /*Copie car
    Warning: A QListWidgetItem can only be added to a QListWidget once.
    Adding the same QListWidgetItem multiple times to a QListWidget will result in undefined behavior.
    */
    ThumbnailItem *i = new ThumbnailItem(*item);
    i->setText(item->getFilePathOutput().toString());
    i->setParent(item);
    i->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    i->setCheckState(Qt::Checked);
    listWidget->addItem(i);

    return listWidget->count();
}

/**
*@brief  Supprime un item de la ThumbnailListWidget.
*@param  item   Item à supprimer.
*/
void SuccessDialog::removeItem(ThumbnailItem *item)
{
    ThumbnailItem *child = item->findChild<ThumbnailItem *>();
    if(child)
        delete child;
}

/**
*@brief  Retourne la liste des Thumbnails.
*@return ThumbnailListWidget* - ThumbnailListWidget.
*/
ThumbnailListWidget* SuccessDialog::getListWidget()
{
    return this->listWidget;
}

/**
*@brief  Efface tous les chemins de la QListWidget.
*/
void SuccessDialog::clearListWidget()
{
    listWidget->clear();
}

/**
*@brief  Fixe le chemin du dossier à ouvrir.
*@param  path    Chemin.
*/
void SuccessDialog::setPathOpenFolder(QString path)
{
    this->openFolderPath = path;
}

/**
*@brief  Fixe le chemin du dossier via la double click
*@param  item    Item sélectionné.
*/
void SuccessDialog::setDoubleClickPathOpenFolder(QListWidgetItem* item)
{
    this->openFolderPath = QFileInfo(item->text()).absolutePath();
    openFolder();
}

/**
*@brief  Fixe le chemin du dossier de l'item courant sélectionné
*/
void SuccessDialog::setSelectionPathOpenFolder()
{
    this->openFolderPath = QFileInfo(listWidget->currentItem()->text()).absolutePath();
    openFolderButton->setEnabled(true);
}


/**
*@brief Ouvre le dossier de destination dont le chemin est openFolderPath.
*/
void SuccessDialog::openFolder()
{
    if(!openFolderPath.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(openFolderPath));
}

/**
*@brief Appelle la fenêtre d'upload surImageShack.
*/
void SuccessDialog::uploadToImageShack()
{
    imageShackUploadWidget->reset();
    imageShackUploadWidget->addData(getItemsListWidget(listWidget,Qt::Checked));
    this->close();
    centerWidget(imageShackUploadWidget);
    imageShackUploadWidget->show();
}

/**
*@brief Enable ou Disable le boutton d'upload.
*/
void SuccessDialog::enableUploadButton()
{
    //Si aucun item est sélectionné
    if(getItemsListWidget(listWidget,Qt::Checked).isEmpty())
         uploadImageShackButton->setEnabled(false);
    else uploadImageShackButton->setEnabled(true);
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void SuccessDialog::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void SuccessDialog::retranslate()
{
    openFolderButton->setText( tr("Open Folder") );
    closeDialogButton->setText( tr("Close") );
}

/**
*@brief Réimplémentation de exec.
*/
void SuccessDialog::exec()
{
    if (getItemsListWidget(listWidget).count() == 1)
    {
     textSaveLabel->setText(tr("<h1>Save file as:</h1>"));
     textSaveLabel->setAlignment(Qt::AlignCenter);
     uploadImageShackButton->setText(tr("Upload to ImageShack"));
    }
    else // Si plus de 1
    {
     textSaveLabel->setText(tr("<h1>Save file(s) as:</h1>"));
     textSaveLabel->setAlignment(Qt::AlignCenter);
      uploadImageShackButton->setText(tr("Upload these files to ImageShack"));
    }

    openFolderButton->setDisabled(true);
    QDialog::exec();
}

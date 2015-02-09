/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockInputOutput.cpp
*       @class  DockInputOutput
*	Cette classe permet la génération du dock "Entrée et sortie".
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
*
*       @changelog  25/09/2011 - Destination Folder Editable.
*******************************************************************************/

#include "DockInputOutput.h"

/**
*@brief Constructeur.
*@param *main_window     Fenêtre principale de Thumbnail me.
*@param *thumbnailEngine Moteur de transformation.
*/

DockInputOutput::DockInputOutput(MainWindow *main_window, ThumbnailEngine *thumbnailEngine) : QDockWidget(main_window)
{
    this->main_window = main_window;
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    this->setObjectName("inputoutputDock");
    this->setAcceptDrops(true);
    this->setFeatures(QDockWidget::DockWidgetMovable);

    thumbnailListWidget = new ThumbnailListWidget(this);

    QGridLayout *batchmodLayout = new QGridLayout;

    loadButton = new QPushButton(QIcon(":/sprites/openfolder.png"),QString());

    resetListButton = new QPushButton(QIcon(":/sprites/recycle-bin-full.png"),QString());
    resetListButton->setDisabled(true);

    runBatchButton = new QPushButton(QIcon(":/sprites/run.png"),QString());
    runBatchButton->setDisabled(true);

    deleteSelectionButton = new QPushButton(QIcon(":/sprites/recycle-bin-full.png"),QString());
    deleteSelectionButton->setDisabled(true);

    pathOutputLabel = new QLabel(tr("Path Output")+":");

    previewSelectionButton = new QPushButton(QIcon(":/sprites/preview.png"),QString());
    previewSelectionButton->setDisabled(true);

    outputButton = new QPushButton(QIcon(":/sprites/openfolder.png"),"...");

    arrowUpButton = new QPushButton(QIcon(":/sprites/arrow_up.png"),QString());
    arrowDownButton = new QPushButton(QIcon(":/sprites/arrow_down.png"),QString());

    arrowUpButton->setDisabled(true);
    arrowDownButton->setDisabled(true);

    pathOutput = new QLineEdit(this);

    sameSourceCheckBox = new QCheckBox(tr("Same folder output as source"));

    QGridLayout * batchModMiddleLayout = new QGridLayout;
    QGridLayout * batchModRightLayout = new QGridLayout;
    QVBoxLayout * arrowsLayout = new QVBoxLayout;

    arrowsLayout->addWidget(arrowUpButton);
    arrowsLayout->addWidget(arrowDownButton);

    batchmodLayout->addLayout(arrowsLayout,0,3);
    batchmodLayout->addWidget( thumbnailListWidget,0,2);
    batchmodLayout->setColumnStretch(2,2);

    batchModMiddleLayout->addWidget( loadButton,0,0 );
    batchModMiddleLayout->addWidget( deleteSelectionButton,1,0);
    batchModMiddleLayout->addWidget( resetListButton,2,0);

    batchModRightLayout->addWidget( sameSourceCheckBox,0,1,Qt::AlignHCenter);

    batchModRightLayout->addWidget( pathOutputLabel,1,0);
    batchModRightLayout->addWidget( pathOutput,1,1);
    batchModRightLayout->addWidget( outputButton,1,2);

    batchModRightLayout->addWidget( previewSelectionButton,2,1);
    batchModRightLayout->addWidget( runBatchButton,3,1);

    batchmodLayout->addLayout(batchModMiddleLayout,0,1);

    batchmodLayout->addWidget(addVSeparator(),0,4);

    batchmodLayout->addLayout(batchModRightLayout,0,5);

    contentWidget = new QWidget(this);
        contentWidget->setLayout(batchmodLayout);

    /*Connections*/
    connect( loadButton,            SIGNAL(clicked()), this, SLOT(loadList()) );
    connect( resetListButton,       SIGNAL(clicked()), this, SLOT(resetListWidget()) );
    connect( deleteSelectionButton, SIGNAL(clicked()), this, SLOT(removeItemSelection()) );
    connect( outputButton,          SIGNAL(clicked()), this, SLOT(openFileDialogPathOutput()) );
    connect( arrowUpButton,         SIGNAL(clicked()), this, SLOT(moveItemUp()) );
    connect( arrowDownButton,       SIGNAL(clicked()), this, SLOT(moveItemDown()) );
    connect( sameSourceCheckBox,    SIGNAL(stateChanged(int)), this, SLOT(disablePathOutput(int)) );
    connect( thumbnailListWidget,   SIGNAL(itemClicked ( QListWidgetItem *)), main_window->mpDockTimeline, SLOT(update( QListWidgetItem * )) );
    connect( thumbnailListWidget,   SIGNAL(itemClicked ( QListWidgetItem *)), this, SLOT(arrowsManager( QListWidgetItem * )) );
    connect( thumbnailListWidget,   SIGNAL(itemSelectionChanged ()),  this, SLOT(enableRemoveSelectionButton()) );
    connect( thumbnailListWidget,   SIGNAL(currentRowChanged ( int )),  this, SLOT(enableResetButton( int )) );
    connect( thumbnailListWidget,   SIGNAL(itemDeleted ()),  this, SLOT(removeItemSelection()) );

    QSignalMapper *signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(runBatchButton,SIMPLE);
    signalMapper->setMapping(previewSelectionButton,PREVIEW);

    connect( signalMapper,          SIGNAL(mapped(int)), thumbnailEngine, SLOT(run(int)) );
    connect( runBatchButton,        SIGNAL(clicked ()),  signalMapper,    SLOT(map()) );
    connect( previewSelectionButton,SIGNAL(clicked ()),  signalMapper,    SLOT(map()) );

    //Par défaut sameSourceCheckBox cochée.
    sameSourceCheckBox->setChecked(true);

    this->setWidget( contentWidget );
    this->retranslate();
}

/**
*@brief Destructeur.
*/
DockInputOutput::~DockInputOutput()
{
}

/**
*@brief  Retourne la QListWidget propre au Dock.
*@return QListWidget* - Pointeur sur la QListWidget du Dock.
*/
ThumbnailListWidget *DockInputOutput::getListWidget()
{
    return thumbnailListWidget;
}

/**
*@brief  Retourne la liste complête des items du QListWidget.
*@return QStringList - Liste des chemins contenus dans la QListWidget.
*/
QStringList DockInputOutput::getAllItemListWidget()
{
    return getItemsListWidget(getListWidget());
}

/**
*@brief  Retourne les chemins des dossiers des items du QListWidget.
*@return QStringList - Liste des chemins.
*/
QStringList DockInputOutput::getAllItemListCanonicalPath()
{
    QStringList canonicalPathStringList;

    foreach(QString item,getAllItemListWidget())
    {
        canonicalPathStringList << QDir::toNativeSeparators(QFileInfo(item).canonicalPath());
    }

    return canonicalPathStringList;
}

/**
*@brief  Retourne le dernier path du QListWidget.
*@return QString - Retourne dernier chemin de la QListWidget.
*/
QString DockInputOutput::getLastItemListWidget()
{
    return getListWidget()->item(getListWidget()->count()-1)->text();
}

/**
*@brief  Retourne le chemin de sortie.
*@return QString - Retourne le chemin de sortie.
*/
QString DockInputOutput::getPathOutput()
{
    return pathOutput->displayText();
}

/**
*@brief  Retourne le ThumbnailItem sélectionné.
*@return ThumbnailItem* - ThumbnailItem.
*/
ThumbnailItem* DockInputOutput::getCurrentItem()
{
    return static_cast<ThumbnailItem*> (this->thumbnailListWidget->currentItem());
}

/**
*@brief  Setteur du chemin du dossier de sortie.
*@param  filePath    Chemin de sortie.
*/
void DockInputOutput::setPathOutput(QString filePath)
{
    if (!filePath.isEmpty())
    {
        settings->setValue("last_path_output_batchmod",filePath);
        pathOutput->setText(filePath);
    }
}

/**
*@brief Appelle la fenêtre d'exploration pour parcourir les fichiers à charger.
*/
void DockInputOutput::loadList()
{
    QStringList files;

    if (settings->value("last_path_input_batchmod").toString() != "undefined")
        files = QFileDialog::getOpenFileNames(this,"",settings->value("last_path_input_batchmod").toString(),"Video Files (*.avi *.mkv *.ts *.m2ts *.mpeg *.mpg *.mp4 *.m4v *.ogg *.wmv *.3gp *.dat *.mov *.vob *.flv *.swf)");
    else
        files = QFileDialog::getOpenFileNames(this,"","","Video Files (*.avi *.mkv *.ts *.m2ts *.mpeg *.mpg *.mp4 *.m4v *.ogg *.wmv *.3gp *.dat *.mov *.vob *.flv *.swf)");

    if (!files.isEmpty())
    {
        QFileInfo fileInfo(files[0]);
        settings->setValue("last_path_input_batchmod",fileInfo.absolutePath());
        arrowUpButton->setDisabled(true);
        arrowDownButton->setEnabled(true);
        thumbnailListWidget->addItems(files);
    }
}

/**
*@brief Appelle la fenêtre d'exploration pour parcourir le dossier de sortie.
*/
void DockInputOutput::openFileDialogPathOutput()
{
    QString path;

    if (settings->value("last_path_output_batchmod").toString() != "undefined")
        path = QFileDialog::getExistingDirectory(this,"",settings->value("last_path_output_batchmod").toString());
    else
        path = QFileDialog::getExistingDirectory();

    this->setPathOutput(QDir::toNativeSeparators(path));
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void DockInputOutput::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QDockWidget::changeEvent(event);
}

/**
*@brief Supprime les items sélectionnés
*/
void DockInputOutput::removeItemSelection()
{
    thumbnailListWidget->removeItemSelection();
    main_window->mpDockTimeline->clear();
}

/**
*@brief  CheckBox "Same Folder output as source" checked?
*@return Vrai ou faux.
*/
bool DockInputOutput::isSameSourceChecked()
{
    return sameSourceCheckBox->isChecked();
}

/**
*@brief  Setter de "Same Folder output as source".
*@param  state  Etat de la checkBox.
*/
void DockInputOutput::setSameSourceChecked(bool state)
{
    sameSourceCheckBox->setChecked(state);
}

/**
*@brief  CheckBox "Same Folder output as source" checked?
*@param  state   Etat de la checkBox.
*/
void DockInputOutput::disablePathOutput(int state)
{
    bool localState = (state == Qt::Checked) ? true : false;
    if(localState)
    {
        pathOutputLabel->setDisabled(localState);
        pathOutput->setDisabled(localState);
        outputButton->setDisabled(localState);
    }
    else
    {
        pathOutputLabel->setDisabled(localState);
        pathOutput->setDisabled(localState);
        outputButton->setDisabled(localState);
    }
}

/**
*@brief Déplace un item vers le haut.
*/
void DockInputOutput::moveItemUp()
{
    int currentRow = thumbnailListWidget->currentRow();
    if (currentRow == 1)
         arrowUpButton->setDisabled(true);
    else
        arrowUpButton->setDisabled(false);

    arrowDownButton->setEnabled(true);

    QListWidgetItem * currentItem = thumbnailListWidget->takeItem(currentRow);
    thumbnailListWidget->insertItem(currentRow - 1, currentItem);
    thumbnailListWidget->setCurrentRow(currentRow - 1);
}

/**
*@brief Déplace un item vers le haut.
*/
void DockInputOutput::moveItemDown()
{
    int currentRow = thumbnailListWidget->currentRow();

    if (currentRow == thumbnailListWidget->count() - 2 )
         arrowDownButton->setDisabled(true);
    else arrowDownButton->setDisabled(false);

    arrowUpButton->setEnabled(true);

    QListWidgetItem * currentItem = thumbnailListWidget->takeItem(currentRow);
    thumbnailListWidget->insertItem(currentRow + 1, currentItem);
    thumbnailListWidget->setCurrentRow(currentRow + 1);
}

/**
*@brief Enable ou Disable les flèches en fonction de l'item selectionné.
*@param item    Item selectionné.
*/
void DockInputOutput::arrowsManager(QListWidgetItem *item)
{
    if(item == thumbnailListWidget->item(0))
         arrowUpButton->setDisabled(true);
    else arrowUpButton->setEnabled(true);

    if(item == thumbnailListWidget->item(thumbnailListWidget->count() - 1))
         arrowDownButton->setDisabled(true);
    else arrowDownButton->setEnabled(true);
}

/**
*@brief Réinitialise la liste des médias.
*/
void DockInputOutput::resetListWidget()
{
    if(thumbnailListWidget->count() != 0)
    {
        thumbnailListWidget->clear();
        arrowUpButton->setDisabled(true);
        arrowDownButton->setDisabled(true);
        main_window->mpDockTimeline->clear();
    }
    else QMessageBox::information(this, _ERROR_, tr("Media list is already empty"));
}

/**
*@brief Enable or Disabled le bouton reset en fonction du nombre d'item présent dans la liste.
*@param row Colonne de l'item courant.
*/
void DockInputOutput::enableResetButton(int row)
{
 //If there is no current item, the currentRow is -1.
    if(row == -1)
    {
        resetListButton->setDisabled(true);
        runBatchButton->setDisabled(true);
    }
    else
    {
        resetListButton->setDisabled(false);
        runBatchButton->setDisabled(false);
    }
}

/**
*@brief Enable or Disabled le bouton Remove Selection si un item est sélectionné ou non.
*/
void DockInputOutput::enableRemoveSelectionButton()
{
    if(thumbnailListWidget->selectedItems().isEmpty())
    {
         deleteSelectionButton->setDisabled(true);
         previewSelectionButton->setDisabled(true);
    }
    else
    {
        deleteSelectionButton->setDisabled(false);
        previewSelectionButton->setDisabled(false);
    }
}

/**
*@brief  Retourne la liste contenant les images à convertir.
*@return QLinkedList  <ThumbnailItem*> - Liste.
*/
QLinkedList <ThumbnailItem*> DockInputOutput::getThumbnailList()
{
    return getListWidget()->getItemsListWidget();
}

/**
*@brief Fonction de traduction dynamique.
*/
void DockInputOutput::retranslate()
{
    this->setWindowTitle( tr("Input and Output") );
    loadButton->setText( tr("Load") );
    resetListButton->setText( tr("Reset") );
    runBatchButton->setText( tr("Start") );
    deleteSelectionButton->setText( tr("Delete Selection") );
    pathOutputLabel->setText( tr("Path Output") + " :" );
    previewSelectionButton->setText( tr("Preview selection file") );
    sameSourceCheckBox->setText( tr("Same folder output as source") );
}

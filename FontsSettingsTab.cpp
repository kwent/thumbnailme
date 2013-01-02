/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	FontsSettingsTab.cpp
*       @class  FontsSettingsTab
*	Cette classe permet d'ajouter ou de supprimer des chemins de dossier contenant des polices.
*       Elle génère un widget disponible dans le widget "Settings".
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

#include "FontsSettingsTab.h"
#include "QtHelper.h"
#include "defines.h"

/**
*@brief Constructeur.
*/
FontsSettingsTab::FontsSettingsTab()
{
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    QGridLayout *layoutPrincipal = new  QGridLayout;

    fontPathListWidget = new QListWidget(this);
        fontPathListWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
        fontPathListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        fontPathListWidget->installEventFilter(this);

    addPathFontButton = new QPushButton(QIcon(":/sprites/add.png"),QString(),this) ;

    removePathFontButton = new QPushButton(QIcon(":/sprites/remove.png"),QString(),this);
    removePathFontButton->setDisabled(true);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
        buttonsLayout->addWidget(addPathFontButton);
        buttonsLayout->addWidget(removePathFontButton);

    layoutPrincipal->addWidget(fontPathListWidget,0,0);
    layoutPrincipal->addLayout(buttonsLayout,1,0);

    this->initializeWidget();
    this->setLayout(layoutPrincipal);
    this->retranslate();

    /*Connections*/
    connect(addPathFontButton,    SIGNAL(clicked()), this, SLOT(setPathFontsOutput()));
    connect(removePathFontButton, SIGNAL(clicked()), this, SLOT(removeSelectedItemsListWidget()));
    connect(fontPathListWidget,   SIGNAL(itemSelectionChanged ()),  this,    SLOT(enableRemoveSelectionButton()) );
}

/**
*@brief Destructeur.
*/
FontsSettingsTab::~FontsSettingsTab()
{
}

/**
*@brief Initialisation des paramètres du widget.
*/
void FontsSettingsTab::initializeWidget()
{
    fontPathListWidget->clear();
    fontPathListWidget->addItems(QtHelper::readPathsFontsValueIni(settings));
}

/**
*@brief Permet d'ajouter un chemin de police à la comboBox.
*/
void FontsSettingsTab::setPathFontsOutput()
{
    QString path = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("Select a font folder"),QString(),QFileDialog::DontUseNativeDialog));

    if (fontPathListWidget->findItems(path,Qt::MatchFixedString).empty() && containsTTF(QString(path)))
        fontPathListWidget->addItem(path);
    else if (!fontPathListWidget->findItems(path,Qt::MatchFixedString).empty()) return ;
    else  if (path.isEmpty()) return;
    else QMessageBox::warning(this, _ERROR_, tr("No fonts found in this folder"));
}

/**
*@brief Retire le/les chemin(s) de police séléctionné(s).
*/
void FontsSettingsTab::removeSelectedItemsListWidget()
{
    if(!QtHelper::removeSelectedItems(getFontPathListWidget()))
        QMessageBox::information(this, _INFORMATION_, tr("You must select a path to remove it from the list"));
}

/**
*@brief  Réimplémentation de eventFilter pour pouvoir retirer des chemins de polices via la touche "Suppr".
*@param  *o    Objet.
*@param  *e    Evénement.
*@return bool - Vrai ou faux.
*/
bool FontsSettingsTab::eventFilter(QObject *o, QEvent *e)
{
    if(o == fontPathListWidget && e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        if (keyEvent->key() == Qt::Key_Delete)
        {
          this->removeSelectedItemsListWidget();
          return true;
        } else return false;
    }
    return QWidget::eventFilter(o,e);
}

/**
*@brief  Détecte si un dossier contient des fichier .ttf ou pas.
*@param  folderPath    Chemin du dossier à scanner.
*@return bool - Vrai ou faux.
*/
bool FontsSettingsTab::containsTTF(QString folderPath)
{
    QDir fontsFolder(folderPath);
        fontsFolder.setNameFilters(QStringList("*.ttf"));
    if(fontsFolder.count() > 0)
        return true;
    else return false;
}



/**
*@brief  Compte le nombre de .ttf dans les dossiers passés en parâmètres.
*@param  foldersPath    Chemin des dossiers à scanner.
*@return int - Nombre ttf.
*/
int FontsSettingsTab::countTTF(QStringList foldersPath)
{
    int i = 0;
    foreach(QString path,foldersPath)
    {
        QDir dir(path);
            dir.setNameFilters(QStringList("*.ttf"));
        i += dir.count();
    }
    return i;
}

/**
*@brief  Retourne un pointeur vers le QListWidget qui contient le /les chemin(s) des polices.
*@return QListWidget* - Pointeur.
*/
QListWidget* FontsSettingsTab::getFontPathListWidget()
{
    return fontPathListWidget;
}

/**
*@brief  Fonction annulation - Réaffecte les paramètres d'origine.
*/
void FontsSettingsTab::reject()
{
    this->initializeWidget();
}

/**
*@brief Enable or Disabled le bouton Remove si un item est sélectionné ou non.
*/
void FontsSettingsTab::enableRemoveSelectionButton()
{
    if(fontPathListWidget->selectedItems().isEmpty())
    {
         this->removePathFontButton->setEnabled(false);
    }
    else this->removePathFontButton->setEnabled(true);
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void FontsSettingsTab::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void FontsSettingsTab::retranslate()
{
    addPathFontButton->setText( tr("Add") ) ;
    removePathFontButton->setText( tr("Remove") );
}

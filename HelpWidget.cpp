/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	HelpWidget.cpp
*       @class  HelpWidget
*	Cette classe permet la génération du widget "Aide" pour l'utilisateur.
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

#include "HelpWidget.h"
#include <QHelpIndexWidget>
#include <QDesktopWidget>
#include <QTimer>
#include "HelpBrowser.h"
#include "defines.h"
#include "QtHelper.h"

/**
*@brief Constructeur.
*@param parent    Fenêtre principale de Thumbnail me.
*/
HelpWidget::HelpWidget(QWidget *parent) : QDialog(parent)
{
    //this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowOkButtonHint | Qt::Dialog);
    this->setWindowIcon( QIcon(":sprites/help.png") );
    this->setWindowModality(Qt::ApplicationModal);
    int height = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).height();
    int width  = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).width();
    this->setMinimumSize((0.55)*width,(0.6)*height);

    QGridLayout *layout = new QGridLayout(this);

    helpEngine = new QHelpEngine(DOCS_PATH,this);
        helpEngine->setupData();
        helpEngine->contentWidget()->setDragEnabled(false);
        helpEngine->contentWidget()->setFocusPolicy(Qt::NoFocus);

    helpBrowser = new HelpBrowser(helpEngine);
        helpBrowser->setOpenExternalLinks(true);

    QSplitter *helpPanel = new QSplitter(Qt::Horizontal,this);
        helpPanel->insertWidget(0, helpEngine->contentWidget());
        helpPanel->insertWidget(1, helpBrowser);
        helpPanel->setStretchFactor(1, 1);

    layout->addWidget(helpPanel);
    this->setLayout(layout);
    this->retranslate();
    QtHelper::centerWidget(this);

    /*Connections*/
    connect(helpEngine->contentWidget(), SIGNAL(clicked (const QModelIndex &)), helpEngine->contentWidget(), SIGNAL(activated(const QModelIndex &)));
    connect(helpEngine->contentWidget(), SIGNAL(linkActivated(const QUrl &)), helpBrowser, SLOT(setSource(const QUrl &)));

    QTimer::singleShot(200, this, SLOT(showHomePage()));
}

/**
*@brief Destructeur.
*/
HelpWidget::~HelpWidget()
{
    delete helpBrowser;
}

/**
*@brief Slot permettant d'afficher la page d'acceuil.
*/
void HelpWidget::showHomePage()
{
    if( helpEngine->contentModel()->isCreatingContents() == true)
          return;
    if( helpEngine->contentModel()->rowCount() < 1)
    return;

    QModelIndex index = helpEngine->contentModel()->index(0, 0);
    if( index.isValid() == true)
    {
          QHelpContentItem* item = helpEngine->contentModel()->contentItemAt(index);
            if(item)
            {
                  helpEngine->contentWidget()->setCurrentIndex(index);
                  helpBrowser->setSource(item->url());
            }
    }
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void HelpWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void HelpWidget::retranslate()
{
    this->setWindowTitle( tr("Help") );
}

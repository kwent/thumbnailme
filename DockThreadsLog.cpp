/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockThreadsLog.cpp
*       @class  DockThreadsLog
*	Cette classe permet la génération du Dock "Journal" qui affiche la sortie (stdout) du processus.
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

#include "DockThreadsLog.h"
#include "MainWindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ThumbnailTreeItem.h"

/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/
DockThreadsLog::DockThreadsLog(QWidget *main_window) : QDockWidget(main_window)
{
    this->mainWindow = (MainWindow*) main_window;
    this->setMinimumWidth(QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).width()/4);
    this->setObjectName("DockThreadsLog");

    QVBoxLayout *contentLayout = new QVBoxLayout;
    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    verboseTextEdit = new QTextEdit(this);
        verboseTextEdit->setReadOnly(true);

    clearAllButton = new QPushButton(QIcon(":sprites/recycle-bin-full.png"),tr("Clear all"),this);
        clearAllButton->setDisabled(true);

    copyToClipboardButton = new QPushButton(QIcon(":sprites/text clipping.png"),tr("Copy to clipboard"),this);
        copyToClipboardButton->setDisabled(true);

    contentLayout->addWidget(verboseTextEdit,0,Qt::AlignVCenter);

    buttonsLayout->addWidget(copyToClipboardButton);
    buttonsLayout->addWidget(clearAllButton);

    contentLayout->addLayout(buttonsLayout);

    contentWidget = new QWidget(this);
        contentWidget->setLayout(contentLayout);

    this->setWidget(contentWidget);
    this->retranslate();

    /*Connections*/
    connect(clearAllButton,         SIGNAL(clicked()), verboseTextEdit, SLOT(clear()));
    connect(copyToClipboardButton,  SIGNAL(clicked()), this, SLOT(copyToClipboard()));
    connect(verboseTextEdit,        SIGNAL(textChanged()), this, SLOT(enabledButtons()));
}

/**
*@brief Destructeur.
*/
DockThreadsLog::~DockThreadsLog()
{
}

///**
//*@brief Setteur de verbosité - La sortie du processus de mtn STDOUT est mappée et récupérée ici.
//*/
//void DockThreadsLog::setVerbose(QStringList outputStringList)
//{
//    foreach(QString current ,outputStringList)
//    {
//        current = current.trimmed();
//        if (current.contains("File:") && verboseTextEdit->document()->isEmpty())
//        {
//          verboseTextEdit->append(QDateTime::currentDateTime().toString()+"\n\n"+current);
//        }
//        else if (current.contains("File:"))
//        {
//          verboseTextEdit->append("\n" + QDateTime::currentDateTime().toString()+"\n\n"+current);
//        }
//        else verboseTextEdit->append(current);
//    }
//}

/**
*@brief Setteur de verbosité.
*@param item    ThumbnailItem à ajouter.
*/
void DockThreadsLog::setLog(QTreeWidgetItem *item, int column)
{
    ThumbnailTreeItem* tmp = (ThumbnailTreeItem*) item;
    this->setWindowTitle(tr( "Logs" ) + ': ' + tmp->thumbnailItem->getFilePath().toString() );
    verboseTextEdit->clear();
    verboseTextEdit->append(QDateTime::currentDateTime().toString()+"\n");
    verboseTextEdit->append(tmp->thumbnailItem->logs);
    this->raise();
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void DockThreadsLog::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QDockWidget::changeEvent(event);
}

/**
*@brief Active ou désactive le boutton "effacer" & "Copier dans le presse papier" selon le contenu du widget.
*/
void DockThreadsLog::enabledButtons()
{
    if(!verboseTextEdit->toPlainText().isEmpty())
    {
         clearAllButton->setEnabled(true);
         copyToClipboardButton->setEnabled(true);
    }
    else
    {
        clearAllButton->setEnabled(false);
        copyToClipboardButton->setEnabled(false);
    }
}

/**
*@brief Copie le contenu du texte dans le presse papier.
*/
void DockThreadsLog::copyToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(verboseTextEdit->toPlainText(),QClipboard::Clipboard);
}

/**
*@brief Fonction de traduction dynamique.
*/
void DockThreadsLog::retranslate()
{
    this->setWindowTitle( tr( "Logs" ) );
    copyToClipboardButton->setText( tr("Copy to clipboard") );
    clearAllButton->setText( tr("Clear all") );
}

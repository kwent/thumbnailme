/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ProcessingStatusBar.cpp
*       @class  ProcessingStatusBar
*	Cette classe permet la génération de la barre de statut de traitement lors du lancement de la génération de la vignette.
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

#include "ProcessingStatusBar.h"
#include <QHBoxLayout>

/**
*@brief Constructeur.
*@param *parent    Widget parent.
*/
ProcessingStatusBar::ProcessingStatusBar(QWidget *parent) : QStatusBar(parent)
{
   this->setWindowTitle(APPLICATION_NAME);

   //Processing files status.
    statusLabel = new QLabel(this);

   //Progress Bar Widget.
    progressBar = new QProgressBar(this);
      progressBar->setValue(0);

    progressionlabel = new QLabel(this);

    QHBoxLayout *progressBarLayout = new  QHBoxLayout;
      progressBarLayout->addWidget(progressionlabel);
      progressBarLayout->addWidget(progressBar);
      progressBarLayout->setMargin(0);

    QWidget *progressBarWidget = new QWidget(this);
      progressBarWidget->setLayout(progressBarLayout);

   this->addWidget(progressBarWidget);
   this->addWidget(statusLabel);
   this->retranslate();

   this->setStyleSheet("QStatusBar{border: 1px solid;background: white;}");
   this->setSizeGripEnabled(false);
}

/**
*@brief Destructeur.
*/
ProcessingStatusBar::~ProcessingStatusBar()
{
}

/**
*@brief Setter du nombre total d'item à traiter.
*@param count    Nombre d'item.
*/
void ProcessingStatusBar::setFilesCount(int count)
{
    this->total = count;
}

/**
*@brief Change le status du dialogue de chargement.
*@param current Stade d'avancement par rapport au nombre total de fichiers traités.
*@param fileName Nom du fichier traité.
*/
void ProcessingStatusBar::setStatus(int current,QString fileName)
{
    QString status = QString(tr("Processing file %1 of %2: %3")).arg(current).arg(total).arg(fileName);
    progressBar->setValue((current * 100) / total);
    statusLabel->setText(status);
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void ProcessingStatusBar::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void ProcessingStatusBar::retranslate()
{
    progressionlabel->setText( tr("Progression:") );
}

/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockTimeLine.cpp
*       @class  DockTimeLine
*	Cette classe permet la génération du dock TimeLine.
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

#include "DockTimeLine.h"
#include "ThumbnailItem.h"
#include "QTHelper.h"

/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/
DockTimeLine::DockTimeLine(QWidget *main_window) : QFrame (main_window)
{
    this->setFrameStyle(QFrame::StyledPanel);
    this->setStyleSheet("DockTimeLine{border-style: solid;border-width: 1px;border-radius: 10px;border-color: grey;padding: 6px;}");

    thumbnailItem = 0;

    titleWidgetLabel     = new QLabel( this );
        titleWidgetLabel->setAlignment(Qt::AlignCenter);
    spanSliderLowerLabel = new QLabel( this );
    spanSliderUpperLabel = new QLabel( this );
    spanSlider = new QxtSpanSlider(Qt::Horizontal,this);
    spanSlider->setHandleMovementMode(QxtSpanSlider::NoOverlapping);
    spanSliderDuration = new QLabel( this );

    QGridLayout *layoutSpanSlider = new QGridLayout;

        layoutSpanSlider->addWidget(titleWidgetLabel,0,0,1,2);
        layoutSpanSlider->addWidget(QtHelper::addHSeparator(),1,0,1,2);
        layoutSpanSlider->addWidget(spanSliderLowerLabel,2,0);
        layoutSpanSlider->addWidget(spanSliderUpperLabel,2,1,Qt::AlignRight);
        layoutSpanSlider->addWidget(spanSlider,3,0,1,2);
        layoutSpanSlider->addWidget(spanSliderDuration,4,0,1,2,Qt::AlignHCenter);

    /*Connections*/
    connect(spanSlider, SIGNAL(lowerPositionChanged(int)), this , SLOT(updateLowerLabel(int)));
    connect(spanSlider, SIGNAL(upperPositionChanged(int)), this , SLOT(updateUpperLabel(int)));

    this->setLayout(layoutSpanSlider);
    this->setDisabled(true);
    this->retranslate();
}

/**
*@brief Destructeur.
*/
DockTimeLine::~DockTimeLine()
{
}

/**
*@brief  Retourne le Thumbnail Item courant associé à la timeline.
*@return ThumbnailItem* - Thumbnail Item.
*/
ThumbnailItem * DockTimeLine::getCurrentItem()
{
    return thumbnailItem;
}

/**
*@brief Modifie la timeline selon les données de l'item.
*@param item    Item sélectionné.
*/
void DockTimeLine::update(QListWidgetItem *item)
{
    this->thumbnailItem = 0;
    this->thumbnailItem = static_cast<ThumbnailItem *> (item);

    /*
    Hack - Si l'utilisateur clique trop vite sur l'item
    ou Service Windows Audio désactivé
    */
    if(this->thumbnailItem->getTotalDuration().isNull())
    {
         this->setDisabled(true); this->retranslate(); return;
    }
    else this->setDisabled(false);
    /*****************************************************/

    if (!this->thumbnailItem->isReadable())
    {
        this->setDisabled(true);
        spanSlider->setLowerPosition(0);
        spanSlider->setUpperPosition(0);
    }
    else
    {
        //update
        this->setEnabled(true);

        spanSlider->setRange(0,-thumbnailItem->getTotalDuration().secsTo(QTime()));

        if(thumbnailItem->getLowerTime().isNull())
        {
             spanSlider->setLowerPosition(0);
             thumbnailItem->setLowerTime(QTime(0,0));
        }
        else
        {
            spanSlider->setLowerPosition(-thumbnailItem->getLowerTime().secsTo(QTime()));
        }

        if(thumbnailItem->getUpperTime().isNull())
        {
              QTime t;
              thumbnailItem->setUpperTime(t.addSecs(-thumbnailItem->getTotalDuration().secsTo(QTime())));
              spanSlider->setUpperPosition(-thumbnailItem->getTotalDuration().secsTo(QTime()));
        }
        else
        {
            spanSlider->setUpperPosition(-thumbnailItem->getUpperTime().secsTo(QTime()));
        }
    }

    this->retranslate();
}


/**
*@brief Traitement des erreurs.
*@param error   Type de l'erreur.
*/
void DockTimeLine::manageErrors(QMediaPlayer::Error error)
{
    this->setDisabled(true);
    titleWidgetLabel->setText( "<b>" + tr( "TimeLine (Not available) | Media isn't fully supported" ) + "</b>");
}

/**
*@brief Update Lower QLabel.
*@param lower   Valeur de "lower" du QxtSpanSlider.
*/
void DockTimeLine::updateLowerLabel(int lower)
{
    lowerQTime = QTime(0,0);
    thumbnailItem->setLowerTime(lowerQTime.addSecs(lower));
    spanSliderLowerLabel->setText(tr( "From" ) + " : " + QString("%1").arg(thumbnailItem->getLowerTime().toString(Qt::TextDate)));
}

/**
*@brief Update Upper QLabel.
*@param upper   Valeur de "upper" du QxtSpanSlider.
*/
void DockTimeLine::updateUpperLabel(int upper)
{
    upperQTime = QTime(0,0);
    thumbnailItem->setUpperTime(upperQTime.addSecs(upper));
    spanSliderUpperLabel->setText(tr( "To" ) + " : " + QString("%1").arg(thumbnailItem->getUpperTime().toString(Qt::TextDate)));
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void DockTimeLine::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Reset la timeline.
*/
void DockTimeLine::clear()
{
    this->thumbnailItem = 0;
    this->setDisabled(true);
    this->spanSlider->setSpan(0,0);
    this->retranslate();
}

/**
*@brief Fonction de traduction dynamique.
*/
void DockTimeLine::retranslate()
{
    if(thumbnailItem && thumbnailItem->isReadable() && thumbnailItem->getLowerTime().isNull() && thumbnailItem->getUpperTime().isNull())
    {
        titleWidgetLabel->setText( "<b>" + tr( "TimeLine" ) + "</b>" );
        spanSliderLowerLabel->setText( tr( "From" ) + " : " + QTime(0,0).toString(Qt::TextDate) );
        spanSliderUpperLabel->setText( tr( "To" ) + " : " + thumbnailItem->getTotalDuration().toString(Qt::TextDate) );
        spanSliderDuration->setText( tr( "Total duration" ) + ": " + thumbnailItem->getTotalDuration().toString(Qt::TextDate) );
    }
    else if(thumbnailItem && thumbnailItem->isReadable() && !thumbnailItem->getLowerTime().isNull() && !thumbnailItem->getUpperTime().isNull())
    {
        titleWidgetLabel->setText( "<b>" + tr( "TimeLine" ) + "</b>" );
        spanSliderLowerLabel->setText( tr( "From" ) + " : " + thumbnailItem->getLowerTime().toString(Qt::TextDate) );
        spanSliderUpperLabel->setText( tr( "To" ) + " : " + thumbnailItem->getUpperTime().toString(Qt::TextDate) );
        spanSliderDuration->setText( tr( "Total duration" ) + " : " + thumbnailItem->getTotalDuration().toString(Qt::TextDate) );
    }
    else if(thumbnailItem && !thumbnailItem->isReadable())
    {
        titleWidgetLabel->setText( "<b>" + tr( "TimeLine (Not available) | Media isn't fully supported" ) + "</b>" );
        spanSliderLowerLabel->setText( tr( "From" ) + " : " + QTime(0,0).toString(Qt::TextDate) );
        spanSliderUpperLabel->setText( tr( "To" ) + " : " + QTime(0,0).toString(Qt::TextDate) );
        spanSliderDuration->setText( tr( "Total duration" ) + " : " + QTime(0,0).toString(Qt::TextDate) );
    }
    else
    {
        titleWidgetLabel->setText( "<b>" + tr( "TimeLine" ) + "</b>" );
        spanSliderLowerLabel->setText( tr( "From" ) + " : " + QTime(0,0).toString(Qt::TextDate) );
        spanSliderUpperLabel->setText( tr( "To" ) + " : " + QTime(0,0).toString(Qt::TextDate) );
        spanSliderDuration->setText( tr( "Total duration" ) + " : " + QTime(0,0).toString(Qt::TextDate) );
    }
}

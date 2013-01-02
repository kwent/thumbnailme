/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ImageShackResultWidget.cpp
*   @class  ImageShackResultWidget
*	Cette classe permet la génération du widget affichant les résultats de l'upload.
*   @attention  ImagesHackUploader API required.
*
*	@author		Quentin Rousseau\n
*	@note   	Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*   @since      3.0
*	@version	3.0
*   @date       2011-2012
*******************************************************************************/

/*
Copyright (c) 2009, ImageShack Corp.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* Neither the name of the ImageShack nor the names of its contributors may be
  used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "ImageShackResultWidget.h"
#include "ui_ImageShackResultWidget.h"


/**
*@brief Constructeur.
*@param *parent    Widget parent.
*/
ImageShackResultWidget::ImageShackResultWidget(QWidget *parent) : QDialog(parent),m_ui(new Ui::ImageShackResultWidget)
{
    this->setParent(parent);
    //this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setWindowModality(Qt::ApplicationModal);
    m_ui->setupUi(this);
    this->retranslate();

    current = 0; // Index courant

    imagesDatasList = new QList < ImageShackResponse * >;

}


/**
*@brief Destructeur.
*/
ImageShackResultWidget::~ImageShackResultWidget()
{
    delete m_ui;
}

/**
*@brief Ajoute les données des résultats à la fenêtre de résultat.
*@param *response   Réponse de ImageShackResponse.
*/
void ImageShackResultWidget::addData(ImageShackResponse *response)
{
    imagesDatasList->append(response);
    setIndex(0);

    m_ui->next->setEnabled(imagesDatasList->size()!=1);
}

/**
*@brief Affiche l'index passé en paramètre.
*@param index Index.
*/
void ImageShackResultWidget::setIndex(int index)
{

    m_ui->count->setText(tr("File %1 of %2").arg(index+1).arg(imagesDatasList->size()));
    m_ui->thumbnailPreviewLabel->setPixmap(QPixmap(imagesDatasList->at(index)->getFileUploaded()->getObjectPath()));

    m_ui->shortLink->setText(imagesDatasList->at(index)->getImageShackResponse()["yfrog_link"]);
    m_ui->directLink->setText(imagesDatasList->at(index)->getImageShackResponse()["image_link"]);
    m_ui->hotlink->setText(imagesDatasList->at(index)->getImageShackResponse()["image_html"]);
    m_ui->thumbnailLink->setText(imagesDatasList->at(index)->getImageShackResponse()["thumb_html"]);
    m_ui->forumThumbnail->setText(imagesDatasList->at(index)->getImageShackResponse()["thumb_bb"]);
    m_ui->forumThumbnail2->setText(imagesDatasList->at(index)->getImageShackResponse()["thumb_bb2"]);
    m_ui->forumHotlink->setText(imagesDatasList->at(index)->getImageShackResponse()["image_bb"]);
    m_ui->forumHotlink2->setText(imagesDatasList->at(index)->getImageShackResponse()["image_bb2"]);
}

/**
*@brief Affiche les résultats de l'index précédent.
*/
void ImageShackResultWidget::prev()
{
    if (current > 0) setIndex(--current);

    if (current == 0)
    {
      m_ui->prev->setEnabled(false);
      m_ui->next->setEnabled(true);
    } else m_ui->next->setEnabled(true);
}

/**
*@brief Affiche les résultats de l'index suivant.
*/
void ImageShackResultWidget::next()
{
    if (current < (imagesDatasList->size() - 1)) setIndex(++current);

    if (current == imagesDatasList->size() - 1)
    {
      m_ui->prev->setEnabled(true);
      m_ui->next->setEnabled(false);
    } else m_ui->prev->setEnabled(true);
}

/**
*@brief Ferme la fenêtre de résultat.
*/
void ImageShackResultWidget::done()
{
    m_ui->thumbnailPreviewLabel->setText("Thumbnail");
    reject();
}

/**
*@brief Réinitialise les résultats de cette fenêtre à zéro.
*/
void ImageShackResultWidget::reset()
{
   current = 0;
   imagesDatasList->clear();
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void ImageShackResultWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        m_ui->retranslateUi(this);
        this->retranslate();
    }
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void ImageShackResultWidget::retranslate()
{
    m_ui->directLink->setTitle(tr("Direct link"));
    m_ui->shortLink->setTitle(tr("Short link"));
    m_ui->hotlink->setTitle(tr("Hotlink for web"));
    m_ui->thumbnailLink->setTitle(tr("Thumbnail for web"));
    m_ui->forumThumbnail->setTitle(tr("Thumbnail for forums 1"));
    m_ui->forumThumbnail2->setTitle(tr("Thumbnail for forums 2"));
    m_ui->forumHotlink->setTitle(tr("Hotlink for forums 1"));
    m_ui->forumHotlink2->setTitle(tr("Hotlink for forums 2"));
}

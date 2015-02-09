/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ImageShackResultWidget.h
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


#ifndef HEADER_IMAGESHACKRESULTWIDGET
#define HEADER_IMAGESHACKRESULTWIDGET

#include <QtGui/QDialog>
#include <QDebug>
#include <QSharedPointer>
#include <QHash>
#include "ImageShackUploader/ImageShackResponse.hpp"

namespace Ui {class ImageShackResultWidget;}

class ImageShackResultWidget : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageShackResultWidget)

    public:
    explicit ImageShackResultWidget(QWidget *parent = 0);
    virtual  ~ImageShackResultWidget();

    private:
    Ui::ImageShackResultWidget *m_ui;
    QList < ImageShackResponse * > *imagesDatasList;
    int current;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public:
    void addData(ImageShackResponse *response);
    void setIndex(int index);

    private slots:
    void prev();
    void next();
    void done();

    public slots:
    void reset();
};

#endif // HEADER_IMAGESHACKRESULTWIDGET


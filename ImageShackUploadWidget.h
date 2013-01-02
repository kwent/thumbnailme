/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ImageShackUploadWidget.h
*   @class  ImageShackUploadWidget
*	Cette classe permet la génération du widget permettant à l'utilisateur
*   d'uploader la vignette courante sur imageShack.
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


#ifndef HEADER_IMAGESHACKUPLOADWIDGET
#define HEADER_IMAGESHACKUPLOADWIDGET

#include <QWidget>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QMovie>
#include <QSettings>
#include "QtHelper.h"
#include "ImageShackUploader/ImageShackObject.hpp"
#include "ImageShackUploader/ImageShackUploader.hpp"
#include "ImageShackUploader/ImageShackError.hpp"
#include "ImageShackResultWidget.h"
#include "defines.h"

namespace Ui {class ImageShackUploadWidget;}

class ImageShackLoginWidget;

class ImageShackUploadWidget : public QWidget {

    Q_OBJECT
    Q_DISABLE_COPY(ImageShackUploadWidget)

    public:
    explicit ImageShackUploadWidget(QWidget *parent = 0);
    explicit ImageShackUploadWidget(QPixmap *pixmapToUpload, QWidget *parent = 0);
    virtual ~ImageShackUploadWidget();

    public:
    QStringList getTags();
    bool        getPrivacy();
    void        addData(QStringList pathFilesToUpload);

    private:
    void		  init(QWidget *parent=0);
    void		  enableLoginSection(bool state);
    void		  updateImageShackObject();
    QNetworkProxy *readProxySettings();
    QString       cleanup(QString);

    protected:
    void changeEvent(QEvent* event);
    void closeEvent(QCloseEvent* event);

    private:
    Ui::ImageShackUploadWidget *m_ui;
    ImageShackUploader         *imageShackUploader;
    ImageShackResultWidget     *imageShackResultWidget;
    ImageShackLoginWidget      *imageShackLoginWidget;
    QSettings                  *settings;
    QMap <int, QString>         items;
    QList <ImageShackObject*>   objectsList;
    bool                        loggedIn;
    int                         current;

    private slots:
    void loginStatusReceiver(bool);
    void upload();
    void manageProgressBar(ImageShackObject * fileUploaded , qint64 bytesReceived,qint64 bytesTotal);
    void manageUploads(ImageShackResponse * uploadResponse);
    void manageErrors(ImageShackError::UploadError);
    void showResults();
    void abort();

    public slots:
    void reset();
};

#endif // HEADER_IMAGESHACKUPLOADWIDGET

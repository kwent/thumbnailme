/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ImageShackUploadWidget.cpp
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


#include "ImageShackUploadWidget.h"
#include "ImageShackLoginWidget.h"
#include "ui_ImageShackUploadWidget.h"
#include "MainWindow.h"
#include "SuccessDialog.h"
#include <QMessageBox>

/**
*@brief Constructeur.
*@param *parent    Widget parent.
*/
ImageShackUploadWidget::ImageShackUploadWidget(QWidget *parent) :  m_ui(new Ui::ImageShackUploadWidget)
{
    this->init(parent);
    current = 1;
    imageShackUploader = new ImageShackUploader(IMAGESHACK_DEVELOPERKEY);
    imageShackResultWidget = new ImageShackResultWidget(this);

    SuccessDialog *sucessDialog = (SuccessDialog*) parent;
    MainWindow *main_window =  (MainWindow*) sucessDialog->parent();
    imageShackLoginWidget = main_window->mpImageShackLoginWidget;

    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    /*Connections*/
    connect( m_ui->uploadNowButton,     SIGNAL(clicked()), this, SLOT(upload()) );
    connect( m_ui->cancelUploadButton,  SIGNAL(clicked()), this, SLOT(abort()) );
    connect( imageShackLoginWidget,     SIGNAL(loginState(bool)), this , SLOT(loginStatusReceiver(bool)));
    connect( imageShackUploader,        SIGNAL(uploadProgress(ImageShackObject *,qint64,qint64)), this, SLOT(manageProgressBar(ImageShackObject *,qint64,qint64)) );
    connect( imageShackUploader,        SIGNAL(uploadDone(ImageShackResponse *)), this, SLOT(manageUploads(ImageShackResponse *)) );
    connect( imageShackUploader,        SIGNAL(endOfUploads()), this, SLOT(showResults()) );
    connect( imageShackUploader,        SIGNAL(uploadError(ImageShackError::UploadError)),this,SLOT(manageErrors(ImageShackError::UploadError)) );
  }

/**
*@brief Constructeur.
*@param *pixmapToUpload   Vignette à uploader.
*@param *parent    Widget parent.
*/
ImageShackUploadWidget::ImageShackUploadWidget(QPixmap *pixmapToUpload, QWidget *parent) :  m_ui(new Ui::ImageShackUploadWidget)
{
    this->init(parent);
    m_ui->countFileLoaded->setText(m_ui->countFileLoaded->text()+" 1");
    m_ui->thumbnailPreviewLabel->setPixmap(*pixmapToUpload);

    /*Connections*/
    connect(m_ui->uploadNowButton,  SIGNAL(clicked()), this, SLOT(upload()));
}


/**
*@brief Initialise l'affichage de la fenêtre.
*/
void ImageShackUploadWidget::init(QWidget *parent)
{
    if(parent)
    {
      this->setWindowIcon(parent->windowIcon());
      this->setWindowTitle(parent->windowTitle());
    }

    m_ui->setupUi(this);
    //this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->objectsList.clear();
    m_ui->thumbnailPreviewLabel->setScaledContents(true);
    m_ui->stackedUploadWidget->setCurrentIndex(0);

	items[0] = "";
	items[1] = "100x100";
	items[2] = "150x150";
	items[3] = "320x320";
	items[4] = "640x640";
	items[5] = "800x800";
	items[6] = "1024x1024";
	items[7] = "1280x1280";
	items[8] = "1600x1600";

    loggedIn = false;
}

/**
*@brief Destructeur.
*/
ImageShackUploadWidget::~ImageShackUploadWidget()
{
    delete m_ui;
}


/**
*@brief Initialise l'affichage de la fenêtre.
*@param pathFilesToUpload   Ajout des chemins des fichiers à uploader.
*/
void ImageShackUploadWidget::addData(QStringList pathFilesToUpload)
{
  foreach(QString path,pathFilesToUpload)
        objectsList.append(new ImageShackObject(path));

  m_ui->countFileLoaded->setText(QString(tr("File(s) loaded: %1")).arg(objectsList.size()));
  m_ui->thumbnailPreviewLabel->setPixmap(QPixmap(pathFilesToUpload.first()));

  m_ui->resizeLabel->setEnabled(true);
  m_ui->resizeComboBox->setEnabled(true);

  if(loggedIn)
       this->enableLoginSection(true);
  else this->enableLoginSection(false);
}

/**
*@brief  Nettoie une chaîne de caractère.
*@param  str   Chaîne à nettoyer.
*@return QString - Chaîne nettoyée.
*/
QString ImageShackUploadWidget::cleanup(QString str)
{
    while ((!str.isNull()) && (str.left(1) == " ")) str.remove(0, 1);
    while ((!str.isNull()) && (str.right(1) == " ")) str.remove(str.length()-1, 1);
    return str;
}


/**
*@brief Retourne les tags entrés pas l'utilisateur.
*@return QStringList - Tags.
*/
QStringList ImageShackUploadWidget::getTags()
{
    QString text = m_ui->tagsLineEdit->text();
    QStringList taglist = text.split(',');
    QStringList result;
    foreach(QString tag, taglist)
    {
        QString newtag = cleanup(tag);
        if (!newtag.isEmpty())
            result.append(newtag);
    }
    return result;
}


/**
*@brief Retourne la privacy (private ou public) sélectionnée par l'utilisateur.
*@return Vrai ou faux - Vrai: Public. Faux: Private.
*/
bool ImageShackUploadWidget::getPrivacy()
{
	if (m_ui->privacyPublic->isChecked())
		 return true;
	else return false;
}


/**
*@brief Modifieur des options d'upload disponibles selon le statut du login passé en paramètre.
*@param state Statut du login - Vrai ou Faux.
*/
void ImageShackUploadWidget::loginStatusReceiver(bool state)
{
    if (state)
    {
        this->enableLoginSection(true);
        m_ui->uploadModeLabel->setText(tr("Upload mode:") + " " + "<font color=\"green\">" + tr("login") + "</font>");
        loggedIn = true;
        this->setToolTip(QString());
    }
    else
    {
        this->enableLoginSection(false);
        m_ui->uploadModeLabel->setText(tr("Upload mode:") + " " + "<font color=\"red\">" + tr("anonymous") + "</font>");
        loggedIn = false;
        this->setToolTip(tr("Log in to use these features"));
    }
}


/**
*@brief Upload le(s) fichier(s).
*/
void ImageShackUploadWidget::upload()
{
    m_ui->resizeLabel->setDisabled(true);
    m_ui->resizeComboBox->setDisabled(true);
    this->enableLoginSection(false);

    this->updateImageShackObject();
    imageShackUploader->setProxy(readProxySettings());

    QMovie *progress = new QMovie(":/sprites/uploading-ImageShack.gif");
        progress->start();

    m_ui->stackedUploadWidget->setCurrentIndex(1);
    m_ui->countFileLoaded->setText(QString(tr("Processing file %1 of %2")).arg(QString::number(current)).arg(objectsList.size()));
    m_ui->progressLabel->setMovie(progress);

    if(!loggedIn)
        imageShackUploader->uploadImages(objectsList);
    else imageShackUploader->uploadImages(objectsList,imageShackLoginWidget->getImageShackUsername(),QByteArray::fromBase64(imageShackLoginWidget->getPassword()));
}

/**
*@brief Annule l'upload.
*/
void ImageShackUploadWidget::abort()
{
    imageShackUploader->abortUploads();
    current = 1;
    m_ui->uploadProgressBar->setValue(0);
    m_ui->totalUploadProgressBar->setValue(0);
    m_ui->thumbnailPreviewLabel->setPixmap(QPixmap(objectsList.first()->getObjectPath()));
    m_ui->countFileLoaded->setText(tr("File loaded: %1").arg(objectsList.size()));
    m_ui->stackedUploadWidget->setCurrentIndex(0);
    imageShackResultWidget->reset();

    m_ui->resizeLabel->setEnabled(true);
    m_ui->resizeComboBox->setEnabled(true);

    if(loggedIn)
         this->enableLoginSection(true);
    else this->enableLoginSection(false);
}

/**
*@brief Gère l'affichage de la barre de progression de l'upload.
*@param fileUploaded  ImageShackObject en train d'être uploader.
*@param bytesReceived Nombre d'octet envoyé.
*@param bytesTotal    Nombre d'octet total.
*/
void ImageShackUploadWidget::manageProgressBar(ImageShackObject * fileUploaded, qint64 bytesReceived,qint64 bytesTotal)
{
    m_ui->thumbnailPreviewLabel->setPixmap(QPixmap(fileUploaded->getObjectPath()));
    if(bytesTotal != 0)
    m_ui->uploadProgressBar->setValue((int)(bytesReceived * 100)/bytesTotal);
}

/**
*@brief Gère l'affichage du widget selon la progression de l'upload.
*@param uploadResponse  Réponse de l'API.
*/
void ImageShackUploadWidget::manageUploads(ImageShackResponse * uploadResponse)
{
  imageShackResultWidget->addData(uploadResponse);
  m_ui->countFileLoaded->setText(QString(tr("Processing file %1 of %2")).arg(QString::number(current+1)).arg(objectsList.size()));
  m_ui->totalUploadProgressBar->setValue((current * 100)/objectsList.count());
  if (current != objectsList.size() -1 ) current++;
}

/**
*@brief Apelle la fenêtre de résultat.
*/
void ImageShackUploadWidget::showResults()
{
    this->close();
    QtHelper::centerWidget(imageShackResultWidget);
    imageShackResultWidget->show();
}

/**
*@brief Réinitialise la fenêtre et ses paramètres à zéro.
*/
void ImageShackUploadWidget::reset()
{
  current = 1;
  objectsList.clear();
  imageShackResultWidget->reset();
  m_ui->uploadProgressBar->setValue(0);
  m_ui->totalUploadProgressBar->setValue(0);
  m_ui->stackedUploadWidget->setCurrentIndex(0);
}

/**
*@brief Active ou désactive certains paramètres selon le statut du login de l'utilisateur.
*@param state  Staut du login - Vrai ou faux.
*/
void ImageShackUploadWidget::enableLoginSection(bool state)
{
  m_ui->privacyLabel->setEnabled(state);
  m_ui->privacyPrivate->setEnabled(state);
  m_ui->privacyPublic->setEnabled(state);
  m_ui->separateCommaLabel->setEnabled(state);
  m_ui->tagsLabel->setEnabled(state);
  m_ui->tagsLineEdit->setEnabled(state);
}

/**
*@brief Lit les paramètres du proxy dans le fichier de configuration.
*@return QNetworkProxy * - Pointeur sur l'objet proxy.
*/
QNetworkProxy *ImageShackUploadWidget::readProxySettings()
{
  QNetworkProxy *proxy = new QNetworkProxy;

  if (settings->value("Proxy/enabled").toBool())
  {

    proxy->setHostName(settings->value("Proxy/hostname").toString());
    proxy->setPort(settings->value("Proxy/port").toInt());

    if(settings->value("Proxy/type").toInt() == 0)
      proxy->setType(QNetworkProxy::HttpProxy);
    else if(settings->value("Proxy/type").toInt() == 1)
      proxy->setType(QNetworkProxy::Socks5Proxy);

    if(settings->value("Proxy/authenticationEnabled").toBool())
    {
      proxy->setUser(QByteArray::fromBase64(settings->value("Proxy/username").toByteArray()));
      proxy->setPassword(QByteArray::fromBase64(settings->value("Proxy/password").toByteArray()));
    }

  }
  else
  {
    proxy->setType(QNetworkProxy::NoProxy);
  }

return proxy;
}


/**
*@brief Gère les erreurs liées à l'upload.
*@param error. Type de l'erreur.
*/
void ImageShackUploadWidget::manageErrors(ImageShackError::UploadError error)
{
  QString message;

  switch(error)
  {
      case ImageShackError::ConnectionRefusedError            : message= tr("Connection refused");              break;
      case ImageShackError::RemoteHostClosedError             : message= tr("Remote host closed");              break;
      case ImageShackError::HostNotFoundError                 : message= tr("Host not found");                  break;
      case ImageShackError::TimeoutError                      : message= tr("Timeout");                         break;
      case ImageShackError::OperationCanceledError            : message= tr("Operation canceled");              break;
      case ImageShackError::SslHandshakeFailedError           : message= tr("SSL handshake failed");            break;
      case ImageShackError::ProxyConnectionRefusedError       : message= tr("Proxy connection refused");        break;
      case ImageShackError::ProxyConnectionClosedError        : message= tr("Proxy connection closed");         break;
      case ImageShackError::ProxyNotFoundError                : message= tr("Proxy not found");                 break;
      case ImageShackError::ProxyTimeoutError                 : message= tr("Proxy timeout");                   break;
      case ImageShackError::ProxyAuthenticationRequiredError  : message= tr("Proxy authentication required");   break;
      case ImageShackError::ContentAccessDenied               : message= tr("Content access denied");           break;
      case ImageShackError::ContentOperationNotPermittedError : message= tr("Content operation not permitted"); break;
      case ImageShackError::ContentNotFoundError              : message= tr("Content not found");               break;
      case ImageShackError::AuthenticationRequiredError       : message= tr("Authentication required");         break;
      case ImageShackError::ProtocolUnknownError              : message= tr("Protocol unknown");                break;
      case ImageShackError::ProtocolInvalidOperationError     : message= tr("Protocol invalid operation");      break;
      case ImageShackError::UnknownNetworkError               : message= tr("Unknown network");                 break;
      case ImageShackError::UnknownProxyError                 : message= tr("Unknown proxy");                   break;
      case ImageShackError::UnknownContentError               : message= tr("Unknown content");                 break;
      case ImageShackError::ProtocolFailure                   : message= tr("Protocol failure");                break;
      case ImageShackError::ContentReSendError                : message= tr("Content resend");                  break;
      case ImageShackError::TemporaryNetworkFailureError      : message= tr("Temporary network failure");       break;
      case ImageShackError::UnKnownError                      : message= tr("Unknown error");                   break;
      case ImageShackError::FailedOpeningTheFile              : message= tr("Failed to open the file");         break;
      case ImageShackError::MaxSizeReached                    : message= tr("Max Size Reached (5 Mb)");         break;

      default: message = tr("Unknown error");
  }

  if(!message.isEmpty())
  {
    QMessageBox::critical(this,_ERROR_,tr("Upload Error:") + ' ' + message);
    this->abort();
  }
}

/**
*@brief Met à jours les tags, la confientialité et la taille de redimensionnement de tous les objets à uploader.
*/
void ImageShackUploadWidget::updateImageShackObject()
{
  foreach(ImageShackObject *o,objectsList)
  {
	o->setPublic(this->getPrivacy());
	o->setTags(this->getTags());
	o->setResizeOption(items.value(m_ui->resizeComboBox->currentIndex()));
  }
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void ImageShackUploadWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        m_ui->retranslateUi(this);
    QWidget::changeEvent(event);
}


/**
*@brief Annule l'upload à la fermeture du QWidget.
*@param *event  Evènement.
*/
void ImageShackUploadWidget::closeEvent(QCloseEvent* event)
{
    if(imageShackUploader->uploadsInProgress())
        this->abort();
    event->accept();
}

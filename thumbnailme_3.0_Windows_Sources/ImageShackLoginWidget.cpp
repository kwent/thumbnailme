/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ImageShackLoginWidget.cpp
*       @class  ImageShackLoginWidget
*	Cette classe permet la génération du widget permettant à l'utilisateur
*       de s'authentifier auprès de imageShack.
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

#include "ImageShackLoginWidget.h"

/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/
ImageShackLoginWidget::ImageShackLoginWidget(MainWindow *main_window) : QStackedWidget(main_window)
{
    this->main_window = main_window;

    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    QWidget *notConnectedWidget = new QWidget(this);
    QWidget *logInProgressWidget = new QWidget(this);
    QWidget *logInWidget = new QWidget(this);

    /*NotConnectedWidget Building*/
    QHBoxLayout *imageShacklayout = new QHBoxLayout;

    QLabel *accountLabel = new QLabel(this);
    loginAccountLabel = new QLabel(this);
    passwordAccountLabel = new QLabel(this);

    QPixmap *imageShackPixmap = new QPixmap(":/sprites/imageShack_frog.png");
        accountLabel->setPixmap(imageShackPixmap->scaled(36,36));

    loginAccountLineEdit = new QLineEdit(this);
        loginAccountLineEdit->installEventFilter(this);
    passwordAccountLineEdit = new QLineEdit(this);
        passwordAccountLineEdit->setEchoMode(QLineEdit::Password);
        passwordAccountLineEdit->installEventFilter(this);

    rememberPasswordCheckBox = new QCheckBox(this);
    loginButton = new QPushButton(QIcon(":/sprites/run.png"),tr("Login"),this);
        loginButton->setAutoDefault(true);

    autoLoginCheckBox = new QCheckBox(this);

    QVBoxLayout *vLayout = new QVBoxLayout;
        vLayout->addWidget(rememberPasswordCheckBox);
        vLayout->addWidget(autoLoginCheckBox);

    imageShacklayout->addWidget(accountLabel);
    imageShacklayout->addWidget(loginAccountLabel);
    imageShacklayout->addWidget(loginAccountLineEdit);
    imageShacklayout->addWidget(passwordAccountLabel);
    imageShacklayout->addWidget(passwordAccountLineEdit);
    imageShacklayout->addLayout(vLayout);
    imageShacklayout->addWidget(loginButton);

    notConnectedWidget->setLayout(imageShacklayout);

    imageShackUploader = new ImageShackUploader(IMAGESHACK_DEVELOPERKEY);
    this->imageShackUsername = QString();

    /*LogInProgress Building*/

    QHBoxLayout *logInProgresslayout = new QHBoxLayout;
        logInProgresslayout->addStretch(1);

    QMovie *progress = new QMovie(":/sprites/uploading.gif",QByteArray(),this);
        progress->start();

    QLabel *progressLabel = new QLabel(this);
        progressLabel->setMovie(progress);

    inProgressLabel = new QLabel(tr("Login in progress..."),this);

    cancelButton = new QPushButton(QIcon(":/sprites/cancel.png"),tr("Cancel"),this);

    logInProgresslayout->addWidget(inProgressLabel);
    logInProgresslayout->addWidget(progressLabel);
    logInProgresslayout->addWidget(cancelButton);

    logInProgressWidget->setLayout(logInProgresslayout);

    /*logInWidget Building*/
    QHBoxLayout *logInlayout = new QHBoxLayout;
        logInlayout->addStretch(1);

    loginAsLabel = new QLabel(this);
    logoutButton = new QPushButton(QIcon(":/sprites/cancel.png"),tr("Logout"),this);

    logInlayout->addWidget(accountLabel);
    logInlayout->addWidget(loginAsLabel);
    logInlayout->addWidget(logoutButton);

    logInWidget->setLayout(logInlayout);

    /*Ajout des Widget au stack*/
    this->addWidget(notConnectedWidget);
    this->addWidget(logInProgressWidget);
    this->addWidget(logInWidget);
    this->retranslate();

    /*Connections*/
    connect(loginButton,              SIGNAL(pressed()), this ,                              SLOT(logIn()));
    connect(logoutButton,             SIGNAL(pressed()), this ,                              SLOT(logOut()));
    connect(cancelButton,             SIGNAL(pressed()), this ,                              SLOT(logOut()));
    connect(loginAccountLineEdit,     SIGNAL(textEdited(QString)), this ,                    SLOT(enabledRememberPassword(QString)));
    connect(passwordAccountLineEdit,  SIGNAL(textEdited(QString)), this ,                    SLOT(enabledRememberPassword(QString)));
    connect(rememberPasswordCheckBox, SIGNAL(toggled(bool)), this ,                          SLOT(enabledAutoLoginCheckBox(bool)));
    connect(rememberPasswordCheckBox, SIGNAL(stateChanged(int)), this ,                      SLOT(forgotPasswordIni(int)));
    connect(autoLoginCheckBox,        SIGNAL(stateChanged(int)), this ,                      SLOT(autoLoginIni(int)));
    connect(imageShackUploader,       SIGNAL(authentificationResponse(bool)), this ,         SLOT(manageIndex(bool)));
    connect(imageShackUploader,       SIGNAL(uploadError(ImageShackError::UploadError)),this,SLOT(manageErrors(ImageShackError::UploadError)));

    this->initializeWidget();

    /*Connection automatique ou non selon les paramètres de l'utilisateur*/
    if(settings->value("ImageShackAccess/autologin").toBool())
      this->logIn();
}

/**
*@brief Destructeur.
*/
ImageShackLoginWidget::~ImageShackLoginWidget()
{
}

/**
*@brief Initialisation des paramètres du widget.
*/
void ImageShackLoginWidget::initializeWidget()
{
    QByteArray lbytes, pbytes;

    lbytes = settings->value("ImageShackAccess/login", QVariant("")).toByteArray();
    pbytes = settings->value("ImageShackAccess/password", QVariant("")).toByteArray();
    QString login = QByteArray::fromBase64(lbytes);
    QString password = QByteArray::fromBase64(pbytes);

    if (!login.isEmpty())
         loginAccountLineEdit->setText(login);

    if (!password.isEmpty())
         passwordAccountLineEdit->setText(password);

    if(!login.isEmpty() && !password.isEmpty())
    {
        rememberPasswordCheckBox->setChecked(false);
        if(settings->value("ImageShackAccess/rememberPassword").toBool())
        {
            rememberPasswordCheckBox->setChecked(true);
            autoLoginCheckBox->setChecked(settings->value("ImageShackAccess/autologin").toBool());
        }
    }
    else if (login.isEmpty() || password.isEmpty())
    {
        rememberPasswordCheckBox->setDisabled(true);
        autoLoginCheckBox->setDisabled(true);
        loginButton->setDisabled(true);
    }
}

/**
*@brief  Connection de l'utilisateur sur ImageShack.
*/
void ImageShackLoginWidget::logIn()
{
    //On change l'index
    this->setCurrentIndex(1);

    //On enregistre le login.
    settings->setValue("ImageShackAccess/login",this->getUserLogin());

    //On enregistre le password si l'utilisateur le souhaite.
    if (rememberPasswordCheckBox->isChecked())
    {
        settings->setValue("ImageShackAccess/rememberPassword",true);
        settings->setValue("ImageShackAccess/password",this->getPassword());
    }

    //Login
    imageShackUploader->setProxy(readProxySettings());
    imageShackUploader->checkUserPassword(loginAccountLineEdit->text(),passwordAccountLineEdit->text());
}

/**
*@brief  Déconnection de l'utilisateur de imageShack.
*/
void ImageShackLoginWidget::logOut()
{
    this->setCurrentIndex(0);
    emit loginState(false);
    imageShackUploader->abortUploads();
}

/**
*@brief Permet de changer l'index du widget selon si l'utilisateur est connecté ou pas.
*@param authentication Etat de la connection.
*/
void ImageShackLoginWidget::manageIndex(bool authentication)
{
  if(authentication)
  {
    this->setCurrentIndex(2);
    this->imageShackUsername = imageShackUploader->getLastUserName();
    this->setLoginAs(imageShackUploader->getLastUserName());
    emit loginState(authentication);
  }
  else
  {
    this->logOut();
    if(!loginAccountLineEdit->text().isEmpty() || !passwordAccountLineEdit->text().isEmpty())
        QMessageBox::warning(this,_WARNING_,tr("Authentication failed. Check your username and password."));
  }
}

/**
*@brief Gère les erreurs liées à l'upload.
*@param error. Type de l'erreur.
*/
void ImageShackLoginWidget::manageErrors(ImageShackError::UploadError error)
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
      QMessageBox::critical(this,_ERROR_,tr("Upload Error:") + ' ' + message);
}

/**
*@brief  Retourne le login saisie par l'utilisateur | Mail ou login.
*@return QByteArray - Mail ou login crypté.
*/
QByteArray ImageShackLoginWidget::getUserLogin()
{
    return loginAccountLineEdit->text().toAscii().toBase64();
}

/**
*@brief  Retourne l'username réel connu de ImageShack de l'utilisateur en fonction de son login ou de son mail.
*@return QString - Username.
*/
QString ImageShackLoginWidget::getImageShackUsername()
{
    return imageShackUsername;
}

/**
*@brief  Retourne le mot de passe.
*@return QByteArray - Mot de passe crypté.
*/
QByteArray ImageShackLoginWidget::getPassword()
{
    return passwordAccountLineEdit->text().toAscii().toBase64();
}

/**
*@brief  Permet d'afficher "Connecté en tant que username".
*@param  username	Nom d'utilisateur connecté.
*/
void ImageShackLoginWidget::setLoginAs(QString username)
{
	loginAsLabel->setText((tr("Login as"))+' '+username);
}

/**
*@brief  Vrai si la case "Se rapeller de mon mot de passe" est coché, faux sinon.
*@return bool - Vrai ou faux.
*/
bool ImageShackLoginWidget::isRememberPasswordChecked()
{
    return rememberPasswordCheckBox->isChecked();
}

/**
*@brief  Lit les paramètres du proxy dans le fichier de configuration.
*@return QNetworkProxy * - Pointeur sur l'objet proxy.
*/
QNetworkProxy *ImageShackLoginWidget::readProxySettings()
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
*@brief  Réimplémentation de eventFilter pour permettre le login de l'utilisateur avec l'action de la touche entrée.
*@param  *o    Objet.
*@param  *e    Evénement.
*@return bool - Vrai ou faux.
*/
bool ImageShackLoginWidget::eventFilter(QObject *o, QEvent *e)
{
  if (e->type() == QEvent::KeyPress)
  {
	QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);

    if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
	{
	  this->logIn();
	  return true;
	}
	else return false;
  }
  else
  {
	return QObject::eventFilter(o, e);
  }
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void ImageShackLoginWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Active la CheckBox "AutoLogin" si la CheckBox "Remember Password" est cochée.
*@param state Etat de la checkbox.
*/
void ImageShackLoginWidget::enabledAutoLoginCheckBox(bool checked)
{
    autoLoginCheckBox->setDisabled((!checked) ? true : false);
}

/**
*@brief Active la CheckBox "Remember Password" si le login et le password ne sont pas vide.
*@param password    Login ou password.
*/
void ImageShackLoginWidget::enabledRememberPassword(QString password)
{
    bool state = password.isEmpty() || loginAccountLineEdit->text().isEmpty() || passwordAccountLineEdit->text().isEmpty() ? true : false;
    rememberPasswordCheckBox->setDisabled(state);
    loginButton->setDisabled(state);
}
/**
*@brief Efface le mot de passe dans le fichier de configuration.
*@param state   Etat de la checkbox.
*/
void ImageShackLoginWidget::forgotPasswordIni(int state)
{
    if(state == Qt::Unchecked)
        settings->setValue("ImageShackAccess/password",QByteArray());
}

/**
*@brief Inscrit l'autologin dans le fichier de configuration.
*@param state   Etat de la checkbox.
*/
void ImageShackLoginWidget::autoLoginIni(int state)
{
    if(state == Qt::Checked)
         settings->setValue("ImageShackAccess/autologin",true);
    else settings->setValue("ImageShackAccess/autologin",false);
}

/**
*@brief Fonction de traduction dynamique.
*/
void ImageShackLoginWidget::retranslate()
{
    loginAccountLabel->setText( tr("Username/E-mail") + " :" );
    passwordAccountLabel->setText( tr("Password") + " :" );
    rememberPasswordCheckBox->setText( tr("Remember Password") );
    autoLoginCheckBox->setText( tr("Autologin") );
    loginButton->setText( tr("Login") );
    inProgressLabel->setText( tr("Login in progress...") );
    logoutButton->setText( tr("Logout") );
    cancelButton->setText( tr("Cancel") );

    if(this->currentIndex() == 2)
    this->setLoginAs(imageShackUsername);
}

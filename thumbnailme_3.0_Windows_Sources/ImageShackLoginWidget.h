/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ImageShackLoginWidget.h
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

#ifndef HEADER_IMAGESHACKLOGINWIDGET
#define HEADER_IMAGESHACKLOGINWIDGET

#include "MainWindow.h"
#include "ImageShackUploader/ImageShackUploader.hpp"

class MainWindow;

class ImageShackLoginWidget : public  QStackedWidget
{
    Q_OBJECT

    public:
    explicit ImageShackLoginWidget(MainWindow *main_window);
    virtual ~ImageShackLoginWidget();
    void     initializeWidget();

    private:
    MainWindow         *main_window;

    QSettings          *settings;
    QLabel             *loginAccountLabel;
    QLabel             *loginAsLabel;
    QLabel             *passwordAccountLabel;
    QLabel             *inProgressLabel;
    QLineEdit          *loginAccountLineEdit;
    QLineEdit          *passwordAccountLineEdit;
    QCheckBox          *rememberPasswordCheckBox;
    QCheckBox          *autoLoginCheckBox;
    QPushButton        *loginButton;
    QPushButton        *logoutButton;
    QPushButton        *cancelButton;
    QString            imageShackUsername;
    ImageShackUploader *imageShackUploader;


    public:
    QByteArray getUserLogin();
    QString    getImageShackUsername();
    QByteArray getPassword();
    void       setLoginAs(QString username);
    bool       isRememberPasswordChecked();

    private:
    QNetworkProxy *readProxySettings();
    void           retranslate();

    protected:
    bool eventFilter(QObject *o, QEvent *e);
    void changeEvent(QEvent* event);

    private slots:
    void logIn();
    void logOut();
    void manageIndex(bool authentication);
    void manageErrors(ImageShackError::UploadError);
    void enabledAutoLoginCheckBox(bool checked);
    void enabledRememberPassword(QString password);
    void forgotPasswordIni(int state);
    void autoLoginIni(int state);

    signals:
    /**
    *@brief Ce signal est émit lorsque le login change d'état.
    */
    void loginState(bool);
};

#endif // HEADER_IMAGESHACKLOGINWIDGET

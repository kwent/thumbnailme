/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	NetworkSettingsTab.h
*       @class  NetworkSettingsTab
*	Cette classe permet de configurer manuellement un proxy.
*       Elle génère un widget disponible dans le widget "Settings".
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

#ifndef HEADER_NETWORKSETTINGSTAB
#define HEADER_NETWORKSETTINGSTAB

#include <QtGui>
#include "IniManager.h"

class NetworkSettingsTab : public QWidget
{

    Q_OBJECT

    public:
    explicit NetworkSettingsTab();
    virtual ~NetworkSettingsTab();
    void     initializeWidget();

    private:
    QSettings     *settings;

    QRadioButton  *directConnectionRadio;
    QRadioButton  *useProxyRadio;

    QGroupBox     *proxyGroupBox;
    QGroupBox     *connectionGroupBox;
    QLabel        *proxyHostnameLabel;
    QLabel        *proxyPortLabel;
    QLabel        *proxyType;
    QRadioButton  *proxyTypeHttpRadio;
    QRadioButton  *proxyTypeSocks5Radio;
    QCheckBox     *proxyAuthenticationCheckbox;
    QLabel        *proxyUsernameLabel;
    QLabel        *proxyPasswordLabel;
    QLineEdit     *proxyHostnameLineEdit;
    QSpinBox      *proxyPortLineEdit;
    QLineEdit     *proxyUsernameLineEdit;
    QLineEdit     *proxyPasswordLineEdit;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public:
    QString    getProxyHostname();
    QString    getProxyPort();
    QByteArray getProxyUsername();
    QByteArray getProxyPassword();

    void    setProxyHostname(QString hostname);
    void    setProxyPort(int port);
    void    setProxyUsername(QByteArray username);
    void    setProxyPassword(QByteArray password);
    void    setProxyType(int type);

    int     getProxyType();
    bool    isProxyChecked();
    bool    isAuthenticationChecked();

    private slots:
    virtual void reject();
    void setEnabledProxyGroupBox(bool checked);
};

#endif // HEADER_NETWORKSETTINGSTAB

/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	NetworkSettingsTab.cpp
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

#include "NetworkSettingsTab.h"

/**
*@brief Constructeur.
*/
NetworkSettingsTab::NetworkSettingsTab()
{
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    QGridLayout *networkLayout = new QGridLayout;
    QHBoxLayout *networkHLayout = new QHBoxLayout;

    /*Construction du groupBox "Connection"*/
    connectionGroupBox = new QGroupBox(this);
        directConnectionRadio = new QRadioButton(this);
        useProxyRadio = new QRadioButton(this);

    QVBoxLayout *networkGroupBoxLayout = new QVBoxLayout;
        networkGroupBoxLayout->addWidget(directConnectionRadio);
        networkGroupBoxLayout->addWidget(useProxyRadio);

    connectionGroupBox->setLayout(networkGroupBoxLayout);

    /*Construction du groupBox "Proxy"*/
    proxyHostnameLabel = new QLabel(this);
    proxyPortLabel = new QLabel(this);
    proxyType = new QLabel(this);

    proxyAuthenticationCheckbox = new QCheckBox(this);
    proxyUsernameLabel = new QLabel(this);
    proxyUsernameLineEdit = new QLineEdit(this);
    proxyPasswordLabel = new QLabel(this);
    proxyPasswordLineEdit = new QLineEdit(this);
    proxyPasswordLineEdit->setEchoMode(QLineEdit::Password);

    proxyGroupBox = new QGroupBox(this);
    QGridLayout *proxyGroupBoxLayout = new QGridLayout;

    proxyHostnameLineEdit = new QLineEdit(this);

    //Range port 0-65535
    proxyPortLineEdit = new QSpinBox(this);
    proxyPortLineEdit->setMaximum(65536);

    proxyTypeHttpRadio = new QRadioButton(this);
    proxyTypeSocks5Radio = new QRadioButton(this);

    proxyGroupBoxLayout->addWidget(proxyHostnameLabel,0,0);
    proxyGroupBoxLayout->addWidget(proxyHostnameLineEdit,0,1);
    proxyGroupBoxLayout->addWidget(proxyPortLabel,1,0);
    proxyGroupBoxLayout->addWidget(proxyPortLineEdit,1,1);

    QHBoxLayout *typeLayout = new QHBoxLayout;
        typeLayout->addWidget(proxyTypeHttpRadio);
        typeLayout->addWidget(proxyTypeSocks5Radio);

    proxyGroupBoxLayout->addWidget(proxyType,2,0);
    proxyGroupBoxLayout->addLayout(typeLayout,2,1);

    proxyGroupBoxLayout->addWidget(proxyAuthenticationCheckbox,3,0);
    proxyGroupBoxLayout->addWidget(proxyUsernameLabel,4,0);
    proxyGroupBoxLayout->addWidget(proxyUsernameLineEdit,4,1,1,2);
    proxyGroupBoxLayout->addWidget(proxyPasswordLabel,5,0);
    proxyGroupBoxLayout->addWidget(proxyPasswordLineEdit,5,1,1,2);

    proxyGroupBox->setLayout(proxyGroupBoxLayout);

    /*Layout en haut*/
    networkHLayout->addWidget(connectionGroupBox);

    /*Layout global*/
    networkLayout->addLayout(networkHLayout,0,0);
    networkLayout->addWidget(proxyGroupBox);

    this->initializeWidget();
    this->setLayout(networkLayout);
    this->retranslate();

    /*Connections*/
    connect(useProxyRadio,SIGNAL(toggled(bool)),this,SLOT(setEnabledProxyGroupBox(bool)));
    connect(proxyAuthenticationCheckbox,SIGNAL(clicked(bool)),proxyUsernameLineEdit,SLOT(setEnabled(bool)));
    connect(proxyAuthenticationCheckbox,SIGNAL(clicked(bool)),proxyPasswordLineEdit,SLOT(setEnabled(bool)));
}

/**
*@brief Destructeur.
*/
NetworkSettingsTab::~NetworkSettingsTab()
{
}

/**
*@brief Initialisation des paramètres du widget.
*/
void NetworkSettingsTab::initializeWidget()
{
    /*Initialisation du widget selon les paramètres du fichier de configuration*/

    setProxyHostname(settings->value("Proxy/hostname").toString());

    if(!settings->value("Proxy/port").isNull())
        setProxyPort(settings->value("Proxy/port").toInt());
    else
        setProxyPort(8080);

    setProxyType(settings->value("Proxy/type").toInt());
    setProxyUsername(settings->value("Proxy/username").toByteArray());
    setProxyPassword(settings->value("Proxy/password").toByteArray());

    if (settings->value("Proxy/enabled") == "true")
    {
         useProxyRadio->setChecked(true);
         setEnabledProxyGroupBox(true);
    }
    else
    {
        directConnectionRadio->setChecked(true);
        proxyGroupBox->setDisabled(true);
    }

    if (settings->value("Proxy/authenticationEnabled") == "true")
         proxyAuthenticationCheckbox->setChecked(true);
    else proxyAuthenticationCheckbox->setChecked(false);
}

/**
*@brief  Retourne l'adresse hôte du proxy.
*@return QString - Valeur du champ.
*/
QString NetworkSettingsTab::getProxyHostname()
{
    return proxyHostnameLineEdit->text();
}

/**
*@brief  Retourne le port du proxy.
*@return QString - Valeur du champ.
*/
QString NetworkSettingsTab::getProxyPort()
{
    return proxyPortLineEdit->text();
}

/**
*@brief  Retourne le nom d'utilisateur codé en base 64 pour une connexion avec authentification.
*@return QByteArray - Valeur du champ.
*/
QByteArray NetworkSettingsTab::getProxyUsername()
{
    return proxyUsernameLineEdit->text().toAscii().toBase64();
}

/**
*@brief  Retourne le mot de passe codé en base 64 pour une connection avec authentification.
*@return QByteArray - Valeur du champ.
*/
QByteArray NetworkSettingsTab::getProxyPassword()
{
    return proxyPasswordLineEdit->text().toAscii().toBase64();
}

/**
*@brief  Retourne le type de proxy (HTTP ou SOCK5).
*@return int - 1 = HTTP | 2 = SOCK5.
*/
int NetworkSettingsTab::getProxyType()
{
    if (proxyTypeHttpRadio->isChecked())
        return 0;
    else return 1;
}

/**
*@brief Setter de l'adresse hôte du proxy.
*@param hostname    Adresse hôte du proxy.
*/
void NetworkSettingsTab::setProxyHostname(QString hostname)
{
    proxyHostnameLineEdit->setText(hostname);
}

/**
*@brief Setter du port du proxy
*@param port    Port du proxy.
*/
void NetworkSettingsTab::setProxyPort(int port)
{
    proxyPortLineEdit->setValue(port);
}

/**
*@brief Setter du nom d'utilisateur pour une connection avec authentification.
*@param username    Nom d'utilisateur en base 64.
*/
void NetworkSettingsTab::setProxyUsername(QByteArray username)
{
    proxyUsernameLineEdit->setText(QByteArray::fromBase64(username));
}

/**
*@brief Setter du mot de passe pour une connection avec authentification.
*@param password    Mot de passe en base 64.
*/
void NetworkSettingsTab::setProxyPassword(QByteArray password)
{
    proxyPasswordLineEdit->setText(QByteArray::fromBase64(password));
}

/**
*@brief Setter du type de proxy (HTTP ou SOCK5).
*@param type    1 = HTTP | 2 = SOCK5.
*/
void NetworkSettingsTab::setProxyType(int type)
{
    if (type == 0)
       proxyTypeHttpRadio->setChecked(true);
    else proxyTypeSocks5Radio->setChecked(true);
}

/**
*@brief  Retourne vrai si le proxy est activé sinon faux.
*@return bool - Vrai ou faux.
*/
bool NetworkSettingsTab::isProxyChecked()
{
    return useProxyRadio->isChecked();
}

/**
*@brief  Retourne vrai si l'authenfication est activée sinon faux.
*@return bool - Vrai ou faux.
*/
bool NetworkSettingsTab::isAuthenticationChecked()
{
    return proxyAuthenticationCheckbox->isChecked();
}

/**
*@brief Active ou désactive la partie proxy.
*@param checked    Vrai ou faux.
*/
void NetworkSettingsTab::setEnabledProxyGroupBox(bool checked)
{
    if(checked)
    {
        proxyGroupBox->setEnabled(true);

        if (settings->value("Proxy/authenticationEnabled") != "true")
        {
           proxyAuthenticationCheckbox->setChecked(false);
           proxyUsernameLineEdit->setDisabled(true);
           proxyPasswordLineEdit->setDisabled(true);
        }

    }
    else
    {
        proxyGroupBox->setDisabled(true);
    }
}

/**
*@brief  Fonction annulation - Réaffecte les paramètres d'origine.
*/
void NetworkSettingsTab::reject()
{
    this->initializeWidget();
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void NetworkSettingsTab::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void NetworkSettingsTab::retranslate()
{
    connectionGroupBox->setTitle( tr("Network Connection") );
    directConnectionRadio->setText( tr("Direct connection") );
    useProxyRadio->setText( tr("Use proxy server") );
    proxyHostnameLabel->setText( tr("Hostname") + " : " );
    proxyPortLabel->setText( tr("Port") + " : " );
    proxyType->setText( tr("Type") + " : " );
    proxyAuthenticationCheckbox->setText( tr("Authentication") );
    proxyUsernameLabel->setText( tr("Username") + " : " );
    proxyPasswordLabel->setText( tr("Password") + " : " );
    proxyGroupBox->setTitle( tr("Proxy Settings") );
    proxyTypeHttpRadio->setText( "HTTP" );
    proxyTypeSocks5Radio->setText( "SOCKS5" );
}

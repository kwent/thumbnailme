/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	SettingsWidget.cpp
*       @class  SettingsWidget
*	Cette classe permet la génération du widget "Options".
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

#include "SettingsWidget.h"

#include "defines.h"
#include "GeneralSettingsTab.h"
#include "MainWindow.h"
#include "FontsSettingsTab.h"
#include "LanguagesSettingsTab.h"
#include "NetworkSettingsTab.h"
#include "QtHelper.h"
#include "ConfigWidget.h"
#include "DockStyles.h"
#include "PreviewGraphicView.h"
#include "FontMapComboBox.h"


/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/
SettingsWidget::SettingsWidget(MainWindow * main_window)
{
    this->main_window = main_window;
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    /*Pointeur initialisés*/
    soft_translator = 0;
    system_translator = 0;

    /*Description Fenetre principale*/
    //this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowOkButtonHint | Qt::Dialog);
    this->setWindowIcon(QIcon( ":/sprites/settings.png" ));
    this->setWindowModality(Qt::ApplicationModal);

    /*Déclaration des widgets contenus dans chaque tab*/
    generalTab = new GeneralSettingsTab;
    fontsTab = new FontsSettingsTab;
    languagesTab = new LanguagesSettingsTab;
    networkTab = new NetworkSettingsTab;

    configWidget = new ConfigWidget;
      configWidget->addPage(generalTab,QIcon( ":/sprites/settings.png" ),QString());
      configWidget->addPage(fontsTab,QIcon( ":/sprites/fonts.png" ),QString());
      configWidget->addPage(languagesTab,QIcon( ":/sprites/languages.png" ),QString());
      configWidget->addPage(networkTab,QIcon( ":/sprites/apps.png" ),QString());
      configWidget->setIconSize(QSize(50,50));

    this->setConfigWidget(configWidget);

    /*Connections*/
    connect( this, SIGNAL(accepted()), this, SLOT(applySettings()));
    connect( this, SIGNAL(rejected()), this, SLOT(close()));

    /*Chargement animatePixmap*/
    updateAnimatedPixmap(generalTab->isAnimatedPixmapChecked());

    /*Chargement openGL*/
    updateOpenGlGraphicViewIni(generalTab->isActiveOpenGlGraphicViewCheckBoxChecked());

    this->setFixedSize(this->sizeHint());
    this->retranslate();
    QtHelper::centerWidget(this);
}

/**
*@brief Destructeur.
*/
SettingsWidget::~SettingsWidget()
{
  delete main_window;
  delete configWidget;
  delete generalTab;
  delete fontsTab;
  delete languagesTab;
  delete networkTab;
}

/**
*@brief Enregistre les modifications dans le fichier de configuration et applique les changements.
*/
void SettingsWidget::applySettings() 
{
        //On ferme la fenêtre avant d'appliquer les paramètres sinon ralentissements.
        this->close();

        updateNeverAskSaveConfigOnExitIni(generalTab->isNeverAskSaveConfigOnExitChecked());

        updateNeverLoadLastConfigurationIni(generalTab->isNeverLoadLastConfigurationChecked());

        if (generalTab->isOutputSuffixCheckBoxChecked())
            updateOutputPrefixIni(generalTab->getOutputSuffixLineEdit());
        else updateOutputPrefixIni(QString());

        updateAnimatedPixmap(generalTab->isAnimatedPixmapChecked());

        updateOpenGlGraphicViewIni(generalTab->isActiveOpenGlGraphicViewCheckBoxChecked());

        updateLanguage();

        updateColorBackgroundPreviewGraphicView(generalTab->getColorBackgroundPreviewGraphicView());

        updateProxyIni(networkTab->isProxyChecked());

        updateFontsListWidget();
}

/**
*@brief Met à jour le suffixe dans le fichier de configuration.
*@param suffix    Nouveau suffixe.
*/
void SettingsWidget::updateOutputPrefixIni(QString suffix)
{
        settings->setValue("Extras/outputSuffix",suffix);
}

/**
*@brief Met à jour les QListWidget contenant le nom des polices du DockStyles.
*/
void SettingsWidget::updateFontsListWidget()
{
    if(QtHelper::readPathsFontsValueIni(settings) != QtHelper::getItemsListWidget(fontsTab->getFontPathListWidget()))
    {
        updatePathsFontsIni();
        main_window->mpDockStyles->getInfoTextComboBox()->clear();
        main_window->mpDockStyles->getTimestampComboBox()->clear();
        this->updateFontsListEngine();
    }
}

void SettingsWidget::updateFontsListEngine()
{
    if (fontsTab->getFontPathListWidget()->count() == 0)
    {
            main_window->mpDockStyles->getInfoTextComboBox()->setnoFontDefined(true);
            main_window->mpDockStyles->getTimestampComboBox()->setnoFontDefined(true);
            return;
    }

    QFile file(FONTS_CACHING);
        file.open(QIODevice::WriteOnly);
    QDataStream out(&file);    // read the data serialized from the file

    main_window->mpDockStyles->setStackedWidgetToLoadingState();
    QMap <QString,QString> mapGlobal  = QtHelper::exploreTTFDir(QtHelper::getItemsListWidget(fontsTab->getFontPathListWidget()));
    QMap <QString,QString> mapDefault = QtHelper::exploreTTFDir(QStringList(DEFAULT_PATH_FONT));

    out << mapGlobal << mapDefault; //Ecriture dans le fichier de cache des polices.

    main_window->mpDockStyles->getInfoTextComboBox()->setMap(mapGlobal);
    main_window->mpDockStyles->getTimestampComboBox()->setMap(mapDefault);

    main_window->mpDockStyles->getInfoTextComboBox()->addFamilyItems();
    main_window->mpDockStyles->getTimestampComboBox()->addFamilyItems();
}

/**
*@brief Met à jour la liste des chemins de dossiers contenant les polices dans le fichier de configuration.
*/
void SettingsWidget::updatePathsFontsIni()
{
	settings->sync();
	settings->remove("Font_Paths");
	
	settings->beginGroup("Font_Paths");

        for(int i= 0; i < fontsTab->getFontPathListWidget()->count(); i++)
                settings->setValue("font_path"+QString::number(i),fontsTab->getFontPathListWidget()->item(i)->text());

	settings->endGroup();
}

/**
*@brief Vrai: l'utilisateur peut quitter Thumbnail Me sans confirmation d'enregistrement de la configuration actuelle.
*@param checked    Vrai ou faux.
*/
void SettingsWidget::updateNeverAskSaveConfigOnExitIni(bool checked)
{
    settings->beginGroup("Extras");

    if (checked)
         settings->setValue("neverAskSaveConfigOnExit","true");
    else settings->setValue("neverAskSaveConfigOnExit","false");

    settings->endGroup();
}

/**
*@brief Vrai: Le chargement du fichier de configuration de la dernière session ne sera pas chargé.
*@param checked    Vrai ou faux.
*/
void SettingsWidget::updateNeverLoadLastConfigurationIni(bool checked)
{
    settings->beginGroup("Extras");

    if (checked)
         settings->setValue("neverLoadLastConfiguration","true");
    else settings->setValue("neverLoadLastConfiguration","false");

    settings->endGroup();
}

/**
*@brief Vrai: La fenêtre de prévisualisation utilise openGL pour faire son rendu.
*@param checked    Vrai ou faux.
*/
void SettingsWidget::updateOpenGlGraphicViewIni(bool checked)
{
    settings->beginGroup("Extras");

    QFlags<QGLFormat::OpenGLVersionFlag> openGL_versions (QGLFormat::openGLVersionFlags ());

    //Au minimum openGL 3.0
    if (checked && QGLFormat::hasOpenGL () && openGL_versions.testFlag(QGLFormat::OpenGL_Version_3_0))
    {
        main_window->mpPreviewGraphicView->setViewportModeOpenGL(true);
        settings->setValue("activeOpenGl","true");
    }
    else if (checked && QGLFormat::hasOpenGL () && !openGL_versions.testFlag(QGLFormat::OpenGL_Version_3_0))
    {
        main_window->mpPreviewGraphicView->setViewportModeOpenGL(false);
        QMessageBox::warning(this, _WARNING_, tr("OpenGL version 3.0 or higher is not present on your system. It will be disabled."));
        generalTab->setActiveOpenGlGraphicViewCheckBoxChecked(false);
        settings->setValue("activeOpenGl","false");
    }
    else if(checked && !QGLFormat::hasOpenGL ())
    {
        QMessageBox::warning(this, _WARNING_, tr("openGL not detected on your system. It will be disabled."));
        main_window->mpPreviewGraphicView->setViewportModeOpenGL(false);
        generalTab->setActiveOpenGlGraphicViewCheckBoxChecked(false);
        settings->setValue("activeOpenGl","false");
    }
    else
    {
        main_window->mpPreviewGraphicView->setViewportModeOpenGL(false);
        settings->setValue("activeOpenGl","false");
    }

    settings->endGroup();
}

/**
*@brief Change la langue de Thumbnail Me.
*/
void SettingsWidget::updateLanguage()
{
    QString locale = languagesTab->getLanguageChecked();

    if (settings->value("Langs/lang").toString() != locale)
    {
        if(system_translator)
            QCoreApplication::removeTranslator(system_translator);
        if(soft_translator)
            QCoreApplication::removeTranslator(soft_translator);

        delete system_translator;
        delete soft_translator;

        system_translator = new QTranslator;
        soft_translator = new QTranslator;

        system_translator->load(TRANSLATORS + "qt_" + locale);
        QCoreApplication::installTranslator(system_translator);

        soft_translator->load(DEFAULT_PATH_LANG + "thumbnailme_" + locale);
        QCoreApplication::installTranslator(soft_translator);

        settings->setValue("Langs/lang",locale);
    }
}


/**
*@brief Met à jour la couleur de l'arrière plan de la fenêtre de prévisualisation dans le fichier de configuration.
*@param color    Nouvelle couleur.
*/
void SettingsWidget::updateColorBackgroundPreviewGraphicView(QColor color)
{
    settings->setValue("Extras/backgroundColorPreviewWindow",QtHelper::qColor2rgbNoSharp(color));
    main_window->mpPreviewGraphicView->setBackgroundBrush(QBrush(color));
}

/**
*@brief Vrai: Met à jour les paramètres de proxy dans le fichier de configuration.
*@param checked    Vrai ou faux.
*/
void SettingsWidget::updateProxyIni(bool checked)
{
    settings->beginGroup("Proxy");

    if (checked)
    {
        settings->setValue("enabled",true);
        settings->setValue("hostname",networkTab->getProxyHostname());
        settings->setValue("port",networkTab->getProxyPort());
        settings->setValue("type",networkTab->getProxyType());
        settings->setValue("authenticationEnabled",networkTab->isAuthenticationChecked());
        settings->setValue("username",networkTab->getProxyUsername());
        settings->setValue("password",networkTab->getProxyPassword());
    }
    else settings->setValue("enabled",false);

    settings->endGroup();
}

/**
*@brief Vrai: Anime le pixmap lors de l'affichage du rendu.
*@param checked    Vrai ou faux.
*/
void SettingsWidget::updateAnimatedPixmap(bool checked)
{
  if (checked)
       settings->setValue("Extras/animatedPixmap",true);
  else settings->setValue("Extras/animatedPixmap",false);

  main_window->mpPreviewGraphicView->setAnimatedPixmap(checked);
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void SettingsWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void SettingsWidget::retranslate()
{
    this->setWindowTitle(tr("Settings"));
    configWidget->setPageTitle(configWidget->indexOf(generalTab),tr("General"));
    configWidget->setPageTitle(configWidget->indexOf(fontsTab),tr("Fonts"));
    configWidget->setPageTitle(configWidget->indexOf(languagesTab),tr("Languages"));
    configWidget->setPageTitle(configWidget->indexOf(networkTab),tr("Network"));
}

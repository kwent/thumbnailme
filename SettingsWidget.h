/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	SettingsWidget.h
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

#ifndef HEADER_SETTINGSWIDGET
#define HEADER_SETTINGSWIDGET

#include "Qxt/qxtconfigdialog.h"
#include <QSettings>
#include <QTranslator>

class GeneralSettingsTab;
class MainWindow;
class FontsSettingsTab;
class LanguagesSettingsTab;
class NetworkSettingsTab;
class ConfigWidget;

class SettingsWidget : public QxtConfigDialog
{

  Q_OBJECT

    public:
    explicit SettingsWidget(MainWindow * main_window);
    virtual ~SettingsWidget();

    private:
    MainWindow *main_window;
    QSettings  *settings;

    ConfigWidget *configWidget;
        GeneralSettingsTab *generalTab;
        FontsSettingsTab *fontsTab;
        LanguagesSettingsTab *languagesTab;
        NetworkSettingsTab *networkTab;

    QTranslator *soft_translator;
    QTranslator *system_translator;

    private:
    void updateAnimatedPixmap(bool checked);
    void updateColorBackgroundPreviewGraphicView(QColor color);
    void updateFontsListWidget();
    void updateFontsListEngine();
    void updateLanguage();
    void updatePathsFontsIni();
    void updateNeverAskSaveConfigOnExitIni(bool checked);
    void updateNeverLoadLastConfigurationIni(bool checked);
    void updateCoresCountToProcess(int count);
    void updateOpenGlGraphicViewIni(bool checked);
    void updateOutputPrefixIni(QString suffix);
    void updateProxyIni(bool checked);
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public slots:
    void applySettings();
};
#endif

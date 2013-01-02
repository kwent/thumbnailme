/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file       main.cpp
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      2.0
*	@version    3.0
*       @date       2011-2012
*******************************************************************************/

#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include "defines.h"
#include "MainWindow.h"

QSettings settings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI);

/**
*@brief  Initialise le fichier de configuration.
*@return QString - Retourne la langue à charger au démarrage de l'application.
*/
QString initSettings()
{

    if (!QFile::exists(settings.fileName()))
    {
        QString locale = QLocale::system().name().section('_', 0, 0);
        settings.beginGroup("Langs");
        settings.setValue("lang",locale);
        settings.endGroup();
        settings.beginGroup("RecentConfs");
        settings.setValue("file1","undefined");
        settings.setValue("file2","undefined");
        settings.setValue("file3","undefined");
        settings.setValue("file4","undefined");
        settings.endGroup();
        settings.setValue("last_path_input","undefined");
        settings.setValue("last_path_output","undefined");
        settings.setValue("last_path_input_batchmod","undefined");
        settings.setValue("last_path_output_batchmod","undefined");
        settings.setValue("last_path_settingload","undefined");
        settings.setValue("last_path_settingsave","undefined");
        settings.beginGroup("Font_Paths");
        settings.setValue("font_path0",DEFAULT_PATH_FONT);
        settings.endGroup();
        return QString(locale);
    } else return settings.value("Langs/lang").toString();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
        app.setWindowIcon(QIcon(":sprites/thumbnailer.png"));
        app.setApplicationName(APPLICATION_NAME);
        app.setApplicationVersion(VERSION);
    /*Initialisation du fichier de configuration + récupération de la langue*/
    QString lang = initSettings();

    /*Chargement de la langue logiciel et qt*/
    QTranslator *system_translator = new QTranslator;
             system_translator->load(TRANSLATORS + "qt_" + lang);

    QTranslator *soft_translator = new QTranslator;
        soft_translator->load(DEFAULT_PATH_LANG + "thumbnailme_" + lang);

    app.installTranslator(system_translator);
    app.installTranslator(soft_translator);

    QPixmap splashPixmap(":sprites/splash.png");

    /* Création de la page de demarrage + La page sera devant toute les fenêtres*/
    QSplashScreen splash(splashPixmap, Qt::WindowStaysOnTopHint);
        splash.setEnabled(false); //Ignore les évènements (Souris, clavier etc.).

    #if defined(Q_OS_LINUX)
        splash.setWindowFlags(Qt::SplashScreen);
    #else
        splash.setWindowFlags(Qt::Dialog);
    #endif

        splash.setMask(QRegion(splashPixmap.mask()));
        splash.show();

    /*Initialisation*/
    splash.showMessage (QObject::tr ("Initialisation"), Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    usleep(500*FACTOR_TIME);
    app.processEvents();

    /*Initialisation of widgets*/
    splash.showMessage (QObject::tr ("Widgets initialisation"), Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    MainWindow mafenetre;
    app.processEvents();

    /*Read preferences*/
    splash.showMessage (QObject::tr("Preferences reading"), Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    usleep(500*FACTOR_TIME);
    app.processEvents();

    /*Starting...*/
    splash.showMessage (QObject::tr("Starting..."), Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    usleep(250*FACTOR_TIME);
    splash.close();

    if(!settings.contains("WindowState/mainWindowGeometry"))
         mafenetre.showMaximized();
    else mafenetre.show();

    app.processEvents();

    /*Lancement de l'application*/
    return app.exec();
}

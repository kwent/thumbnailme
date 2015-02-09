/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	IniManager.cpp
*       @class  IniManager
*	Cette classe gère toutes les lectures/écritures dans le fichier de configuration.
*       Elle applique également les paramètres lus dans le fichier de configuration aux différents Docks.
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

#include "IniManager.h"

/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/
IniManager::IniManager(MainWindow *main_window)
{
    this->main_window=main_window;
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);
}

/**
*@brief Destructeur.
*/
IniManager::~IniManager()
{
    delete main_window;
}


/**
*@brief Permet l'ouverture des dialogues afin de parcourir le fichier de configuration à importer.
*/
void IniManager::importConf()
{
    QString fileName;

    if (settings->value("last_path_settingload").toString() != "undefined")
        fileName = QFileDialog::getOpenFileName(main_window, tr("Open Configuration File"),settings->value("last_path_settingload").toString(),tr("Configuration file(*.ini)"));
    else
        fileName = QFileDialog::getOpenFileName(main_window, tr("Open Configuration File"),"",tr("Configuration file(*.ini)"));

    QSettings *mpSettingsLoad = new QSettings(fileName, QSettings::IniFormat);

    if (!fileName.isEmpty())
    {
        settings->setValue("last_path_settingload",fileName);

            if (mpSettingsLoad->value("Program").toString() == "thumbnailme")
            {
                    QQueue<QString> fifo;

                    if (fileName != settings->value("RecentConfs/file1") && fileName != settings->value("RecentConfs/file2") && fileName != settings->value("RecentConfs/file3") && fileName != settings->value("RecentConfs/file4"))
                    {
                            fifo.enqueue(fileName);
                            fifo.enqueue(settings->value("RecentConfs/file1").toString());
                            fifo.enqueue(settings->value("RecentConfs/file2").toString());
                            fifo.enqueue(settings->value("RecentConfs/file3").toString());
                            fifo.enqueue(settings->value("RecentConfs/file4").toString());

                            for (int i = 1 ; i<=4 ; i++)
                            {
                                settings->setValue("RecentConfs/file"+QString::number(i) ,fifo.dequeue());
                            }
                    }

                    /*Lit la configuration et applique les paramètres aux docks*/
                    loadIni(mpSettingsLoad);

                    main_window->setWindowTitle(QApplication::applicationName()+" - "+tr("Configuration file loaded")+": "+fileName);
                    this->setCurrentFileLoaded(fileName);
            }
            else QMessageBox::warning(main_window,_WARNING_,tr("Incorrect settings file"));
    }
}

/**
*@brief Charge les informations de configuration lues dans le fichier .ini passe en paramètre.
*@param *conf   Fichier de configuration à charger.
*/
void IniManager::loadIni(QSettings *conf)
{
    /*Settings Loading*/
    main_window->mpDockConf->setColumns(conf->value("Settings/columns").toInt());
    main_window->mpDockConf->setRows(conf->value("Settings/rows").toInt());
    main_window->mpDockConf->setWidth(conf->value("Settings/width").toInt());
    main_window->mpDockConf->setGap(conf->value("Settings/gap").toInt());
    main_window->mpDockConf->setFormatFile(conf->value("Settings/formatFile").toString());
    main_window->mpDockConf->setQuality(conf->value("Settings/quality").toInt());
    main_window->mpDockConf->setBlankSkip(conf->value("Settings/blank_skip").toDouble());
    main_window->mpDockConf->setEdgeDetect(conf->value("Settings/edge_detect").toInt());

    /*Style Loading*/
    main_window->mpDockStyles->setTitleEdit(conf->value("Styles/additional_title").toString());
    main_window->mpDockStyles->setColorBackground(conf->value("Styles/background_color").toString());

    main_window->mpDockStyles->setCheckedInfoText(conf->value("Styles/infotext_checked").toBool());
    main_window->mpDockStyles->setInfoTextLocation(conf->value("Styles/infotext_location").toInt());
    main_window->mpDockStyles->setSizeInfoText(conf->value("Styles/infotext_size").toInt());
    main_window->mpDockStyles->setFontInfoText(conf->value("Styles/infotext_font").toString());
    main_window->mpDockStyles->setColorInfoText(conf->value("Styles/infotext_color").toString());

    main_window->mpDockStyles->setCheckedTimeStamp(conf->value("Styles/timestamp_checked").toBool());
    main_window->mpDockStyles->setTimeStampLocation(conf->value("Styles/timestamp_location").toInt());
    main_window->mpDockStyles->setSizeTimeStamp(conf->value("Styles/timestamp_size").toInt());
    main_window->mpDockStyles->setFontTimeStamp(conf->value("Styles/timestamp_font").toString());
    main_window->mpDockStyles->setColorTimeStamp(conf->value("Styles/timestamp_color").toString());
    main_window->mpDockStyles->setColorShadow(conf->value("Styles/shadow_color").toString());

    /*Output Path Loading*/
    main_window->mpDockInputOutput->setSameSourceChecked(conf->value("Styles/isSameSourceChecked").toBool());
    main_window->mpDockInputOutput->setPathOutput(conf->value("Styles/path_output_batchmod").toString());

    this->setCurrentFileLoaded(conf->fileName());
    this->retranslate();
}


/**
*@brief Enregistre les informations de configuration dans le fichier .ini passe en paramètre.
*@param *conf   Fichier de configuration à charger.
*/
void IniManager::registerIni(QSettings *conf)
{
    conf->setValue("Program","thumbnailme");
    conf->setValue("Date_file",QDateTime::currentDateTime().toString());

    /*Settings Saving*/
    conf->beginGroup("Settings");
    conf->setValue("columns",     main_window->mpDockConf->getColumns());
    conf->setValue("rows",        main_window->mpDockConf->getRows());
    conf->setValue("width",       main_window->mpDockConf->getWidth());
    conf->setValue("gap",         main_window->mpDockConf->getGap());
    conf->setValue("formatFile",  main_window->mpDockConf->getFormatFile());
    conf->setValue("quality",     main_window->mpDockConf->getQuality());
    conf->setValue("blank_skip",  main_window->mpDockConf->getBlankSkip());
    conf->setValue("edge_detect", main_window->mpDockConf->getEdgeDetect());
    conf->endGroup();

    /*Style Saving*/
    conf->beginGroup("Styles");
    conf->setValue("additional_title",   main_window->mpDockStyles->getTitleEdit());
    conf->setValue("background_color",   main_window->mpDockStyles->getColorBackground().name());
    conf->setValue("infotext_checked",   main_window->mpDockStyles->isInfoTextChecked());
    conf->setValue("timestamp_checked",  main_window->mpDockStyles->isTimeStampChecked());
    conf->setValue("infotext_font",      main_window->mpDockStyles->getFontInfoText(1));
    conf->setValue("timestamp_font",     main_window->mpDockStyles->getFontTimeStamp(1));
    conf->setValue("infotext_location",  main_window->mpDockStyles->getInfoTextLocation());
    conf->setValue("timestamp_location", main_window->mpDockStyles->getTimeStampLocation());
    conf->setValue("infotext_size",      main_window->mpDockStyles->getSizeInfoText());
    conf->setValue("timestamp_size",     main_window->mpDockStyles->getSizeTimeStamp());
    conf->setValue("infotext_color",     main_window->mpDockStyles->getColorInfoText().name());
    conf->setValue("timestamp_color",    main_window->mpDockStyles->getColorTimeStamp().name());
    conf->setValue("shadow_color",       main_window->mpDockStyles->getColorShadow().name());

    /*Output Path Saving*/
    conf->setValue("isSameSourceChecked",  main_window->mpDockInputOutput->isSameSourceChecked());
    conf->setValue("path_output_batchmod", main_window->mpDockInputOutput->getPathOutput());
    conf->endGroup();

    this->setCurrentFileLoaded(conf->fileName());
    this->retranslate();
}

/**
*@brief Permet de sauvegarder la configuration courante de Thumbnail Me.
*/
void IniManager::saveSettings()
{
    if (getCurrentFileLoaded().isEmpty())
      saveSettingsUnder();
    else
    {
      registerIni(new QSettings(getCurrentFileLoaded(), QSettings::IniFormat));
      QMessageBox::information(main_window, tr("Configuration file"),getCurrentFileLoaded()+tr(" saved successfully"));
    }
}

/**
*@brief Permet de sauvegarder la configuration courante de Thumbnail Me sous...
*/
QString IniManager::saveSettingsUnder()
{
    QString fileName;

    if (settings->value("last_path_settingsave").toString() != "undefined")
      fileName = QFileDialog::getSaveFileName(main_window, tr("Save Configuration File"),settings->value("last_path_settingsave").toString(),tr("Configuration file(*.ini)"));
    else
      fileName = QFileDialog::getSaveFileName(main_window, tr("Save Configuration File"),"",tr("Configuration file(*.ini)"));

    if(!fileName.isEmpty())
    {
       settings->setValue("last_path_settingload",fileName);
       settings->setValue("last_path_settingsave",fileName);
       registerIni(new QSettings(fileName, QSettings::IniFormat));
       this->setCurrentFileLoaded(fileName);
    }
return fileName;
}

/**
*@brief Permet de charger la configuration attachée à l'action 1 du menu "Importer une configuration récente" si elle existe.
*/
void IniManager::loadRecentSettings1()
{
    QSettings conf(settings->value("Recentconfs/file1").toString(), QSettings::IniFormat);
    main_window->setWindowTitle(QApplication::applicationName()+" - "+tr("Configuration file loaded")+": "+settings->value("Recentconfs/file1").toString());
    loadIni(&conf);
    setCurrentFileLoaded(settings->value("Recentconfs/file1").toString());
}

/**
*@brief Permet de charger la configuration attachée à l'action 2 du menu "Importer une configuration récente" si elle existe.
*/
void IniManager::loadRecentSettings2()
{
    QSettings conf(settings->value("Recentconfs/file2").toString(), QSettings::IniFormat);
    main_window->setWindowTitle(QApplication::applicationName()+" - "+tr("Configuration file loaded")+": "+settings->value("Recentconfs/file2").toString());
    loadIni(&conf);
    setCurrentFileLoaded(settings->value("Recentconfs/file2").toString());
}

/**
*@brief Permet de charger la configuration attachée à l'action 3 du menu "Importer une configuration récente" si elle existe.
*/
void IniManager::loadRecentSettings3()
{
    QSettings conf(settings->value("Recentconfs/file3").toString(), QSettings::IniFormat);
    main_window->setWindowTitle(QApplication::applicationName()+" - "+tr("Configuration file loaded")+": "+settings->value("Recentconfs/file3").toString());
    loadIni(&conf);
    setCurrentFileLoaded(settings->value("Recentconfs/file3").toString());
}

/**
*@brief Permet de charger la configuration attachée à l'action 4 du menu "Importer une configuration récente" si elle existe.
*/
void IniManager::loadRecentSettings4()
{
    QSettings conf(settings->value("Recentconfs/file4").toString(), QSettings::IniFormat);
    main_window->setWindowTitle(QApplication::applicationName()+" - "+tr("Configuration file loaded")+": "+settings->value("Recentconfs/file4").toString());
    loadIni(&conf);
    setCurrentFileLoaded(settings->value("Recentconfs/file4").toString());
}

/**
*@brief Génere le actions du menu "Importer une configuration récente".
*/
void IniManager::loadRecentConfs()
{
    main_window->getActionOpenRecent()->clear();
    if (!QFileInfo(settings->value("RecentConfs/file1").toString()).exists())
    settings->setValue("RecentConfs/file1","undefined");
    if (!QFileInfo(settings->value("RecentConfs/file2").toString()).exists())
    settings->setValue("RecentConfs/file2","undefined");
    if (!QFileInfo(settings->value("RecentConfs/file3").toString()).exists())
    settings->setValue("RecentConfs/file3","undefined");
    if (!QFileInfo(settings->value("RecentConfs/file4").toString()).exists())
    settings->setValue("RecentConfs/file4","undefined");

    if (settings->value("RecentConfs/file1").toString() == "undefined" && settings->value("RecentConfs/file2").toString() == "undefined" && settings->value("RecentConfs/file3").toString() == "undefined" && settings->value("RecentConfs/file4").toString() == "undefined")
    {
        main_window->getActionOpenRecent()->addAction(QIcon( ":/sprites/openconf.png" ),tr("Not recent files"));
        return;
    }

    if (settings->value("RecentConfs/file1").toString() != "undefined")
    {
        QAction* pointeurAction1 = main_window->getActionOpenRecent()->addAction(QIcon( ":/sprites/openconf.png" ),settings->value("RecentConfs/file1").toString());
        connect( pointeurAction1, SIGNAL(triggered()), this, SLOT(loadRecentSettings1()));
    }
    if (settings->value("RecentConfs/file2").toString() != "undefined")
    {
        QAction* pointeurAction2 = main_window->getActionOpenRecent()->addAction(QIcon( ":/sprites/openconf.png" ),settings->value("RecentConfs/file2").toString());
        connect( pointeurAction2, SIGNAL(triggered()), this, SLOT(loadRecentSettings2()));
    }
    if (settings->value("RecentConfs/file3").toString() != "undefined")
    {
        QAction* pointeurAction3 = main_window->getActionOpenRecent()->addAction(QIcon( ":/sprites/openconf.png" ),settings->value("RecentConfs/file3").toString());
        connect( pointeurAction3, SIGNAL(triggered()), this, SLOT(loadRecentSettings3()));
    }
    if (settings->value("RecentConfs/file4").toString() != "undefined")
    {
        QAction* pointeurAction4 = main_window->getActionOpenRecent()->addAction(QIcon( ":/sprites/openconf.png" ),settings->value("RecentConfs/file4").toString());
        connect( pointeurAction4, SIGNAL(triggered()), this, SLOT(loadRecentSettings4()));
    }
}

/**
*@brief  Retourne le chemin de la dernière configuration chargée.
*@return QString - Chemin.
*/
QString IniManager::getCurrentFileLoaded()
{
    return currentFileLoaded;
}

/**
*@brief Setter du chemin de la dernière configuration chargée.
*@param newFileLoaded    Nouveau chemin.
*/
void IniManager::setCurrentFileLoaded(QString newFileLoaded)
{
    currentFileLoaded = newFileLoaded;
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void IniManager::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void IniManager::retranslate()
{
    if(!currentFileLoaded.isEmpty())
    main_window->setWindowTitle(QApplication::applicationName()+" "+QApplication::applicationVersion()+" - "+tr("Configuration file loaded")+": "+this->getCurrentFileLoaded());
}

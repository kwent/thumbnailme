/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	MainWindow.cpp
*       @class  MainWindow
*	Cette classe permet la génération  de la fenêtre principale de Thumbnail Me.
*       @attention  Qt eXTension library required - http://www.libqxt.org/
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

#include "MainWindow.h"

/**
*@brief Constructeur.
*/
MainWindow::MainWindow()
{
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);
    mpIniManager = new IniManager(this);

    this->setWindowTitle(QApplication::applicationName()+" "+QApplication::applicationVersion());
    this->setStyle(new STYLE);
    this->setAcceptDrops(true);
    this->setWindowState(Qt::WindowActive);
    this->createMenuBar();
    this->createToolBar();
    this->createDocks();
    this->createMenuConnections();
    this->retranslate();
    this->restoreWindowState();
}

/**
*@brief Destructeur.
*/
MainWindow::~MainWindow()
{
    delete fileMenu;
}

/**
*@brief Instancie les Qmenu et les QAction.
*/
void MainWindow::createMenuBar()
{
    initializeMenuItems();		// Creates all QMenu
    initializeActions();		// Creates and add all QAction to the menu
}

/**
*@brief Instancie les Qmenu.
*/
void MainWindow::initializeMenuItems()
{
    fileMenu = menuBar()->addMenu( QString() );
    editionMenu = menuBar()->addMenu( QString() );
    viewMenu = menuBar()->addMenu( QString() );
    configurationMenu = menuBar()->addMenu( QString() );
    aboutMenu = menuBar()->addMenu( QString() );

    /*Initialize Status Bar*/
    processStatusBar = new ProcessingStatusBar();
    this->setStatusBar(processStatusBar);
    this->statusBar()->hide();
}


/**
*@brief Instancie les QAction et les ajoute à leurs Qmenu respectifs.
*/

void MainWindow::initializeActions()
{
    // File menu's actions

    openMediasAction = fileMenu->addAction(QIcon( ":/sprites/openconf.png" ),QString() );
    openMediasAction->setShortcut(QKeySequence(QKeySequence::Open));

    fileMenu->addSeparator();

    openSettingsAction = fileMenu->addAction(QIcon( ":/sprites/openconf.png" ),QString() );

    openRecentSettingsAction = fileMenu->addMenu(QIcon( ":/sprites/openrecent.png" ),QString() );
    mpIniManager->loadRecentConfs();

    fileMenu->addSeparator();

    saveAction = fileMenu->addAction(QIcon( ":/sprites/save.png" ),QString() );
    saveAction->setShortcut(QKeySequence(QKeySequence::Save));

    saveUnderAction = fileMenu->addAction(QIcon( ":/sprites/save.png" ),QString() );
    saveUnderAction->setShortcut(QKeySequence(QKeySequence::SaveAs));

    fileMenu->addSeparator();

    printAction = fileMenu->addAction(QIcon( ":/sprites/print.png" ),QString() );
    printAction->setShortcut(QKeySequence(QKeySequence::Print));

    fileMenu->addSeparator();

    quitAction = fileMenu->addAction(QIcon( ":/sprites/quit.png" ),QString() );
    quitAction->setShortcut(QKeySequence(QKeySequence::Quit));

            configuration1 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"1 x 2" );
            configuration2 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"1 x 3" );
            configuration3 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"1 x 4" );
            configuration4 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"1 x 5" );
            configurationMenu->addSeparator();
            configuration5 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"2 x 2" );
            configuration6 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"2 x 3" );
            configuration7 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"2 x 4" );
            configuration8 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"2 x 5" );
            configurationMenu->addSeparator();
            configuration9  = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"3 x 2" );
            configuration10 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"3 x 3" );
            configuration11 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"3 x 4" );
            configuration12 = configurationMenu->addAction(QIcon( ":/sprites/row.png" ),"3 x 5" );
            configurationMenu->addSeparator();
            configuration13  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"2 x 1" );
            configuration14  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"3 x 1" );
            configuration15  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"4 x 1" );
            configuration16  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"5 x 1" );
            configurationMenu->addSeparator();
            configuration17  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"2 x 2" );
            configuration18  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"3 x 2" );
            configuration19  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"4 x 2" );
            configuration20  = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"5 x 2" );
            configurationMenu->addSeparator();
            configuration21 = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"2 x 3" );
            configuration22 = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"3 x 3" );
            configuration23 = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"4 x 3" );
            configuration24 = configurationMenu->addAction(QIcon( ":/sprites/columns.png" ),"5 x 3" );


    settingsAction = editionMenu->addAction(QIcon( ":/sprites/settings.png" ),QString() );
    settingsAction->setShortcut(QKeySequence(QKeySequence::Preferences));

    zoomInAction = viewMenu->addAction(QIcon( ":/sprites/zoomIn.png" ),QString() );
    zoomInAction->setShortcut(QKeySequence(QKeySequence::ZoomIn));

    zoomOutAction = viewMenu->addAction(QIcon( ":/sprites/zoomOut.png" ),QString() );
    zoomOutAction->setShortcut(QKeySequence(QKeySequence::ZoomOut));

    clearSceneAction = viewMenu->addAction(QIcon( ":/sprites/recycle-bin-full.png"),QString() );

    viewMenu->addSeparator();

    fullScreenAction = viewMenu->addAction(QString());
    fullScreenAction->setShortcut(QKeySequence(Qt::Key_F11));

    helpAction = aboutMenu->addAction(QIcon( ( ":sprites/help.png" ) ),QString() );
    helpAction->setShortcut(QKeySequence(QKeySequence::HelpContents));

    aboutThumbnailMeAction = aboutMenu->addAction(QIcon( ":/sprites/thumbnailer.png" ),QString() );
    aboutThumbnailMeAction->setShortcut(QKeySequence(Qt::Key_F2));

    aboutQtAction = aboutMenu->addAction(QIcon( ( ":/trolltech/qmessagebox/images/qtlogo-64.png" ) ),QString() );
    aboutQtAction->setShortcut(QKeySequence(Qt::Key_F3));

    aboutMenu->addSeparator();

    donateAction = aboutMenu->addAction(QIcon( ( ":/sprites/donate.png" ) ),QString() );
    donateAction->setShortcut(QKeySequence(Qt::Key_F4));

    websiteAction = aboutMenu->addAction(QIcon( ( ":/sprites/apps.png" ) ),QString() );
    websiteAction->setShortcut(QKeySequence(Qt::Key_F5));
}

/**
*@brief Création la barre d'outil de la fenêtre principale.
*/
void MainWindow::createToolBar()
{
    // Creating the ToolBar and setting its own properties
    toolBar = addToolBar( QString() );
    toolBar->setObjectName("toolBar");
    mpImageShackLoginWidget = new ImageShackLoginWidget(this);

    // Adding all previously created ( in MainWindow::InitializeActions() ) QAction to the ToolBar
    toolBar->addAction( openSettingsAction );
    toolBar->addAction( saveAction );
              toolBar->addSeparator();
    toolBar->addAction( settingsAction );
              toolBar->addSeparator();
    toolBar->addAction( zoomInAction );
    toolBar->addAction( zoomOutAction );
    toolBar->addAction( clearSceneAction );
    toolBar->addAction( printAction );
             toolBar->addSeparator();
    toolBar->addWidget(mpImageShackLoginWidget);
              toolBar->addSeparator();
    toolBar->addAction( quitAction );
}

/**
*@brief Création les différents docks de la fenêtre principale.
*/
void MainWindow::createDocks()
{
    mpSuccessDialog = new SuccessDialog(this);
    mpDockConf = new DockConf(this);
    mpDockStyles = new DockStyles(this);
    mpDockTimeline = new DockTimeLine(this);
    mpVerboseWindow = new VerboseWindow(this);
    mpPreviewGraphicView = new PreviewGraphicView(this,zoomInAction,zoomOutAction,clearSceneAction,printAction);
    mpThumbnailEngine = new ThumbnailEngine(this);
    mpDockInputOutput = new DockInputOutput(this,mpThumbnailEngine);
    mpSettingsWidget = new SettingsWidget(this);
    mpHelpWidget = new HelpWidget(this);

    QWidget *contentScrollWidget = new QWidget(this);
    QVBoxLayout *contentLayoutScrollWidget = new QVBoxLayout;
    contentLayoutScrollWidget->addWidget(mpDockConf);
    contentLayoutScrollWidget->addWidget(mpDockStyles);
    contentLayoutScrollWidget->addWidget(mpDockTimeline);
    contentLayoutScrollWidget->setMargin(0);
    contentScrollWidget->setLayout(contentLayoutScrollWidget);

    QScrollArea *scrollWidget = new QScrollArea(this);
    scrollWidget->setWidget(contentScrollWidget);
    scrollWidget->setStyleSheet("QScrollArea{border-radius: 10px;padding: 6px;}");

    configurationDockWidget = new QDockWidget(this);
        configurationDockWidget->setObjectName("configurationDockWidget");
        configurationDockWidget->setWidget(scrollWidget);
        configurationDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
        configurationDockWidget->setMaximumWidth(QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).width()/2);

    this->addDockWidget(Qt::LeftDockWidgetArea,   configurationDockWidget, Qt::Vertical);
    this->addDockWidget(Qt::BottomDockWidgetArea, mpDockInputOutput,       Qt::Horizontal);
    this->addDockWidget(Qt::BottomDockWidgetArea, mpVerboseWindow,         Qt::Horizontal);
    this->setCentralWidget(mpPreviewGraphicView);
}

/**
*@brief Connection des QAction avec leurs différents slots.
*/
void MainWindow::createMenuConnections()
{
    connect( openMediasAction, SIGNAL(triggered()), mpDockInputOutput, SLOT(loadList()) );
    connect( openSettingsAction, SIGNAL(triggered()), mpIniManager, SLOT(importConf()) );
    connect( openRecentSettingsAction, SIGNAL(aboutToShow()), mpIniManager, SLOT(loadRecentConfs()) );
    connect( saveAction, SIGNAL(triggered()), mpIniManager, SLOT(saveSettings()));
    connect( saveUnderAction, SIGNAL(triggered()), mpIniManager, SLOT(saveSettingsUnder()) );
    connect( settingsAction, SIGNAL(triggered()), mpSettingsWidget, SLOT(show()) );
    connect( fullScreenAction, SIGNAL(triggered()), this, SLOT(manageFullScreen ()) );
    connect( configurationMenu, SIGNAL(triggered(QAction*)), mpDockConf, SLOT(setPredefinedConfiguration(QAction*)) );
    connect( aboutThumbnailMeAction, SIGNAL(triggered()), this, SLOT(aboutThumbnailme()) );
    connect( aboutQtAction, SIGNAL(triggered()), qApp,SLOT(aboutQt()) );
    connect( helpAction, SIGNAL(triggered()), mpHelpWidget,SLOT(show()) );
    connect( donateAction, SIGNAL(triggered()), this,SLOT(donateThumbnailme()) );
    connect( websiteAction, SIGNAL(triggered()), this,SLOT(websiteThumbnailme()) );
    connect( quitAction, SIGNAL(triggered()), this, SLOT(close()) );
}

/**
*@brief Charge le fichier de configuration de la dernière session selon les paramètres de l'utilisateur.
*/
void MainWindow::loadLastConfiguration()
{ 
    if(!settings->value("Extras/neverLoadLastConfiguration").toBool())
    {      
        if(settings->value("last_path_settingload").toString() != "undefined")
        {
          if(QFile::exists(settings->value("last_path_settingload").toString()))
          {
              QSettings conf (settings->value("last_path_settingload").toString(),QSettings::IniFormat);
              mpIniManager->loadIni(&conf);
              settings->setValue("Extras/neverLoadLastConfigurationWarning",true);
          }
          else
          {
              if(settings->value("Extras/neverLoadLastConfigurationWarning").toBool())
              {
                  QMessageBox::warning(this,_WARNING_,tr("Last configuration file cannot be opened. The configuration layout will be reset."));
                  settings->setValue("Extras/neverLoadLastConfigurationWarning",false);
              }
          }
        }
    }
}

/**
*@brief Réimplémentation de dragEntere - Verifications des extensions et valide l'action si extension acceptée.
*@param *e    Evènement.
*/
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    foreach(QUrl url, e->mimeData()->urls())
    {
        if (isvalidExtension(url.toString()))
            e->acceptProposedAction();
    }
    QMainWindow::dragEnterEvent(e);
}

/**
*@brief Actions s'effectuant lors du drop - Ajout des fichiers dans le DockFile et/ou le DockInputOutput.
*@param *e    Evènement.
*/
void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (QUrl url, e->mimeData()->urls())
    {
        if (isvalidExtension(url.toString()))
        {
            e->acceptProposedAction();
            mpDockInputOutput->getListWidget()->addItem(url.toLocalFile());
        }
    }

    QMainWindow::dropEvent(e);
}

/**
*@brief  Cf. FenPrincipal.h pour voir les extensions valides.
*@param  filePath    Chemin du fichier à valider.
*@return bool - Retourne vrai si extension de filePath valide sinon faux.
*/
bool MainWindow::isvalidExtension(QString filePath)
{
    QString suffix;
    QFileInfo fileInfo(filePath);
    suffix = fileInfo.suffix();
    QStringList valid_extensions;
    valid_extensions << VALID_EXTENSIONS;
    return valid_extensions.contains(suffix,Qt::CaseInsensitive);
}

/**
*@brief Affiche le "A propos" de Thumbnail me.
*/
void MainWindow::aboutThumbnailme()
{
    About *aboutWidget = new About(this);
        centerWidget(aboutWidget);
        aboutWidget->show();
}

/**
*@brief Rend l'utilisateur sur la page de donation de thumbnail me.
*/
void MainWindow::donateThumbnailme()
{
    QDesktopServices::openUrl(QUrl(DONATION_URL, QUrl::StrictMode));
}

/**
*@brief Rend l'utilisateur sur le site web de thumbnail me.
*/
void MainWindow::websiteThumbnailme()
{
    QDesktopServices::openUrl(QUrl(WEBSITE_URL, QUrl::TolerantMode));
}

/**
*@brief  Permet d'accéder au QMenu "Ouvrir une configuration recente".
*@return QMenu* - Pointeur vers le QMenu.
*/
QMenu* MainWindow:: getActionOpenRecent()
{
    return openRecentSettingsAction;
}

/**
*@brief Redéfinition de closeEvent (QCloseEvent *e) pour demander d'enregistrer la configuration actuelle avant de quitter (si l'option "Ne jamais enregistrer la configuration actuelle avant de quitter" est désactivée).
*@param *e    Evènement.
*/
void MainWindow::closeEvent(QCloseEvent *e)
{
    if (mpIniManager->getCurrentFileLoaded().isEmpty() && !settings->value("Extras/neverAskSaveConfigOnExit").toBool())
    {
        if (QMessageBox::question(this,this->windowTitle(),tr("Would you like save current configuration before exit Thumbnail me?"),QMessageBox::Save | QMessageBox::No,QMessageBox::No) == QMessageBox::Save)
        {
            if(!mpIniManager->saveSettingsUnder().isEmpty())
                {
                    QMessageBox::information(this,_INFORMATION_,mpIniManager->getCurrentFileLoaded()+' '+tr("saved successfully"));
                    e->accept();

                    /*Suppresion des fichiers temporaires*/
                    mpThumbnailEngine->deleteTemporaryFiles();
                }
                else
                {
                    e->ignore();
                    return;
                }
        }
        e->accept();
        /*Enregistrement de l'état de la fenêtre*/
        settings->setValue("WindowState/mainWindowGeometry", saveGeometry());
        settings->setValue("WindowState/mainWindowState", saveState());
        /*Suppresion des fichiers temporaires*/
        mpThumbnailEngine->deleteTemporaryFiles();    }
    else
    {
        e->accept();
        /*Enregistrement de l'état de la fenêtre*/
        settings->setValue("WindowState/mainWindowGeometry", saveGeometry());
        settings->setValue("WindowState/mainWindowState", saveState());
        /*Suppresion des fichiers temporaires*/
        mpThumbnailEngine->deleteTemporaryFiles();    }

    QMainWindow::closeEvent(e);
}

/**
*@brief Redéfinition de keyPressEvent(QKeyEvent *e) pour sortir du mode fullscreen.
*@param *e  Evènement.
*/
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape && this->isFullScreen())
        this->showMaximized();

    QMainWindow::keyPressEvent(e);
}

/**
*@brief ChangeEvent.
*@param *e  Evenement.
*/
void MainWindow::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::LanguageChange)
        retranslate();

    QMainWindow::changeEvent(e);
}

/**
*@brief ShowEvent
*@param *e Evenement
*/
void MainWindow::showEvent(QShowEvent *e)
{
    this->loadingFinishedBoolean = true;
    if(loadingFinishedBoolean)
    {
        QTimer::singleShot(500,this , SLOT(buildFontsCacheEngine()));
        QTimer::singleShot(800,this , SLOT(loadLastConfiguration()));
    }

    QMainWindow::showEvent(e);
}

/**
*@brief Construit le cache des polices.
*/
void MainWindow::buildFontsCache()
{
    if(!QFile::exists(QDesktopServices::storageLocation(QDesktopServices::DataLocation)))
    {
        QDir folder;
        folder.mkpath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    }

    QFile file(FONTS_CACHING);
        file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file

    this->mpDockStyles->setStackedWidgetToLoadingState();
    QMap <QString,QString> mapGlobal  = exploreTTFDir(readPathsFontsValueIni(settings));
    QMap <QString,QString> mapDefault = exploreTTFDir(QStringList(DEFAULT_PATH_FONT));
    out << mapGlobal << mapDefault;

    if(mapDefault.isEmpty())
    {
        QMessageBox::warning(this,_WARNING_,DEFAULT_PATH_FONT+' '+tr("contains no truetype fonts files. Please choose another fonts folder in Settings Menu."));
        this->mpDockStyles->getInfoTextComboBox()->setnoFontDefined(true);
        this->mpDockStyles->getTimestampComboBox()->setnoFontDefined(true);
        this->mpDockStyles->stackedWidgetsToComboBox();
    }
    else
    {
        this->mpDockStyles->getInfoTextComboBox()->setMap(mapGlobal);
        this->mpDockStyles->getTimestampComboBox()->setMap(mapDefault);

        this->mpDockStyles->getInfoTextComboBox()->addFamilyItems();
        this->mpDockStyles->getTimestampComboBox()->addFamilyItems();
    }
}

/**
*@brief Construit le cache des polices.
*/
void MainWindow::buildFontsCacheEngine()
{
    if(!QFile::exists(FONTS_CACHING))
    {
        this->buildFontsCache();
        settings->setValue("Extras/FontsLastModified",QFileInfo(DEFAULT_PATH_FONT).lastModified());
    }
    else if (settings->value("Extras/FontsLastModified").toDateTime() !=  QFileInfo(DEFAULT_PATH_FONT).lastModified())
    {
        this->buildFontsCache();
        settings->setValue("Extras/FontsLastModified",QFileInfo(DEFAULT_PATH_FONT).lastModified());
    }
    else
    {
        QFile file(FONTS_CACHING);
            file.open(QIODevice::ReadOnly);
        QDataStream in(&file);    // read the data serialized from the file
        QMap <QString,QString> mapGlobal;
        QMap <QString,QString> mapDefault;
        in >> mapGlobal >> mapDefault;

        this->mpDockStyles->getInfoTextComboBox()->setMap(mapGlobal);
        this->mpDockStyles->getTimestampComboBox()->setMap(mapDefault);

        this->mpDockStyles->getInfoTextComboBox()->addFamilyItems();
        this->mpDockStyles->getTimestampComboBox()->addFamilyItems();
    }
}


/**
*@brief Restore l'état de la fenêtre de la session précédente.
*/
void MainWindow::restoreWindowState()
{
    this->restoreGeometry(settings->value("WindowState/mainWindowGeometry").toByteArray());
    this->restoreState(settings->value("WindowState/mainWindowState").toByteArray());
}

/**
*@brief Réimplémentation de QWidget::showFullScreen.
*/
void MainWindow::manageFullScreen()
{
    if(!this->isFullScreen())
        this->showFullScreen();
    else this->showMaximized();
}

/**
*@brief Fonction de traduction dynamique.
*/
void MainWindow::retranslate()
{
    //QToolBar
    toolBar->setWindowTitle( tr( "Toolbar" ) );
    //QMenu
    fileMenu->setTitle( tr( "File" ) );
    editionMenu->setTitle(tr( "Edition" ) );
    viewMenu->setTitle(tr( "View" ) );
    configurationMenu->setTitle(tr( "Predefined Configuration" ) );
    aboutMenu->setTitle( tr( "About" ) );

    //QAction
    configurationDockWidget->setWindowTitle( tr("Configuration") );
    openMediasAction->setText( tr( "Open" ) );
    openSettingsAction->setText( tr( "Import a configuration file" ) );
    openRecentSettingsAction->setTitle( tr( "Import a recent configuration file" ) );
    saveAction->setText( tr( "Save my current configuration" ) );
    saveUnderAction->setText( tr( "Save my current configuration as")+"..." );
    printAction->setText( tr( "Print" ) );
    quitAction->setText( tr( "Exit" ) );
    settingsAction->setText( tr( "Settings" ) );
    zoomInAction->setText( tr( "Zoom in" ) );
    zoomOutAction->setText( tr( "Zoom out" ) );
    clearSceneAction->setText( tr( "Clear all" ) );
    fullScreenAction->setText( tr( "Fullscreen" ) );
    helpAction->setText( tr( "Help" ) );
    aboutThumbnailMeAction->setText( tr( "About" ) );
    aboutQtAction->setText( tr( "About QT" ) );
    donateAction->setText( tr( "Donate" ) );
    websiteAction->setText( tr( "Website" ) );
}

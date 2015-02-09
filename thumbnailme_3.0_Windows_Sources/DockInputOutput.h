/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockInputOutput.h
*       @class  DockInputOutput
*	Cette classe permet la génération du dock "Entrée et sortie".
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
*
*       @changelog  25/09/2011 - Destination Folder Editable.
*******************************************************************************/

#ifndef HEADER_DOCKINPUTOUTPUT
#define HEADER_DOCKINPUTOUTPUT

#include "MainWindow.h"
#include "ThumbnailListWidget.h"
#include "ThumbnailItem.h"

#define SIMPLE  1
#define PREVIEW 2

class MainWindow;
class ThumbnailEngine;

class DockInputOutput : public QDockWidget
{
    Q_OBJECT

    public:
    explicit DockInputOutput(MainWindow *main_window, ThumbnailEngine *thumbnailEngine);
    virtual ~DockInputOutput();

    private:
    MainWindow *main_window;
    QSettings  *settings;

    QCheckBox           *sameSourceCheckBox;
    ThumbnailListWidget *thumbnailListWidget;
    QLineEdit           *pathOutput;
    QPushButton         *loadButton;
    QPushButton         *resetListButton;
    QPushButton         *runBatchButton;
    QPushButton         *deleteSelectionButton;
    QPushButton         *outputButton;
    QPushButton         *arrowUpButton;
    QPushButton         *arrowDownButton;
    QLabel              *pathOutputLabel;
    QPushButton         *previewSelectionButton;
    QWidget             *contentWidget;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public:
    ThumbnailListWidget* getListWidget();
    QStringList  getAllItemListWidget();
    QStringList  getAllItemListCanonicalPath();
    QString      getLastItemListWidget();
    QString      getPathOutput();
    void         setPathOutput(QString filePath);
    bool         isSameSourceChecked();
    void         setSameSourceChecked(bool state);

    QLinkedList<ThumbnailItem *> getThumbnailList();
    ThumbnailItem* getCurrentItem();

    private slots:
    void disablePathOutput(int state);
    void arrowsManager(QListWidgetItem *item);
    void moveItemUp();
    void moveItemDown();
    void removeItemSelection();
    void resetListWidget();
    void enableResetButton(int row);
    void enableRemoveSelectionButton();

    public slots:
    void loadList();
    void openFileDialogPathOutput();
};
#endif

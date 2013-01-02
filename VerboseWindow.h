/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	VerboseWindow.h
*       @class  VerboseWindow
*	Cette classe permet la génération du Dock "Journal" qui affiche la sortie (stdout) du processus.
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      2.0
*       @version    3.0
*       @date       2011-2012
*******************************************************************************/

#ifndef HEADER_VERBOSEWINDOW
#define HEADER_VERBOSEWINDOW

#include <QTextEdit>
#include <QPushButton>
#include <QDockWidget>

class MainWindow;

class VerboseWindow : public QDockWidget
{
    Q_OBJECT

    public:
    explicit VerboseWindow(QWidget *main_window);
    virtual ~VerboseWindow();

    private:
    QWidget       *contentWidget;
    QTextEdit     *verboseTextEdit;
    QPushButton   *clearAllButton;
    QPushButton   *copyToClipboardButton;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public:
    void setVerbose(QString string);
    void setVerbose(QStringList outputStringList);

    public slots:
    void copyToClipboard();
    void enabledButtons();
};
#endif

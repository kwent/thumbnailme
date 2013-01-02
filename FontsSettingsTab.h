/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	FontsSettingsTab.h
*       @class  FontsSettingsTab
*	Cette classe permet d'ajouter ou de supprimer des chemins de dossier contenant des polices.
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

#ifndef HEADER_FONTSSETTINGSTAB
#define HEADER_FONTSSETTINGSTAB

#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>

class FontsSettingsTab : public QWidget
{
    Q_OBJECT

    public:
    explicit FontsSettingsTab();
    virtual ~FontsSettingsTab();
    void     initializeWidget();

    private:
    QSettings   *settings;

    QListWidget *fontPathListWidget;
    QPushButton *addPathFontButton;
    QPushButton *removePathFontButton;

    private:
    void        retranslate();

    protected:
    bool eventFilter(QObject *o, QEvent *e);
    void changeEvent(QEvent* event);

    public:
    bool                   containsTTF(QString folderPath);
    int                    countTTF(QStringList foldersPath);
    QListWidget            *getFontPathListWidget();

    private slots:
    void enableRemoveSelectionButton();
    void removeSelectedItemsListWidget();
    void setPathFontsOutput();
    virtual void reject();
};

#endif // HEADER_FONTSSETTINGSTAB

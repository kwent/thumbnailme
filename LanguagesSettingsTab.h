/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	LanguagesSettingsTab.h
*       @class  LanguagesSettingsTab
*	Cette classe permet de changer la langue de Thumbnail Me.
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
*
*	@changelog  08/14/2011 - Add Dutch Language.
*******************************************************************************/

#ifndef HEADER_LANGUAGESSETTINGSTAB
#define HEADER_LANGUAGESSETTINGSTAB

#include <QtGui>
#include <QRadioButton>
#include <QGroupBox>

class LanguagesSettingsTab : public QWidget
{
    Q_OBJECT

    public:
    explicit LanguagesSettingsTab();
    virtual ~LanguagesSettingsTab();
    void     initializeWidget();

    private:
    QSettings    *settings;

    QGroupBox    *languagesTabGroupBox;
    QRadioButton *radioFrench;
    QRadioButton *radioEnglish;
    QRadioButton *radioSpanish;
    QRadioButton *radioGerman;
    QRadioButton *radioDutch;
    QRadioButton *radioItalian;
    QRadioButton *radioCzech;
    QRadioButton *radioHungarian;
    QRadioButton *radioCroatian;
    QRadioButton *radioPortugese;
    QRadioButton *radioChinese;
    QRadioButton *radioRussian;
    QRadioButton *radioVietnamese;
    QRadioButton *radioTurkish;
    QRadioButton *radioSwedish;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public:
    QString getLanguageChecked();

    private slots:
    virtual void reject();
};

#endif // HEADER_LANGUAGESSETTINGSTAB

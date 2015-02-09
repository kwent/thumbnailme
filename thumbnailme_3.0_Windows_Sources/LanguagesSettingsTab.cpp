/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	LanguagesSettingsTab.cpp
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
*	@changelog  09/24/2011 - Add Italian & Czech Language.
*******************************************************************************/

#include "LanguagesSettingsTab.h"

/**
*@brief Constructeur.
*/
LanguagesSettingsTab::LanguagesSettingsTab()
{
    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    QLabel *pixmapLabelEnglish = new QLabel(this);
        pixmapLabelEnglish->setPixmap(QPixmap(":/sprites/english.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelFrench = new QLabel(this);
        pixmapLabelFrench->setPixmap(QPixmap(":/sprites/french.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelSpanish = new QLabel(this);
        pixmapLabelSpanish->setPixmap(QPixmap(":/sprites/spanish.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelGerman = new QLabel(this);
        pixmapLabelGerman->setPixmap(QPixmap(":/sprites/deutsch.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelDutch = new QLabel(this);
        pixmapLabelDutch->setPixmap(QPixmap(":/sprites/dutch.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelItalian = new QLabel(this);
        pixmapLabelItalian->setPixmap(QPixmap(":/sprites/italian.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelCzech = new QLabel(this);
        pixmapLabelCzech->setPixmap(QPixmap(":/sprites/czech.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelHungarian = new QLabel(this);
        pixmapLabelHungarian->setPixmap(QPixmap(":/sprites/hungarian.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelCroatian = new QLabel(this);
        pixmapLabelCroatian->setPixmap(QPixmap(":/sprites/croatian.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelPortugese = new QLabel(this);
        pixmapLabelPortugese->setPixmap(QPixmap(":/sprites/portugese.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelChinese = new QLabel(this);
        pixmapLabelChinese->setPixmap(QPixmap(":/sprites/chinese.png").scaledToHeight(48,Qt::SmoothTransformation));
    QLabel *pixmapLabelRussian = new QLabel(this);
    pixmapLabelRussian->setPixmap(QPixmap(":/sprites/russian.png").scaledToHeight(48,Qt::SmoothTransformation));


    radioEnglish   = new QRadioButton(this);
    radioFrench    = new QRadioButton(this);
    radioSpanish   = new QRadioButton(this);
    radioGerman    = new QRadioButton(this);
    radioDutch     = new QRadioButton(this);
    radioItalian   = new QRadioButton(this);
    radioCzech     = new QRadioButton(this);
    radioHungarian = new QRadioButton(this);
    radioCroatian  = new QRadioButton(this);
    radioPortugese = new QRadioButton(this);
    radioChinese   = new QRadioButton(this);
    radioRussian   = new QRadioButton(this);

    QGridLayout *languagesLayoutRight = new QGridLayout(this);

    languagesLayoutRight->addWidget(radioEnglish,0,1);
    languagesLayoutRight->addWidget(pixmapLabelEnglish,0,2);
    languagesLayoutRight->addWidget(radioFrench,0,3);
    languagesLayoutRight->addWidget(pixmapLabelFrench,0,4);
    languagesLayoutRight->addWidget(radioSpanish,1,1);
    languagesLayoutRight->addWidget(pixmapLabelSpanish,1,2);
    languagesLayoutRight->addWidget(radioGerman,1,3);
    languagesLayoutRight->addWidget(pixmapLabelGerman,1,4);
    languagesLayoutRight->addWidget(radioDutch,2,1);
    languagesLayoutRight->addWidget(pixmapLabelDutch,2,2);
    languagesLayoutRight->addWidget(radioItalian,2,3);
    languagesLayoutRight->addWidget(pixmapLabelItalian,2,4);
    languagesLayoutRight->addWidget(radioCzech,3,1);
    languagesLayoutRight->addWidget(pixmapLabelCzech,3,2);
    languagesLayoutRight->addWidget(radioHungarian,3,3);
    languagesLayoutRight->addWidget(pixmapLabelHungarian,3,4);
    languagesLayoutRight->addWidget(radioCroatian,4,1);
    languagesLayoutRight->addWidget(pixmapLabelCroatian,4,2);
    languagesLayoutRight->addWidget(radioPortugese,4,3);
    languagesLayoutRight->addWidget(pixmapLabelPortugese,4,4);
    languagesLayoutRight->addWidget(radioChinese,5,1);
    languagesLayoutRight->addWidget(pixmapLabelChinese,5,2);
    languagesLayoutRight->addWidget(radioRussian,5,3);
    languagesLayoutRight->addWidget(pixmapLabelRussian,5,4);
    languagesLayoutRight->setSpacing(5);

    languagesTabGroupBox = new QGroupBox(this);
        languagesTabGroupBox->setLayout(languagesLayoutRight);

    QLabel *translationLabel = new QLabel(this);

        translationLabel->setText(
         "<p>"+tr("Can't see your language in this list?","Don't translate this sentence")+"</p></br>"+
         "<p>"+tr("Help us to translate","Don't translate this sentence")+" "+APPLICATION_NAME+"."+"</p></br>"+
         "<p>"+tr("More information at","Don't translate this sentence")+" <a href='"+TRANSLATION_HELP_URL+"'>"+TRANSLATION_HELP_URL+"</a>.</p>"
          );

        translationLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse | Qt::LinksAccessibleByKeyboard);
        translationLabel->setOpenExternalLinks(true);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
        layoutPrincipal->addWidget(languagesTabGroupBox);
        layoutPrincipal->addWidget(translationLabel);

    this->initializeWidget();
    this->setLayout(layoutPrincipal);
    this->retranslate();
}

/**
*@brief Destructeur.
*/
LanguagesSettingsTab::~LanguagesSettingsTab()
{
}

/**
*@brief Initialisation des paramètres du widget.
*/
void LanguagesSettingsTab::initializeWidget()
{
    /*On coche la radio associé à la langue lue dans le fichier de configuration*/
    if (settings->value("Langs/lang") == "en")
        radioEnglish->setChecked(true);
    else if (settings->value("Langs/lang") == "fr")
        radioFrench->setChecked(true);
    else if (settings->value("Langs/lang") == "de")
        radioGerman->setChecked(true);
    else if (settings->value("Langs/lang") == "es")
        radioSpanish->setChecked(true);
    else if (settings->value("Langs/lang") == "nl")
        radioDutch->setChecked(true);
    else if (settings->value("Langs/lang") == "it")
        radioItalian->setChecked(true);
    else if (settings->value("Langs/lang") == "cz")
        radioCzech->setChecked(true);
    else if (settings->value("Langs/lang") == "hu")
        radioHungarian->setChecked(true);
    else if (settings->value("Langs/lang") == "hr")
        radioCroatian->setChecked(true);
    else if (settings->value("Langs/lang") == "pt")
        radioPortugese->setChecked(true);
    else if (settings->value("Langs/lang") == "cn")
        radioChinese->setChecked(true);
    else if (settings->value("Langs/lang") == "ru")
        radioRussian->setChecked(true);
    else radioEnglish->setChecked(true);
}


/**
*@brief  Retourne la langue cochée.
*@return Langue ("en" ou "fr" ou "de" ou "es").
*/
QString LanguagesSettingsTab::getLanguageChecked()
{
    if (radioEnglish->isChecked())
        return "en";
    else if (radioFrench->isChecked())
        return "fr";
    else if (radioGerman->isChecked())
        return "de";
    else if (radioSpanish->isChecked())
        return "es";
    else if (radioDutch->isChecked())
        return "nl";
    else if (radioItalian->isChecked())
        return "it";
    else if (radioCzech->isChecked())
        return "cz";
    else if (radioHungarian->isChecked())
        return "hu";
    else if (radioCroatian->isChecked())
        return "hr";
    else if (radioPortugese->isChecked())
        return "pt";
    else if (radioChinese->isChecked())
        return "cn";
    else if (radioRussian->isChecked())
        return "ru";
    else return "en";
}

/**
*@brief  Fonction annulation - Réaffecte les paramètres d'origine.
*/
void LanguagesSettingsTab::reject()
{
    this->initializeWidget();
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void LanguagesSettingsTab::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void LanguagesSettingsTab::retranslate()
{
    languagesTabGroupBox->setTitle( tr("Select a language") );
    radioEnglish->setText( tr("English") );
    radioFrench->setText( tr("French") );
    radioSpanish->setText( tr("Spanish") );
    radioGerman->setText( tr("German") );
    radioDutch->setText( tr("Dutch") );
    radioItalian->setText( tr("Italian") );
    radioCzech->setText( tr("Czech") );
    radioHungarian->setText( tr("Hungarian") );
    radioCroatian->setText( tr("Croatian") );
    radioPortugese->setText( tr("Portuguese") );
    radioChinese->setText( tr("Chinese") );
    radioRussian->setText( tr("Russian") );
}

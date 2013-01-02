/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	GeneralSettingsTab.cpp
*       @class  GeneralSettingsTab
*	Cette classe permet de configurer des paramètres généraux sur Thumbnail Me.
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

#include "GeneralSettingsTab.h"
#include "IniManager.h"
#include <QGridLayout>
#include "defines.h"

/**
*@brief Constructeur.
*/
GeneralSettingsTab::GeneralSettingsTab()
{

    settings = new QSettings(QSettings::IniFormat,DEFAULT_PATH_INI,APPLICATION_NAME,DEFAULT_FILE_INI,this);

    //NeverAskSaveConfigOnExit
    neverAskSaveConfigOnExit = new QCheckBox(this);

    //neverLoadLastConfiguration
    neverLoadLastConfiguration = new QCheckBox(this);

    /*Background Color PreviewGraphicView Initialisation*/
    backgroundColorPreviewGraphicViewLabel = new QLabel(this);

    backgroundColorPicker = new QtColorPicker(this);
        backgroundColorPicker->setStandardColors();

    /*Output Suffix Initialisation*/
    outputSuffixLineEdit = new QLineEdit(this);
    outputSuffixCheckBox = new QCheckBox(this);

    /*OpenGl Initialisation*/
    activeOpenGlGraphicViewCheckBox = new QCheckBox(tr("Activate openGL to preview thumbnails"));

    /*Animate Pixmap checkbox*/
    animatedPixmapCheckBox = new QCheckBox(tr("Animate pixmap while rendering"));

    //Mise en place des layout
    generalGroupBox = new QGroupBox(this);

    QGridLayout *generalGroupBoxLayout = new QGridLayout(this);
        generalGroupBoxLayout->addWidget(neverAskSaveConfigOnExit,0,0,1,3);
        generalGroupBoxLayout->addWidget(neverLoadLastConfiguration,1,0,1,3);
        generalGroupBoxLayout->addWidget(outputSuffixCheckBox,2,0);
        generalGroupBoxLayout->addWidget(outputSuffixLineEdit,2,1);
        generalGroupBoxLayout->addWidget(animatedPixmapCheckBox,3,0,1,2);
        generalGroupBoxLayout->addWidget(activeOpenGlGraphicViewCheckBox,4,0,1,2);
        generalGroupBoxLayout->addWidget(backgroundColorPreviewGraphicViewLabel,5,0);
        generalGroupBoxLayout->addWidget(backgroundColorPicker,5,1,1,2);
        generalGroupBox->setLayout(generalGroupBoxLayout);

   QHBoxLayout *layoutPrincipal = new QHBoxLayout(this);
        layoutPrincipal->addWidget(generalGroupBox);

    this->initializeWidget();
    this->setLayout(layoutPrincipal);
    this->retranslate();

    /*Connections*/
    connect(outputSuffixCheckBox, SIGNAL(clicked(bool)), outputSuffixLineEdit, SLOT(setEnabled(bool)));
}

/**
*@brief Destructeur.
*/
GeneralSettingsTab::~GeneralSettingsTab()
{
}

/**
*@brief Initialisation des paramètres du widget.
*/
void GeneralSettingsTab::initializeWidget()
{
    //NeverAskSaveConfigOnExit Initialisation
    if (settings->value("Extras/neverAskSaveConfigOnExit").isNull())
        settings->setValue("Extras/neverAskSaveConfigOnExit","false");

    if (settings->value("Extras/neverAskSaveConfigOnExit").toBool())
         neverAskSaveConfigOnExit->setCheckState(Qt::Checked);
    else neverAskSaveConfigOnExit->setCheckState(Qt::Unchecked);

    //NeverLoadLastConfiguration Initialisation
    if (settings->value("Extras/neverLoadLastConfiguration").isNull())
        settings->setValue("Extras/neverLoadLastConfiguration","false");

    if (settings->value("Extras/neverLoadLastConfiguration").toBool())
         neverLoadLastConfiguration->setCheckState(Qt::Checked);
    else neverLoadLastConfiguration->setCheckState(Qt::Unchecked);

    //OutputSuffix Initialisation
	if (!settings->value("Extras/outputSuffix").toString().isEmpty())
    {
            outputSuffixCheckBox->setChecked(true);
            outputSuffixLineEdit->setEnabled(true);
            outputSuffixLineEdit->setText(settings->value("Extras/outputSuffix").toString());
    }
    else
    {
            outputSuffixLineEdit->setEnabled(false);
    }

    //Animated Pixmap Initialisation
    if (settings->value("Extras/animatedPixmap").isNull())
        settings->setValue("Extras/animatedPixmap","true");

    if (settings->value("Extras/animatedPixmap").toBool())
         animatedPixmapCheckBox->setCheckState(Qt::Checked);
    else animatedPixmapCheckBox->setCheckState(Qt::Unchecked);

    //ActiveOpengGl Initialisation
    if (settings->value("Extras/activeOpenGl").isNull())
        settings->setValue("Extras/activeOpenGl","true");

    if (settings->value("Extras/activeOpenGl").toBool())
         activeOpenGlGraphicViewCheckBox->setCheckState(Qt::Checked);
    else activeOpenGlGraphicViewCheckBox->setCheckState(Qt::Unchecked);

    //BackgroundColorPreviewWindow Initialisation
    if (settings->value("Extras/backgroundColorPreviewWindow").isNull())
            backgroundColorPicker->setCurrentColor(Qt::lightGray);
    else backgroundColorPicker->setCurrentColor("#"+settings->value("Extras/backgroundColorPreviewWindow").toString());

}

/**
*@brief  Retourne vrai si la checkbox "neverAskSaveConfigOnExit" est coché sinon faux.
*@return bool - Vrai ou faux.
*/
bool GeneralSettingsTab::isNeverAskSaveConfigOnExitChecked()
{
    return neverAskSaveConfigOnExit->isChecked();
}

/**
*@brief  Retourne vrai si la checkbox "neverLoadLastConfiguration" est coché sinon faux.
*@return bool - Vrai ou faux.
*/
bool GeneralSettingsTab::isNeverLoadLastConfigurationChecked()
{
    return neverLoadLastConfiguration->isChecked();
}

/**
*@brief  Retourne vrai si la checkbox "outputSuffixCheckBox" est coché sinon faux.
*@return bool - Vrai ou faux.
*/
bool GeneralSettingsTab::isOutputSuffixCheckBoxChecked()
{
    return outputSuffixCheckBox->isChecked();
}

/**
*@brief  Retourne vrai si la checkbox "activeOpenGl" est coché sinon faux.
*@return bool - Vrai ou faux.
*/
bool GeneralSettingsTab::isActiveOpenGlGraphicViewCheckBoxChecked()
{
    return activeOpenGlGraphicViewCheckBox->isChecked();
}

/**
*@brief Setteur de la checkBox "Activer OpenGl".
*@param value   Vrai ou faux.
*/
void GeneralSettingsTab::setActiveOpenGlGraphicViewCheckBoxChecked(bool value)
{
    activeOpenGlGraphicViewCheckBox->setChecked(value);
}

/**
*@brief  Retourne vrai si la checkbox animatedPixmap" est coché sinon faux.
*@return bool - Vrai ou faux.
*/
bool GeneralSettingsTab::isAnimatedPixmapChecked()
{
  return animatedPixmapCheckBox->isChecked();
}

/**
*@brief  Retourne le suffixe de fichier paramétré.
*@return QString - Suffixe.
*/
QString GeneralSettingsTab::getOutputSuffixLineEdit()
{
    return outputSuffixLineEdit->text();
}

/**
*@brief  Retourne la couleur de "Arrière plan de la fenêtre de prévisualisation".
*@return QColor - Couleur.
*/
QColor GeneralSettingsTab::getColorBackgroundPreviewGraphicView()
{
    return backgroundColorPicker->currentColor();
}

/**
*@brief  Fonction annulation - Réaffecte les paramètres d'origine.
*/
void GeneralSettingsTab::reject()
{
    this->initializeWidget();
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void GeneralSettingsTab::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void GeneralSettingsTab::retranslate()
{
    generalGroupBox->setTitle( tr("General Settings") );
    neverAskSaveConfigOnExit->setText( tr("Never ask me to save my configuration on exit") );
    neverLoadLastConfiguration->setText( tr("Don't load the last configuration on startup") );
    backgroundColorPreviewGraphicViewLabel->setText( tr("Background color of preview window") + " : " );
    outputSuffixCheckBox->setText( tr("Output suffix:") );
    activeOpenGlGraphicViewCheckBox->setText( tr("Activate openGL to preview thumbnails") );
    animatedPixmapCheckBox->setText( tr("Animate pixmap while rendering") );
}

/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockStyles.cpp
*       @class  DockStyles
*	Cette classe permet la génération du dock qui met en place les styles à appliquer à la vignette.
*       @attention  QtColorPicker required - http://qt.nokia.com/products/appdev/add-on-products/catalog/4/Widgets/qtcolorpicker/
*
*	@author		Quentin Rousseau\n
*	@note   	Copyright (C) 2011-2012 Quentin Rousseau\n
*                       License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*                       Site web: www.thumbnailme.com\n
*                       Email: quentin.rousseau@thumbnailme.com
*
*       @since      2.0
*	@version    3.0
*       @date       2011-2012
*******************************************************************************/

#include "DockStyles.h"
#include "MainWindow.h"
#include "FontMapComboBox.h"
#include "QtHelper.h"
#include "Qtcolorpicker/qtcolorpicker.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QStackedWidget>

/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/

DockStyles::DockStyles(QWidget *main_window) : QFrame(main_window)
{
    this->setFrameStyle(QFrame::StyledPanel);
    this->setStyleSheet("DockStyles{border-style: solid;border-width: 1px;border-radius: 10px;border-color: grey;padding: 6px;}");

    titleWidgetLabel = new QLabel(this);

    QGridLayout *stylesLayout = new QGridLayout;
    titleLineEdit = new QLineEdit(this);
    titleLineEdit->setCursorPosition(0);

    infoTextCheckBox = new QCheckBox( this );
    infoTextCheckBox->setChecked(true);
    timestampCheckBox = new QCheckBox( this );
    timestampCheckBox->setChecked(true);

    fontInfoTextComboBox  = new FontMapComboBox(this);
    fontTimestampComboBox = new FontMapComboBox(this);

    QMovie *loadingMovie = new QMovie(":/sprites/refresh_fonts.gif");
        loadingMovie->start();

    loadingFontsLabel1 = new QLabel(this);
    loadingFontsLabel2 = new QLabel(this);

    QLabel *loadingFontsMovie1 = new QLabel(this);
        loadingFontsMovie1->setMovie(loadingMovie);

    QLabel *loadingFontsMovie2 = new QLabel(this);
        loadingFontsMovie2->setMovie(loadingMovie);

    QWidget *loadingFontsWidget1 = new QWidget(this);
    QWidget *loadingFontsWidget2 = new QWidget(this);

    QHBoxLayout *loadingFontsLayout1 = new QHBoxLayout;
        loadingFontsLayout1->addWidget(loadingFontsMovie1);
        loadingFontsLayout1->addWidget(loadingFontsLabel1, Qt::AlignLeft);
        loadingFontsLayout1->setContentsMargins(0,0,0,0);

    QHBoxLayout *loadingFontsLayout2 = new QHBoxLayout;
        loadingFontsLayout2->addWidget(loadingFontsMovie2);
        loadingFontsLayout2->addWidget(loadingFontsLabel2, Qt::AlignLeft);
        loadingFontsLayout2->setContentsMargins(0,0,0,0);

    loadingFontsWidget1->setLayout(loadingFontsLayout1);
    loadingFontsWidget2->setLayout(loadingFontsLayout2);

    fontInfoTextStackedWidget = new QStackedWidget(this);
        fontInfoTextStackedWidget->addWidget(fontInfoTextComboBox);
        fontInfoTextStackedWidget->addWidget(loadingFontsWidget1);

    fontTimestampStackedWidget = new QStackedWidget(this);
        fontTimestampStackedWidget->addWidget(fontTimestampComboBox);
        fontTimestampStackedWidget->addWidget(loadingFontsWidget2);

    infoTextSizeSpinBox = new QSpinBox(this);
    infoTextSizeSpinBox->setRange(6,72);
    infoTextSizeSpinBox->setValue(12);

    timestampSizeSpinBox = new QSpinBox(this);
    timestampSizeSpinBox->setRange(6,72);
    timestampSizeSpinBox->setValue(10);

    infoTextLocationComboBox = new QComboBox(this);
    infoTextLocationComboBox->addItems(location);
    infoTextLocationComboBox->setCurrentIndex(3);
    timestampLocationComboBox = new QComboBox(this);
    timestampLocationComboBox->addItems(location);
    timestampLocationComboBox->setCurrentIndex(1);

    titleLabel= new QLabel( this );
        titleLabel->setAlignment(Qt::AlignCenter);
    backgroundColorLabel= new QLabel( this );
        backgroundColorLabel->setAlignment(Qt::AlignCenter);
    shadowColorLabel= new QLabel( this );
        shadowColorLabel->setAlignment(Qt::AlignCenter);

    backgroundColorpicker = new QtColorPicker(this);
        backgroundColorpicker->setStandardColors();
        backgroundColorpicker->setCurrentColor(QColor(Qt::black));
    infoTextColorpicker   = new QtColorPicker(this);
        infoTextColorpicker->setStandardColors();
        infoTextColorpicker->setCurrentColor(QColor(Qt::white));
    timeStampColorpicker  = new QtColorPicker(this);
        timeStampColorpicker->setStandardColors();
        timeStampColorpicker->setCurrentColor(QColor(Qt::white));
    shadowColorpicker     = new QtColorPicker(this);
        shadowColorpicker->setStandardColors();
        shadowColorpicker->setCurrentColor(QColor(Qt::black));

    stylesLayout->addWidget(titleWidgetLabel,0,0,1,4,Qt::AlignCenter);

    stylesLayout->addWidget(QtHelper::addHSeparator(),1,0,1,4);

    stylesLayout->addWidget(titleLabel,2,0);

    stylesLayout->addWidget(titleLineEdit,2,1);

    stylesLayout->addWidget(backgroundColorLabel,3,0);

    stylesLayout->addWidget(backgroundColorpicker,3,1);

    stylesLayout->addWidget(QtHelper::addHSeparator(),4,0,1,2);

    stylesLayout->addWidget(infoTextCheckBox,5,0);

    stylesLayout->addWidget(fontInfoTextStackedWidget,6,0);
    stylesLayout->addWidget(infoTextSizeSpinBox,6,1);

    stylesLayout->addWidget(infoTextLocationComboBox,7,0);
    stylesLayout->addWidget(infoTextColorpicker,7,1);

    stylesLayout->addWidget(QtHelper::addHSeparator(),8,0,1,2);

    stylesLayout->addWidget(timestampCheckBox,9,0);

    stylesLayout->addWidget(fontTimestampStackedWidget,10,0);

    stylesLayout->addWidget(timestampSizeSpinBox,10,1);

    stylesLayout->addWidget(timestampLocationComboBox,11,0);
    stylesLayout->addWidget(timeStampColorpicker,11,1);

    stylesLayout->addWidget(shadowColorLabel,12,0);
    stylesLayout->addWidget(shadowColorpicker,12,1);

    this->setLayout(stylesLayout);
    this->retranslate();

    /*Connections*/
    connect(infoTextCheckBox,      SIGNAL(stateChanged(int)),  this, SLOT(disabledInfoTextSection(int)));
    connect(timestampCheckBox,     SIGNAL(stateChanged(int)),  this, SLOT(disabledTimeStampSection(int)));
    connect(fontInfoTextComboBox,  SIGNAL(loadFontsFinished()),this, SLOT(stackedWidgetsToComboBox()));
}

/**
*@brief Destructeur.
*/
DockStyles::~DockStyles()
{
}

/**
*@brief  Retourne la position des détails techniques.
*@return QString - Index de la position séléctionnée.
*/
int DockStyles::getInfoTextLocation()
{
    return infoTextLocationComboBox->currentIndex()+1;
}

/**
*@brief  Retourne la position du timestamp.
*@return QString - Index de la position séléctionnée.
*/
int DockStyles::getTimeStampLocation()
{
    return timestampLocationComboBox->currentIndex()+1;
}

/**
*@brief  Retourne le titre additionnel.
*@return QString - Titre additionnel.
*/
QString DockStyles::getTitleEdit()
{
    return titleLineEdit->displayText();
}

/**
*@brief  Retourne un QColor de "Couleur d'arrière-plan".
*@return QColor - Couleur.
*/
QColor DockStyles::getColorBackground()
{
    return backgroundColorpicker->currentColor();
}

/**
*@brief  Retourne un QColor de "Détails techniques".
*@return QColor - Couleur.
*/
QColor DockStyles::getColorInfoText()
{
    return infoTextColorpicker->currentColor();
}

/**
*@brief  Retourne un QColor de "Pas".
*@return QColor - Couleur.
*/
QColor DockStyles::getColorTimeStamp()
{
    return timeStampColorpicker->currentColor();
}

/**
*@brief  Retourne un QColor de "Couleur d'ombre".
*@return QColor - Couleur.
*/
QColor DockStyles::getColorShadow()
{

    return shadowColorpicker->currentColor();
}

/**
*@brief  Retourne le nom de la police sélectionné pour "Détails techniques".
*@param  type   0 = AbsoluthPath | 1 = FamilyName | 2 = FileName.
*@return QString - Nom de la police séléctionné (TrueType Font).
*/
QString DockStyles::getFontInfoText(int type)
{
    switch(type)
    {
    case 0:
        return fontInfoTextComboBox->currentFontPath(); break;
    case 1:
        return fontInfoTextComboBox->currentText(); break;
    case 2:
        return fontTimestampComboBox->currentFontFileName(); break;
    default:
        return QString();
    }
}

/**
*@brief  Retourne le nom de la police sélectionné pour "Pas".
*@param  type   0 = AbsoluthPath | 1 = FamilyName | 2 = FileName.
*@return QString - Nom de la police séléctionné (TrueType Font).
*/
QString DockStyles::getFontTimeStamp(int type)
{
    switch(type)
    {
    case 0:
        return fontTimestampComboBox->currentFontPath(); break;
    case 1:
        return fontTimestampComboBox->currentText(); break;
    case 2:
        return fontTimestampComboBox->currentFontFileName(); break;
    default:
        return QString();
    }
}

/**
*@brief  Retourne la taille de la police sélectionnée pour "Détails techniques".
*@return QString - Taille de la police séléctionnée. Range: [6-72].
*/
double DockStyles::getSizeInfoText()
{
    return (double) infoTextSizeSpinBox->value();
}

/**
*@brief  Retourne la taille de la police sélectionnée pour "Pas".
*@return QString - Taille de la police séléctionnée. Range: [6-72].
*/
double DockStyles::getSizeTimeStamp()
{
    return (double) timestampSizeSpinBox->value();
}

/**
@brief  Retourne vrai si la checkbox "Détails techniques" est cochée sinon faux.
@return bool - Vrai ou faux.
*/
bool DockStyles::isInfoTextChecked()
{
    return infoTextCheckBox->isChecked();
}

/**
*@brief  Retourne vrai si la checkbox "Pas" est cochée sinon faux.
*@return bool - Vrai ou faux.
*/
bool DockStyles::isTimeStampChecked()
{
    return timestampCheckBox->isChecked();
}

/**
*@brief  Retourne un pointeur vers la QComboBox "Détails techniques" qui contient les polices.
*@return FontMapComboBox* - Pointeur.
*/
FontMapComboBox* DockStyles::getInfoTextComboBox()
{
    return fontInfoTextComboBox;
}

/**
*@brief  Retourne un pointeur vers la QComboBox "Pas" qui contient les polices.
*@return FontMapComboBox* - Pointeur.
*/
FontMapComboBox* DockStyles::getTimestampComboBox()
{
    return fontTimestampComboBox;
}

/**
*@brief Place l'index courant de la QComboBox à index - Change la position de "Détails techniques".
*@param index    Nouvel index.
*/
void DockStyles::setInfoTextLocation(int index)
{
    infoTextLocationComboBox->setCurrentIndex(index -1);
}

/**
*@brief Place l'index courant de la QComboBox à index - Change la position de "Pas".
*@param index    Nouvel index.
*/
void DockStyles::setTimeStampLocation(int index)
{
    timestampLocationComboBox->setCurrentIndex(index -1);
}

/**
*@brief Change le QLineEdit "Titre additionnel".
*@param title    Nouveau titre.
*/
void DockStyles::setTitleEdit(QString title)
{
    titleLineEdit->setText(title);
    titleLineEdit->setCursorPosition(0);
}

/**
*@brief Vrai: Coche la QCheckBox "Détails techniques".
*@param check    Vrai ou faux.
*/
void DockStyles::setCheckedInfoText(bool check)
{
    infoTextCheckBox->setChecked(check);
}

/**
*@brief Vrai: Coche la QCheckBox "Pas".
*@param check    Vrai ou faux.
*/
void DockStyles::setCheckedTimeStamp(bool check)
{
    timestampCheckBox->setChecked(check);
}

/**
*@brief Setter de la taille de la police pour les "Détails techniques".
*@param size    Nouvelle taille.
*/
void DockStyles::setSizeInfoText(int size)
{
    infoTextSizeSpinBox->setValue(size);
}

/**
*@brief Setter de la taille de la police pour "Pas".
*@param size    Nouvelle taille.
*/
void DockStyles::setSizeTimeStamp(int size)
{
    timestampSizeSpinBox->setValue(size);
}

/**
*@brief Setter de police pour le comboBox "Détails techniques".
*@param font    Nom de la police.
*/
void DockStyles::setFontInfoText(QString font)
{
    int index = fontInfoTextComboBox->findText(font,Qt::MatchExactly);
    if(index != -1)
         fontInfoTextComboBox->setCurrentIndex(index);
    else fontInfoTextComboBox->setCurrentFont(QApplication::font());
}

/**
*@brief Setter de police sur le comboBox "Pas".
*@param font    Nom de la police.
*/
void DockStyles::setFontTimeStamp(QString font)
{
    int index = fontTimestampComboBox->findText(font,Qt::MatchExactly);
    if(index != -1)
         fontTimestampComboBox->setCurrentIndex(index);
    else fontInfoTextComboBox->setCurrentFont(QApplication::font());
}

/**
*@brief Setter de couleur pour l'arrière plan de la vignette.
*@param color    Couleur.
*/
void DockStyles::setColorBackground(QColor color)
{
    backgroundColorpicker->setCurrentColor(color);
}

/**
*@brief Setter de couleur de la police concernant les "Détails techniques".
*@param color    Couleur.
*/
void DockStyles::setColorInfoText(QColor color)
{
    infoTextColorpicker->setCurrentColor(color);
}

/**
*@brief Setter de couleur de la police concernant le "Pas".
*@param color    Couleur.
*/
void DockStyles::setColorTimeStamp(QColor color)
{
    timeStampColorpicker->setCurrentColor(color);
}

/**
*@brief Setter de couleur de la police concernant la "Couleur d'ombre" du "Pas".
*@param color    Couleur.
*/
void DockStyles::setColorShadow(QColor color)
{
    shadowColorpicker->setCurrentColor(color);
}

/**
*@brief Active ou désactive la section "Détails techniques" selon l'état de la QCheckBox correspondante.
*@param state    Etat de la QCheckBox.
*/
void DockStyles::disabledInfoTextSection(int state)
{
    bool stateBis = (state == Qt::Checked) ? true : false;

    infoTextLocationComboBox->setEnabled(stateBis);
    infoTextSizeSpinBox->setEnabled(stateBis);
    fontInfoTextStackedWidget->setEnabled(stateBis);
    infoTextColorpicker->setEnabled(stateBis);
}

/**
*@brief Active ou désactive la section "Pas" selon l'état de la QCheckBox correspondante.
*@param state    Etat de la QCheckBox.
*/
void DockStyles::disabledTimeStampSection(int state)
{
    bool stateBis = (state == Qt::Checked) ? true : false;

    timestampLocationComboBox->setEnabled(stateBis);
    timestampSizeSpinBox->setEnabled(stateBis);
    fontTimestampStackedWidget->setEnabled(stateBis);
    timeStampColorpicker->setEnabled(stateBis);
    shadowColorpicker->setEnabled(stateBis);
}

/**
*@brief Affiche les QFontComboBox.
*/
void DockStyles::stackedWidgetsToComboBox()
{
    this->fontInfoTextStackedWidget->setCurrentIndex(0);
    this->fontTimestampStackedWidget->setCurrentIndex(0);
}

/**
*@brief Affiche les QFontComboBox en état de chargement.
*/
void DockStyles::setStackedWidgetToLoadingState()
{
    this->fontInfoTextStackedWidget->setCurrentIndex(1);
    this->fontTimestampStackedWidget->setCurrentIndex(1);
}

/**
*@brief Si aucune police définie -> Vrai.
*@return bool - Vrai ou faux.
*/
bool DockStyles::isNoFontDefined()
{
    if(fontInfoTextComboBox->isNoFontDefined() && fontTimestampComboBox->isNoFontDefined())
         return true;
    else return false;
}

/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void DockStyles::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void DockStyles::retranslate()
{
    this->setWindowTitle( tr( "Styles" ) );
    titleWidgetLabel->setText( "<b>" + tr( "Styles" ) + "</b>" );
    titleLineEdit->setText( tr( "Generated by Thumbnail me" ) );
    infoTextCheckBox->setText( tr( "Info Text" ) + " :" );
    timestampCheckBox->setText( tr( "Timestamp" ) + " :" );
    titleLabel->setText( tr( "Additional Title" ) + " :" );
    backgroundColorLabel->setText( tr( "Background Color" ) + " :" );
    shadowColorLabel->setText( tr( "Shadow Color" ) + " :" );
    loadingFontsLabel1->setText( tr( "Building Font Cache..." ) );
    loadingFontsLabel2->setText( tr( "Building Font Cache..." ) );

    location.clear();
    location << tr("Lower Left") << tr("Lower Right") << tr("Upper Right") << tr("Upper Left");

    infoTextLocationComboBox->clear();
    infoTextLocationComboBox->addItems(location);
    infoTextLocationComboBox->setCurrentIndex(3);
    timestampLocationComboBox->clear();
    timestampLocationComboBox->addItems(location);
    timestampLocationComboBox->setCurrentIndex(1);
}

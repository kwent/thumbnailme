/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockConf.cpp
*       @class  DockConf
*	Cette classe permet la génération du dock de configuration.
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

#include "defines.h"
#include "DockConf.h"
#include "QtHelper.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QAction>

/**
*@brief Constructeur.
*@param *main_window    Fenêtre principale de Thumbnail me.
*/

DockConf::DockConf(MainWindow *main_window) : QFrame(main_window)
{
    this->main_window = main_window;
    this->setFrameStyle(QFrame::StyledPanel);
    this->setStyleSheet("DockConf{border-style: solid;border-width: 1px;border-radius: 10px;border-color: grey;padding: 6px;}");

    columnsSpinBox = new QSpinBox(this);
        columnsSpinBox->setMinimum( 1 );

    rowsSpinBox = new QSpinBox(this);
        rowsSpinBox->setMinimum( 1 );

    widthSpinBox = new QSpinBox(this);
        widthSpinBox->setSingleStep( 4 );

    QStringList outputFormat;
        outputFormat << OUTPUT_FORMAT;

    formatFileLabel = new QLabel(this);
        formatFileLabel->setAlignment(Qt::AlignCenter);

    formatFileComboBox = new QComboBox(this);
        formatFileComboBox->addItems(outputFormat);
        formatFileComboBox->setCurrentIndex(1);

    gapSpinBox        = new QSpinBox(this);
    qualitySpinBox    = new QSpinBox(this);
    blankSkipSpinBox  = new QSpinBox(this);
    edgeDetectSpinBox = new QSpinBox(this);

    widthSpinBox->setSuffix(" px");
    gapSpinBox->setSuffix(" px");
    qualitySpinBox->setSuffix(" %");
    blankSkipSpinBox->setSuffix(" %");

    columnsSpinBox->setMaximum( 100 );
    columnsSpinBox->setValue( 4 );
    rowsSpinBox->setMaximum( 256 );
    rowsSpinBox->setValue( 4 );
    widthSpinBox->setRange( 256, 4096 );
    widthSpinBox->setValue( 1024 );
    gapSpinBox->setMaximum( 100 );
    gapSpinBox->setValue( 1 );
    qualitySpinBox->setMaximum( 100 );
    qualitySpinBox->setValue( 80 );
    blankSkipSpinBox->setMaximum( 100 );
    blankSkipSpinBox->setValue( 80 );
    edgeDetectSpinBox->setMaximum( 12 );

    QGridLayout *layoutSettings = new QGridLayout;

    titleWidgetLabel = new QLabel(this);
        titleWidgetLabel->setAlignment(Qt::AlignCenter);
    labelColumns = new QLabel( this );
        labelColumns->setAlignment(Qt::AlignCenter);
    labelRows = new QLabel( this );
        labelRows->setAlignment(Qt::AlignCenter);
    labelWidth = new QLabel( this );
        labelWidth->setAlignment(Qt::AlignCenter);
    labelGap = new QLabel( this );
        labelGap->setAlignment(Qt::AlignCenter);
    labelQuality = new QLabel( this );
        labelQuality->setAlignment(Qt::AlignCenter);
    labelBlankSkip = new QLabel( this );
        labelBlankSkip->setAlignment(Qt::AlignCenter);
    labelEdgeDetect= new QLabel( this );
        labelEdgeDetect->setAlignment(Qt::AlignCenter);

    /*Layout building*/

    layoutSettings->addWidget(titleWidgetLabel,0,0,1,4);
    layoutSettings->addWidget(QtHelper::addHSeparator(),1,0,1,4);

    layoutSettings->addWidget(labelRows,2,0);
    layoutSettings->addWidget(rowsSpinBox,2,1);

    layoutSettings->addWidget(labelColumns,2,2);
    layoutSettings->addWidget(columnsSpinBox,2,3);

    layoutSettings->addWidget(labelWidth,3,0);
    layoutSettings->addWidget(widthSpinBox,3,1);
    layoutSettings->addWidget(labelGap,3,2);
    layoutSettings->addWidget(gapSpinBox,3,3);

    layoutSettings->addWidget(QtHelper::addHSeparator(),4,0,1,4);

    layoutSettings->addWidget(formatFileLabel,5,0);
    layoutSettings->addWidget(formatFileComboBox,5,1);
    layoutSettings->addWidget(labelQuality,5,2);
    layoutSettings->addWidget(qualitySpinBox,5,3);

    layoutSettings->addWidget(labelBlankSkip,6,0);
    layoutSettings->addWidget(blankSkipSpinBox,6,1);
    layoutSettings->addWidget(labelEdgeDetect,6,2);
    layoutSettings->addWidget(edgeDetectSpinBox,6,3);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
        layoutPrincipal->addLayout(layoutSettings);

    this->setLayout(layoutPrincipal);
    this->retranslate();

    /*Connections*/
    connect(formatFileComboBox, SIGNAL(currentIndexChanged(QString)), this , SLOT(disabledQualitySpinBox(QString)));
}

/**
*@brief Destructeur.
*/
DockConf::~DockConf()
{
}

/**
*@brief  Retourne le nombre de colonnes.
*@return QString - Valeur du champ.
*/
int DockConf::getColumns()
{
    return columnsSpinBox->value();
}

/**
*@brief  Retourne le nombre de lignes.
*@return QString - Valeur du champ.
*/
int DockConf::getRows()
{
    return rowsSpinBox->value();
}

/**
*@brief  Retourne la largeur de la vignette à générer.
*@return QString - Valeur du champ.
*/
int DockConf::getWidth()
{
    return widthSpinBox->value();
}

/**
*@brief  Retourne l'espacement entre les vignettes.
*@return QString - Valeur du champ.
*/
int DockConf::getGap()
{
    return gapSpinBox->value();
}

/**
*@brief  Retourne la qualité de l'image en pourcentage.
*@return QString - Retourne la valeur du champ.
*/
int DockConf::getQuality()
{
    return qualitySpinBox->value();
}

/**
*@brief  Retourne la tolérance au blanc.
*@return QString - Valeur du champ.
*/
double DockConf::getBlankSkip()
{
    return double(blankSkipSpinBox->value())/100;
}

/**
*@brief  Retourne la détéction d'angle.
*@return QString - Valeur du champ.
*/
int DockConf::getEdgeDetect()
{
    return edgeDetectSpinBox->value();
}

/**
*@brief  Retourne le format de l'image à générer.
*@return QString - Valeur du champ.
*/
QString DockConf::getFormatFile()
{
    return formatFileComboBox->currentText();
}

/**
*@brief Setter du nombre de colonnes.
*@param columns    Nombre de colonnes.
*/
void DockConf::setColumns(int columns)
{
    columnsSpinBox->setValue(columns);
}

/**
*@brief Setter du nombre de lignes.
*@param rows    Nombre de lignes.
*/
void DockConf::setRows(int rows)
{
    rowsSpinBox->setValue(rows);
}

/**
*@brief Setter de la largeur de la vignette a générer.
*@param width    Largeur de la vignette.
*/
void DockConf::setWidth(int width)
{
    widthSpinBox->setValue(width);
}

/**
*@brief Setter de l'espacement entre les vignettes.
*@param gap    Espacement entre les vignettes.
*/
void DockConf::setGap(int gap)
{
    gapSpinBox->setValue(gap);
}

/**
*@brief Setter la qualité de l'image en pourcentage.
*@param quality    Qualité de l'image.
*/
void DockConf::setQuality(int quality)
{
    qualitySpinBox->setValue(quality);
}

/**
*@brief Setter de la tolérance au blanc.
*@param blankskip    Tolérance au blanc.
*/
void DockConf::setBlankSkip(double blankskip)
{
    int convert2int = int(blankskip*100);
    blankSkipSpinBox->setValue(convert2int);
}

/**
*@brief Setter de la détéction d'angle.
*@param edgedetect    Détection d'angle.
*/
void DockConf::setEdgeDetect(int edgedetect)
{
    edgeDetectSpinBox->setValue(edgedetect);
}

/**
*@brief Setter du format d'image.
*@param format    Format de l'image.
*/
void DockConf::setFormatFile(QString format)
{
    if (format == "bmp")
        formatFileComboBox->setCurrentIndex(0);
    else if (format == "jpeg")
        formatFileComboBox->setCurrentIndex(1);
    else if (format == "png")
        formatFileComboBox->setCurrentIndex(2);
    else if (format == "tiff")
        formatFileComboBox->setCurrentIndex(3);
    else formatFileComboBox->setCurrentIndex(2);
}

/**
*@brief Setter de la couleur d'arrière plan des SpinBoxes colonne et ligne.
*@param color    Couleur de l'arrière plan.
*/
void DockConf::setBackgroundColorSpinBoxRowsColumns(QString color)
{
    columnsSpinBox->setStyleSheet("color:white ; background-color:"+color);
    rowsSpinBox->setStyleSheet("color:white ; background-color:"+color);
}

/**
*@brief Setter de configurations prédéfinies.
*@param *actiontrigerred    Pointeur vers le QAction activé.
*/
void DockConf::setPredefinedConfiguration(QAction *actiontrigerred)
{
    QString rows,columns;

    rows = actiontrigerred->text().section(' ',0,0);
    columns = actiontrigerred->text().section(' ',-1);

    main_window->mpDockConf->setRows(rows.toInt());
    main_window->mpDockConf->setColumns(columns.toInt());

    main_window->mpDockConf->setBackgroundColorSpinBoxRowsColumns(QString("darkGreen"));
}

/**
*@brief Active ou désactive la QSpinBox définissant la qualité selon le format de fichier sélectionné.
*       Désactiver quand le format sélectionné est BMP ou TIFF.
*@param format    Format sélectionné.
*/
void DockConf::disabledQualitySpinBox(QString format)
{
    if (format == "bmp" || format == "tiff")
         qualitySpinBox->setDisabled(true);
    else qualitySpinBox->setEnabled(true);
}


/**
*@brief ChangeEvent.
*@param *event Evenement.
*/
void DockConf::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(event);
}

/**
*@brief Fonction de traduction dynamique.
*/
void DockConf::retranslate()
{
    this->setWindowTitle( tr( "Configuration" ) );
    titleWidgetLabel->setText( "<b>" + tr( "Configuration" ) + "</b>" );
    formatFileLabel->setText( tr( "Output Format" ) + " :" );
    labelColumns->setText( tr( "Columns" ) + " :" );
    labelRows->setText( tr( "Rows" ) + " :" );
    labelWidth->setText( tr( "Width" ) + " :" );
    labelGap->setText( tr( "Gap" ) + " :" );
    labelQuality->setText( tr( "Quality" ) + " :" );
    labelBlankSkip->setText( tr( "Blank skip" ) + " :" );
    labelEdgeDetect->setText(  tr( "Edge detection" ) + " :" );
}

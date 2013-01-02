/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	GeneralSettingsTab.h
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

#ifndef HEADER_GENERALSETTINGSTAB
#define HEADER_GENERALSETTINGSTAB

#include <QGroupBox>
#include <QCheckBox>
#include <QSettings>
#include <QLineEdit>
#include "Qtcolorpicker/qtcolorpicker.h"

class GeneralSettingsTab : public QWidget
{
    Q_OBJECT

    public:
    explicit GeneralSettingsTab();
    virtual ~GeneralSettingsTab();
    void     initializeWidget();

    private:
    QSettings     *settings;

    QGroupBox     *generalGroupBox;
    QCheckBox     *activeOpenGlGraphicViewCheckBox;
    QCheckBox     *animatedPixmapCheckBox;
    QLabel        *backgroundColorPreviewGraphicViewLabel;
    QtColorPicker *backgroundColorPicker;
    QCheckBox     *neverAskSaveConfigOnExit;
    QCheckBox     *neverLoadLastConfiguration;
    QCheckBox     *outputSuffixCheckBox;
    QLineEdit     *outputSuffixLineEdit;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);
    
    public:
    QColor  getColorBackgroundPreviewGraphicView();
    QString getOutputSuffixLineEdit();

    bool    isActiveOpenGlGraphicViewCheckBoxChecked();
    bool    isAnimatedPixmapChecked();
    bool    isNeverAskSaveConfigOnExitChecked();
    bool    isNeverLoadLastConfigurationChecked();
    bool    isOutputSuffixCheckBoxChecked();

    void    setActiveOpenGlGraphicViewCheckBoxChecked(bool value);

    private slots:
    virtual void reject();
};

#endif // HEADER_GENERALSETTINGSTAB

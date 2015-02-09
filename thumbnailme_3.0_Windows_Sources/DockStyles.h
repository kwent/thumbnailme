/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockStyles.h
*       @class  DockStyles
*	Cette classe permet la génération du dock qui met en place les styles à appliquer à la vignette.
*       @attention  QtColorPicker required - http://qt.nokia.com/products/appdev/add-on-products/catalog/4/Widgets/qtcolorpicker/
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

#ifndef HEADER_DOCKSTYLES
#define HEADER_DOCKSTYLES

#include "MainWindow.h"
#include "FontMapComboBox.h"
#include "qtcolorpicker.h"

class DockStyles : public QFrame
{
    Q_OBJECT

    public:
    explicit DockStyles(QWidget *main_window);
    virtual ~DockStyles();

    private:
    QLineEdit       *titleLineEdit;
    QtColorPicker   *backgroundColorpicker;
    QtColorPicker   *infoTextColorpicker;
    QtColorPicker   *timeStampColorpicker;
    QtColorPicker   *shadowColorpicker;
    QStackedWidget  *fontInfoTextStackedWidget;
    QStackedWidget  *fontTimestampStackedWidget;
    FontMapComboBox *fontInfoTextComboBox;
    FontMapComboBox *fontTimestampComboBox;
    QCheckBox       *infoTextCheckBox;
    QCheckBox       *timestampCheckBox;
    QSpinBox        *infoTextSizeSpinBox;
    QSpinBox        *timestampSizeSpinBox;
    QComboBox       *infoTextLocationComboBox;
    QComboBox       *timestampLocationComboBox;
    QLabel          *titleWidgetLabel;
    QLabel          *titleLabel;
    QLabel          *backgroundColorLabel;
    QLabel          *shadowColorLabel;
    QLabel          *loadingFontsLabel1;
    QLabel          *loadingFontsLabel2;
    QStringList     location;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    public slots:
    void disabledInfoTextSection(int state);
    void disabledTimeStampSection(int state);
    void stackedWidgetsToComboBox();

    public:
    QString         getInfoTextLocation();
    QString         getTimeStampLocation();
    QString         getTitleEdit();
    QColor          getColorBackground();
    QColor          getColorInfoText();
    QColor          getColorTimeStamp();
    QColor          getColorShadow();
    QString         getFontInfoText(int type);
    QString         getFontTimeStamp(int type);
    QString         getSizeInfoText();
    QString         getSizeTimeStamp();
    FontMapComboBox *getInfoTextComboBox();
    FontMapComboBox *getTimestampComboBox();
    bool            isInfoTextChecked();
    bool            isTimeStampChecked();
    bool            isNoFontDefined();

    void setInfoTextLocation(int index);
    void setTimeStampLocation(int index);
    void setTitleEdit(QString title);
    void setCheckedInfoText(bool check);
    void setCheckedTimeStamp(bool check);
    void setSizeInfoText(int size);
    void setSizeTimeStamp(int size);
    void setFontInfoText(QString font);
    void setFontTimeStamp(QString font);
    void setColorBackground(QColor color);
    void setColorInfoText(QColor color);
    void setColorTimeStamp(QColor color);
    void setColorShadow(QColor color);
    void setStackedWidgetToLoadingState();
};
#endif

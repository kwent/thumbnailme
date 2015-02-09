/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	DockConf.h
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

#ifndef HEADER_DOCKCONF
#define HEADER_DOCKCONF

#include "MainWindow.h"

class MainWindow;

class DockConf : public QFrame
{
    Q_OBJECT

    public:
    explicit DockConf(MainWindow *main_window);
    virtual ~DockConf();

    private:
    MainWindow    *main_window;
    QComboBox     *formatFileComboBox;
    QSpinBox      *columnsSpinBox;
    QSpinBox      *rowsSpinBox;
    QSpinBox      *widthSpinBox;
    QSpinBox      *gapSpinBox;
    QSpinBox      *qualitySpinBox;
    QSpinBox      *blankSkipSpinBox;
    QSpinBox      *edgeDetectSpinBox;

    QLabel        *titleWidgetLabel;
    QLabel        *formatFileLabel;
    QLabel        *labelColumns;
    QLabel        *labelRows;
    QLabel        *labelWidth;
    QLabel        *labelGap;
    QLabel        *labelQuality;
    QLabel        *labelBlankSkip;
    QLabel        *labelEdgeDetect;

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent* event);

    private slots:
    void disabledQualitySpinBox(QString format);

    public:
    QString getBlankSkip();
    QString getColumns();
    QString getEdgeDetect();
    QString getFormatFile();
    QString getGap();
    QString getQuality();
    QString getRows();
    QString getWidth();

    void setBackgroundColorSpinBoxRowsColumns(QString color);
    void setBlankSkip(double blankskip);
    void setColumns(int columns);
    void setEdgeDetect(int edgedetect);
    void setFormatFile(QString format);
    void setGap(int gap);
    void setQuality(int quality);
    void setRows(int rows);
    void setWidth(int width);

    public slots:
    void setPredefinedConfiguration(QAction *actiontrigerred);
};
#endif

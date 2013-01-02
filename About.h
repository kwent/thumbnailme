/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	About.h
*       @class	About
*	Cette classe génère une QFrame "A propos" de Thumbnail me.
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

#ifndef HEADER_ABOUT
#define HEADER_ABOUT

#include <QApplication>
#include <QFrame>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QKeyEvent>

class About : public QWidget
{
    Q_OBJECT

    public:
    explicit About(QWidget *parent = 0);
    virtual ~About();

    private:
    void retranslate();

    protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *e);
};

#endif // HEADER_ABOUT

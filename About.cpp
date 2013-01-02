/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	About.cpp
*       @class  About
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

#include "About.h"
#include "QtHelper.h"
#include "defines.h"

/**
*@brief Constructeur.
*/
About::About(QWidget *parent)
{
    //this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowOkButtonHint | Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowIcon(parent->windowIcon());
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->retranslate();

    QGridLayout *layout = new QGridLayout(this);

    QLabel *logoLabel = new QLabel(this);
        logoLabel->setPixmap(QPixmap(":/sprites/about.png"));

    QLabel *aboutLabel = new QLabel(this);

        aboutLabel->setText(
                            "<h2>What's "+APPLICATION_NAME+" ?</h2>"+
                            "<p>"+APPLICATION_NAME+" is a free and open source thumbnails generator built on movie thumbnailer binary.</p>"+
                            "<p>"+APPLICATION_NAME+" is coded in C++ and uses the <a href='http://qt.nokia.com/'>Qt library</a>.</p>"+
                            "<h2>Who is involved ?</h2>"+
                            "<p><b>Quentin Rousseau</b> : Developer - <a href=\"mailto:"+AUTHOR_EMAIL+"\">"+AUTHOR_EMAIL+"</a> - <a href=\"http://www.quentinrousseau.fr\">www.quentinrousseau.fr</a></p>"+
                            "<p><b>Christ Azika-Eros</b> : Linux compilation & ImageShack API Developer - <a href=\"mailto:christ@azika-eros.org\">christ@azika-eros.org</a> - <a href=\"http://azika-eros.org\">azika-eros.org</a></p>"
                            "<h2>Special thanks to :</h2></br>"+
                            "<p><b>Pierre Arnout</b> : Splashscreen logo Designer - <a href=\"mailto:arnout.pierre@gmail.com\">arnout.pierre@gmail.com</a> - <a href=\"http://artpi.lescigales.org\">http://artpi.lescigales.org</a></p>"+
                            "<p><b>Antonio José Berenguer Verdú</b> : Spanish translation - <a href=\"mailto:anbever@gmail.com\">anbever@gmail.com</a></p>"+
                            "<p><b>Samuele Pilleri</b> : Italian translation - <a href=\"mailto:sammypillo96@gmail.com\">sammypillo96@gmail.com</a></p>"+
                            "<p><b>Philippe Da Silva</b> :  Portugese translation - <a href=\"mailto:contact@philippedasilva.fr\">contact@philippedasilva.fr</a> - <a href=\"http://www.philippedasilva.fr\">www.philippedasilva.fr</a></p>"+
                            "<p><b>Qinlin Zha</b> :  Chinese translation - <a href=\"mailto:qinlin.zha@gmail.com\">qinlin.zha@gmail.com</a></p>"+
                            "<p><b>Dmitry Bochkov</b> :  Russian translation - <a href=\"mailto:translation@ukr.net\">translation@ukr.net</a></p>"+
                            "<h2>Websites :</h2><p>"+
                            "<a href='"+WEBSITE_URL+"'>"+WEBSITE_URL+"</a><br/><br/>"+
                            "<a href=\"http://moviethumbnail.sourceforge.net\">http://moviethumbnail.sourceforge.net</a> (Original Project)</p>"+
                            "<h2>License :</h2>"+
                            "<p>This work is licensed under a <a rel=\"license\" href=\"http://www.gnu.org/licenses/gpl-2.0.html\">GNU General Public License version 2 (GPLv2)</a>.</p>"
                            );

        aboutLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse | Qt::LinksAccessibleByKeyboard);
        aboutLabel->setOpenExternalLinks(true);


    QHBoxLayout *topLayout = new QHBoxLayout;
        topLayout->addStretch(1);
        topLayout->addWidget(logoLabel,Qt::AlignHCenter);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
        QDialogButtonBox *acceptButton = new QDialogButtonBox(QDialogButtonBox::Ok);
        bottomLayout->addWidget(acceptButton,Qt::AlignRight);

    layout->addLayout(topLayout,0,0,Qt::AlignHCenter);;
    layout->addWidget(aboutLabel,1,0,Qt::AlignHCenter);
    layout->addWidget(QtHelper::addHSeparator(),2,0);
    layout->addLayout(bottomLayout,3,0);

    this->setLayout(layout);

    /*Connections*/
    connect(acceptButton,SIGNAL(accepted ()),this,SLOT(close()));
}

/**
*@brief Destructeur.
*/
About::~About()
{
}

/**
*@brief ChangeEvent
*@param *e Evenement.
*/
void About::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        retranslate();
    QWidget::changeEvent(e);
}

/**
*@brief KeyPressEvent
*@param *e Evenement.
*/
void About::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
       this->close();
    QWidget::keyPressEvent(e);
}

/**
*@brief Fonction de traduction dynamique.
*/
void About::retranslate()
{
    this->setWindowTitle(tr("About"));
}

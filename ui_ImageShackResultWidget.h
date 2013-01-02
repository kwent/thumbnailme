/********************************************************************************
** Form generated from reading UI file 'ImageShackResultWidget.ui'
**
** Created: Wed 2. Jan 19:21:12 2013
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESHACKRESULTWIDGET_H
#define UI_IMAGESHACKRESULTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "copyablelineedit.h"

QT_BEGIN_NAMESPACE

class Ui_ImageShackResultWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *thumbnailPreviewLabel;
    QSpacerItem *horizontalSpacer_7;
    QLabel *count;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *prev;
    QToolButton *next;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QGridLayout *gridLayout;
    CopyableLineEdit *directLink;
    CopyableLineEdit *shortLink;
    CopyableLineEdit *hotlink;
    CopyableLineEdit *thumbnailLink;
    CopyableLineEdit *forumHotlink;
    CopyableLineEdit *forumThumbnail;
    CopyableLineEdit *forumHotlink2;
    CopyableLineEdit *forumThumbnail2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *close;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ImageShackResultWidget)
    {
        if (ImageShackResultWidget->objectName().isEmpty())
            ImageShackResultWidget->setObjectName(QStringLiteral("ImageShackResultWidget"));
        ImageShackResultWidget->resize(497, 573);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImageShackResultWidget->sizePolicy().hasHeightForWidth());
        ImageShackResultWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(ImageShackResultWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        thumbnailPreviewLabel = new QLabel(ImageShackResultWidget);
        thumbnailPreviewLabel->setObjectName(QStringLiteral("thumbnailPreviewLabel"));
        thumbnailPreviewLabel->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(thumbnailPreviewLabel->sizePolicy().hasHeightForWidth());
        thumbnailPreviewLabel->setSizePolicy(sizePolicy1);
        thumbnailPreviewLabel->setMinimumSize(QSize(150, 150));
        thumbnailPreviewLabel->setMaximumSize(QSize(150, 150));
        thumbnailPreviewLabel->setAutoFillBackground(false);
        thumbnailPreviewLabel->setFrameShape(QFrame::Box);
        thumbnailPreviewLabel->setFrameShadow(QFrame::Raised);
        thumbnailPreviewLabel->setLineWidth(2);
        thumbnailPreviewLabel->setScaledContents(true);
        thumbnailPreviewLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(thumbnailPreviewLabel, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 2, 1, 1);

        count = new QLabel(ImageShackResultWidget);
        count->setObjectName(QStringLiteral("count"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(count->sizePolicy().hasHeightForWidth());
        count->setSizePolicy(sizePolicy2);
        count->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(count, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        prev = new QToolButton(ImageShackResultWidget);
        prev->setObjectName(QStringLiteral("prev"));
        prev->setEnabled(false);
        prev->setText(QStringLiteral("<"));

        horizontalLayout_2->addWidget(prev);

        next = new QToolButton(ImageShackResultWidget);
        next->setObjectName(QStringLiteral("next"));
        next->setEnabled(false);
        next->setText(QStringLiteral(">"));

        horizontalLayout_2->addWidget(next);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        line = new QFrame(ImageShackResultWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        directLink = new CopyableLineEdit(ImageShackResultWidget);
        directLink->setObjectName(QStringLiteral("directLink"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(directLink->sizePolicy().hasHeightForWidth());
        directLink->setSizePolicy(sizePolicy3);
        directLink->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(directLink, 0, 1, 1, 1);

        shortLink = new CopyableLineEdit(ImageShackResultWidget);
        shortLink->setObjectName(QStringLiteral("shortLink"));
        sizePolicy3.setHeightForWidth(shortLink->sizePolicy().hasHeightForWidth());
        shortLink->setSizePolicy(sizePolicy3);
        shortLink->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(shortLink, 0, 0, 1, 1);

        hotlink = new CopyableLineEdit(ImageShackResultWidget);
        hotlink->setObjectName(QStringLiteral("hotlink"));
        sizePolicy3.setHeightForWidth(hotlink->sizePolicy().hasHeightForWidth());
        hotlink->setSizePolicy(sizePolicy3);
        hotlink->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(hotlink, 1, 0, 1, 1);

        thumbnailLink = new CopyableLineEdit(ImageShackResultWidget);
        thumbnailLink->setObjectName(QStringLiteral("thumbnailLink"));
        sizePolicy3.setHeightForWidth(thumbnailLink->sizePolicy().hasHeightForWidth());
        thumbnailLink->setSizePolicy(sizePolicy3);
        thumbnailLink->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(thumbnailLink, 1, 1, 1, 1);

        forumHotlink = new CopyableLineEdit(ImageShackResultWidget);
        forumHotlink->setObjectName(QStringLiteral("forumHotlink"));
        sizePolicy3.setHeightForWidth(forumHotlink->sizePolicy().hasHeightForWidth());
        forumHotlink->setSizePolicy(sizePolicy3);
        forumHotlink->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(forumHotlink, 2, 0, 1, 1);

        forumThumbnail = new CopyableLineEdit(ImageShackResultWidget);
        forumThumbnail->setObjectName(QStringLiteral("forumThumbnail"));
        sizePolicy3.setHeightForWidth(forumThumbnail->sizePolicy().hasHeightForWidth());
        forumThumbnail->setSizePolicy(sizePolicy3);
        forumThumbnail->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(forumThumbnail, 2, 1, 1, 1);

        forumHotlink2 = new CopyableLineEdit(ImageShackResultWidget);
        forumHotlink2->setObjectName(QStringLiteral("forumHotlink2"));
        sizePolicy3.setHeightForWidth(forumHotlink2->sizePolicy().hasHeightForWidth());
        forumHotlink2->setSizePolicy(sizePolicy3);
        forumHotlink2->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(forumHotlink2, 3, 0, 1, 1);

        forumThumbnail2 = new CopyableLineEdit(ImageShackResultWidget);
        forumThumbnail2->setObjectName(QStringLiteral("forumThumbnail2"));
        sizePolicy3.setHeightForWidth(forumThumbnail2->sizePolicy().hasHeightForWidth());
        forumThumbnail2->setSizePolicy(sizePolicy3);
        forumThumbnail2->setMinimumSize(QSize(0, 55));

        gridLayout->addWidget(forumThumbnail2, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        close = new QPushButton(ImageShackResultWidget);
        close->setObjectName(QStringLiteral("close"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(close->sizePolicy().hasHeightForWidth());
        close->setSizePolicy(sizePolicy4);
        close->setLayoutDirection(Qt::LeftToRight);
        close->setDefault(true);

        horizontalLayout->addWidget(close);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ImageShackResultWidget);
        QObject::connect(prev, SIGNAL(clicked()), ImageShackResultWidget, SLOT(prev()));
        QObject::connect(next, SIGNAL(clicked()), ImageShackResultWidget, SLOT(next()));
        QObject::connect(close, SIGNAL(clicked()), ImageShackResultWidget, SLOT(done()));

        QMetaObject::connectSlotsByName(ImageShackResultWidget);
    } // setupUi

    void retranslateUi(QDialog *ImageShackResultWidget)
    {
        ImageShackResultWidget->setWindowTitle(QApplication::translate("ImageShackResultWidget", "Uploaded files", 0));
        thumbnailPreviewLabel->setText(QString());
        count->setText(QApplication::translate("ImageShackResultWidget", "File 1 of 1", 0));
        close->setText(QApplication::translate("ImageShackResultWidget", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageShackResultWidget: public Ui_ImageShackResultWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESHACKRESULTWIDGET_H

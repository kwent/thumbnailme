/********************************************************************************
** Form generated from reading UI file 'ImageShackUploadWidget.ui'
**
** Created: Wed 2. Jan 19:21:12 2013
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESHACKUPLOADWIDGET_H
#define UI_IMAGESHACKUPLOADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageShackUploadWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topLayout;
    QSpacerItem *horizontalSpacer_8;
    QLabel *imageShackLabel;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *uploadModeLabel;
    QFrame *line_top;
    QHBoxLayout *uploadConfigurationLayout;
    QGridLayout *gridLayoutLeft;
    QLabel *thumbnailPreviewLabel;
    QHBoxLayout *filesUploadedLayout;
    QLabel *countFileLoaded;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_9;
    QFrame *line;
    QGridLayout *gridLayoutRight;
    QLabel *resizeLabel;
    QComboBox *resizeComboBox;
    QLabel *privacyLabel;
    QRadioButton *privacyPrivate;
    QRadioButton *privacyPublic;
    QLabel *tagsLabel;
    QLineEdit *tagsLineEdit;
    QLabel *separateCommaLabel;
    QFrame *line_2;
    QLabel *authenticationInstructionsLabel;
    QFrame *line_bottom;
    QStackedWidget *stackedUploadWidget;
    QWidget *page;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *uploadNowButton;
    QSpacerItem *horizontalSpacer_6;
    QWidget *page_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_10;
    QLabel *progressLabel;
    QLabel *label;
    QPushButton *cancelUploadButton;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_3;
    QHBoxLayout *indicatorProgressBarsLayout;
    QLabel *uploadProgressLabel;
    QProgressBar *uploadProgressBar;
    QFrame *line_4;
    QLabel *totalUploadProgressLabel_2;
    QProgressBar *totalUploadProgressBar;

    void setupUi(QWidget *ImageShackUploadWidget)
    {
        if (ImageShackUploadWidget->objectName().isEmpty())
            ImageShackUploadWidget->setObjectName(QStringLiteral("ImageShackUploadWidget"));
        ImageShackUploadWidget->setWindowModality(Qt::ApplicationModal);
        ImageShackUploadWidget->setEnabled(true);
        ImageShackUploadWidget->resize(728, 591);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImageShackUploadWidget->sizePolicy().hasHeightForWidth());
        ImageShackUploadWidget->setSizePolicy(sizePolicy);
        ImageShackUploadWidget->setFocusPolicy(Qt::NoFocus);
        verticalLayout = new QVBoxLayout(ImageShackUploadWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->setContentsMargins(0, -1, 0, 0);
        topLayout = new QHBoxLayout();
        topLayout->setObjectName(QStringLiteral("topLayout"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topLayout->addItem(horizontalSpacer_8);

        imageShackLabel = new QLabel(ImageShackUploadWidget);
        imageShackLabel->setObjectName(QStringLiteral("imageShackLabel"));
        imageShackLabel->setEnabled(true);
        imageShackLabel->setMaximumSize(QSize(16777215, 120));
        imageShackLabel->setLayoutDirection(Qt::LeftToRight);
        imageShackLabel->setPixmap(QPixmap(QString::fromUtf8(":/sprites/imageShack.png")));

        topLayout->addWidget(imageShackLabel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topLayout->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(topLayout);

        groupBox = new QGroupBox(ImageShackUploadWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setTitle(QStringLiteral(""));
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        uploadModeLabel = new QLabel(groupBox);
        uploadModeLabel->setObjectName(QStringLiteral("uploadModeLabel"));
        uploadModeLabel->setLayoutDirection(Qt::LeftToRight);
        uploadModeLabel->setFrameShape(QFrame::NoFrame);
        uploadModeLabel->setFrameShadow(QFrame::Plain);
        uploadModeLabel->setLineWidth(1);
        uploadModeLabel->setMidLineWidth(0);
        uploadModeLabel->setTextFormat(Qt::AutoText);
        uploadModeLabel->setScaledContents(false);
        uploadModeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(uploadModeLabel);

        line_top = new QFrame(groupBox);
        line_top->setObjectName(QStringLiteral("line_top"));
        line_top->setFrameShape(QFrame::HLine);
        line_top->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_top);

        uploadConfigurationLayout = new QHBoxLayout();
        uploadConfigurationLayout->setObjectName(QStringLiteral("uploadConfigurationLayout"));
        gridLayoutLeft = new QGridLayout();
        gridLayoutLeft->setObjectName(QStringLiteral("gridLayoutLeft"));
        thumbnailPreviewLabel = new QLabel(groupBox);
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

        gridLayoutLeft->addWidget(thumbnailPreviewLabel, 0, 1, 1, 1);

        filesUploadedLayout = new QHBoxLayout();
        filesUploadedLayout->setObjectName(QStringLiteral("filesUploadedLayout"));
        countFileLoaded = new QLabel(groupBox);
        countFileLoaded->setObjectName(QStringLiteral("countFileLoaded"));
        countFileLoaded->setAlignment(Qt::AlignCenter);

        filesUploadedLayout->addWidget(countFileLoaded);


        gridLayoutLeft->addLayout(filesUploadedLayout, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutLeft->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutLeft->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutLeft->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutLeft->addItem(horizontalSpacer_9, 1, 0, 1, 1);


        uploadConfigurationLayout->addLayout(gridLayoutLeft);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        uploadConfigurationLayout->addWidget(line);

        gridLayoutRight = new QGridLayout();
        gridLayoutRight->setObjectName(QStringLiteral("gridLayoutRight"));
        resizeLabel = new QLabel(groupBox);
        resizeLabel->setObjectName(QStringLiteral("resizeLabel"));
        resizeLabel->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(resizeLabel->sizePolicy().hasHeightForWidth());
        resizeLabel->setSizePolicy(sizePolicy2);

        gridLayoutRight->addWidget(resizeLabel, 0, 0, 1, 1);

        resizeComboBox = new QComboBox(groupBox);
        resizeComboBox->setObjectName(QStringLiteral("resizeComboBox"));
        resizeComboBox->setEnabled(true);

        gridLayoutRight->addWidget(resizeComboBox, 0, 4, 1, 2);

        privacyLabel = new QLabel(groupBox);
        privacyLabel->setObjectName(QStringLiteral("privacyLabel"));
        privacyLabel->setEnabled(false);

        gridLayoutRight->addWidget(privacyLabel, 1, 0, 1, 1);

        privacyPrivate = new QRadioButton(groupBox);
        privacyPrivate->setObjectName(QStringLiteral("privacyPrivate"));
        privacyPrivate->setEnabled(false);

        gridLayoutRight->addWidget(privacyPrivate, 1, 4, 1, 1);

        privacyPublic = new QRadioButton(groupBox);
        privacyPublic->setObjectName(QStringLiteral("privacyPublic"));
        privacyPublic->setEnabled(false);
        privacyPublic->setChecked(true);

        gridLayoutRight->addWidget(privacyPublic, 1, 5, 1, 1);

        tagsLabel = new QLabel(groupBox);
        tagsLabel->setObjectName(QStringLiteral("tagsLabel"));
        tagsLabel->setEnabled(false);

        gridLayoutRight->addWidget(tagsLabel, 2, 0, 1, 1);

        tagsLineEdit = new QLineEdit(groupBox);
        tagsLineEdit->setObjectName(QStringLiteral("tagsLineEdit"));
        tagsLineEdit->setEnabled(false);
        tagsLineEdit->setMinimumSize(QSize(210, 0));
        tagsLineEdit->setFrame(true);
        tagsLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayoutRight->addWidget(tagsLineEdit, 2, 3, 1, 2);

        separateCommaLabel = new QLabel(groupBox);
        separateCommaLabel->setObjectName(QStringLiteral("separateCommaLabel"));
        separateCommaLabel->setEnabled(false);

        gridLayoutRight->addWidget(separateCommaLabel, 2, 5, 1, 1);


        uploadConfigurationLayout->addLayout(gridLayoutRight);


        verticalLayout_2->addLayout(uploadConfigurationLayout);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        authenticationInstructionsLabel = new QLabel(groupBox);
        authenticationInstructionsLabel->setObjectName(QStringLiteral("authenticationInstructionsLabel"));
        authenticationInstructionsLabel->setEnabled(true);
        authenticationInstructionsLabel->setMinimumSize(QSize(116, 0));
        authenticationInstructionsLabel->setAcceptDrops(false);
        authenticationInstructionsLabel->setLayoutDirection(Qt::LeftToRight);
        authenticationInstructionsLabel->setAutoFillBackground(false);
        authenticationInstructionsLabel->setWordWrap(false);
        authenticationInstructionsLabel->setOpenExternalLinks(true);

        verticalLayout_2->addWidget(authenticationInstructionsLabel);

        line_bottom = new QFrame(groupBox);
        line_bottom->setObjectName(QStringLiteral("line_bottom"));
        line_bottom->setFrameShape(QFrame::HLine);
        line_bottom->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_bottom);

        stackedUploadWidget = new QStackedWidget(groupBox);
        stackedUploadWidget->setObjectName(QStringLiteral("stackedUploadWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(stackedUploadWidget->sizePolicy().hasHeightForWidth());
        stackedUploadWidget->setSizePolicy(sizePolicy3);
        stackedUploadWidget->setAutoFillBackground(false);
        stackedUploadWidget->setFrameShape(QFrame::NoFrame);
        stackedUploadWidget->setFrameShadow(QFrame::Plain);
        stackedUploadWidget->setLineWidth(1);
        stackedUploadWidget->setMidLineWidth(0);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setEnabled(true);
        sizePolicy3.setHeightForWidth(page->sizePolicy().hasHeightForWidth());
        page->setSizePolicy(sizePolicy3);
        page->setMinimumSize(QSize(0, 55));
        horizontalLayoutWidget = new QWidget(page);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 691, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        uploadNowButton = new QToolButton(horizontalLayoutWidget);
        uploadNowButton->setObjectName(QStringLiteral("uploadNowButton"));
        uploadNowButton->setStyleSheet(QStringLiteral("font: 75 8pt \"MS Shell Dlg 2\";"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/sprites/imageShack_frog.png"), QSize(), QIcon::Normal, QIcon::Off);
        uploadNowButton->setIcon(icon);
        uploadNowButton->setIconSize(QSize(30, 30));
        uploadNowButton->setPopupMode(QToolButton::DelayedPopup);
        uploadNowButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_2->addWidget(uploadNowButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        stackedUploadWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        sizePolicy3.setHeightForWidth(page_2->sizePolicy().hasHeightForWidth());
        page_2->setSizePolicy(sizePolicy3);
        page_2->setMinimumSize(QSize(0, 0));
        horizontalLayoutWidget_2 = new QWidget(page_2);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 691, 51));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        progressLabel = new QLabel(horizontalLayoutWidget_2);
        progressLabel->setObjectName(QStringLiteral("progressLabel"));
        progressLabel->setMinimumSize(QSize(16, 16));

        horizontalLayout_5->addWidget(progressLabel);

        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        cancelUploadButton = new QPushButton(horizontalLayoutWidget_2);
        cancelUploadButton->setObjectName(QStringLiteral("cancelUploadButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/sprites/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelUploadButton->setIcon(icon1);

        horizontalLayout_5->addWidget(cancelUploadButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        stackedUploadWidget->addWidget(page_2);

        verticalLayout_2->addWidget(stackedUploadWidget);

        line_3 = new QFrame(groupBox);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        indicatorProgressBarsLayout = new QHBoxLayout();
        indicatorProgressBarsLayout->setObjectName(QStringLiteral("indicatorProgressBarsLayout"));
        uploadProgressLabel = new QLabel(groupBox);
        uploadProgressLabel->setObjectName(QStringLiteral("uploadProgressLabel"));

        indicatorProgressBarsLayout->addWidget(uploadProgressLabel);

        uploadProgressBar = new QProgressBar(groupBox);
        uploadProgressBar->setObjectName(QStringLiteral("uploadProgressBar"));
        uploadProgressBar->setEnabled(true);
        uploadProgressBar->setValue(0);

        indicatorProgressBarsLayout->addWidget(uploadProgressBar);

        line_4 = new QFrame(groupBox);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        indicatorProgressBarsLayout->addWidget(line_4);

        totalUploadProgressLabel_2 = new QLabel(groupBox);
        totalUploadProgressLabel_2->setObjectName(QStringLiteral("totalUploadProgressLabel_2"));

        indicatorProgressBarsLayout->addWidget(totalUploadProgressLabel_2);

        totalUploadProgressBar = new QProgressBar(groupBox);
        totalUploadProgressBar->setObjectName(QStringLiteral("totalUploadProgressBar"));
        totalUploadProgressBar->setValue(0);

        indicatorProgressBarsLayout->addWidget(totalUploadProgressBar);


        verticalLayout_2->addLayout(indicatorProgressBarsLayout);

        line_top->raise();
        line_2->raise();
        authenticationInstructionsLabel->raise();
        line_bottom->raise();
        stackedUploadWidget->raise();
        line_3->raise();
        uploadModeLabel->raise();

        verticalLayout->addWidget(groupBox);


        retranslateUi(ImageShackUploadWidget);

        stackedUploadWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ImageShackUploadWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageShackUploadWidget)
    {
#ifndef QT_NO_TOOLTIP
        ImageShackUploadWidget->setToolTip(QApplication::translate("ImageShackUploadWidget", "Log in to use this features", 0));
#endif // QT_NO_TOOLTIP
        imageShackLabel->setText(QString());
        uploadModeLabel->setText(QApplication::translate("ImageShackUploadWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Upload mode: </span><span style=\" font-size:8pt; color:#ff0000;\">anonymous</span></p></body></html>", 0));
        thumbnailPreviewLabel->setText(QString());
        countFileLoaded->setText(QApplication::translate("ImageShackUploadWidget", "File loaded: %1", 0));
        resizeLabel->setText(QApplication::translate("ImageShackUploadWidget", "<b>Image resize:</b>", 0));
        resizeComboBox->clear();
        resizeComboBox->insertItems(0, QStringList()
         << QApplication::translate("ImageShackUploadWidget", "Do not resize", 0)
         << QApplication::translate("ImageShackUploadWidget", "100x100 (avatar)", 0)
         << QApplication::translate("ImageShackUploadWidget", "150x150 (thumbnail)", 0)
         << QApplication::translate("ImageShackUploadWidget", "320x320 (for websites and email)", 0)
         << QApplication::translate("ImageShackUploadWidget", "640x640 (for message boards)", 0)
         << QApplication::translate("ImageShackUploadWidget", "800x800 (12-inch monitor)", 0)
         << QApplication::translate("ImageShackUploadWidget", "1024x1024 (15-inch monitor)", 0)
         << QApplication::translate("ImageShackUploadWidget", "1280x1280 (19-inch monitor)", 0)
         << QApplication::translate("ImageShackUploadWidget", "1600x1600 (21-inch monitor)", 0)
        );
        privacyLabel->setText(QApplication::translate("ImageShackUploadWidget", "<b>Privacy:</b>", 0));
        privacyPrivate->setText(QApplication::translate("ImageShackUploadWidget", "Private", 0));
        privacyPublic->setText(QApplication::translate("ImageShackUploadWidget", "Public", 0));
        tagsLabel->setText(QApplication::translate("ImageShackUploadWidget", "<b>Tags:</b>", 0));
        separateCommaLabel->setText(QApplication::translate("ImageShackUploadWidget", "Comma separated list", 0));
        authenticationInstructionsLabel->setText(QApplication::translate("ImageShackUploadWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Authentication required to set Privacy and Tags on your thumbnail</span></p>\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://my.imageshack.us/registration\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">Sign in</span></a></p></body></html>", 0));
        uploadNowButton->setText(QApplication::translate("ImageShackUploadWidget", "Upload now", 0));
        progressLabel->setText(QString());
        label->setText(QApplication::translate("ImageShackUploadWidget", "Upload in progress...", 0));
        cancelUploadButton->setText(QApplication::translate("ImageShackUploadWidget", "Cancel", 0));
        uploadProgressLabel->setText(QApplication::translate("ImageShackUploadWidget", "File upload progress:", 0));
        totalUploadProgressLabel_2->setText(QApplication::translate("ImageShackUploadWidget", "Total upload progress:", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageShackUploadWidget: public Ui_ImageShackUploadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESHACKUPLOADWIDGET_H

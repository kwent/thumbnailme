/********************************************************************************
** Form generated from reading UI file 'copyablelineedit.ui'
**
** Created: Wed 2. Jan 17:26:28 2013
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYABLELINEEDIT_H
#define UI_COPYABLELINEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelineedit.h"

QT_BEGIN_NAMESPACE

class Ui_CopyableLineEdit
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QHBoxLayout *horizontalLayout;
    ClickableLineEdit *text;
    QToolButton *copy;

    void setupUi(QWidget *CopyableLineEdit)
    {
        if (CopyableLineEdit->objectName().isEmpty())
            CopyableLineEdit->setObjectName(QStringLiteral("CopyableLineEdit"));
        CopyableLineEdit->resize(443, 56);
        CopyableLineEdit->setMinimumSize(QSize(0, 50));
        CopyableLineEdit->setWindowTitle(QStringLiteral("Form"));
        verticalLayout = new QVBoxLayout(CopyableLineEdit);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        title = new QLabel(CopyableLineEdit);
        title->setObjectName(QStringLiteral("title"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        title->setFont(font);
        title->setText(QStringLiteral("Content:"));

        verticalLayout->addWidget(title);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        text = new ClickableLineEdit(CopyableLineEdit);
        text->setObjectName(QStringLiteral("text"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
        text->setSizePolicy(sizePolicy1);
        text->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        text->setFont(font1);
        text->setReadOnly(true);

        horizontalLayout->addWidget(text);

        copy = new QToolButton(CopyableLineEdit);
        copy->setObjectName(QStringLiteral("copy"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(copy->sizePolicy().hasHeightForWidth());
        copy->setSizePolicy(sizePolicy2);
        copy->setMinimumSize(QSize(25, 25));
        QIcon icon;
        icon.addFile(QStringLiteral(":/sprites/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        copy->setIcon(icon);

        horizontalLayout->addWidget(copy);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CopyableLineEdit);
        QObject::connect(text, SIGNAL(clicked()), CopyableLineEdit, SLOT(select()));
        QObject::connect(copy, SIGNAL(clicked()), CopyableLineEdit, SLOT(copy()));

        QMetaObject::connectSlotsByName(CopyableLineEdit);
    } // setupUi

    void retranslateUi(QWidget *CopyableLineEdit)
    {
#ifndef QT_NO_TOOLTIP
        copy->setToolTip(QApplication::translate("CopyableLineEdit", "Copy to clipboard", 0));
#endif // QT_NO_TOOLTIP
        copy->setText(QString());
        Q_UNUSED(CopyableLineEdit);
    } // retranslateUi

};

namespace Ui {
    class CopyableLineEdit: public Ui_CopyableLineEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYABLELINEEDIT_H

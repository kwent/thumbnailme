/*
Copyright (c) 2009, ImageShack Corp.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* Neither the name of the ImageShack nor the names of its contributors may be
  used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <QClipboard>

#include "copyablelineedit.h"
#include "ui_copyablelineedit.h"

CopyableLineEdit::CopyableLineEdit(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::CopyableLineEdit)
{
    m_ui->setupUi(this);
}

CopyableLineEdit::~CopyableLineEdit()
{
    delete m_ui;
}

void CopyableLineEdit::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CopyableLineEdit::copy()
{
    QApplication::clipboard()->setText(m_ui->text->text());
}

void CopyableLineEdit::select()
{
    m_ui->text->selectAll();
}

void CopyableLineEdit::setTitle(QString value)
{
    m_ui->title->setText(value);
}

void CopyableLineEdit::setText(QString value)
{
    m_ui->text->setText(value);
}

void CopyableLineEdit::setLabelVisible(bool st)
{
    m_ui->title->setVisible(st);
}

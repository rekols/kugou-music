/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "downloaddialog.h"
#include "dwindowclosebutton.h"
#include <QPlainTextEdit>

DownloadDialog::DownloadDialog(MusicData *data, QWidget *parent)
    : DAbstractDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose, true);

    setFixedSize(500, 300);

    DWindowCloseButton *closeButton = new DWindowCloseButton;
    closeButton->setFixedSize(27, 23);
    connect(closeButton, &DWindowCloseButton::clicked, this, &DAbstractDialog::close);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);

    QPlainTextEdit *urlEdit = new QPlainTextEdit;
    urlEdit->setReadOnly(true);
    urlEdit->setPlainText(data->url);
    urlEdit->setStyleSheet("QPlainTextEdit { border: 1px solid #eee; border-radius: 4px; background: #FAFAFA; }");

    QLabel *tips = new QLabel("请自行复制链接下载！");
    tips->setStyleSheet("QLabel { color: #2ca7f8; }");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("名称："), new QLabel(data->songName));
    formLayout->addRow(new QLabel("歌手："), new QLabel(data->signerName));
    formLayout->addRow(new QLabel("时长："), new QLabel(data->timeLength));
    layout->addLayout(formLayout);
    layout->addWidget(urlEdit);
    layout->addSpacing(10);
    layout->addWidget(tips, 0, Qt::AlignHCenter);

    layout->setContentsMargins(20, 10, 10, 20);
}

DownloadDialog::~DownloadDialog()
{
}

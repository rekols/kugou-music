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
#include <QApplication>
#include <QPushButton>
#include <QClipboard>
#include "dtoast.h"

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

    QPushButton *btn1 = new QPushButton("复制下载链接");
    QPushButton *btn2 = new QPushButton("复制下载链接");
    btn1->setObjectName("BlueButton");
    btn2->setObjectName("BlueButton");
    btn1->setFixedWidth(150);
    btn2->setFixedWidth(150);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("名称："), new QLabel(data->songName));
    formLayout->addRow(new QLabel("歌手："), new QLabel(data->signerName));
    formLayout->addRow(new QLabel("时长："), new QLabel(data->timeLength));
    formLayout->addRow(new QLabel("128kbps："), btn1);
    formLayout->addRow(new QLabel("320kbps："), btn2);
    formLayout->setVerticalSpacing(12);
    formLayout->setContentsMargins(30, 0, 30, 10);
    layout->addSpacing(10);
    layout->addLayout(formLayout);
    layout->addStretch();

    connect(btn1, &QPushButton::clicked, this,
            [=] {
                QApplication::clipboard()->setText(data->url);

                DToast *toast = new DToast(this);
                toast->setText("复制成功");
                toast->setFixedHeight(40);
                toast->pop();
                toast->move((width() - toast->width()) / 2, (height() - 60));
            });
}

DownloadDialog::~DownloadDialog()
{
}

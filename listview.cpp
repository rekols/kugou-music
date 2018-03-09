/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
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

#include "listview.h"
#include <QHeaderView>
#include <QStandardItem>
#include <QAction>
#include <QDebug>

ListView::ListView(QWidget *parent)
    : QTableView(parent),
      m_itemModel(new QStandardItemModel)
{
    init();
}

ListView::~ListView()
{
}

void ListView::init()
{
    QStringList titles;
    titles << "" << "音乐标题" << "歌手" << "时长";

    m_itemModel->setHorizontalHeaderLabels(titles);
    setModel(m_itemModel);

    setWordWrap(true);
    setShowGrid(false);
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setContextMenuPolicy(Qt::CustomContextMenu);

    QHeaderView *hHeader = horizontalHeader();
    hHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    hHeader->setSectionResizeMode(1, QHeaderView::Stretch);
    hHeader->setSectionResizeMode(2, QHeaderView::Stretch);
    hHeader->setSectionResizeMode(3, QHeaderView::Fixed);
    hHeader->setHighlightSections(false);

    setColumnWidth(0, 50);
    setColumnWidth(1, 300);
    setColumnWidth(2, 100);
    setColumnWidth(3, 100);

    connect(this, &QTableView::customContextMenuRequested, this,
            [=] (QPoint point) {
                QModelIndex index = indexAt(point);
                QMenu menu(this);

                QAction *downAction = menu.addAction("下载");
                QAction *a = menu.exec(QCursor::pos());

                if (a == downAction) {
                    emit downloadActionPress(index.row());
                }
            });
}

void ListView::appendItem(MusicData *data)
{
    int row = m_itemModel->rowCount();
    m_itemModel->insertRow(row);
    setRowHeight(row, 45);

    QStandardItem *rowItem = new QStandardItem(QString::number(row));
    m_itemModel->setItem(row, 0, rowItem);

    QStandardItem *nameItem = new QStandardItem(data->songName);
    m_itemModel->setItem(row, 1, nameItem);

    QStandardItem *singerItem = new QStandardItem(data->singerName);
    m_itemModel->setItem(row, 2, singerItem);

    QStandardItem *timeItem = new QStandardItem(data->timeLength);
    m_itemModel->setItem(row, 3, timeItem);
}

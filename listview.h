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

#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QMenu>
#include "musicdata.h"

class ListView : public QTableView
{
    Q_OBJECT

public:
    ListView(QWidget *parent = nullptr);
    ~ListView();

    void init();
    void appendItem(MusicData *data);
    QStandardItemModel *getModel() { return m_itemModel; };

signals:
    void downloadActionPress(const int &index);
    void playActionPress(const int &index);

private:
    QStandardItemModel *m_itemModel;
};

#endif

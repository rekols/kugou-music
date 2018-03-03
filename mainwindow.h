#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QModelIndex>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include "titlebar.h"
#include "slidebar.h"
#include "bottomwidget.h"
#include "searchpage.h"
#include "listview.h"
#include "kugouapi.h"
#include "musicdata.h"
#include "downloaddialog.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleReturnPressed(const QString &);
    void handleSearchFinished(MusicData *);
    void handleDoubleClicked(const QModelIndex &);
    void handleDownloadActionClicked(const int &index);

private:
    Titlebar *m_titlebar;
    SlideBar *m_leftSlideBar;
    QMediaPlayer *m_player;
    BottomWidget *m_bottomWidget;
    SearchPage *m_searchPage;
    ListView *m_listView;
    KugouAPI *m_kugouAPI;

    QList<MusicData *> m_musicList;
};

#endif // MAINWINDOW_H

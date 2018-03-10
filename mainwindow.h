#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QModelIndex>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QMediaPlaylist>
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

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void handleReturnPressed(const QString &);
    void handleSearchFinished(MusicData *);
    void handleDoubleClicked(const QModelIndex &);
    void handleDownloadActionClicked(const int &index);
    void handlePlayPressed(const int &index);

private:
    Titlebar *m_titlebar;
    SlideBar *m_leftSlideBar;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_currentList;
    QMediaPlaylist *m_webList;
    BottomWidget *m_bottomWidget;
    SearchPage *m_searchPage;
    ListView *m_listView;
    KugouAPI *m_kugouAPI;

    QList<MusicData *> m_musicList;
};

#endif // MAINWINDOW_H

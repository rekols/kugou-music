#include "mainwindow.h"
#include "dtitlebar.h"
#include <QDebug>
#include <QUrl>
#include <QStandardItemModel>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_titlebar(new Titlebar),
      m_leftSlideBar(new SlideBar),
      m_player(new QMediaPlayer),
      m_currentList(new QMediaPlaylist),
      m_webList(new QMediaPlaylist),
      m_bottomWidget(new BottomWidget(m_player)),
      m_searchPage(new SearchPage),
      m_listView(new ListView),
      m_kugouAPI(new KugouAPI)
{
    if (titlebar()) {
        setShadowOffset(QPoint(0, 0));
        titlebar()->setFixedHeight(45);
        titlebar()->setSeparatorVisible(true);
        titlebar()->setCustomWidget(m_titlebar, Qt::AlignVCenter, false);
    }

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->setMargin(0);
    centralLayout->setSpacing(0);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setSpacing(0);
    topLayout->addWidget(m_leftSlideBar);
    topLayout->addWidget(m_listView);

    m_player->setPlaylist(m_webList);

    centralLayout->addLayout(topLayout);
    centralLayout->addWidget(m_bottomWidget);

    setFocusPolicy(Qt::ClickFocus);
    setCentralWidget(centralWidget);
    setMinimumSize(900, 610);

    connect(m_titlebar, &Titlebar::editReturnPressed, this, &MainWindow::handleReturnPressed);
    connect(m_kugouAPI, &KugouAPI::searchFinished, this, &MainWindow::handleSearchFinished);
    connect(m_listView, &ListView::doubleClicked, this, &MainWindow::handleDoubleClicked);
    connect(m_listView, &ListView::downloadActionPress, this, &MainWindow::handleDownloadActionClicked);

    connect(m_webList, &QMediaPlaylist::currentIndexChanged, this,
            [=] (int index) {
                m_leftSlideBar->updateData(m_musicList.at(index));
            });
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QSettings *settings = new QSettings("kugou-music", "config");
    bool isExit = settings->value("exit", true).toBool();

    qDebug() << isExit;
}

void MainWindow::handleReturnPressed(const QString &text)
{
    if (text.isEmpty())
        return;

    QStandardItemModel *model = m_listView->getModel();
    if (model->rowCount() > 0) {
        model->removeRows(0, model->rowCount());
    }

    if (!m_musicList.isEmpty()) {
        qDeleteAll(m_musicList);
        m_musicList.clear();
    }

    m_webList->clear();
    m_currentList->clear();
    m_kugouAPI->search(text);
}

void MainWindow::handleSearchFinished(MusicData *data)
{
    m_musicList << data;
    m_listView->appendItem(data);

    // m_webList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    m_webList->setPlaybackMode(QMediaPlaylist::Loop);
    m_webList->addMedia(QUrl(data->url));
}

void MainWindow::handleDoubleClicked(const QModelIndex &index)
{
    m_webList->setCurrentIndex(index.row());
    m_leftSlideBar->updateData(m_musicList.at(index.row()));
}

void MainWindow::handleDownloadActionClicked(const int &index)
{
    if (!m_musicList.isEmpty()) {
        MusicData *data = m_musicList.at(index);
        DownloadDialog *dlg = new DownloadDialog(data, this);
        dlg->show();
    }
}

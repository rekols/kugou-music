#include "mainwindow.h"
#include "dtitlebar.h"
#include <QDebug>
#include <QUrl>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_titlebar(new Titlebar),
      m_leftSlideBar(new SlideBar),
      m_player(new QMediaPlayer),
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

    centralLayout->addLayout(topLayout);
    centralLayout->addWidget(m_bottomWidget);

    setFocusPolicy(Qt::ClickFocus);
    setCentralWidget(centralWidget);
    setMinimumSize(900, 600);

    connect(m_titlebar, &Titlebar::editReturnPressed, this, &MainWindow::handleReturnPressed);
    connect(m_kugouAPI, &KugouAPI::searchFinished, this, &MainWindow::handleSearchFinished);
    connect(m_listView, &ListView::doubleClicked, this, &MainWindow::handleDoubleClicked);
    connect(m_listView, &ListView::downloadActionPress, this, &MainWindow::handleDownloadActionClicked);
}

MainWindow::~MainWindow()
{

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

    m_kugouAPI->search(text);
}

void MainWindow::handleSearchFinished(MusicData *data)
{
    m_musicList << data;
    m_listView->appendItem(data);
}

void MainWindow::handleDoubleClicked(const QModelIndex &index)
{
    const int row = index.row();

    const QString url = m_musicList.at(row)->url;
    m_player->setMedia(QUrl(url));
    m_player->play();

    m_bottomWidget->updateData(m_musicList.at(row));
}

void MainWindow::handleDownloadActionClicked(const int &index)
{
    if (!m_musicList.isEmpty()) {
        MusicData *data = m_musicList.at(index);
        DownloadDialog *dlg = new DownloadDialog(data, this);
        dlg->show();
    }    
}

#include "slidebar.h"
#include <QPainter>

SlideBar::SlideBar(QWidget *parent)
    : QFrame(parent),
      m_networkManager(new QNetworkAccessManager(this)),
      m_layout(new QVBoxLayout(this)),
      m_buttonGroup(new QButtonGroup),
      m_coverLabel(new QLabel),
      m_songLabel(new QLabel),
      m_singerLabel(new QLabel)
{
    m_titleList << "新歌榜" << "歌手" << "搜索列表" << "播放列表";
    setObjectName("SlideBar");

    const auto ratio = devicePixelRatioF();
    m_coverPixmap = QPixmap(":/images/info_cover.svg");
    m_coverPixmap.setDevicePixelRatio(ratio);

    setStyleSheet("#SlideBar {"
                  "border: solid #eee;"
                  "border-right-width: 1px;"
                  "background-color: #FAFAFA;"
                  "}"
                  "#NavButton {"
                  "border: none;"
                  "text-align: left;"
                  "font-size: 15px;"
                  "padding-left: 20px;"
                  "border: 1px solid transparent;"
                  "border-left-width: 4px;"
                  "}"
                  "#NavButton:hover {"
                  "background-color: #EDEDEE;"
                  "}"
                  "#NavButton:checked {"
                  "color: #2CA7F8;"
                  "background-color: #D5EDFE;"
                  "border: 1px solid #C5E6FD;"
                  "border-left: 4px solid #2CA7F8;"
                  "}");

    m_layout->setSpacing(0);
    m_layout->setMargin(0);

    setFixedWidth(200);
    initUI();

    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(currentIndexChanged(int)));
}

void SlideBar::updateData(MusicData *data)
{
    m_coverLabel->setPixmap(m_coverPixmap);
    m_songLabel->setText(m_songLabel->fontMetrics().elidedText(data->songName, Qt::ElideRight, 100));
    m_singerLabel->setText(m_singerLabel->fontMetrics().elidedText(data->singerName, Qt::ElideRight, 100));

    QEventLoop loop;
    QUrl url(data->imgUrl);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imgData = reply->readAll();
        if (!imgData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imgData);
            m_coverLabel->setPixmap(pixmap.scaled(50, 50));
        }
    }
}

void SlideBar::initUI()
{
    for (int i = 0; i < m_titleList.count(); ++i) {
        QPushButton *btn = new QPushButton(m_titleList.at(i));
        btn->setCheckable(true);
        btn->setObjectName("NavButton");
        btn->setFixedSize(width(), 43);
        m_layout->addWidget(btn);
        m_buttonGroup->addButton(btn, i);

        if (i == 0) {
            btn->setChecked(true);
        }
    }

    m_layout->addStretch();

    m_coverLabel->setFixedSize(55, 55);
    m_coverLabel->setPixmap(m_coverPixmap);

    m_songLabel->setStyleSheet("QLabel {"
                               "color: #4A4A4A;"
                               "font-size: 13px;"
                               "}");

    m_singerLabel->setStyleSheet("QLabel {"
                                 "color: #4A4A4A;"
                                 "font-size: 13px;"
                                 "}");

    // init bottom widget.

    QWidget *bottomWidget = new QWidget;
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    QVBoxLayout *infoLayout = new QVBoxLayout;

    infoLayout->addStretch();
    infoLayout->addWidget(m_songLabel);
    infoLayout->addWidget(m_singerLabel);
    infoLayout->addStretch();

    bottomLayout->addSpacing(5);
    bottomLayout->addWidget(m_coverLabel);
    bottomLayout->addSpacing(3);
    bottomLayout->addLayout(infoLayout);
    bottomWidget->setFixedHeight(70);

    m_layout->addWidget(bottomWidget);
    m_layout->addSpacing(5);
}

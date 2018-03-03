#include "bottomwidget.h"
#include "dsvgrenderer.h"
#include <QPainter>
#include <QFormLayout>
#include <QTime>

DWIDGET_USE_NAMESPACE

BottomWidget::BottomWidget(QMediaPlayer *p, QWidget *parent)
    : QWidget(parent),
      m_networkManager(new QNetworkAccessManager(this)),
      m_player(p)
{
    const auto ratio = devicePixelRatioF();
    m_coverPixmap = DSvgRenderer::render(":/images/info_cover.svg", QSize(50, 50) * ratio);
    m_coverPixmap.setDevicePixelRatio(ratio);

    setFixedHeight(75);
    initUI();

    connect(m_player, &QMediaPlayer::stateChanged, this, &BottomWidget::handleStateChanged);
    connect(m_playButton, &DImageButton::clicked, this, &BottomWidget::playButtonClicked);
    connect(m_player, &QMediaPlayer::durationChanged, this, &BottomWidget::handleDurationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &BottomWidget::handlePositionChanged);

    connect(m_songSlider, &QSlider::sliderPressed, this,
            [=] {
                m_player->setPosition(m_songSlider->value());
            });
}

void BottomWidget::updateData(MusicData *data)
{
    m_songLabel->setText(data->songName + " - " + data->signerName);
    m_coverWidget->setPixmap(m_coverPixmap);

    // load conver image.
    QEventLoop loop;
    QUrl url(data->imgUrl);
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray imgData = reply->readAll();
    if (!imgData.isEmpty()) {
        QPixmap pixmap;
        pixmap.loadFromData(imgData);
        m_coverWidget->setPixmap(pixmap.scaled(50, 50));
    }
}

void BottomWidget::initUI()
{
    m_previousButton = new DImageButton(":/images/previous-normal.svg",
                                        ":/images/previous-hover.svg",
                                        ":/images/previous-press.svg");
    m_playButton = new DImageButton(":/images/play-normal.svg",
                                    ":/images/play-hover.svg",
                                    ":/images/play-press.svg");
    m_nextButton = new DImageButton(":/images/next-normal.svg",
                                    ":/images/next-hover.svg",
                                    ":/images/next-press.svg");
    m_coverWidget = new QLabel;
    m_songLabel = new QLabel;
    m_timeLabel = new QLabel;
    m_songSlider = new QSlider(Qt::Horizontal);

    m_previousButton->setFixedSize(30, 30);
    m_playButton->setFixedSize(30, 30);
    m_nextButton->setFixedSize(30, 30);

    m_coverWidget->setFixedSize(50, 50);
    m_coverWidget->setPixmap(m_coverPixmap);

    m_songSlider->setFixedHeight(5);
    m_songSlider->setCursor(Qt::PointingHandCursor);
    m_songLabel->setFixedWidth(250);
    m_timeLabel->setFixedWidth(250);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QVBoxLayout *songLayout = new QVBoxLayout;
    songLayout->addWidget(m_songLabel);
    songLayout->addWidget(m_timeLabel);

    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_coverWidget);
    mainLayout->addSpacing(15);
    mainLayout->addLayout(songLayout);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(m_previousButton);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(m_playButton);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(m_nextButton);
    mainLayout->addSpacing(30);
    mainLayout->addStretch();

    layout->addWidget(m_songSlider);
    layout->addLayout(mainLayout);
    layout->addSpacing(10);
}

void BottomWidget::handleStateChanged(QMediaPlayer::State status)
{
    if (status == QMediaPlayer::PlayingState) {
        m_playButton->setNormalPic(":/images/pause-normal.svg");
        m_playButton->setHoverPic(":/images/pause-hover.svg");
        m_playButton->setPressPic(":/images/pause-press.svg");
    } else {
        m_playButton->setNormalPic(":/images/play-normal.svg");
        m_playButton->setHoverPic(":/images/play-hover.svg");
        m_playButton->setPressPic(":/images/play-press.svg");
    }
}

void BottomWidget::handleDurationChanged(qint64 duration)
{
    QTime time(0, 0, 0);
    time = time.addMSecs(duration);

    m_songSlider->setRange(0, duration);
    m_duration = time.toString("mm:ss");
    m_timeLabel->setText(QString("%1 / %2").arg(m_position).arg(m_duration));
}

void BottomWidget::handlePositionChanged(qint64 position)
{
    QTime time(0, 0, 0);
    time = time.addMSecs(position);

    m_songSlider->setValue(position);
    m_position = time.toString("mm:ss");
    m_timeLabel->setText(QString("%1 / %2").arg(m_position).arg(m_duration));
}

void BottomWidget::playButtonClicked()
{
    if (m_player->state() == QMediaPlayer::PlayingState)
        m_player->pause();
    else
        m_player->play();
}

void BottomWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    painter.setPen(QColor("#EAEAEA"));
    painter.drawLine(QPoint(0, 0), QPoint(rect().width(), 0));
    // painter.setPen(QColor("#FBFBFB"));
    // painter.drawLine(QPoint(0, 6), QPoint(rect().width(), 6));
}

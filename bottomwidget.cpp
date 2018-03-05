#include "bottomwidget.h"
#include "dsvgrenderer.h"
#include <QPainter>
#include <QFormLayout>
#include <QTime>

DWIDGET_USE_NAMESPACE

BottomWidget::BottomWidget(QMediaPlayer *p, QWidget *parent)
    : QWidget(parent),
      m_player(p)
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
    m_volumeButton = new DImageButton(":/images/audio-volume-high-normal.svg",
                                      ":/images/audio-volume-high-hover.svg",
                                      ":/images/audio-volume-high-press.svg");
    m_songLabel = new QLabel;
    m_timeLabel = new QLabel;
    m_songSlider = new QSlider(Qt::Horizontal);
    m_volumeSlider = new QSlider(Qt::Horizontal);
    m_totalTimeLabel = new QLabel;
    m_posTimeLabel = new QLabel;

    m_volumeSlider->setFixedWidth(100);

    m_totalTimeLabel->setFixedWidth(40);
    m_posTimeLabel->setFixedWidth(40);

    m_previousButton->setFixedSize(30, 30);
    m_playButton->setFixedSize(30, 30);
    m_nextButton->setFixedSize(30, 30);
    m_volumeButton->setFixedSize(30, 30);

    m_songSlider->setFixedHeight(25);
    m_songSlider->setCursor(Qt::PointingHandCursor);
    m_songLabel->setFixedWidth(200);
    m_timeLabel->setFixedWidth(200);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QVBoxLayout *songLayout = new QVBoxLayout;
    songLayout->addStretch();
    songLayout->addWidget(m_songLabel);
    songLayout->addWidget(m_timeLabel);
    songLayout->addStretch();

    mainLayout->addSpacing(25);
    mainLayout->addWidget(m_previousButton);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_playButton);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_nextButton);
    mainLayout->addSpacing(60);
    mainLayout->addWidget(m_posTimeLabel);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_songSlider);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_totalTimeLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_volumeButton);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_volumeSlider);
    mainLayout->addSpacing(20);
    setFixedHeight(65);

    connect(m_player, &QMediaPlayer::stateChanged, this, &BottomWidget::handleStateChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &BottomWidget::handleMediaStatusChanged);
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
    m_musicData = data;
    m_player->setMedia(QUrl(data->url));
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

void BottomWidget::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::LoadingMedia:
        m_songLabel->setText("加载中...");
        m_songSlider->setValue(0);
        break;

    case QMediaPlayer::EndOfMedia:
        m_player->play();
        m_songSlider->setValue(0);
    break;

    case QMediaPlayer::LoadedMedia: case QMediaPlayer::BufferedMedia:
        QFontMetrics fm(m_songLabel->font());
        const QString text = m_musicData->songName + " - " + m_musicData->singerName;
        m_songLabel->setText(fm.elidedText(text, Qt::ElideRight, 195));
        m_player->play();
        // m_timeLabel->show();
        break;
    }
}

void BottomWidget::handleDurationChanged(qint64 duration)
{
    QTime time(0, 0, 0);
    time = time.addMSecs(duration);

    m_songSlider->setRange(0, duration);
    m_totalTimeLabel->setText(time.toString("mm:ss"));
}

void BottomWidget::handlePositionChanged(qint64 position)
{
    QTime time(0, 0, 0);
    time = time.addMSecs(position);

    m_songSlider->setValue(position);
    m_posTimeLabel->setText(time.toString("mm:ss"));
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

#include "bottomwidget.h"
#include <QPainter>
#include <QFormLayout>
#include <QTime>

BottomWidget::BottomWidget(QMediaPlayer *p, QWidget *parent)
    : QWidget(parent),
      m_player(p)
{
    setFixedHeight(70);
    initUI();

    connect(m_player, &QMediaPlayer::stateChanged, this,
            [=] (QMediaPlayer::State status) {
                if (status == QMediaPlayer::PlayingState) {
                    m_playButton->setNormalPic(":/images/pause-normal.svg");
                    m_playButton->setHoverPic(":/images/pause-hover.svg");
                    m_playButton->setPressPic(":/images/pause-press.svg");
                } else {
                    m_playButton->setNormalPic(":/images/play-normal.svg");
                    m_playButton->setHoverPic(":/images/play-hover.svg");
                    m_playButton->setPressPic(":/images/play-press.svg");
                }
            });

    connect(m_playButton, &DImageButton::clicked, this,
            [=] {
                if (m_player->state() == QMediaPlayer::PlayingState)
                    m_player->pause();
                else
                    m_player->play();
            });

    connect(m_songSlider, &QSlider::sliderPressed, this,
            [=] {
                m_player->setPosition(m_songSlider->value());
            });

    connect(m_player, &QMediaPlayer::durationChanged, this,
            [=](qint64 duration) {
                QTime time(0, 0, 0);
                time = time.addMSecs(duration);

                m_songSlider->setRange(0, duration);
                m_duration = time.toString("mm:ss");
                m_timeLabel->setText(QString("%1 / %2").arg(m_position).arg(m_duration));
            });

    connect(m_player, &QMediaPlayer::positionChanged, this,
            [=](qint64 position) {
                QTime time(0, 0, 0);
                time = time.addMSecs(position);

                m_songSlider->setValue(position);
                m_position = time.toString("mm:ss");
                m_timeLabel->setText(QString("%1 / %2").arg(m_position).arg(m_duration));    
            });
}

void BottomWidget::updateData(MusicData *data)
{
    m_songLabel->setText(data->songName + " - " + data->signerName);
}

void BottomWidget::initUI()
{
    m_previousButton = new DImageButton(":/images/previous-normal.svg",
                                        ":/images/previous-hover.svg",
                                        ":/images/previous-press.svg");
    m_playButton = new DImageButton(":/images/play-normal.svg",
                                    ":/images/play-hover.svg",
                                    ":/images/play-press.svg");
    m_pauseButton = new DImageButton(":/images/pause-normal.svg",
                                     ":/images/pause-hover.svg",
                                     ":/images/pause-press.svg");
    m_nextButton = new DImageButton(":/images/next-normal.svg",
                                    ":/images/next-hover.svg",
                                    ":/images/next-press.svg");
    m_coverWidget = new QSvgWidget;
    m_songLabel = new QLabel;
    m_timeLabel = new QLabel;
    m_songSlider = new QSlider(Qt::Horizontal);

    m_previousButton->setFixedSize(30, 30);
    m_playButton->setFixedSize(30, 30);
    m_pauseButton->setFixedSize(30, 30);
    m_nextButton->setFixedSize(30, 30);
    m_pauseButton->hide();

    m_coverWidget->setFixedSize(50, 50);
    m_coverWidget->load(QString(":/images/info_cover.svg"));

    m_songSlider->setFixedHeight(5);
    m_songLabel->setAlignment(Qt::AlignLeft);
    m_timeLabel->setAlignment(Qt::AlignRight);
    m_songSlider->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addSpacing(25);
    mainLayout->addWidget(m_previousButton);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_playButton);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_pauseButton);
    mainLayout->addWidget(m_nextButton);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(m_coverWidget);
    mainLayout->addSpacing(20);

    QFormLayout *songLayout = new QFormLayout;
    songLayout->addRow(m_songLabel, m_timeLabel);
    songLayout->addRow(m_songSlider);
    songLayout->setVerticalSpacing(10);
    songLayout->setContentsMargins(0, 15, 0, 15);

    mainLayout->addLayout(songLayout);
    mainLayout->addSpacing(20);
}

void BottomWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    painter.setPen(QColor("#EAEAEA"));
    painter.drawLine(QPoint(0, 0), QPoint(rect().width(), 0));
}

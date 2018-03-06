#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QSlider>
#include <QMediaPlayer>
#include "dimagebutton.h"
#include "musicdata.h"

DWIDGET_USE_NAMESPACE

class BottomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BottomWidget(QMediaPlayer *p, QWidget *parent = nullptr);

    void updateData(MusicData *);

private:
    void handleStateChanged(QMediaPlayer::State status);
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handleDurationChanged(qint64 duration);
    void handlePositionChanged(qint64 position);
    void playButtonClicked();

protected:
    void paintEvent(QPaintEvent *);

private:
    DImageButton *m_previousButton;
    DImageButton *m_playButton;
    DImageButton *m_nextButton;
    DImageButton *m_volumeButton;
    DImageButton *m_repeatButton;
    QLabel *m_songLabel;
    QLabel *m_timeLabel;
    QLabel *m_totalTimeLabel;
    QLabel *m_posTimeLabel;
    QSlider *m_songSlider;
    QSlider *m_volumeSlider;
    QMediaPlayer *m_player;
    MusicData *m_musicData;

    QPixmap m_coverPixmap;
};

#endif // BOTTOMWIDGET_H

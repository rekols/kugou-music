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
    void initUI();

protected:
    void paintEvent(QPaintEvent *);

private:
    DImageButton *m_previousButton;
    DImageButton *m_playButton;
    DImageButton *m_pauseButton;
    DImageButton *m_nextButton;
    QSvgWidget *m_coverWidget;
    QLabel *m_songLabel;
    QLabel *m_timeLabel;
    QString m_duration;
    QString m_position;
    QSlider *m_songSlider;
    QMediaPlayer *m_player;
};

#endif // BOTTOMWIDGET_H

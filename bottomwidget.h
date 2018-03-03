#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QSlider>
#include <QMediaPlayer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
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
    void handleStateChanged(QMediaPlayer::State status);
    void handleDurationChanged(qint64 duration);
    void handlePositionChanged(qint64 position);
    void playButtonClicked();

protected:
    void paintEvent(QPaintEvent *);

private:
    QNetworkAccessManager *m_networkManager;
    DImageButton *m_previousButton;
    DImageButton *m_playButton;
    DImageButton *m_nextButton;
    QLabel *m_coverWidget;
    QLabel *m_songLabel;
    QLabel *m_timeLabel;
    QString m_duration;
    QString m_position;
    QSlider *m_songSlider;
    QMediaPlayer *m_player;

    QPixmap m_coverPixmap;
};

#endif // BOTTOMWIDGET_H

#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include <QFrame>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include "musicdata.h"

class SlideBar : public QFrame
{
    Q_OBJECT

public:
    explicit SlideBar(QWidget *parent = nullptr);

    void updateData(MusicData *);

signals:
    void currentIndexChanged(int);

private:
    void initUI();

private:
    QNetworkAccessManager *m_networkManager;
    QVBoxLayout *m_layout;
    QButtonGroup *m_buttonGroup;
    QStringList m_titleList;

    QPixmap m_coverPixmap;
    QLabel *m_coverLabel;
    QLabel *m_songLabel;
    QLabel *m_singerLabel;
};

#endif // SLIDEBAR_H

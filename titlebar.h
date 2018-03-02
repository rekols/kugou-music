#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include "dsearchedit.h"

DWIDGET_USE_NAMESPACE

class Titlebar : public QWidget
{
    Q_OBJECT

public:
    explicit Titlebar(QWidget *parent = nullptr);

signals:
    void editReturnPressed(const QString &text);

private:
    DSearchEdit *m_searchEdit;
};

#endif // TITLEBAR_H

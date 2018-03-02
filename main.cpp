#include "mainwindow.h"
#include <DApplication>
#include <QDesktopWidget>
#include <QFile>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    MainWindow w;
    w.show();
    w.setWindowIcon(QIcon(":/images/icon.svg"));
    w.move((QApplication::desktop()->width() - w.width()) / 2,
           (QApplication::desktop()->height() - w.height()) / 2);

    QFile file(":/qss/style.qss");
    if (file.open(QIODevice::ReadOnly)) {
        const QString qss = file.readAll();
        w.setStyleSheet(qss);
    }

    return a.exec();
}

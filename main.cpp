#include "mainwindow.h"
#include <DApplication>
#include <QDesktopWidget>
#include <QFile>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);
    app.loadTranslator();
    app.setOrganizationName("deepin");
    app.setApplicationVersion(DApplication::buildVersion("1.0"));
    app.setApplicationAcknowledgementPage("https://github.com/rekols");
    app.setProductIcon(QIcon(":/images/icon.svg"));
    app.setProductName(DApplication::translate("Main", "酷狗音乐"));
    app.setApplicationDescription(DApplication::translate("Main", "本项目代码不用于商用，仅限研究和学习使用"));

    if (app.setSingleInstance("kugou-music")) {
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

        return app.exec();
    }

    return 0;
}

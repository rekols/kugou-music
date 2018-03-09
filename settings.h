#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings *instance();

    Settings(QObject *parent=0);
    ~Settings();

    QVariant getOption(const QString &key);
    void setOption(const QString &key, QVariant &value);

private:
    QSettings m_settings;
};

#endif

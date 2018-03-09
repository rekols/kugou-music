#include "settings.h"

static Settings *INSTANCE = nullptr;

Settings* Settings::instance()
{
    if (!INSTANCE) {
        INSTANCE = new Settings;
    }

    return INSTANCE;
}

Settings::Settings(QObject *parent)
    : QObject(parent),
      m_settings("deepin", "kugou-music")
{

}

Settings::~Settings()
{
}

QVariant Settings::getOption(const QString &key)
{
    return m_settings.value(key);
}

void Settings::setOption(const QString &key, QVariant &value)
{
    m_settings.setValue(key, value);
}

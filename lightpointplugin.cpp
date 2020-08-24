#include "LightPoint.h"
#include "lightpointplugin.h"

#include <QtPlugin>

LightPointPlugin::LightPointPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LightPointPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LightPointPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LightPointPlugin::createWidget(QWidget *parent)
{
    return new LightPoint(parent);
}

QString LightPointPlugin::name() const
{
    return QLatin1String("LightPoint");
}

QString LightPointPlugin::group() const
{
    return QLatin1String("");
}

QIcon LightPointPlugin::icon() const
{
    return QIcon();
}

QString LightPointPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LightPointPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LightPointPlugin::isContainer() const
{
    return false;
}

QString LightPointPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LightPoint\" name=\"lightPoint\">\n</widget>\n");
}

QString LightPointPlugin::includeFile() const
{
    return QLatin1String("LightPoint.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(LightPoint, LightPointPlugin)
#endif // QT_VERSION < 0x050000

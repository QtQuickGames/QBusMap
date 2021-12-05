#include "coloredmapwidget.h"

#include "ArcGISRuntimeEnvironment.h"
#include "coloredmap.h"

using namespace Esri::ArcGISRuntime;

ColoredMapWidget::ColoredMapWidget(const QUrl& source, QWidget* parent)
    : QQuickWidget(source, parent)
{
    m_map = this->rootObject()->findChild<ColoredMap*>(QStringLiteral("coloredMap"));
    if (!m_map) {
        qWarning() << "Map object not found!";
    }
    connect(m_map, &ColoredMap::takeSnapshot, this, &ColoredMapWidget::takeSnapshot);
}

void ColoredMapWidget::init()
{
    ColoredMap::init();
}

void ColoredMapWidget::setApiKey(const QString& apiKey)
{
    if (apiKey.isEmpty()) {
        qWarning() << "Use of Esri location services, including basemaps, requires"
                      "you to authenticate with an ArcGIS identity or set the API Key property.";
    } else {
        ArcGISRuntimeEnvironment::setApiKey(apiKey);
    }
}

void ColoredMapWidget::setPathToTpkMapFile(const QString& pathToTpkMapFile)
{
    if (!m_map) {
        qWarning() << "Map object not found!";
        return;
    }

    m_map->setPathToTpkMapFile(pathToTpkMapFile);
}

void ColoredMapWidget::setPathToShapeFile(const QString&  name,const QString& pathToShapeFile)
{
    if (!m_map) {
        qWarning() << "Map object not found!";
        return;
    }

    m_map->setPathToShapeFile(name, pathToShapeFile);
}

void ColoredMapWidget::setFieldNames(const QStringList& fieldNames)
{
    if (!m_map) {
        qWarning() << "Map object not found!";
        return;
    }

    m_map->setFieldNames(fieldNames);
}

void ColoredMapWidget::setBusStopFieldNames(const QStringList &fieldNames)
{
    if (!m_map) {
        qWarning() << "Map object not found!";
        return;
    }

    m_map->setBusStopFieldNames(fieldNames);
}

void ColoredMapWidget::setRegionsData(const QStringList& regionsData)
{
    if (!m_map) {
        qWarning() << "Map object not found!";
        return;
    }

    m_map->setRegionsData(regionsData);
}
